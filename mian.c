#include <stdio.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "car_motion.h"

static const char *TAG = "MAIN";

void app_main(void)
{
    printf("hello yahboom\n");
    ESP_LOGI(TAG, "Nice to meet you!");
    int count = 0;
    vTaskDelay(pdMS_TO_TICKS(1000));

    float target_Wz = 0.0f;  // 期望角速度：0 表示希望它走直线
    float Kp = 0.5f;         // 比例系数（需要根据实车调试）
    float base_speed = 0.5f; // 基础直行速度

    Motor_Init();
    for (int cycle = 0; cycle < 4; cycle++)
    {
        Motion_Ctrl(0.5, 0, 0);
        car_motion_t micro_car;

        while (1)
        {
            Motion_Get_Speed(&micro_car);
            ESP_LOGI(TAG, "Read Motion:%.2f, %.2f, %.2f", micro_car.Vx, micro_car.Vy, micro_car.Wz);

            target_Wz = 0;
            // 2. 计算误差 (期望值 - 实际值)
            float error = target_Wz - micro_car.Wz;

            // 3. 计算补偿角速度 (P控制)
            float correction_Wz = target_Wz + Kp * error;

            // 4. 将补偿量叠加到基础指令上，重新下发电机指令
            Motion_Ctrl(base_speed, 0, correction_Wz);
            vTaskDelay(pdMS_TO_TICKS(100));
            count++;
            if (count >= 20)
            {
                Motion_Stop(STOP_COAST);
                break;
            }
        }

        count = 0;
        Motion_Ctrl(0.5, 0, 1.25);

        while (1)
        {
            Motion_Get_Speed(&micro_car);
            ESP_LOGI(TAG, "Read Motion:%.2f, %.2f, %.2f", micro_car.Vx, micro_car.Vy, micro_car.Wz);

            target_Wz = 1.25;
            // 2. 计算误差 (期望值 - 实际值)
            float error = target_Wz - micro_car.Wz;

            // 3. 计算补偿角速度 (P控制)
            float correction_Wz = target_Wz + Kp * error;

            // 4. 将补偿量叠加到基础指令上，重新下发电机指令
            Motion_Ctrl(base_speed, 0, correction_Wz);

            vTaskDelay(pdMS_TO_TICKS(100));
            count++;
            if (count >= 26) // 实测25偏大，19偏小
            {
                Motion_Stop(STOP_COAST);
                break;
            }
        }
        count = 0;
    }
}
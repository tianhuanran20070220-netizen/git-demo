# git-demo

这是一个在 VS Code 中创建的本地 Git 仓库示例。

## 环境

- Git: 2.55.0.windows.5（DSH Desktop 自带 managed-git）
- 编辑器: VS Code（`F:\software\Microsoft VS Code`）

## 目录结构

```
git-demo/
├── README.md          # 本文件
├── .gitignore         # 忽略规则
├── src/
│   └── hello.py       # 示例脚本
└── docs/
    └── notes.md       # 示例文档
```

## 使用方法

```bash
git status          # 查看改动
git add .           # 暂存
git commit -m "..."  # 提交
```

在 VS Code 中按 `Ctrl+Shift+G` 打开源代码管理面板，可以图形化完成同样的操作。

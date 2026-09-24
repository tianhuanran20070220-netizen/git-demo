# 笔记

## 为什么本地仓库没有"链接"

Git 仓库分两种：

- **本地仓库**：只是你磁盘上的一个 `.git` 目录，没有 URL，只有文件系统路径。
- **远程仓库**：托管在 GitHub / Gitee / GitLab 等平台上，才有 `https://...` 形式的链接。

推送步骤大致是：

```bash
git remote add origin <远程仓库地址>
git branch -M main           # 如果默认分支是 master
git push -u origin main
```

推送成功后才会得到可分享的仓库链接。

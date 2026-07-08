# Mirror 导入（保留完整历史）

内网 GitLab 不能直接连 GitHub 时，在 能上网的机器 做中转。

### 1. 在有网络的机器上镜像克隆

git clone --mirror https://github.com/owner/repo.git

cd repo.git

`--mirror` 会拉取：

- 所有 commit 历史
- 所有分支
- 所有 tag
- 完整 reflog 等引用

### 2. 打包带到内网（若物理隔离）

tar czf repo.git.tar.gz repo.git

*# U 盘等方式拷贝到内网*

### 3. 在内网 GitLab 创建空项目

网页新建项目，不要勾选 “Initialize with README”。

### 4. 推送到内网 GitLab

- #### **全量推送**

  *# 若已解压*

  cd repo.git

  *# HTTP*

  git push --mirror http://192.168.1.100/group/project.git

  *# 或 SSH*

  git push --mirror git@192.168.1.100:group/project.git

  `--mirror` 会把所有分支（会冲掉内网新建的分支、新提的commit）、tag 一次性推上去。

- #### **推送指定分支**

```bash
# 1. 从外网克隆镜像（拿到完整引用）
git clone --mirror https://外网仓库.git external-mirror.git
cd external-mirror.git
# 2. 添加内网远程
git remote add internal https://内网仓库.git
# 3. 只推送需要同步的分支（不要用 --mirror）
git push internal main
git push internal BranchA
# 4. 如需同步标签（可选，不会删内网独有标签）
git push internal --tags
```



### 若用了 Git LFS

普通 mirror 不会自动带 LFS 大文件，需额外处理：

git clone --mirror https://github.com/owner/repo.git

cd repo.git

git lfs fetch --all

*# 再 push --mirror 到内网*

内网 GitLab 需开启 LFS：`gitlab.rb` 中 `gitlab_rails['lfs_enabled'] = true` 并 `reconfigure`。





# Mirror增量同步（内网物理隔离）

1. 在有网机器：`git remote update`（或 `git fetch origin`）
2. 打包 `repo.git` 带到内网（或只传增量，见下）
3. 内网：`git push --mirror` 到 GitLab

## 注意事项

### 1. 内网仓库是否有自己的 commit？

内网从未 push 过新 commit（纯镜像）
→ 直接 `fetch` + `push --mirror` 即可。

内网已有开发 commit（与 GitHub 分叉）
→ `--mirror` 会 强制覆盖 内网所有分支/tag，可能丢内网改动。
此时应：

- 只同步特定分支，例如：

  git fetch origin main

  git push internal refs/heads/main:refs/heads/main

- 或在内网用 merge/rebase 合并外网更新，而不是 `--mirror`。

### 2. 删除的分支 / 被 force-push 的历史

`git push --mirror` 会 同步删除：GitHub 上已删的分支，内网也会被删；若外网有 force-push，内网会被覆盖。
只读镜像场景下这通常是预期行为。

### 3. Git LFS

若仓库用 LFS，同步时还要：

git lfs fetch origin --all

git lfs push internal --all

### 4. 自动化
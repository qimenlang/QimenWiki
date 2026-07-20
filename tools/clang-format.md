## 1. 编辑器保存时格式化

在 Cursor / VS Code 里装扩展 Clang-Format（或用自带的 C/C++ 格式化），并加工作区设置。

新建或编辑 `.vscode/settings.json`：

```json
{
    "clang-format.assumeFilename": "file",
    "clang-format.executable.windows": "C:\\Program Files\\LLVM\\bin\\clang-format.exe",
    "editor.formatOnSave": false,
    "[cpp]": {
        "editor.defaultFormatter": "xaver.clang-format",
        "editor.formatOnSave": false
    },
    "[c]": {
        "editor.defaultFormatter": "xaver.clang-format",
        "editor.formatOnSave": false
    }
}
```

`style: file` 会自动用仓库根目录的 `.clang-format`。

------

## 2. 配置precommit

需要分别做三件事：

1. `pip install pre-commit`
   安装 pre-commit 这个工具本身（Python 包）。装完才能用 `pre-commit` / `python -m pre_commit`。
2. `python -m pre_commit install`
   在当前仓库写入 Git 的 pre-commit hook（装到 `.git/hooks/pre-commit`）。
   之后每次执行 `git commit`，会自动按 `.pre-commit-config.yaml` 跑检查；其中 clang-format 会格式化本次要提交的 C/C++ 文件。
   只需每个克隆仓库做一次（或换机器后再做一次）。
3. `python -m pre_commit run clang-format --all-files --show-diff-on-failure`
   立刻手动跑一遍 clang-format，不依赖 commit：
   - `--all-files`：检查仓库里所有匹配文件（不只是本次 staged）
   - `--show-diff-on-failure`：若改了文件，把 diff 打出来
     用来全量对齐格式、或验证 CI 会不会过。需要时再跑，不是每次提交都必须。
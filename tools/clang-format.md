## 1. 主动跑一次：只格式化本工程代码

只动 `engine/`，不要碰 `thirdparty/`。

PowerShell（在仓库根目录）：

```powershell
*# 先看会改哪些文件（不写入）*
Get-ChildItem .\engine -Recurse -Include *.cpp,*.h,*.hpp | ForEach-Object { clang-format -n --Werror $_.FullName }
*# 确认无误后再原地格式化*
Get-ChildItem .\engine -Recurse -Include *.cpp,*.h,*.hpp | ForEach-Object { clang-format -i $_.FullName }
```

说明：

- `-n` / `--dry-run`：只检查，不改文件
- `--Werror`：有格式差异时非 0 退出（适合 CI）
- `-i`：原地修改

当前 `engine/` 大约只有 7 个源文件，一次就能刷完。

------

## 2. 改完代码后自动处理（推荐：编辑器保存时格式化）

在 Cursor / VS Code 里装扩展 Clang-Format（或用自带的 C/C++ 格式化），并加工作区设置。

新建或编辑 `.vscode/settings.json`：

```json
{

  "editor.formatOnSave": true,

  "[cpp]": {

​    "editor.defaultFormatter": "xaver.clang-format",

​    "editor.formatOnSave": true

  },

  "[c]": {

​    "editor.defaultFormatter": "xaver.clang-format",

​    "editor.formatOnSave": true

  },

  "clang-format.language.cpp.enable": true,

  "clang-format.executable": "clang-format",

  "files.associations": {

​    "*.h": "cpp",

​    "*.hpp": "cpp"

  }

}
```

若用 Microsoft C/C++ 扩展，可改成：

```json
{

  "C_Cpp.clang_format_style": "file",

  "C_Cpp.clang_format_path": "clang-format",

  "editor.formatOnSave": true,

  "[cpp]": {

​    "editor.defaultFormatter": "ms-vscode.cpptools"

  }

}
```

`style: file` 会自动用仓库根目录的 `.clang-format`。
保存 `engine/` 下的 `.cpp/.h` 时就会按该规范排版；`thirdparty/` 里一般有自己的 `.clang-format`，不会被根配置误伤（clang-format 按最近的配置文件生效）。

------

## 3. 「检查」而不是「改写」：提交 / CI

若你要的是检查未格式化就失败（而不是自动改）：

```powershell
*# 本地检查*
Get-ChildItem .\engine -Recurse -Include *.cpp,*.h,*.hpp |  ForEach-Object { clang-format -n --Werror $_.FullName }
```

CI 里可在 `build&test.yml` 加一步（示例）：

```yaml
\- name: Check clang-format

  shell: pwsh

  run: |

​    $files = Get-ChildItem .\engine -Recurse -Include *.cpp,*.h,*.hpp

​    $failed = $false

​    foreach ($f in $files) {

​      clang-format -n --Werror $f.FullName

​      if ($LASTEXITCODE -ne 0) { $failed = $true }

​    }

​    if ($failed) { exit 1 }
```

Git 钩子可用 [pre-commit](https://pre-commit.com/) 的 `clang-format` hook，只对暂存文件检查/格式化；需要的话可以再帮你加。

------

## 建议组合

| 场景               | 做法                               |
| :----------------- | :--------------------------------- |
| 现在刷一遍存量代码 | `clang-format -i` 作用于 `engine/` |
| 日常改代码         | `formatOnSave`                     |
| 防漏网             | CI 或 pre-commit 用 `-n --Werror`  |

需要的话我可以直接帮你：
1）对 `engine/` 跑一次 `-i`；
2）写好 `.vscode/settings.json`；
3）在 CI 里加上 format 检查步骤。要做哪几项直接说即可。
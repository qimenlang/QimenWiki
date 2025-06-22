以下是使用 **lnav** 查看、搜索、过滤和高亮日志文件的分步指南：

---

### **1. 安装 lnav**
#### **Ubuntu/Debian**
```bash
sudo apt update && sudo apt install lnav
```

#### **macOS**
```bash
brew install lnav
```

#### **Windows**
- 通过 [WSL](https://learn.microsoft.com/en-us/windows/wsl/install) 安装 Ubuntu，再使用 `apt` 安装。
- 或从 [lnav 官网](https://lnav.org/)下载 Windows 预编译版本。

---

### **2. 基本操作**
#### **打开日志文件**
```bash
lnav /path/to/logfile.log          # 打开单个文件
lnav /var/log/*.log                # 打开多个日志文件
```

#### **界面导航**
- **上下滚动**：`↑`/`↓` 或 `j`/`k`
- **翻页**：`Page Up`/`Page Down` 或 `Ctrl+U`/`Ctrl+D`
- **切换视图**：按 `i` 进入 **时间轴视图**，按 `q` 返回原始视图。

---

### **3. 查找关键字**
#### **快速搜索**
1. 按 `/` 进入搜索模式。
2. 输入关键字（支持正则表达式），如 `ERROR`。
3. 按 `Enter` 跳转到第一个匹配项，按 `n`/`N` 跳转到下一个/上一个匹配项。

#### **示例**
```bash
/error.*failed  # 搜索包含 "error" 后接 "failed" 的行
```

---

### **4. 过滤日志**
#### **显示包含关键字的行**
```bash
:filter-in "ERROR"        # 仅显示包含 "ERROR" 的行
:filter-in "404|500"      # 显示包含 404 或 500 的行（正则）
```

#### **排除特定关键字的行**
```bash
:filter-out "DEBUG"       # 隐藏包含 "DEBUG" 的行
```

#### **重置过滤**
```bash
:reset-session            # 清除所有过滤条件
```

---

### **5. 高亮关键字**
#### **单关键词高亮**
```bash
:highlight "WARNING" yellow  # 将 "WARNING" 高亮为黄色
```

#### **多关键词高亮**
```bash
:highlight "ERROR" red
:highlight "INFO" green
```

#### **使用正则表达式高亮**
```bash
:highlight "\\b\d{3}\\b" cyan  # 高亮所有三位数（如 HTTP 状态码）
```

#### **清除高亮**
```bash
:clear-highlight             # 清除所有高亮规则
```

---

### **6. 高级功能**
#### **时间轴导航**
1. 按 `i` 进入时间轴视图。
2. 使用 `←`/`→` 选择时间点，按 `Enter` 查看该时间段的日志。

#### **自动解析日志格式**
- lnav 支持常见日志格式（如 Apache、syslog、JSON）。
- 自动提取时间戳、日志级别等字段，按 `p` 查看解析后的字段。

#### **查看统计信息**
- 按 `m` 进入直方图模式，按日志时间或级别分布查看统计。

---

### **7. 保存配置**
#### **自定义高亮和过滤规则**
编辑 `~/.lnav/config.json`，添加永久规则：
```json
{
  "ui": {
    "highlights": [
      { "pattern": "ERROR", "color": "red" },
      { "pattern": "WARNING", "color": "yellow" }
    ]
  }
}
```

---

### **8. 示例操作流程**
1. **打开日志并高亮关键错误**：
   ```bash
   lnav /var/log/nginx/error.log
   :highlight "error" red
   ```
2. **过滤 500 错误并查看时间分布**：
   ```bash
   :filter-in "500"
   :toggle-filtering  # 临时关闭过滤
   i                  # 进入时间轴视图
   ```
3. **保存常用高亮规则**：
   - 编辑 `~/.lnav/config.json` 添加规则，重启 lnav 生效。

---

### **总结**
| **操作**   | **命令/快捷键**              | **说明**                        |
| ---------- | ---------------------------- | ------------------------------- |
| 打开文件   | `lnav /path/to/log`          | 支持通配符 (`*.log`)            |
| 搜索关键字 | `/` + 输入关键字 + `Enter`   | 支持正则表达式                  |
| 过滤日志   | `:filter-in "PATTERN"`       | 仅显示匹配行                    |
| 排除日志   | `:filter-out "PATTERN"`      | 隐藏匹配行                      |
| 高亮关键字 | `:highlight "PATTERN" COLOR` | 颜色可选：red, green, yellow 等 |
| 时间轴视图 | `i`                          | 按时间导航日志                  |
| 重置会话   | `:reset-session`             | 清除过滤和高亮                  |

通过上述步骤，您可以高效地使用 **lnav** 分析日志文件，快速定位关键信息。
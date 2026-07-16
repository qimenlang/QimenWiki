## CIGI 是什么

CIGI（Common Image Generator Interface） 是 Host（仿真主机）与 IG（视景/图像生成器）之间的线上二进制消息协议。现行正式版是 CIGI 4.0 / SISO-STD-013-2014。

它规定：消息怎么组、会话怎么建、各数据包字段是什么、Host↔IG 怎么按帧收发。
它不规定 IG 画质、场景库格式，也不规定多投影之间的硬件 Framelock。

------

## 协议具体内容（按 ICD 结构）

### 1. 会话与传输骨架

- Session：一对 Host–IG 端口上的全部 CIGI 通信与状态；可多会话并存（如 OTW 一路、传感器一路）。
- 消息结构：固定包头（Packet ID、Size 等）+ 载荷；字节序有明确约定。
- 每帧必带头包：
  - Host→IG：先发 IG Control
  - IG→Host：先发 Start of Frame（SOF）
- 帧号在 IG Control ↔ SOF 间回传（Host Frame / IG Frame），用来对齐双方“这一帧”。

### 2. 帧拍与同步模式（Host–IG，不是通道间）

| 模式 | 行为                                                         | 适用               |
| :--- | :----------------------------------------------------------- | :----------------- |
| 同步 | IG 发 SOF（常由显示 VSync 驱动）→ Host 立刻回 IG Control + 状态 | 高保真、减抖动     |
| 异步 | Host 任意时刻发包；IG 帧内取到才用                           | 低保真；易多帧延迟 |

ICD 明确：同步模式下 SOF 扮演 Host–IG 的 heartbeat，可降低错帧抖动；并可用 Timestamp / Velocity / Acceleration 做外推。

### 3. Host→IG 主要数据包（“画什么”）

按类别（CIGI 4.0 Table 1）：

- 控制：IG Control（模式、帧号、时间戳等）
- 实体：Entity Control / Position、速度加速度、铰接部件、动画、组件
- 视点：View Definition / View Control（位姿、FOV 等）— 多通道常靠多 View
- 环境：大气、区域天气、海面/波浪、地表、天体
- 传感器：Sensor Control、Motion Tracker
- 查询：HAT/HOT、LOS、位置/环境条件请求
- 碰撞定义：段/体碰撞检测定义
- 符号：表面/文字/圆/多边形等 HUD 类叠加

### 4. IG→Host 主要数据包（“回报什么”）

- SOF（每帧必须）
- HAT/HOT、LOS、传感器、位置/天气等 Response
- 碰撞通知、动画结束、事件、IG Message 等
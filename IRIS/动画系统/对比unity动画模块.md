| unity动画功能列表        |                                      | irisengine对应支持情况 |                                                  |
| ------------------------ | ------------------------------------ | ---------------------- | ------------------------------------------------ |
| 动画控制器               | 播放、暂停、恢复、速度、循环、重置等 | 支持                   |                                                  |
| 刚体层级动画             |                                      | 支持                   |                                                  |
| 骨骼蒙皮动画             |                                      | 支持                   |                                                  |
| 变形动画（morph target） |                                      | 不支持                 | 主要用于面部表情动画                             |
| 动画状态机               |                                      |                        |                                                  |
|                          | 状态                                 | 支持                   |                                                  |
|                          | 状态机过渡                           | 部分支持               | 目前的过渡条件只支持事件，不支持条件判断         |
|                          | 动画参数                             | 支持                   |                                                  |
|                          | 状态机行为                           | 不支持                 |                                                  |
|                          | 子状态机                             | 不支持                 |                                                  |
|                          | 动画层                               | 不支持                 | 因为混合树中支持了部分混合，可以不需要动画层     |
|                          | solo和mute                           | 不支持                 | 用于辅助调试动画效果，暂不需支持                 |
|                          | 目标匹配                             | 不支持                 |                                                  |
|                          | 根运动                               | 不支持                 |                                                  |
| 反向动力学               |                                      |                        |                                                  |
|                          | two bone ik                          | 支持                   |                                                  |
|                          | aim ik                               | 不支持                 | ozz支持，可以直接移植                            |
|                          | FABRIK                               | 不支持                 | 需自行实现                                       |
| 混合树                   |                                      | 部分支持               | 目前支持直接混合clip，不支持对混合的结果再次混合 |
|                          | 一维混合                             | 支持                   |                                                  |
|                          | 二维混合                             | 支持                   |                                                  |
|                          | 加法混合                             | 支持                   |                                                  |
|                          | 部分混合                             | 支持                   |                                                  |
|                          | 直接混合                             | 不支持                 |                                                  |
| 动画事件                 |                                      | 不支持                 |                                                  |
| 动画曲线                 |                                      | 不支持                 |                                                  |
| 重定向人形动画           |                                      | 不支持                 | 两个不同骨骼之间的映射                           |


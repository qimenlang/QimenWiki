MRT 中的每个 attachment，只要被启用，就必须在 fragment shader 中被确定性写入；试图通过“不写输出”来保持原值在 OpenGL 中属于未定义行为，正确的工程解法只能是拆 pass 或禁用对应的 draw buffer。

GBuffer 只能描述“第一个不透明表面”；

Blend 永远作用在“当前绑定 FBO 的 color attachment0”上。
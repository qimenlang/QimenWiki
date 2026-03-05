## MSAA 本质是什么？

MSAA 只在两个阶段发挥作用：

1. 光栅化阶段（coverage）
2. 深度测试阶段（per-sample depth）

它不自动提供：

- per-sample shading（除非显式使用 sampler2DMS）
- 正确的 resolve depth

## resolve 是不可逆的

一旦：

```
8x → resolve → 1x
```

你就丢失了：

- per-sample depth
- coverage 信息
- 边缘真实几何形状

resolve depth 不是物理正确深度。
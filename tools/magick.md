1. 精灵图裁剪

   -  -crop 8x8@ ： 裁剪尺寸，`@` 表示“自动均分”；
   - +repage ： 清除裁剪偏移信息

   ```shell
   magick input.png -crop 8x8@ +repage output_%03d.png
   ```

2. 生成图片

   ```shell
   magick -size 256x256 xc:black -fx "channel(i/255,j/255,0)" output16.png
   ```

   

3. Magick 支持哪些插值

   常见：

   | 插值     | 参数               | 特点           |
   | -------- | ------------------ | -------------- |
   | 最近邻   | `-filter point`    | 不插值，像素风 |
   | 双线性   | `-filter triangle` | 较平滑         |
   | Bicubic  | `-filter cubic`    | 更自然         |
   | Mitchell | `-filter mitchell` | 比较均衡       |
   | Lanczos  | `-filter lanczos`  | 默认高质量     |
   | Gaussian | `-filter gaussian` | 偏模糊         |
   | Catrom   | `-filter catrom`   | 更锐利         |

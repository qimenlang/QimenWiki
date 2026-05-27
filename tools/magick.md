1. 精灵图裁剪

   -  -crop 8x8@ ： 裁剪尺寸，`@` 表示“自动均分”；
   - +repage ： 清除裁剪偏移信息

   ```
   magick input.png -crop 8x8@ +repage output_%03d.png
   ```

2. 
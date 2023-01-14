1. filament中的shadowmap的渲染过程；
   - 第一个Pass，创建了FrameGraph，设置了shadow map参数
   - 对应的shader代码在哪？
   - light_shadowmap是怎么得到的；

1. 三个开关对阴影怎么施加的影响，uniform在哪？
   - light::setShadowCaster 决定加不加shadow pass
   - view
   - renderable::setShadowCast & renderable::setShadowReciver

1. prapreShadowPass与shadowPass的区别； 

1. 光源的相机参数是怎么设置的，会不会相机矩阵far太大，导致得到的shadow map是接近纯黑的；

1. 为什么depth_main.fs不能修改shadow map结果



抓帧

- 带IBL，没有Shadow Pass

<img src="D:\ForBY\QimenWiki\IRIS\images\ibl_no_shadow_pass.png" style="zoom:67%;" />

- shadow map为纯黑
  - 改depth_main之后，还是为纯黑；shadow pass没有执行？？

- 抓帧多数抓不到shadow pass

- 手机上不显示阴影问题
  - release版本是否显示




​    //return step(0.1,mod(base.x,0.2));


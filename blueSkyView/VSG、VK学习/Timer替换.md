vsg 没有专门的 Timer 类，而是直接使用 C++ 标准库的 std::chrono，并给它起了两个别名，位于 <vsg/ui/UIEvent.h>：

```c++
  namespace vsg {
      using clock = std::chrono::steady_clock;
      using time_point = clock::time_point;
  }
```

  osg::Timer → vsg 对照

![image-20260709161340239](..\Pic\vsg_osg_time.png)

  典型移植示例

  osg 原代码：

```c++
  osg::Timer_t start = osg::Timer::instance()->tick();
  doWork();
  double elapsed = osg::Timer::instance()->delta_s(start, osg::Timer::instance()->tick());
  std::cout << "elapsed = " << elapsed << " s\n";
```

  vsg 移植：

```c++
  auto start = vsg::clock::now();
  doWork();
  double elapsed = std::chrono::duration<double>(vsg::clock::now() - start).count();
  std::cout << "elapsed = " << elapsed << " s\n";
```

  场景相关的时间

  如果你原来用 osg::Timer 是为了配合 viewer 的帧循环（如 frameStamp->getSimulationTime()），vsg 里对应的是：

  - Viewer::start_point() — viewer 启动时间（Viewer.h:49）
  - FrameStamp::simulationTime — 帧的模拟时间（秒，从 start_point 起算）
  - FrameStamp::time — 该帧的 vsg::time_point

  在渲染循环里通常不需要自己 tick，直接读 viewer->getFrameStamp()->simulationTime 就行。

  建议封装

  如果移植量大、想少改代码，可以在你项目里加个薄壳兼容 osg 老接口：

```c++
  namespace compat {
      inline vsg::time_point tick() { return vsg::clock::now(); }
      inline double delta_s(vsg::time_point a, vsg::time_point b) {
          return std::chrono::duration<double>(b - a).count();
      }
      inline double delta_m(vsg::time_point a, vsg::time_point b) {
          return std::chrono::duration<double, std::milli>(b - a).count();
      }
  }
```

  批量替换 osg::Timer::instance()-> → compat::，改动最小。

---
  顺带一提：vsg 里更完整的性能计时基础设施在 vsg/utils/Instrumentation.h 和 vsg/utils/Profiler.h，如果你原来的 osg::Timer   是用于性能剖析（而不是普通计时），可以考虑改用这套，配合 Tracy 之类工具更方便。
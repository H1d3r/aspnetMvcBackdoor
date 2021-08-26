针对ASP.NET MVC程序的后门应用

设置环境变量：

```powershell
set COR_ENABLE_PROFILING=1
set COR_PROFILER={cf0d821e-299b-5307-a3d8-b283c03916dd}
set COR_PROFILER_PATH=E:\source_code\ReJITEnterLeaveHooks\Debug\ClrProfiler.dll
```

MORESEC_PROFILER_PROCESSES变量是探测器加载CLR程序后进行判断是否是需要加载的目标程序

其他三个就是探测器常规设置

设置探查器环境前后对比：

![image-20210812153729764](.\Dingtalk_20210826180525.jpg)
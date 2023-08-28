# BoxEngine
Game Engine.

## Platform
写存在平台差异代码时候的统一格式
```c++
// WindowsPlatformThread.h
class FWindowsPlatformThread { };
typedef FWindowsPlatformThread FPlatformThread;

// Runnable.h
class FRunnableThread : public FPlatformThread { };
```

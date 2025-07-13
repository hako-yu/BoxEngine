# BoxEngine

Game Engine

## 构建要求

### Windows
- Visual Studio 2019/2022 或 Visual Studio Build Tools
- CMake 3.27+
- Windows SDK

### Linux/macOS
- GCC 10+ 或 Clang 12+
- CMake 3.27+
- Make

## 构建步骤

### Windows
1. 打开 Visual Studio Developer Command Prompt
2. 运行构建脚本：
   ```cmd
   cd Engine\Build
   build.bat
   ```

### Linux/macOS
1. 确保已安装必要的开发工具
2. 运行构建脚本：
   ```bash
   cd Engine/Build
   chmod +x build.sh
   ./build.sh
   ``` 
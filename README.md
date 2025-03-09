# swam
C++代码

### 项目构建
#### macOS
```shell
$ cmake -G Ninja -S . -B build -Dtest=ON -DCMAKE_CXX_COMPILER="/usr/local/opt/llvm@17/bin/clang++"
$ cmake --build build && ctest --test-dir build
```

#### Windows Visual Studio 2017
```powershell
> cmake -G "Visual Studio 15 2017 Win64" -S . -B build
> cmake --config Release --build build
> cmake 
```
#### Windows Visual Studio 2022
```powershell
> cmake -G "Visual Studio 17 2022" -S . -B build
> cmake --config Release --build build
> cmake 
```

### 代码格式
vsc可以安装clang-format插件，clang-format的配置请参考[官方文档](https://clang.llvm.org/docs/ClangFormatStyleOptions.html)
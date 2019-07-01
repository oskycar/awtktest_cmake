# awtktest_cmake
awtk库示例程序，使用cmake进行编译配置，mac平台下测试通过

# 编译
1. 将awtk克隆到awtk.git目录下，按提示完成awtklib库的编译，结果在awtk.git/lib目录下
2. 将本工程克隆到和awtk.git同级目录下
3. 使用Xcode编译：进入awtktest_cmake目录，在命令行运行`cmake . -G Xcode`，然后打开xcode工程编译运行即可。
4. 纯命令行编译：运行`cmake .` ,然后再在命令行运行` make`完成编译。

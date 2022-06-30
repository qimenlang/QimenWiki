CMake使用手册

1. target_include_directories : 用于给target中所有的源码文件，增加头文件查找目录，可以避免#include头文件时，必须写路径

2. file

    Generate a list of files that match the <globbing-expressions> and store it into the <variable>. 

3. source_group  感觉没啥用

4. add_compile_definitions("ZEUS_ROOT_DIR=${ZEUS_ROOT_DIR}")

    通过编译选项的方式，将cmake中的变量传到编译的程序中；

5. 


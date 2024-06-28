cmake_minimum_required(VERSION 3.22.1) #cmake版本号
project("mylib") #工程名，也是生成的库文件
add_library(${CMAKE_PROJECT_NAME} SHARED #生成共享库
        native-lib.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} #生成库名
        android #链接android库
        log)    #链接log库
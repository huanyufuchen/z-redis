cmake_minimum_required(VERSION 2.8.9)
project(redisHelper)


if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    message(STATUS "optional:-std=c++11 -g -O0 -fpermissive")
endif(CMAKE_COMPILER_IS_GNUCXX)

#Bring the headers, such as Student.h into the project
include_directories(include)
include_directories(../include/hiredis)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")


add_library(redisHelper SHARED ${SOURCES})

#add_executable(redisHelpera ${SOURCES})

target_link_libraries(redisHelper hiredis glog)

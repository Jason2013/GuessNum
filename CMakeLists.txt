cmake_minimum_required(VERSION 3.15)
project(GuessNum)

add_executable(GuessNum
    GuessNum.cpp
    GuessNum.rc
    number.cpp
    StdAfx.cpp
)

target_link_options(GuessNum PRIVATE
    "/SUBSYSTEM:WINDOWS"
)

target_link_libraries(GuessNum Winmm.lib)

# About Resource Files
# https://docs.microsoft.com/en-us/windows/win32/menurc/about-resource-files
# 
# Using RC (The RC Command Line)
# https://docs.microsoft.com/en-us/windows/win32/menurc/using-rc-the-rc-command-line-

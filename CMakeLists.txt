cmake_minimum_required(VERSION 3.6)
project(AVLTree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Main.cpp
        AVLTree.h
        IKeyComparer.h
        ITraverseCallback.h
        )
add_executable(AVLTree ${SOURCE_FILES})
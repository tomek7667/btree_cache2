cmake_minimum_required(VERSION 3.19)
project(btree_cache)

set(CMAKE_CXX_STANDARD 14)

add_executable(btree_cache main.cpp Node.cpp Node.h BTree.cpp BTree.h)
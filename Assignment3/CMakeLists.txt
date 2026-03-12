cmake_minimum_required(VERSION 3.29)
project(Ass3)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ass3
        cmake-build-debug/Jerry.h
        cmake-build-debug/Jerry.c
        cmake-build-debug/LinkedList.h
        cmake-build-debug/LinkedLIst.c
        cmake-build-debug/KeyValuePair.h
        cmake-build-debug/KeyValuePair.c
        cmake-build-debug/hashTable.h
        cmake-build-debug/hashTable.c
        cmake-build-debug/MultiValueHashTable.h
        cmake-build-debug/MultiValueHashTable.c
        cmake-build-debug/JerryBoreeMain.c
)

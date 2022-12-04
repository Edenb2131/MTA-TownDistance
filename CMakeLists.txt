cmake_minimum_required(VERSION 3.20)
project(MTA_TownDistance)

set(CMAKE_CXX_STANDARD 14)

add_executable(MTA_TownDistance
        MTA-TownDistance/main.cpp
        MTA-TownDistance/Stack.cpp
        MTA-TownDistance/Stack.h
        MTA-TownDistance/Node.cpp
        MTA-TownDistance/Node.h
        MTA-TownDistance/Item.cpp
        MTA-TownDistance/Item.h
        )

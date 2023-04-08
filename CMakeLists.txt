cmake_minimum_required(VERSION 3.20)
project(Qommy)

# copy all dependencies
file(COPY import/lib/ DESTINATION .)

include_directories(import/include)
include_directories(include)
link_directories(import/lib)

add_executable(test src/main.cpp)
target_link_libraries(test LogCPP)
target_link_libraries(test JsonCPP)
add_library(QommyBase SHARED src/utils/ByteBuffer.cpp
                            src/encrypt/Md5.cpp)
target_link_libraries(QommyBase JsonCPP)
target_link_libraries(QommyBase LogCPP)
target_link_libraries(test QommyBase)
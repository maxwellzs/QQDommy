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
add_library(QommyUtils SHARED src/utils/ByteBuffer.cpp
                            src/encrypt/Md5.cpp
                            src/core/Tlv.cpp)
target_link_libraries(QommyUtils JsonCPP)
target_link_libraries(QommyUtils LogCPP)
target_link_libraries(test QommyUtils)
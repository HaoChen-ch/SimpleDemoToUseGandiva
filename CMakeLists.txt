cmake_minimum_required(VERSION 3.16)
project(SimpleDemoToUseGandiva)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(GANDIVA)


include_directories(SimpleDemoToUseGandiva  ${GANDVIA_INCLUDE_DIR})

add_executable(SimpleDemoToUseGandiva main.cpp test_util.h)

target_link_libraries(SimpleDemoToUseGandiva  gandiva arrow gtest)
target_link_libraries(SimpleDemoToUseGandiva -lpthread -lm)
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(set_position_plugin)

set(CMAKE_CXX_STANDARD 11)
set(LIBRARY_OUTPUT_PATH ../../plugins)

find_package(gazebo REQUIRED)
find_package(rclcpp REQUIRED)
find_package(ttr_msgs REQUIRED)

include_directories(${GAZEBO_INCLUDE_DIRS})
include_directories(${rclcpp_INCLUDE_DIRS})
include_directories(${ttr_msgs_INCLUDE_DIRS})

link_directories(${GAZEBO_LIBRARY_DIRS})

list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(set_position_plugin SHARED set_position_plugin.cc)
target_link_libraries(set_position_plugin ${GAZEBO_LIBRARIES} ${rclcpp_LIBRARIES} ${ttr_msgs_LIBRARIES})

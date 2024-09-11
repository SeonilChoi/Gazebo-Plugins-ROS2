cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(custom_joint_state_publisher_plugin)

set(CMAKE_CXX_STANDARD 11)
set(LIBRARY_OUTPUT_PATH ../../plugins)

find_package(gazebo REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

include_directories(${rclcpp_INCLUDE_DIRS})
include_directories(${sensor_msgs_INCLUDE_DIRS})
include_directories(${GAZEBO_INCLUDE_DIRS})

link_directories(${GAZEBO_LIBRARY_DIRS})

list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(${PROJECT_NAME} SHARED custom_joint_state_publisher.cc)

target_link_libraries(${PROJECT_NAME} ${GAZEBO_LIBRARIES} ${rclcpp_LIBRARIES} ${sensor_msgs_LIBRARIES})

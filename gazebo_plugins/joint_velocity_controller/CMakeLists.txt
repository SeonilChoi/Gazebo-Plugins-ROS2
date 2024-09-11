cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(joint_velocity_controller_plugin)

set(CMAKE_CXX_STANDARD 11)
set(LIBRARY_OUTPUT_PATH ../../plugins)

find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(gazebo REQUIRED)

include_directories(${EIGEN_INCLUDE_DIRS})
include_directories(${rclcpp_INCLUDE_DIRS})
include_directories(${std_msgs_INCLUDE_DIRS})
include_directories(${GAZEBO_INCLUDE_DIRS})

link_directories(${GAZEBO_LIBRARY_DIRS})

list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(${PROJECT_NAME} SHARED joint_velocity_controller.cc)

target_link_libraries(${PROJECT_NAME} ${GAZEBO_LIBRARIES} ${rclcpp_LIBRARIES} ${std_msgs_LIBRARIES})

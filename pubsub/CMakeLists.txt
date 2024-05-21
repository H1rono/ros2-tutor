cmake_minimum_required(VERSION 3.8)
project(pubsub)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(subscriber
    src/subscriber.cpp
    src/subscriber_main.cpp
)

add_executable(publisher
    src/publisher.cpp
    src/publisher_main.cpp
)

ament_target_dependencies(subscriber
    rclcpp
    std_msgs
)

ament_target_dependencies(publisher
    rclcpp
    std_msgs
)

target_include_directories(subscriber
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(publisher
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(
    TARGETS subscriber publisher
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()

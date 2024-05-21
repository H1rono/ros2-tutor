cmake_minimum_required(VERSION 3.8)
project(custom_pubsub)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tutorial_interfaces REQUIRED)

add_executable(num_sub
    src/num_subscriber.cpp
    src/num_subscriber_main.cpp
)

add_executable(num_pub
    src/num_publisher.cpp
    src/num_publisher_main.cpp
)

ament_target_dependencies(num_sub
    rclcpp
    tutorial_interfaces
)

ament_target_dependencies(num_pub
    rclcpp
    tutorial_interfaces
)

target_include_directories(num_sub
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(num_pub
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(
    TARGETS num_sub num_pub
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()

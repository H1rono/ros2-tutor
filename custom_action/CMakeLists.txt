cmake_minimum_required(VERSION 3.8)
project(custom_action)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(tutorial_interfaces REQUIRED)

add_library(action_server SHARED
    src/fibonacci_action_server.cpp
)
add_library(action_client SHARED
    src/fibonacci_action_client.cpp
)

ament_target_dependencies(action_server
    rclcpp
    rclcpp_action
    rclcpp_components
    tutorial_interfaces
)

ament_target_dependencies(action_client
    rclcpp
    rclcpp_action
    rclcpp_components
    tutorial_interfaces
)

target_include_directories(action_server
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(action_client
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_definitions(action_server
    PRIVATE "CUSTOM_ACTION_CPP_BUILDING_DLL"
)

target_compile_definitions(action_client
    PRIVATE "CUSTOM_ACTION_CPP_BUILDING_DLL"
)

rclcpp_components_register_node(action_server
    PLUGIN "fibonacci::ActionServer"
    EXECUTABLE fibonacci_action_server
)

rclcpp_components_register_node(action_client
    PLUGIN "fibonacci::ActionClient"
    EXECUTABLE fibonacci_action_client
)

install(
    TARGETS action_server action_client
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

ament_package()

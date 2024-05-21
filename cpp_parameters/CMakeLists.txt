cmake_minimum_required(VERSION 3.8)
project(cpp_parameters)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)

add_library(param
    SHARED
    src/parameters.cpp
)

ament_target_dependencies(param
    rclcpp
    rclcpp_components
)

target_include_directories(param
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

rclcpp_components_register_node(
    param
    PLUGIN "param::Parameters"
    EXECUTABLE parameters
)

install(
    TARGETS param
    EXPORT export_param_component
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(
    DIRECTORY launch
    DESTINATION share/${PROJECT_NAME}
)

ament_package()

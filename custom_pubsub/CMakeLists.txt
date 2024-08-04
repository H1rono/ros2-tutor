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
find_package(rclcpp_components REQUIRED)
find_package(tutorial_interfaces REQUIRED)

add_library(numsub
    SHARED
    src/num_subscriber.cpp
)

add_library(numpub
    SHARED
    src/num_publisher.cpp
)

ament_target_dependencies(numsub
    rclcpp
    rclcpp_components
    tutorial_interfaces
)

ament_target_dependencies(numpub
    rclcpp
    rclcpp_components
    tutorial_interfaces
)

target_include_directories(numsub
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(numpub
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

rclcpp_components_register_node(
    numsub
    PLUGIN "num_sub::NumSubscriber"
    EXECUTABLE num_sub
)

rclcpp_components_register_node(
    numpub
    PLUGIN "num_pub::NumPublisher"
    EXECUTABLE num_pub
)

install(
    TARGETS numsub numpub
    EXPORT export_num_pubsub
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

ament_package()

cmake_minimum_required(VERSION 3.8)
project(custom_srv)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tutorial_interfaces REQUIRED)

add_executable(server
  src/add_three_ints_server_main.cpp
  src/add_three_ints_server.cpp
)

add_executable(client
  src/add_three_ints_client_main.cpp
  src/add_three_ints_client.cpp
)

ament_target_dependencies(server
  rclcpp
  tutorial_interfaces
)

ament_target_dependencies(client
  rclcpp
  tutorial_interfaces
)

target_include_directories(server
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(client
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS
    server client
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

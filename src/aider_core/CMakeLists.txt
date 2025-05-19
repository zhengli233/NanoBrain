cmake_minimum_required(VERSION 3.8)
project(aider_core)


if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(vision_interfaces REQUIRED)
find_package(arm_interfaces REQUIRED)
find_package(lowerbody_interfaces REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(yaml-cpp REQUIRED)

add_executable(aider_core
      src/task_lib/grab_cup/grab_cup.cpp
      src/task_lib/carry_box/carry_box.cpp
      src/aider_core.cpp
      src/primitive_lib/locate_object_center/locate_object_center.cpp
      src/primitive_lib/single_arm_move_to/single_arm_move_to.cpp
      src/primitive_lib/crouch/crouch.cpp
      src/primitive_lib/double_arm_move_to/double_arm_move_to.cpp
      src/primitive_lib/locate_object_rl/locate_object_rl.cpp
      src/param_center/param_center.cpp
      src/aider_global_node.cpp
      src/main.cpp)
target_include_directories(aider_core PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Client>
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/aider_core/task_lib>
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/aider_core/primitive_lib>
$<INSTALL_INTERFACE:include>
)
target_compile_features(aider_core PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
  aider_core
  "rclcpp"
  "vision_interfaces"
  "arm_interfaces"
  "geometry_msgs"
  "lowerbody_interfaces"
)

target_link_libraries(aider_core yaml-cpp)

install(TARGETS aider_core
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

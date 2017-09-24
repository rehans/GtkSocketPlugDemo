cmake_minimum_required (VERSION 3.4.3)

project (GtkSocketPlugDemo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wno-multichar")
link_libraries(stdc++fs pthread dl)

find_package(X11 REQUIRED)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
  include_directories(${X11_INCLUDE_DIR}
    ${GTK3_INCLUDE_DIRS})

add_executable(GtkSocketPlugDemo source/main.cpp)

target_link_libraries(GtkSocketPlugDemo
  ${X11_LIBRARIES}
  ${GTK3_LIBRARIES}
  ${GTKMM3_LIBRARIES})

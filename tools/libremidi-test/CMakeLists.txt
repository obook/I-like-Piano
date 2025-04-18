cmake_minimum_required(VERSION 3.16)

project(libremidi-test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# LIBREMIDI
FetchContent_Declare(
  LIBREMIDI
  GIT_REPOSITORY https://github.com/jcelerier/libremidi.git
  GIT_TAG  v5.1.0)
FetchContent_MakeAvailable(LIBREMIDI)

add_executable(libremidi-test main.cpp)

# example of folder structure
# add_subdirectory(3rdparty/libremidi)

include(GNUInstallDirs)
install(TARGETS libremidi-test
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  $<BUILD_INTERFACE:libremidi>
)



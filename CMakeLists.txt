cmake_minimum_required(VERSION 3.14)
project(sorting-in-cxx VERSION 0.1.0 LANGUAGES C CXX)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.6.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(sorting-in-cxx src/main.cpp)
target_link_libraries(sorting-in-cxx PRIVATE Catch2::Catch2)
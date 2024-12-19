cmake_minimum_required(VERSION 3.27)
project(10)

set(CMAKE_CXX_STANDARD 23)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../lib)

include(FetchContent)

# Fetch Google Test
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# Fetch SFML
FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG master
)
FetchContent_MakeAvailable(sfml)

# Fetch Boost
FetchContent_Declare(
        Boost
        URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
        URL_MD5 893b5203b862eb9bbd08553e24ff146a
        DOWNLOAD_EXTRACT_TIMESTAMP ON
)
set(BOOST_INCLUDE_LIBRARIES filesystem regex signals2)
FetchContent_MakeAvailable(Boost)


# Gather source files
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/**/*.h" "${CMAKE_SOURCE_DIR}/src/**/*.cpp")

# Exclude specific files from the source list
list(REMOVE_ITEM SOURCE_FILES "${CMAKE_SOURCE_DIR}/cmd/main.cpp")
list(REMOVE_ITEM SOURCE_FILES "${CMAKE_SOURCE_DIR}/test/test.cpp")

message(STATUS "Found source files: ${SOURCE_FILES}")

# Define executables
add_executable(main_app cmd/main.cpp ${SOURCE_FILES})
add_executable(main_test test/test.cpp ${SOURCE_FILES})

# Link libraries for the main application
target_link_libraries(main_app PRIVATE sfml-system sfml-window sfml-graphics Boost::filesystem Boost::regex Boost::signals2)

# Link libraries for the test application
target_link_libraries(main_test PRIVATE gtest_main gmock gtest sfml-system sfml-window sfml-graphics Boost::filesystem Boost::regex Boost::signals2)

# Enable testing and add tests
enable_testing()
add_test(NAME main_test COMMAND main_test)

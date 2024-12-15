cmake_minimum_required(VERSION 3.27)
project(2)

set(CMAKE_CXX_STANDARD 20)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ./../bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY  ./../lib )

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        Boost
        URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
        URL_MD5 893b5203b862eb9bbd08553e24ff146a
        DOWNLOAD_EXTRACT_TIMESTAMP ON
)

set(BOOST_INCLUDE_LIBRARIES filesystem regex signals2)
FetchContent_MakeAvailable(Boost)

# Задание 1
set(SOURCE_FILES_1
        1/cmd/main.cpp
        1/lib/Observer.h
        1/lib/WeatherData.h
)

set(TEST_SOURCE_FILES_1
        1/test/testProvider.cpp
        1/lib/Observer.h
        1/lib/WeatherData.h
)

add_executable(1 ${SOURCE_FILES_1})

add_executable(1_test ${TEST_SOURCE_FILES_1})

target_link_libraries(1_test gtest_main)
enable_testing()
add_test(NAME 1_test COMMAND 1_test)

# Задание 2
set(SOURCE_FILES_1
        2/cmd/main.cpp
        2/lib/Observer.h
        2/lib/WeatherData.h
)

set(TEST_SOURCE_FILES_1
        2/test/testProvider.cpp
        2/lib/Observer.h
        2/lib/WeatherData.h
)

add_executable(2 ${SOURCE_FILES_1})

add_executable(2_test ${TEST_SOURCE_FILES_1})

target_link_libraries(2_test gtest_main)
enable_testing()
add_test(NAME 2_test COMMAND 2_test)

# Задание 3
set(SOURCE_FILES_1
        3/cmd/main.cpp
        3/lib/Observer.h
        3/lib/WeatherData.h
)

set(TEST_SOURCE_FILES_1
        3/test/testProvider.cpp
        3/lib/Observer.h
        3/lib/WeatherData.h
)

add_executable(3 ${SOURCE_FILES_1})

add_executable(3_test ${TEST_SOURCE_FILES_1})

target_link_libraries(3_test gtest_main)
enable_testing()
add_test(NAME 3_test COMMAND 3_test)

# Задание 4
set(SOURCE_FILES_1
        4/cmd/main.cpp
        4/lib/Observer.h
        4/lib/WeatherData.h
)

set(TEST_SOURCE_FILES_1
        4/test/testProvider.cpp
        4/lib/Observer.h
        4/lib/WeatherData.h
)

add_executable(4 ${SOURCE_FILES_1})

add_executable(4_test ${TEST_SOURCE_FILES_1})

target_link_libraries(4_test gmock gtest_main)
enable_testing()
add_test(NAME 4_test COMMAND 4_test)

# Задание 5
set(SOURCE_FILES_1
        5/cmd/main.cpp
        5/lib/Observer.h
        5/lib/WeatherData.h
)

set(TEST_SOURCE_FILES_1
        5/test/testProvider.cpp
        5/lib/Observer.h
        5/lib/WeatherData.h
)

add_executable(5 ${SOURCE_FILES_1})

add_executable(5_test ${TEST_SOURCE_FILES_1})

target_link_libraries(5_test gmock gtest_main)
enable_testing()
add_test(NAME 5_test COMMAND 5_test)

# Задание 7
set(SOURCE_FILES_1
        7/cmd/main.cpp
        7/lib/Observer.h
        7/lib/WeatherData.h
)

set(TEST_SOURCE_FILES_1
        7/test/testProvider.cpp
        7/lib/Observer.h
        7/lib/WeatherData.h
)

add_executable(7 ${SOURCE_FILES_1})

add_executable(7_test ${TEST_SOURCE_FILES_1})

target_link_libraries(7_test gmock gtest_main)
enable_testing()
add_test(NAME 7_test COMMAND 7_test)

# Задание 8
set(SOURCE_FILES_1
        8/cmd/main.cpp
        8/lib/Observer.h
        8/lib/WeatherData.h
)

set(TEST_SOURCE_FILES_1
        8/test/testProvider.cpp
        8/lib/Observer.h
        8/lib/WeatherData.h
)

add_executable(8 ${SOURCE_FILES_1})

add_executable(8_test ${TEST_SOURCE_FILES_1})

target_link_libraries(8_test gmock gtest_main Boost::filesystem Boost::regex Boost::signals2)
target_link_libraries(8 PRIVATE Boost::filesystem Boost::regex Boost::signals2)
enable_testing()
add_test(NAME 8_test COMMAND 8_test)
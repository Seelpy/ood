cmake_minimum_required(VERSION 3.27)
project(10)

set(CMAKE_CXX_STANDARD 23)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ./../bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY  ./../lib )

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG master
)
FetchContent_MakeAvailable(sfml)

FetchContent_Declare(
        Boost
        URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
        URL_MD5 893b5203b862eb9bbd08553e24ff146a
        DOWNLOAD_EXTRACT_TIMESTAMP ON
)

set(BOOST_INCLUDE_LIBRARIES filesystem regex signals2)
FetchContent_MakeAvailable(Boost)


file(GLOB_RECURSE SOURCE_FILES_2 "${CMAKE_SOURCE_DIR}/src/**/*.h" "${CMAKE_SOURCE_DIR}/src/**/*.cpp" )

list(REMOVE_ITEM SOURCE_FILES_2
        "${CMAKE_SOURCE_DIR}/cmd/main.cpp"
        "${CMAKE_SOURCE_DIR}/test/test.cpp"
)

message(STATUS "Found source files: ${SOURCE_FILES_2}")

set(SOURCE_FILES_2
        cmd/main.cpp
        /Users/maksimveselov/Projects/ood/1/10/src/model/common/Color.h
        /Users/maksimveselov/Projects/ood/1/10/src/model/common/Point.h
        /Users/maksimveselov/Projects/ood/1/10/src/model/common/Rect.h
        /Users/maksimveselov/Projects/ood/1/10/src/model/common/Size.h
        /Users/maksimveselov/Projects/ood/1/10/src/model/draft/Draft.h
        /Users/maksimveselov/Projects/ood/1/10/src/model/draft/IDraft.h
        /Users/maksimveselov/Projects/ood/1/10/src/model/shape/IShape.h
        /Users/maksimveselov/Projects/ood/1/10/src/model/shape/Shape.h
        /Users/maksimveselov/Projects/ood/1/10/src/model/style/fill/IFillStyle.h
        /Users/maksimveselov/Projects/ood/1/10/src/model/style/fill/FIllStyle.h
        /Users/maksimveselov/Projects/ood/1/10/src/model/style/line/ILineStyle.h
        /Users/maksimveselov/Projects/ood/1/10/src/model/style/line/LineStyle.h
        /Users/maksimveselov/Projects/ood/1/10/src/presenter/IPresenter.h
        /Users/maksimveselov/Projects/ood/1/10/src/presenter/command/ICommand.h
        /Users/maksimveselov/Projects/ood/1/10/src/presenter/command/IExecuter.h
        /Users/maksimveselov/Projects/ood/1/10/src/presenter/command/IHistory.h
        /Users/maksimveselov/Projects/ood/1/10/src/presenter/command/History.h
        /Users/maksimveselov/Projects/ood/1/10/src/presenter/command/MultiCommand.h
        /Users/maksimveselov/Projects/ood/1/10/src/presenter/draft/Draft.h
        /Users/maksimveselov/Projects/ood/1/10/src/presenter/shape/Shape.h
        /Users/maksimveselov/Projects/ood/1/10/src/presenter/shape/ViewFactory.h
        /Users/maksimveselov/Projects/ood/1/10/src/view/canvas/ICanvas.h
        /Users/maksimveselov/Projects/ood/1/10/src/view/IView.h
        /Users/maksimveselov/Projects/ood/1/10/src/view/draft/Draft.h
        /Users/maksimveselov/Projects/ood/1/10/src/view/shape/IShapeViewStrategy.h
        /Users/maksimveselov/Projects/ood/1/10/src/view/shape/Shape.h
        /Users/maksimveselov/Projects/ood/1/10/src/view/shape/strategy/Cricle.h
        /Users/maksimveselov/Projects/ood/1/10/src/app/Editor.h
        /Users/maksimveselov/Projects/ood/1/10/src/lib/sfml/canvas/Canvas.h
        /Users/maksimveselov/Projects/ood/1/10/src/lib/sfml/canvas/Canvas.cpp
)

set(SOURCE_FILES_1
        cmd/main.cpp
)

set(TEST_SOURCE_FILES_1
        test/test.cpp
)

add_executable(1)
target_sources(1 PRIVATE ${SOURCE_FILES_1} ${SOURCE_FILES_2})

add_executable(1_test)
target_sources(1_test PRIVATE ${TEST_SOURCE_FILES_1}  ${SOURCE_FILES_2})

target_link_libraries(1_test gtest_main gmock gtest sfml-system sfml-window sfml-graphics Boost::filesystem Boost::regex Boost::signals2)
target_link_libraries(1 sfml-system sfml-window sfml-graphics Boost::filesystem Boost::regex Boost::signals2)
enable_testing()
add_test(NAME 1_test COMMAND 1_test)
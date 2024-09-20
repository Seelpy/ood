cmake_minimum_required(VERSION 3.27)

project(1_1)

set(CMAKE_CXX_STANDARD 20)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ./../bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY  ./../lib )

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

# Задание 1
set(SOURCE_FILES_1
        1/cmd/main.cpp
        1/lib/Duck/Fly/FlyNoWay.h
        1/lib/Duck/Fly/FlyWithWings.h
        1/lib/Duck/Fly/IFlyBehavior.h
        1/lib/Duck/Quack/IQuakBehavior.h
        1/lib/Duck/Quack/MuteQuackBehavior.h
        1/lib/Duck/Quack/QuackBehavior.h
        1/lib/Duck/Quack/SqueakBehavior.h
        1/lib/Duck/DecoyDuck.h
        1/lib/Duck/Duck.h
        1/lib/Duck/MallardDuck.h
        1/lib/Duck/ModelDuck.h
        1/lib/Duck/RedheadDuck.h
        1/lib/Duck/RubberDuck.h
        1/lib/DuckFunctions.h
        1/lib/Duck/Dance/DanceNoWay.h
        1/lib/Duck/Dance/DanceMinuet.h
        1/lib/Duck/Dance/DanceWaltz.h
        1/lib/Duck/Dance/IDanceBehavior.h
        4/lib/Picture/ShapeStrategy/Type.cpp
)

set(TEST_SOURCE_FILES_1
        1/test/testProvider.cpp
        1/lib/Duck/Fly/FlyNoWay.h
        1/lib/Duck/Fly/FlyWithWings.h
        1/lib/Duck/Fly/IFlyBehavior.h
        1/lib/Duck/Quack/IQuakBehavior.h
        1/lib/Duck/Quack/MuteQuackBehavior.h
        1/lib/Duck/Quack/QuackBehavior.h
        1/lib/Duck/Quack/SqueakBehavior.h
        1/lib/Duck/DecoyDuck.h
        1/lib/Duck/Duck.h
        1/lib/Duck/MallardDuck.h
        1/lib/Duck/ModelDuck.h
        1/lib/Duck/RedheadDuck.h
        1/lib/Duck/RubberDuck.h
        1/lib/DuckFunctions.h
        1/lib/Duck/Dance/DanceNoWay.h
        1/lib/Duck/Dance/DanceMinuet.h
        1/lib/Duck/Dance/DanceWaltz.h
        1/lib/Duck/Dance/IDanceBehavior.h
)

add_executable(1_1 ${SOURCE_FILES_1})

add_executable(1_1_test ${TEST_SOURCE_FILES_1})

target_link_libraries(1_1_test gtest_main)
enable_testing()
add_test(NAME 1_1_test COMMAND 1_1_test)

########################

# Задание 2
set(SOURCE_FILES_2
        2/cmd/main.cpp
        2/lib/Duck/Fly/FlyNoWay.h
        2/lib/Duck/Fly/FlyWithWings.h
        2/lib/Duck/Fly/IFlyBehavior.h
        2/lib/Duck/Quack/IQuakBehavior.h
        2/lib/Duck/Quack/MuteQuackBehavior.h
        2/lib/Duck/Quack/QuackBehavior.h
        2/lib/Duck/Quack/SqueakBehavior.h
        2/lib/Duck/DecoyDuck.h
        2/lib/Duck/Duck.h
        2/lib/Duck/MallardDuck.h
        2/lib/Duck/ModelDuck.h
        2/lib/Duck/RedheadDuck.h
        2/lib/Duck/RubberDuck.h
        2/lib/DuckFunctions.h
)

set(TEST_SOURCE_FILES_2
        2/test/testProvider.cpp
        2/lib/Duck/Fly/FlyNoWay.h
        2/lib/Duck/Fly/FlyWithWings.h
        2/lib/Duck/Fly/IFlyBehavior.h
        2/lib/Duck/Quack/IQuakBehavior.h
        2/lib/Duck/Quack/MuteQuackBehavior.h
        2/lib/Duck/Quack/QuackBehavior.h
        2/lib/Duck/Quack/SqueakBehavior.h
        2/lib/Duck/DecoyDuck.h
        2/lib/Duck/Duck.h
        2/lib/Duck/MallardDuck.h
        2/lib/Duck/ModelDuck.h
        2/lib/Duck/RedheadDuck.h
        2/lib/Duck/RubberDuck.h
        2/lib/DuckFunctions.h
)

add_executable(1_2 ${SOURCE_FILES_2})

add_executable(1_2_test ${TEST_SOURCE_FILES_2})

target_link_libraries(1_2_test gtest_main)
enable_testing()
add_test(NAME 1_2_test COMMAND 1_2_test)

########################

# Задание 3
set(SOURCE_FILES_3
        3/cmd/main.cpp
        3/lib/Duck/Fly/FlyNoWay.h
        3/lib/Duck/Fly/FlyWithWings.h
        3/lib/Duck/Fly/FlyBehavior.h
        3/lib/Duck/Quack/QuakBehavior.h
        3/lib/Duck/Quack/MuteQuack.h
        3/lib/Duck/Quack/Quack.h
        3/lib/Duck/Quack/Squeak.h
        3/lib/Duck/DecoyDuck.h
        3/lib/Duck/Duck.h
        3/lib/Duck/MallardDuck.h
        3/lib/Duck/ModelDuck.h
        3/lib/Duck/RedheadDuck.h
        3/lib/Duck/RubberDuck.h
        3/lib/DuckFunctions.h
        3/lib/Duck/Dance/DanceBehavior.h
        3/lib/Duck/Dance/DanceMinuet.h
        3/lib/Duck/Dance/DanceNoWay.h
        3/lib/Duck/Dance/DanceWaltz.h
)

set(TEST_SOURCE_FILES_3
        3/test/testProvider.cpp
        3/lib/Duck/Fly/FlyNoWay.h
        3/lib/Duck/Fly/FlyWithWings.h
        3/lib/Duck/Fly/FlyBehavior.h
        3/lib/Duck/Quack/QuakBehavior.h
        3/lib/Duck/Quack/MuteQuack.h
        3/lib/Duck/Quack/Quack.h
        3/lib/Duck/Quack/Squeak.h
        3/lib/Duck/DecoyDuck.h
        3/lib/Duck/Duck.h
        3/lib/Duck/MallardDuck.h
        3/lib/Duck/ModelDuck.h
        3/lib/Duck/RedheadDuck.h
        3/lib/Duck/RubberDuck.h
        3/lib/DuckFunctions.h
        3/lib/Duck/Dance/DanceBehavior.h
        3/lib/Duck/Dance/DanceMinuet.h
        3/lib/Duck/Dance/DanceNoWay.h
        3/lib/Duck/Dance/DanceWaltz.h
)

add_executable(1_3 ${SOURCE_FILES_3})

add_executable(1_3_test ${TEST_SOURCE_FILES_3})

target_link_libraries(1_3_test gtest_main)
enable_testing()
add_test(NAME 1_3_test COMMAND 1_3_test)

########################

# Задание 4
set(SOURCE_FILES_4
        4/cmd/main.cpp
        4/lib/Picture/Point.h
        4/lib/Picture/Point.cpp
        4/lib/Canvas/ICanvas.h
        4/lib/Picture/Shape.h
        4/lib/Picture/ShapeStrategy/Type.h
        4/lib/Picture/ShapeStrategy/Type.cpp
        4/lib/Picture/ShapeStrategy/IShapeStrategy.h
        4/lib/Picture/ShapeStrategy/CircleStrategy.h
        4/lib/Picture/ShapeStrategy/RectangleStrategy.h
        4/lib/Picture/ShapeStrategy/TriangleStrategy.h
        4/lib/Picture/ShapeStrategy/LineStrategy.h
        4/lib/Picture/ShapeStrategy/TextStrategy.h
        4/lib/Picture/Picture.h
        4/lib/Handler/ShapeCommandHandler.h
        4/lib/Canvas/PNGCanvas/PNGCanvas.cpp
        4/lib/Canvas/PNGCanvas/PNGCanvas.cpp
        4/lib/Canvas/PNGCanvas/PNGCanvas.cpp
        4/lib/Picture/Picture.cpp
        4/lib/Handler/CommandsHandlers/ParseFunc.h
        4/lib/Handler/CommandsHandlers/CommandType.h
        4/lib/Handler/CommandsHandlers/MoveShapeHandler.h
        4/lib/Handler/CommandsHandlers/MovePictureHandler.h
        4/lib/Handler/CommandsHandlers/DeleteShapeHandler.h
        4/lib/Handler/CommandsHandlers/ListShapesHandler.h
        4/lib/Handler/CommandsHandlers/ChangeColorHandler.h
        4/lib/Handler/CommandsHandlers/ChangeShapeHandler.h
        4/lib/Handler/CommandsHandlers/AddShapeHandler.h
        4/lib/Handler/CommandsHandlers/DrawShapeHandler.h
        4/lib/Handler/CommandsHandlers/DrawPictureHandler.h
        4/lib/Handler/CommandsHandlers/CloneShapeHandler.h
        4/lib/Handler/CommandsHandlers/CloneShapeHandler.h
        4/lib/Canvas/PNGCanvas/PNGCanvas.h
        4/lib/Canvas/PNGCanvas/stb_image_write.h
        4/lib/Canvas/PNGCanvas/stb_truetype.h
)

set(TEST_SOURCE_FILES_4
        4/test/testProvider.cpp
        4/lib/Canvas/ICanvas.h
        4/lib/Picture/Shape.h
        4/lib/Picture/Point.h
        4/lib/Picture/Point.cpp
        4/lib/Picture/ShapeStrategy/Type.h
        4/lib/Picture/ShapeStrategy/Type.cpp
        4/lib/Picture/ShapeStrategy/IShapeStrategy.h
        4/lib/Picture/ShapeStrategy/CircleStrategy.h
        4/lib/Picture/ShapeStrategy/RectangleStrategy.h
        4/lib/Picture/ShapeStrategy/TriangleStrategy.h
        4/lib/Picture/ShapeStrategy/LineStrategy.h
        4/lib/Picture/ShapeStrategy/TextStrategy.h
        4/lib/Picture/Picture.h
        4/lib/Handler/ShapeCommandHandler.h
        4/lib/Canvas/PNGCanvas/PNGCanvas.cpp
        4/lib/Canvas/PNGCanvas/PNGCanvas.cpp
        4/lib/Canvas/PNGCanvas/PNGCanvas.cpp
        4/lib/Picture/Picture.cpp
        4/lib/Handler/CommandsHandlers/ParseFunc.h
        4/lib/Handler/CommandsHandlers/CommandType.h
        4/lib/Handler/CommandsHandlers/MoveShapeHandler.h
        4/lib/Handler/CommandsHandlers/MovePictureHandler.h
        4/lib/Handler/CommandsHandlers/DeleteShapeHandler.h
        4/lib/Handler/CommandsHandlers/ListShapesHandler.h
        4/lib/Handler/CommandsHandlers/ChangeColorHandler.h
        4/lib/Handler/CommandsHandlers/ChangeShapeHandler.h
        4/lib/Handler/CommandsHandlers/AddShapeHandler.h
        4/lib/Handler/CommandsHandlers/DrawShapeHandler.h
        4/lib/Handler/CommandsHandlers/DrawPictureHandler.h
        4/lib/Handler/CommandsHandlers/CloneShapeHandler.h
        4/lib/Canvas/PNGCanvas/PNGCanvas.h
        4/lib/Canvas/PNGCanvas/stb_image_write.h
        4/lib/Canvas/PNGCanvas/stb_truetype.h
)

add_executable(1_4 ${SOURCE_FILES_4})

add_executable(1_4_test ${TEST_SOURCE_FILES_4})

target_link_libraries(1_4_test gtest_main)

enable_testing()
add_test(NAME 1_4_test COMMAND 1_4_test)
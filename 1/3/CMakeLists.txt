cmake_minimum_required(VERSION 3.27)
project(3)

set(CMAKE_CXX_STANDARD 23)

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
        1/lib/Condiment.h
        1/lib/Beverage.h
        1/lib/IBeverage.h
        1/lib/Beverages/Cofee.h
        1/lib/Beverages/Cappucciono.h
        1/lib/Beverages/Latte.h
        1/lib/Beverages/Tea.h
        1/lib/Beverages/Milkshake.h
        1/lib/Condiments/Cinnamon.h
        1/lib/Condiments/Lemon.h
        1/lib/Condiments/IceCubes.h
        1/lib/Condiments/Syrup.h
        1/lib/Condiments/ChocolateCrumbs.h
        1/lib/Condiments/CoconutFlakes.h
        1/lib/InfoByType.h
        1/lib/Beverages/LattePreset.h
        1/lib/Beverages/CappuccinoPreset.h
        1/lib/Beverages/TeaPreset.h
        1/lib/Beverages/MilkshakePreset.h
        1/lib/Condiments/CondimentMaker.h
        3/lib/IO/Modifications/CInputDataStreamDecorator.h
)

set(TEST_SOURCE_FILES_1
        1/test/testProvider.cpp
        1/lib/Condiment.h
        1/lib/Beverage.h
        1/lib/IBeverage.h
        1/lib/Beverages/Cofee.h
        1/lib/Beverages/Cappucciono.h
        1/lib/Beverages/Latte.h
        1/lib/Beverages/Tea.h
        1/lib/Beverages/Milkshake.h
        1/lib/Condiments/Cinnamon.h
        1/lib/Condiments/Lemon.h
        1/lib/Condiments/IceCubes.h
        1/lib/Condiments/Syrup.h
        1/lib/Condiments/ChocolateCrumbs.h
        1/lib/Condiments/CoconutFlakes.h
        1/lib/InfoByType.h
        1/lib/Beverages/LattePreset.h
        1/lib/Beverages/CappuccinoPreset.h
        1/lib/Beverages/TeaPreset.h
        1/lib/Beverages/MilkshakePreset.h
        1/lib/Condiments/CondimentMaker.h
)

add_executable(1 ${SOURCE_FILES_1})

add_executable(1_test ${TEST_SOURCE_FILES_1})

target_link_libraries(1_test gtest_main)
enable_testing()
add_test(NAME 1_test COMMAND 1_test)

# Задание 2
set(SOURCE_FILES_1
        2/cmd/main.cpp
        2/lib/Condiment.h
        2/lib/Beverage.h
        2/lib/IBeverage.h
        2/lib/Beverages/Cofee.h
        2/lib/Beverages/Cappucciono.h
        2/lib/Beverages/Latte.h
        2/lib/Beverages/Tea.h
        2/lib/Beverages/Milkshake.h
        2/lib/Condiments/Cinnamon.h
        2/lib/Condiments/Lemon.h
        2/lib/Condiments/IceCubes.h
        2/lib/Condiments/Syrup.h
        2/lib/Condiments/ChocolateCrumbs.h
        2/lib/Condiments/CoconutFlakes.h
        2/lib/InfoByType.h
        2/lib/Beverages/LattePreset.h
        2/lib/Beverages/CappuccinoPreset.h
        2/lib/Beverages/TeaPreset.h
        2/lib/Beverages/MilkshakePreset.h
        2/lib/Condiments/CondimentMaker.h
        2/lib/Condiments/Cream.h
        2/lib/Condiments/Chocolate.h
        2/lib/Condiments/Liquor.h
        2/lib/Condiments/LiquorPreset.h
)

set(TEST_SOURCE_FILES_1
        2/test/testProvider.cpp
        2/lib/Condiment.h
        2/lib/Beverage.h
        2/lib/IBeverage.h
        2/lib/Beverages/Cofee.h
        2/lib/Beverages/Cappucciono.h
        2/lib/Beverages/Latte.h
        2/lib/Beverages/Tea.h
        2/lib/Beverages/Milkshake.h
        2/lib/Condiments/Cinnamon.h
        2/lib/Condiments/Lemon.h
        2/lib/Condiments/IceCubes.h
        2/lib/Condiments/Syrup.h
        2/lib/Condiments/ChocolateCrumbs.h
        2/lib/Condiments/CoconutFlakes.h
        2/lib/InfoByType.h
        2/lib/Beverages/LattePreset.h
        2/lib/Beverages/CappuccinoPreset.h
        2/lib/Beverages/TeaPreset.h
        2/lib/Beverages/MilkshakePreset.h
        2/lib/Condiments/CondimentMaker.h
        2/lib/Condiments/Cream.h
        2/lib/Condiments/Chocolate.h
        2/lib/Condiments/Liquor.h
        2/lib/Condiments/LiquorPreset.h
)

add_executable(2 ${SOURCE_FILES_1})

add_executable(2_test ${TEST_SOURCE_FILES_1})

target_link_libraries(2_test gtest_main)
enable_testing()
add_test(NAME 2_test COMMAND 2_test)

# Задание 3
set(SOURCE_FILES_1
        3/cmd/main.cpp
        3/lib/IO/IInputDataStream.h
        3/lib/IO/IOutputDataStream.h
        3/lib/IO/Streams/CFileOutputStream.h
        3/lib/IO/Streams/CMemoryOutputStream.h
        3/lib/IO/Streams/CFileInputStream.h
        3/lib/IO/Streams/CMemoryInputStream.h
        3/lib/IO/Modifications/EnctyptDecorator.h
        3/lib/IO/Modifications/COutputDataStreamDecorator.h
        3/lib/IO/Modifications/UtilsFunc.h
        3/lib/IO/Modifications/DecryptDecorator.h
        3/lib/IO/Modifications/DecompressDecorator.h
        3/lib/IO/Modifications/CompressDecorator.h
        3/lib/IO/Modifications/RLE.h
        3/lib/transform/Handler.h
)

set(TEST_SOURCE_FILES_1
        3/test/testProvider.cpp
        3/lib/IO/IInputDataStream.h
        3/lib/IO/IOutputDataStream.h
        3/lib/IO/Streams/CFileOutputStream.h
        3/lib/IO/Streams/CMemoryOutputStream.h
        3/lib/IO/Streams/CFileInputStream.h
        3/lib/IO/Streams/CMemoryInputStream.h
        3/lib/IO/Modifications/EnctyptDecorator.h
        3/lib/IO/Modifications/COutputDataStreamDecorator.h
        3/lib/IO/Modifications/UtilsFunc.h
        3/lib/IO/Modifications/DecryptDecorator.h
        3/lib/IO/Modifications/DecompressDecorator.h
        3/lib/IO/Modifications/CompressDecorator.h
        3/lib/IO/Modifications/RLE.h
        3/lib/transform/Handler.h
)

add_executable(3 ${SOURCE_FILES_1})

add_executable(3_test ${TEST_SOURCE_FILES_1})

target_link_libraries(3_test gtest_main)
enable_testing()
add_test(NAME 3_test COMMAND 3_test)
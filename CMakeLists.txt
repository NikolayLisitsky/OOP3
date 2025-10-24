cmake_minimum_required(VERSION 3.14)
project(lab3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Собираем библиотеку из всех .cpp в src/
file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_library(${PROJECT_NAME}_lib ${SRC_FILES})
target_include_directories(${PROJECT_NAME}_lib PUBLIC include)

# Основной исполняемый файл
add_executable(${PROJECT_NAME}_exe main.cpp)
target_link_libraries(${PROJECT_NAME}_exe PRIVATE ${PROJECT_NAME}_lib)

# Тесты
enable_testing()
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME}_tests test/tests.cpp)
target_link_libraries(${PROJECT_NAME}_tests
    PRIVATE
        ${PROJECT_NAME}_lib
        GTest::gtest
        GTest::gtest_main
        Threads::Threads
)
add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests)
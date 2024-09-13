cmake_minimum_required(VERSION 3.0.0)
project(viier VERSION 0.1.0)

include(CTest)
enable_testing()

# Adiciona os arquivos de cabeçalho
include_directories(include)
include_directories(types)

# Adiciona as classes .cpp
add_library(FileManager source/FileManager/fileManager.cpp)
add_library(Sort source/Sort/sort.cpp)

# Adiciona os testes para a classe1
add_executable(test1_FileManager source/FileManager/test1.cpp)
add_executable(test2_FileManager source/FileManager/test2.cpp)

# Adiciona os testes para a classe2
add_executable(test1_Sort source/Sort/test1.cpp)
add_executable(test2_Sort source/Sort/test2.cpp)


# Linka as classes FileManager e Sort com seus respectivos testes
target_link_libraries(test1_FileManager FileManager)
target_link_libraries(test2_FileManager FileManager)

target_link_libraries(test1_Sort Sort)
target_link_libraries(test2_Sort Sort)


# Inclui a pasta build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../build)

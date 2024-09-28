cmake_minimum_required(VERSION 3.10)
project(viier VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

# Incluir os arquivos de cabeçalho e tipos
include_directories(${PROJECT_SOURCE_DIR}/source/include)
include_directories(${PROJECT_SOURCE_DIR}/source/types)

# Ativar suporte a testes
include(CTest)
enable_testing()

# Adicionar as bibliotecas .cpp
add_library(FileManager source/lib/FileManager/fileManager.cpp)
add_library(Quicksort source/lib/Quicksort/quicksort.cpp)

# Configurar testes da classe FileManager
add_executable(test1_FileManager source/lib/FileManager/test1.cpp)
add_executable(test2_FileManager source/lib/FileManager/test2.cpp)
add_executable(test3_FileManager source/lib/FileManager/test3.cpp)

# Vincular a biblioteca FileManager aos seus testes
target_link_libraries(test1_FileManager FileManager)
target_link_libraries(test2_FileManager FileManager)
target_link_libraries(test3_FileManager FileManager)

# Garantir que os arquivos de teste sejam considerados como testes
add_test(NAME test1_FileManager COMMAND test1_FileManager)
add_test(NAME test2_FileManager COMMAND test2_FileManager)
add_test(NAME test3_FileManager COMMAND test3_FileManager)

# Configurar testes da classe Quicksort
add_executable(test1_Quicksort source/lib/Quicksort/test1.cpp)
add_executable(test2_Quicksort source/lib/Quicksort/test2.cpp)

# Vincular a biblioteca Quicksort aos seus testes
target_link_libraries(test1_Quicksort Quicksort FileManager) # Adiciona FileManager aqui se necessário
target_link_libraries(test2_Quicksort Quicksort FileManager) # Adiciona FileManager aqui se necessário

# Adicionar os testes de Quicksort mais tarde, quando implementados
add_test(NAME test1_Quicksort COMMAND test1_Quicksort)
add_test(NAME test2_Quicksort COMMAND test2_Quicksort)

# Adicionar o executável principal
add_executable(viier_exec source/main.cpp)
target_link_libraries(viier_exec FileManager Quicksort) # Vincula ambas as bibliotecas

# Especificar o diretório de saída para executáveis
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../build)

# Configurar o projeto e a versão
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

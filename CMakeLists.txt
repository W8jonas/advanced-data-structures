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
#add_library(Sort source/lib/Sort/sort.cpp)



# Configurar testes da classe FileManager
add_executable(test1_FileManager source/lib/FileManager/test1.cpp)
add_executable(test2_FileManager source/lib/FileManager/test2.cpp)

# Vincular a biblioteca FileManager aos seus testes
target_link_libraries(test1_FileManager FileManager)
target_link_libraries(test2_FileManager FileManager)

# Garantir que os arquivos de teste sejam considerados como testes
add_test(NAME test1_FileManager COMMAND test1_FileManager)
add_test(NAME test2_FileManager COMMAND test2_FileManager)



# Configurar testes da classe Sort (comentado por enquanto)
#add_executable(test1_Sort source/lib/Sort/test1.cpp)
#add_executable(test2_Sort source/lib/Sort/test2.cpp)

# Vincular a biblioteca Sort aos seus testes (comentado por enquanto)
#target_link_libraries(test1_Sort Sort)
#target_link_libraries(test2_Sort Sort)

# Adicionar os testes de Sort mais tarde, quando implementados
#add_test(NAME test1_Sort COMMAND test1_Sort)
#add_test(NAME test2_Sort COMMAND test2_Sort)


# Adicionar o executável principal
add_executable(viier_exec source/main.cpp)
target_link_libraries(viier_exec FileManager)



# Especificar o diretório de saída para executáveis
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../build)

# Configurar o projeto e a versão
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


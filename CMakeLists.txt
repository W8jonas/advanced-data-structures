cmake_minimum_required(VERSION 3.10)
project(viier VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

# Incluir os arquivos de cabeçalho e tipos
include_directories(${PROJECT_SOURCE_DIR}/source/include)
include_directories(${PROJECT_SOURCE_DIR}/source/types)
include_directories(${PROJECT_SOURCE_DIR}/source/lib/Mergesort)
include_directories(${PROJECT_SOURCE_DIR}/source/lib/Quicksort)
include_directories(${PROJECT_SOURCE_DIR}/source/lib/Heapsort)
include_directories(${PROJECT_SOURCE_DIR}/source/lib/RedBlackTree)
include_directories(${PROJECT_SOURCE_DIR}/source/lib/BTree)

# Ativar suporte a testes
include(CTest)
enable_testing()

# Adicionar as bibliotecas .cpp
add_library(FileManager source/lib/FileManager/fileManager.cpp)
# add_library(Quicksort source/lib/Quicksort/quicksort.tpp)
add_library(Metrics source/lib/Metrics/metrics.cpp)
# add_library(Mergesort source/lib/Mergesort/mergesort.tpp)
# add_library(Heapsort source/lib/Heapsort/heapsort.tpp)
add_library(Hash source/lib/Hash/hash.cpp)
add_library(Huffman source/lib/Huffman/huffman.cpp)  # Biblioteca Huffman
#add_library(Compress source/compress.cpp)  # Biblioteca Compressão
#target_link_libraries(Compress Huffman)  # Vincula Compress à biblioteca Huffman
#add_library(BTree source/lib/BTree/BTree.tpp) # Adicionar a biblioteca BTree
#add_library(RedBlackTree source/lib/RedBlackTree/RedBlackTree.tpp) # Adiciona a Red Black Tree


# Configurar testes da classe FileManager
add_executable(test1_FileManager source/lib/FileManager/test1.cpp)
add_executable(test2_FileManager source/lib/FileManager/test2.cpp)
add_executable(test3_FileManager source/lib/FileManager/test3.cpp)
target_link_libraries(test1_FileManager FileManager)
target_link_libraries(test2_FileManager FileManager)
target_link_libraries(test3_FileManager FileManager)
add_test(NAME test1_FileManager COMMAND test1_FileManager)
add_test(NAME test2_FileManager COMMAND test2_FileManager)
add_test(NAME test3_FileManager COMMAND test3_FileManager)

# Configurar testes da classe Quicksort
add_executable(test1_Quicksort source/lib/Quicksort/test1.cpp)
add_executable(test2_Quicksort source/lib/Quicksort/test2.cpp)
target_link_libraries(test1_Quicksort Metrics FileManager)
target_link_libraries(test2_Quicksort Metrics FileManager)
add_test(NAME test1_Quicksort COMMAND test1_Quicksort)
add_test(NAME test2_Quicksort COMMAND test2_Quicksort)

# Configurar testes da classe Metrics
add_executable(test1_Metrics source/lib/Metrics/test1.cpp)
add_executable(test2_Metrics source/lib/Metrics/test2.cpp)
add_executable(test3_Metrics source/lib/Metrics/test3.cpp)
target_link_libraries(test1_Metrics Metrics)
target_link_libraries(test2_Metrics Metrics)
target_link_libraries(test3_Metrics Metrics)
add_test(NAME test1_Metrics COMMAND test1_Metrics)
add_test(NAME test2_Metrics COMMAND test2_Metrics)
add_test(NAME test3_Metrics COMMAND test3_Metrics)

# Configurar testes da classe Mergesort
add_executable(test1_Mergesort source/lib/Mergesort/test1.cpp)
target_link_libraries(test1_Mergesort Metrics FileManager)
add_test(NAME test1_Mergesort COMMAND test1_Mergesort)

# Configurar testes da classe Heapsort
add_executable(test1_Heapsort source/lib/Heapsort/test1.cpp)
target_link_libraries(test1_Heapsort Metrics FileManager)
add_test(NAME test1_Heapsort COMMAND test1_Heapsort)

# Incluir testes da classe RedBlackTree
add_executable(test1_RedBlack source/lib/RedBlackTree/test1.cpp)
target_link_libraries(test1_RedBlack Metrics)
add_test(NAME test1_RedBlack COMMAND test1_RedBlack)

# Incluir testes da classe BTree
add_executable(test1_BTree source/lib/BTree/test1.cpp)
target_link_libraries(test1_BTree Metrics)
add_test(NAME test1_BTree COMMAND test1_BTree)

# Incluir testes da classe Huffman
add_executable(test1_Huffman source/lib/Huffman/test1.cpp) 
target_link_libraries(test1_Huffman Huffman FileManager) 
add_test(NAME test1_Huffman COMMAND test1_Huffman)


# Adiciona os executáveis principais
add_executable(viier_exec source/main.cpp)
add_executable(compara_sort source/compara_sort.cpp)
add_executable(compara_tree source/compara_tree.cpp)
add_executable(compress source/compress.cpp)
add_executable(vote_average_hash source/vote_average_hash.cpp)

# Certifique-se de que todas as bibliotecas necessárias estão vinculadas ao executável principal
target_link_libraries(viier_exec FileManager Metrics Huffman)
target_link_libraries(compara_sort FileManager Metrics)
target_link_libraries(compara_tree FileManager Metrics)
target_link_libraries(compress FileManager Metrics Huffman)
target_link_libraries(vote_average_hash FileManager Metrics Hash)



# Especificar o diretório de saída para executáveis
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../build)

# Configurar o projeto e a versão para CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

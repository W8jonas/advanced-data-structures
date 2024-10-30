
# **TRABALHO ESTRUTURA DE DADOS II**


1. **Introdução**

Neste trabalho, utilizaremos uma base de dados do Kaggle que contem informações de contém diversas informações sobre aproximadamente 45 mil filmes, incluindo metadados detalhados. O conjunto de dados é composto por arquivos CSV que abrangem informações como:

* Dados gerais de filmes (títulos, datas de lançamento, gêneros)  
* Avaliações e dados de usuários do TMDb e do IMDb  
* Palavras-chave e empresas de produção.

Os dados estão armazenados no arquivo source/data/movies_dataset.csv.

2. **Objetivos**

O objetivo principal deste trabalho é manipular uma base de dados real de médio porte usando as estruturas de dados vistas na disciplina. 

* Manipular adequadamente arquivos em modo texto e binário.  
* Compreender, implementar corretamente algoritmos de ordenação, indexação e compressão de dados.  
* Analisar o desempenho dos algoritmos implementados segundo o referencial teórico adquirido na disciplina;  
* Apresentar os resultados obtidos com o trabalho de maneira formal.

3. **Desenvolvimento** 

As etapas para o desenvolvimento do trabalho são descritas abaixo.

***Etapa 1: Definição de uma estrutura de dados***

Nesta etapa, deve ser proposto um tipo abstrato de dados (TAD) para a leitura e armazenamento dos filmes.


***Etapa 2: Processamento dos dados***

Nessa fase, deve ser analisado o arquivo CSV fornecido e desenvolver:

1) Uma rotina para convertê-lo em um arquivo binário. O programa deve ler o arquivo de texto, extrair cada atributo de um filme e salvar essas informações no arquivo binário. Tratamento de exceções é necessário para alguns campos, e o grupo tem liberdade para escolher como lidar com esses casos.   
2) Pelo menos duas rotinas extrações de dados para o arquivo binário:	  
   1) Extrair todos os filmes para um vetor de filmes.  
   2) Extrair N filmes aleatórios da base de dados (N < numero total de filmes) para um vetor de filmes.

***Etapa 3: Análise de algoritmos de ordenação***

Nesta etapa, o objetivo é comparar o desempenho de diferentes algoritmos de ordenação quando aplicados sobre os dados pré-processados. O programa deverá seguir os seguintes passos:

1) importar conjuntos de N registros aleatórios do arquivo binário gerado pelo pré-processamento  
2) realizar a ordenação desses registros, utilizando como chave de ordenação ***popularity***. Durante a ordenação, **deverão ser computados** o **total de comparações de chaves** e o **total de movimentações de chaves**. Além disso, o **tempo de execução do algoritmo** deverá ser medido.

Para gerar as estatísticas de desempenho, o programa deverá executar os passos acima para 3 diferentes conjuntos de N registros aleatórios. Ao final, compute as médias de cada uma das métricas (comparações, movimentações e tempo). O programa deverá realizar a simulação descrita acima para os seguintes valores de N:

5000  
10000  
20000  
40000

Para esta etapa, o executável deverá ser chamado de compara_sort.cpp. O programa deve fazer a leitura dos valores de N (a lista acima) a partir de um arquivo chamado `compara_sort.dat`. Salve todos os resultados obtidos em um arquivo `compara_sort.out`, contendo tanto os resultados individuais quanto a média final.

Os métodos selecionados para a ordenação foram: 

* Mergesort  
* Quicksort   
* Heapsort   
  


***Aplicação - Gêneros mais frequentes***

Aqui deve-se criar um *TAD Hash* para auxiliar na contagem de filmes classificados por vote_average. O programa deve ler N filmes aleatórios e contar quantos filmes receberam um determinado vote_average.

Utilize uma tabela *hash* para armazenar os vote_average dos filmes. A função *hash* deve ser rápida e gerar poucas colisões, além de ocupar a tabela uniformemente. Escolha um método adequado para tratar colisões.

Para cada filme lido, insira a string de vote_average na tabela *hash*. No final, o programa deve imprimir o número de filmes para 5 maiores vote_average, ordenados em ordem crescente de frequência. Use o algoritmo de ordenação com melhor desempenho da Etapa 2.

Nomeie seu executável com vote_average*_hash*. Seu programa deve ler do arquivo de entrada vote_average.dat o valor de N. O resultado deve ser escrito no arquivo vote_average.txt.


***Etapa 4 - Análise das estruturas balanceadas***

Seu grupo deverá implementar duas estruturas de dados em árvore: 

- Árvore Vermelho-Preto  
- Árvore B. 

O tipo abstrato de dados deve implementar as operações de inserção e busca (não há necessidade de implementar a remoção). Cada nó deve armazenar o id da avaliação e a sua localização no arquivo binário. A ordenação da árvore será determinada pelo id. As outras informações do registro, quando necessárias, serão recuperadas através do acesso ao disco. 

Nesta etapa, você irá comparar o desempenho das estruturas implementadas quanto às operações de inserção e busca. O seu programa deverá seguir os seguintes passos:

1. importar conjuntos de N registros aleatórios do arquivo binário gerado pelo pré-processamento;  
2. realizar a inserção desses registros na estrutura. Durante a inserção, deverão ser computados o total de comparações de chaves e o tempo de execução;  
3. realizar a busca de outros B registros aleatórios na estrutura. Durante as buscas, também deverão ser computados o total de comparações de chaves e o tempo de execução;

Para gerar as estatísticas de desempenho, o programa deverá executar os passos acima, minimamente, M = 3 vezes, para N = 20000. Ao final, compute as médias de cada uma das métricas (comparações e tempo) obtidas para as M execuções.   
As estruturas de dados que devem ser analisadas são as seguintes:

* Árvore Vermelho-Preto  
* Árvore B (m = 20)  
* Árvore B (m = 200)

Considere que a ordem m da árvore B representa o número **máximo** de filhos em cada nó (exceto a raiz), conforme visto em sala de aula. **Não há necessidade de se manter preso aos valores de m especificados acima**, o grupo pode adotar valores diferentes (ou mais que dois valores) para os testes. Tenha o cuidado, no entanto, de escolher valores que permitam avaliar a diferença no desempenho para árvores de ordem baixa e árvores de ordem alta.

O programa deve se chamar compara_tree e deve salvar todos os resultados obtidos em um arquivo compara_tree.txt, contendo tanto os resultados individuais quanto a média final.

***Etapa 5 -  Compressão dos Overviews***

Deve-se implementar o método de compressão de Huffman para o processamento de uma cadeia de caracteres aleatória. Esta cadeia de caracteres será formada pela concatenação dos overview dos N registros aleatórios importados. Deve-se implementar as rotinas de compressão e descompressão.

O programa deve se chamar compress e possuir opções de menu para:

* Comprimir um conjunto de N (definido pelo usuário) review_overview aleatórios e salvar dois arquivos: overviewOrd.txt (texto original)e overviewComp.bin (texto comprimido);  
* Descomprimir o arquivo overviewComp.bin e salvar o texto resultante em um arquivo overviewDecomp.bin;

4. **Relatório Final**

O grupo deverá confeccionar um relatório completo contendo todas as análises feitas. Este relatório deve conter, obrigatoriamente, os seguintes itens:

* detalhamento das atividades realizadas por cada membro do grupo;  
* decisões de implementação;  
* toda e qualquer referência utilizada no desenvolvimento do trabalho.



5. **Exigências**

O trabalho deverá, obrigatoriamente, atender aos seguintes requisitos:

* Implementação em C ou C++  
* O projeto deve ser compilável e executável via linha de comando. Não conte com a presença de IDEs como Code::Blocks ou Visual Studio. Caso seu grupo opte por utilizar algum ambiente de desenvolvimento, certifique-se de que o projeto enviado possa também ser facilmente compilado em um sistema operacional Linux sem esses ambientes instalados. Forneça instruções claras e precisas de compilação e execução pela linha de comando. **Recomenda-se utilizar algum Makefile, CMake ou script para a compilação.** Caso o grupo julgue necessário, é possível solicitar que o professor verifique as instruções de compilação **antes** do prazo final de envio.  
* **Nenhum trabalho será aceito após o prazo.**  
* **O programa desenvolvido deve permitir que o usuário entre com o caminho do diretório que contém os arquivos de dados como um argumento na linha de comando.**  Veja o Exemplo:

| $ ./programa /diretorio/contendo/arquivos/entrada  |
| :---- |

* O programa deve procurar pela existência do arquivo binário na pasta (gerado na Parte 1 do trabalho). Se não existir, deve encerrar, emitindo uma mensagem de erro.  
* Não é permitida a utilização de bibliotecas externas. Os algoritmos de ordenação devem ser implementados pelo grupo. Caso haja dúvida quanto à utilização de alguma função ou biblioteca, entre em contato com o professor.  
* Obviamente, todo código deve ser de autoria do grupo. Não é permitida a utilização de códigos de terceiros ou de outros grupos. É permitida a pesquisa por estratégias para a solução dos problemas (e as r**eferências utilizadas nessas pesquisas devem constar do relatório**), porém a apropriação de código alheio não será aceita. **Qualquer tentativa de plágio identificada resultará em nota zero. Os códigos fontes serão analisados pelo sistema Moss ([http://theory.stanford.edu/\~aiken/moss/](http://theory.stanford.edu/~aiken/moss/))**  
* **Todos os componentes do grupo devem submeter suas contribuições no GitHub via *commits***.  Uma forma de avaliação individual será os históricos de submissão. Por tanto, submissão por upload de arquivos serão penalizadas.


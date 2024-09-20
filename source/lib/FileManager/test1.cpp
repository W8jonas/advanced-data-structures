#include <iostream>
#include <string>
#include "fileManager.h"

using namespace std;

// Testa instanciar fileManager com parâmetros errados

int main()
{
  try
  {
    fileManager manager("", "");
    // Se não lançar exceção, o teste falhou
    return -1;
  }
  catch (const invalid_argument &e)
  {
    // Se a exceção correta for capturada, o teste passou
    return 0;
  }
  catch (...)
  {
    // Se qualquer outra exceção for lançada, o teste falhou
    return -1;
  }
}

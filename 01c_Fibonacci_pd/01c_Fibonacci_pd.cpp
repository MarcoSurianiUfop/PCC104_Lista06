/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                 LISTA 06 - ATIVIDADES PRÁTICAS - EXERCÍCIO 01C
                             FIBONACCI PROG DINAMICA
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <iomanip>  // setw
#include <vector>

using namespace std;

int fibonacci_pd2(int n, vector<int>& Cache) {
    /*  Implementação do FIBONACCI PROG DINAMICA
    * Retorna o n-ésimo nro de Fibonacci
    * ENTRADAS:
    * Inteiro n
    * Ponteiro para Vetor de inteiros Cache com cache
    */

    // Caso o n-ésimo nro de fibonacci já tenha sido calculado, retorne-o
    if (Cache[n] > 0) { return Cache[n]; }

    // Caso n seja igual a 0 ou 1, atualize Cache com 1
    if (n == 0 or n == 1) { Cache[n] = 1; }
    else {
        // Caso n >= 2, retorne a soma dos dois nros de Fibonacci anteriores
        Cache[n] = fibonacci_pd2(n - 1, Cache) + fibonacci_pd2(n - 2, Cache);
    }

    // Retorne o n-ésimo nro de fibonacci
    return Cache[n];
}

int fibonacci_pd(int n) {
    /*  Implementação do FIBONACCI PROG DINAMICA - Versão usuário
    * Retorna o n-ésimo nro de Fibonacci
    * ENTRADA:
    * Inteiro n
    */

    // Cria um cache com n+1 elementos iguais a -1
    vector<int> Cache(n + 1, -1);

    // Retorna o resultado da função fibonacci_pd2 com auxílio do Cache
    return fibonacci_pd2(n, Cache);
}

int main()
{
    cout << "Fibonacci Prog Dinamica" << endl;

    // Calcula e imprime os 20 primeiros números de fibonacci
    for (int i = 0; i <= 20; i++) {
        cout << "Fibonacci(" << setw(2) << i << ") = " << fibonacci_pd(i) << endl;
    }

}

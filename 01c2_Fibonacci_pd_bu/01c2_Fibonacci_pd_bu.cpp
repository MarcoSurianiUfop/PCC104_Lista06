/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                 LISTA 06 - ATIVIDADES PRÁTICAS - EXERCÍCIO 01C
                       FIBONACCI PROG DINAMICA - Bottom-Up
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <iomanip>  // setw
#include <vector>

using namespace std;

int fibonacci_pd_bu(int n) {
    /*  Implementação do FIBONACCI PROG DINAMICA - Bottom-Up
    * Retorna o n-ésimo nro de Fibonacci
    * ENTRADA:
    * Inteiro n
    */

    // Caso n seja igual a 0 ou 1, retorne 1
    if (n == 0 or n == 1) { return 1; }

    // Cria um cache com n+1 elementos iguais a -1
    vector<int> Cache(n + 1, -1);
    Cache[0] = 1;
    Cache[1] = 1;

    // Calcula Fibo(2) até Fibo(n)
    for (int i = 2; i <= n; i++) { Cache[i] = Cache[i - 1] + Cache[i - 2]; }

    // Retorne o n-ésimo nro de fibonacci
    return Cache[n];
}

int main()
{
    cout << "Fibonacci Prog Dinamica - Bottom-Up" << endl;

    // Calcula e imprime os 20 primeiros números de fibonacci
    for (int i = 0; i <= 20; i++) {
        cout << "Fibonacci(" << setw(2) << i << ") = " << fibonacci_pd_bu(i) << endl;
    }

}

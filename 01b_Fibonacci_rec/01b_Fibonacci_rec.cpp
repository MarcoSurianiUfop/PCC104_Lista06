/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                 LISTA 06 - ATIVIDADES PRÁTICAS - EXERCÍCIO 01B
                               FIBONACCI RECURSIVO
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <iomanip>  // setw

using namespace std;

int fibonacci_rec(int n) {
    /*  Implementação do FIBONACCI RECURSIVO
    * Retorna o n-ésimo nro de Fibonacci 
    * ENTRADA:
    * Inteiro n
    */

    // Caso n seja igual a 0 ou 1, retorne 1
    if (n == 0 or n == 1) { return 1; }

    // Caso n >= 2, retorne a soma dos dois nros de Fibonacci anteriores
    return fibonacci_rec(n - 1) + fibonacci_rec(n - 2);
}

int main()
{   
    cout << "Fibonacci Recursivo" << endl;

    // Calcula e imprime os 20 primeiros números de fibonacci
    for (int i = 0; i <= 20; i++) {
        cout << "Fibonacci(" << setw(2) << i << ") = " << fibonacci_rec(i) << endl;
    }

}

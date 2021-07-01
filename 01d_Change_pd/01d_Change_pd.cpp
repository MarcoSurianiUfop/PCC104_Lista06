/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                 LISTA 06 - ATIVIDADES PRÁTICAS - EXERCÍCIO 01D
                           CHANGE MAKING PROG DINAMICA
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <iomanip>  // setw
#include <vector>
#include <limits>   // infinito

using namespace std;

int changemaking_pd(int n, vector<int>& Denom) {
    /*  Implementação do CHANGE MAKING PROBLEM PROG DINAMICA
    * Retorna o número mínimo de moeadas a atingir um valor
    * ENTRADAS:
    * Inteiro n com valor a ser atingido
    * Ponteiro p/ Vetor de inteiros Denom com denominacoes das moedas
    * SAÍDA:
    * The minimum number of coins that add up to n
    */

    // m: quantidade de moedas
    int m = Denom.size();

    // Cria um vetor com n+1 elementos iguais a -1 p/ resultados
    // Para valor 0 é necessário 0 moedas
    vector<int> F(n + 1, -1);
    F[0] = 0;

    // Inicializa variáveis auxiliares
    int temp, j;

    // Para valores entre 1 e n
    for (int i = 1; i <= n; i++) {
        // Valores iniciais das variáveis auxiliares
        temp = std::numeric_limits<int>::max();
        j = 0; // Itera as denominações das moedas

        // Faça para todas as moedas j \in D, 
        // desde que o valor atual i seja menor que a j-ésima denominação
        while (j < m and i >= Denom[j]) {
            // F[i - Denom[j]]: quantas moedas são necessárias para fazer o
            // troco do valor [i] menos a j-ésima denominação?
            // Minimize tal expressão em função de j
            temp = min(F[i - Denom[j]], temp);
            j++;
        }
        // Some 1 ao valor mínimo encontrado (é preciso mais uma moeda
        // além do valor mínimo)
        F[i] = temp + 1;
    }

    return F[n];
}

int main()
{
    // Denominações: declara e imprime
    vector<int> Denom = {1, 5, 10};
    cout << "Denominations: ";
    for (int d : Denom) { cout << setw(2) << d << " ;"; }
    cout << endl;


    // Calcula e imprime os 20 primeiros trocos
    for (int i = 0; i <= 20; i++) {
        cout << "Change(" << setw(2) << i << ") = " << changemaking_pd(i, Denom) << endl;
    }

}

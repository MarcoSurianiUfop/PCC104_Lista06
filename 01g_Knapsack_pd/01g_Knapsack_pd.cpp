/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                 LISTA 06 - ATIVIDADES PRÁTICAS - EXERCÍCIO 01G
                             KNAPSACK PROG DINAMICA
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <iomanip>  // setw
#include <vector>

using namespace std;

void printKnapSack(vector< vector<int> >& M, int& W);


int MFKnapSack(vector<vector<int>>& I, vector<vector<int>>& F, int i, int j) {
    /*  Implementação do método da função de memória para o KNAPSACK PROBLEM 
    * Resolução via Prog Dinamica - RECURSIVO (TOP-DOWN)
    * ENTRADAS:
    * Ponteiro para matriz I (2, n) com pesos e valores de cada
    * item, composto por inteiros
    * Ponteiro para matriz F (n+1, W+1) com resultado do valor máximo para cada
    * combinação de quantidade de itens (0 a n) e peso (0 a W) possível
    * Inteiro i com a qtd de itens na mochila que se deseja saber o valor max
    * Inteiro j com o peso máximo para o qual se deseja saber o valor máximo
    * SAÍDA:
    * Inteiro com o valor final da mochila
    */

    // Caso F[i][j] >= 0, posição já foi calculada: retorne tal valor
    // Caso contrário, calcule tal valor
    if (F[i][j] < 0) {
        /* O valor de uma posição é:
        *           { max[F(i-1,j), vi+F(i-1,j-wi)]  se j >= wi
        * F[i][j] = {
        *           { F(i-1,j)                       se j < wi
        */
        int v1 = MFKnapSack(I, F, i - 1, j);
        if (j < I[0][i-1]) { F[i][j] = v1; }
        else { 
            F[i][j] = max(v1, I[1][i-1] + MFKnapSack(I, F, i - 1, j - I[0][i-1]));
        }
    }
    return F[i][j];
}

int KnapSackProblem_pd(vector<vector<int>>& I, int& W) {
    /*  Implementação do KNAPSACK PROBLEM via Prog Dinamica - RECURSIVO TOP-DOWN
    * Encontra a forma de encher uma mochila com os itens mais valiosos
    * possível, dada sua capacidade e um lista de itens com peso e valor
    * ENTRADAS:
    * Ponteiro para matriz I (vetor de vetores) com pesos e valores de cada
    * item, composto por inteiros
    * Ponteiro para inteiro W com capacidade da mochila
    * SAÍDA:
    * Inteiro com o valor final da mochila
    */

    // n: quantidade de itens
    int n = I[0].size();

    // Cria um matriz de resultados F com (n+1, W+1) elementos iguais a -1 
    // Primeira linha e primeira coluna contém apenas 0s
    vector<vector<int>> F;
    vector<int> f1(W + 1, 0);
    F.push_back(f1);
    vector<int> f2(W + 1, -1);
    f2[0] = 0;
    for (int i = 1; i <= n; i++) { F.push_back(f2); }

    return MFKnapSack(I, F, n, W);
}

int main() {
    // Cria uma Matriz M (vetor de vetores) com pesos e valores
    // Primeira linha: pesos, Segunda linha: valores
    vector< vector<int> > V = { { 14,  6,  8, 10 },
                                { 42, 12, 40, 25 } };

    // Declara a capacidade
    int W = 20;

    // Imprime capacidade e itens (peso, valor) da mochila
    printKnapSack(V, W);

    // Calcula valor máximo e itens que o compõem e determina a qtdade de itens
    int max_knap = KnapSackProblem_pd(V, W);

    // Imprime o maior valor possível e os itens que compõem tal mochila
    cout << "Maximum Value: " << max_knap << endl;

    return 0;
}

void printKnapSack(vector< vector<int> >& M, int& W) {
    /*  Função para Imprimir KnapSack
    * ENTRADAS:
    * Ponteiro para Matriz M (vetor de vetores) com elementos de qualquer datatype
    * Ponteiro para objeto W de qualquer datatype com capacidade da mochila
    */

    // Determina a quantidade de itens em I
    int n = M[0].size();

    // Imprime cabeçalho
    cout << "Capacidade da Mochila (Peso): " << W << endl
        << "Itens da Mochila (Peso, Valor):" << endl;

    // Itera todos os itens da Matriz M
    for (int i = 0; i < n; i++)
        // Imprime par (peso, valor)
        cout << "(" << M[0][i] << " , " << M[1][i] << ")" << endl;
    cout << endl;
}

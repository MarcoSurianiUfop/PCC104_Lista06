/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                 LISTA 06 - ATIVIDADES PRÁTICAS - EXERCÍCIO 01E
                           COIN COLLECT PROG DINAMICA
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <iomanip>  // setw
#include <vector>

using namespace std;

int collect_pd(vector<vector<int>>& C) {
    /*  Implementação do COIN COLLECT PROG DINAMICA
    * Retorna o máximo de moedas que podem ser coletadas entre em um tabuleiro
    * ENTRADAS:
    * Ponteiro para Vetor de vetores inteiros C com tabuleiro
    * Dimensões C (n x m); Valores: 0 (sem moeda), 1 (com moeda)
    * SAÍDA:
    * Maior nro de moedas entre C(1,1) e C(n,m) podendo mover apenas para frente
    * (Não pode retorceder, apenas avançar)
    */

    // n, m: quantidade de linhas e colunas
    int n = C.size();
    int m = C[0].size();

    // Inicializando Matriz de resultados F com valores -1
    // Vetor auxiliar f possui m colunas iguais a -1
    vector<int> f;
    for (int i = 0; i < m; i++) { f.push_back(-1); }

    // Matriz F possui n linhas iguais a f
    vector<vector<int>> F;
    for (int i = 0; i < n; i++) { F.push_back(f); }

    // O resultado da 1a casa (0,0) é igual aà qtd de moeda em tal casa
    F[0][0] = C[0][0];

    // Preenche a primeira linha e a primeira coluna (anterior + qtd moeda)
    for (int i = 1; i < m; i++) { F[0][i] = F[0][i - 1] + C[0][i]; }
    for (int i = 1; i < n; i++) { F[i][0] = F[i - 1][0] + C[i][0]; }
    
    // Preenche as casas das linhas e colunas 2 em diante
    // Para cada linha, itere as colunas
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            // O resultado da casa é igual ao máximo entre os dois resultados
            // anteriores mais a qtd de moedas da casa
            F[i][j] = max(F[i - 1][j], F[i][j - 1]) + C[i][j];
        }
    }
    return F[n - 1][m - 1];
}

void print_tabuleiro(vector<vector<int>> C) {
    for (vector<int> ci : C) {
        for (int cj : ci) {
            if (cj == 0) { cout << "_"; }
            else { cout << "X"; }
        }
        cout << endl;
    }
}

int main()
{
    // Cria Tabuleiro
    vector<vector<int>> C = {   { 0,0,0,0,1,0 },
                                { 0,1,0,1,0,0 },
                                { 0,0,0,1,0,1 },
                                { 0,0,1,0,0,1 },
                                { 1,0,0,0,1,0 } };

    // Imprime tabuleiro
    cout << "Tabuleiro: " << endl;
    print_tabuleiro(C);

    // caulcula e imprime resultado
    cout << endl << "Maior quantidade de moedas: " << collect_pd(C) << endl;

}

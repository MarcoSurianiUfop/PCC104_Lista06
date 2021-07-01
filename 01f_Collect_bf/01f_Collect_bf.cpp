/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                 LISTA 06 - ATIVIDADES PRÁTICAS - EXERCÍCIO 01F
                            COIN COLLECT BRUTE FORCE
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <iomanip>  // setw
#include <vector>

using namespace std;

vector<int> decimal2binary(int dec, int n) {
    /*  Converte um decimal em binário com n dígitos
    * ENTRADAS:
    * Inteiro dec a ser convertido
    * Inteiro n com tamanho da saída
    * SAÍDA:
    * Vator de inteiros bin com tamanho n contendo dec em binário
    */

    // Inicializa a saída: vetor com n valores zero
    vector<int> bin(n, 0);

    // Indicador do dígito atual, começando pelo último (n-1)
    int i = n - 1;

    // Enquanto o valor dec for maior que 0, ele ainda pode ser dividido
    while (dec > 0) {
        // O dígito atual é o resto da divisão por 2 de dec
        bin[i] = dec % 2;

        // Reduz dec à metade, arredondando para baixo
        dec = (dec % 2 == 0) ? dec / 2 : (dec - 1) / 2;

        // Decrementa o dígito atual
        i--;
    }

    return bin;
}

int collect_bf(vector<vector<int>>& C) {
    /*  Implementação do COIN COLLECT BRUTE FORCE
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

    // Vetor de índice: quando 0: movimenta em n, quando 1: movimenta em m
    vector<int> I;
    // k: quantidade de movimentos disponíveis
    int k = n + m - 2;

    // Variáveis auxiliares
    int acc = 0, in = 0, im = 0, maxi = 0;

    // Para cada valor j < 2^k, converte j em binário com k bits
    for (int j = 0; j < pow(2, k); j++) {
        I = decimal2binary(j, k);

        // Índices 1 significa que movimenta no sentido de m
        // Cada trajetória pode se movimentar m-1 vezes no sentido de m
        // Logo a soma soma de 1s deve ser igual a m-1
        acc = 0;
        for (int i : I) { acc += i; }

        if (acc == m - 1) {
            // Caso I contenha uma trajetória válida, colete as moedas

            // Comece com C[0][0]
            acc = C[0][0];
            in = 0;
            im = 0;

            // Para cada posição de I, 
            for (int i : I) { 
                // movimente em n se 0, movimente em m se 1
                if (i == 0) { in += 1; }
                else { im += 1; }
                // Adicione a qtd de moedas da nova casa no acumulador
                acc += C[in][im];
            }
            // Guarda a maior qtd de moedas adquirida até então
            maxi = max(acc, maxi);
        }
    }

    return maxi;
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
    cout << endl << "Maior quantidade de moedas: " << collect_bf(C) << endl;

}

/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                 LISTA 06 - ATIVIDADES PRÁTICAS - EXERCÍCIO 03B
                             LE INSTANCIAS BRAZIL58
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <fstream>  // ifstream
#include <sstream>  // stringstream
#include <iomanip>  // setw
#include <string>
#include <vector>

using namespace std;

void printSolution(vector<vector<int>>& Matrix)
{
    for (vector<int> linha : Matrix) {
        for (int val : linha)
            cout << setw(4) << val << "  ";
        cout << endl;
    }
}

vector<vector<int>> readMatrix(string tsp_file, int nhead, int nnodes) {
    /* Lê arquivo tsp com matriz de distãncia entre cidades
    * ENTRADAS:
    * String com nome do arquivo
    * Inteiro nhead com número de linhas do cabeçalho (serão ignoradas)
    * Inteiro nnodes com tamanho da matriz (número de nós ou cidades)
    * SAÍDA:
    * Matriz nnodes x nnodes
    */

    // Cria matriz nnodes x nnodes preenchida com zeros
    vector<vector<int>> matrix(nnodes, vector<int>(nnodes, 0));

    // Recebe as linhas lidas
    string line;

    // Contador que indica a linha atual do arquivo
    int linecount = 0;

    // Linha da matriz e coluna inicial (ncol = nline + 1)
    int nline, ncol;

    // Valor auxiliar
    int val;

    // Stream do arquivo
    ifstream inputFile(tsp_file);

    while (inputFile) {
        // Pega uma linha
        getline(inputFile, line);

        // Atualiza linha atual
        linecount += 1;

        // Se linha atual for maior que cabeçalho e menor ou igual ao total
        if (linecount > nhead and linecount <= nhead + nnodes) {

            // Linha da matriz: linha atual - tamanho do cabeçalho -1
            nline = linecount - nhead - 1;
            ncol = nline + 1;

            // Itera os valores da linha
            stringstream stream(line);
            while (stream >> val) {
                // Acrescenta cada valor na matriz e incrementa a coluna
                matrix[ncol][nline] = val;
                matrix[nline][ncol] = val;
                ncol++;
            }
        }
    }

    return matrix;
}

int main()
{
    // Nome do arquivo
    string tsp_file = "brazil58.tsp"; // alternativa: gr17

    // Cabeçalho tem 7 linhas, matriz tem 58 cidades (nós)
    int nhead = 7;
    int nnodes = 58; // para gr17: 17

    // Lê o arquivo, guarda distâncias em matrix e imprime
    vector<vector<int>> matrix = readMatrix(tsp_file, nhead, nnodes);
    printSolution(matrix);

    return 0;
}

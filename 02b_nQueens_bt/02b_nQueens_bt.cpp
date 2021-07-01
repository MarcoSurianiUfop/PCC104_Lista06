/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                 LISTA 06 - ATIVIDADES PRÁTICAS - EXERCÍCIO 02B
                             NQUEENS - BACKTRACKING
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <iomanip>  // setw
#include <vector>

using namespace std;

class QueensBoard {
private:
    // Cria Tabuleiro
    vector<vector<bool>> B;

    // Check Linhas e Diagonais
    vector<vector<bool>> LC;
    vector<vector<bool>> DD;

    // Progresso
    vector<vector<int>> queenspos;
    int numqueens;

public:
    // Tamanho do Tabuleiro, variável pública para acesso rápido
    int n;

    // Construtor da classe
    QueensBoard(int k) {
        // Atualiza tamanho
        n = k;

        // Cria Tabuleiro: n linhas de n colunas, todas casas com false
        // Se casa = false: vazia
        // Se casa = true : preenchida com rainha
        B = vector<vector<bool>>(n, vector<bool>(n, false));

        // Check Linhas e Diagonais
        // Caso true, a linha, coluna ou diagonal corresponte está livre
        // Caso false, a linha, coluna ou diagonal corresponte está ocupada
        // LC: LC[0][l] controla as linhas l, LC[1][c] controla colunas c
        LC = vector<vector<bool>>(2, vector<bool>(n, true));
        // DD[0][d] controla as diagonais l+c-1
        // DD[1][d] controla as diagonais l-c+n
        DD = vector<vector<bool>>(2, vector<bool>(2 * n * n - 1, true));

        // Progresso
        // Vetor com as posições ocupadas por rainhas
        queenspos = vector<vector<int>>(2, vector<int>(n, -1));
        // Quantidade de rainhas posicionadas
        numqueens = 0;
    }

    // Adiciona uma rainha na posição l, c
    void add_Queen(int l, int c) {
        // Posição no Board alterada para true
        B[l - 1][c - 1] = true;

        // Bloqueia a linha, a coluna e as diagonais
        LC[0][l - 1] = false;
        LC[1][c - 1] = false;
        DD[0][l + c - 2] = false;
        DD[1][l - c + n - 1] = false;

        // Acrescenta a posição na lista de rainhas e incrementa numqueens
        queenspos[0][numqueens] = l;
        queenspos[1][numqueens] = c;
        numqueens += 1;
    }

    // Exclui uma rainha na posição l, c
    void del_Queen(int l, int c) {
        // Posição no Board alterada para true
        B[l - 1][c - 1] = false;

        // Desbloqueia a linha, a coluna e as diagonais
        LC[0][l - 1] = true;
        LC[1][c - 1] = true;
        DD[0][l + c - 2] = true;
        DD[1][l - c + n - 1] = true;

        // Decrementa numqueens e retira a posição na lista de rainhas
        numqueens -= 1;
        queenspos[0][numqueens] = -1;
        queenspos[1][numqueens] = -1;
    }

    // Checa posição l, c
    // Se casa preenchida, retorna false
    // Verifica se a linha, se a coluna e se as diagonais estão todas livres
    // Caso alguma linha, coluna ou diagonal esteja bloqueada, retorna false, 
    // caso contrário retorna true
    bool check_Position(int l, int c) {
        if (B[l - 1][c - 1]) { return false; }
        return (LC[0][l - 1] and LC[1][c - 1] and DD[0][l + c - 2] and DD[1][l - c + n - 1]);
    }

    // Retorna lista com posições das rainhas
    vector<vector<int>> get_Queens() { return queenspos; }

    // Retorna tabuleiro (true se há rainha na casa, false se casa vazia)
    vector<vector<bool>> get_Board() { return B; }

    // Retorna a quantidade de rainhas já posicionadas
    int get_number() { return numqueens; }
};


bool nQueens_bt(QueensBoard& QB) {
    /*  Implementação do N-QUEENS com BACKTRACKING
    * Tenta colocar n rainhas em um tabuleiro nxn
    * ENTRADA:
    * Ponteiro QB para objeto da classe QueensBoard contendo
    *    tabuleiro, posições preenchidas e funções de manipulação
    * SAÍDA:
    * Booleano res com true se achou solução, e false se não achou
    * Ponteiro QB atualizado com a solução, caso haja alguma
    */

    // Caso tenha preenchido n rainhas, retorna verdadeiro
    if (QB.get_number() == QB.n) { return true; }

    // Itera todas linhas e colunas
    for (int i = 1; i <= QB.n; i++) {
        for (int j = 1; j <= QB.n; j++) {
            // Se a casa atual estiver livre
            if (QB.check_Position(i, j)) { 
                // Coloca uma rainha na casa
                QB.add_Queen(i, j); 
                // Tenta colocar mais uma rainha no tabuleiro
                // Se não conseguir, retira a rainha dessa casa e prossegue busca
                // Caso consiga, retorna true
                if(!nQueens_bt(QB)) { QB.del_Queen(i, j); }
                else { return true; }
            }
        }
    }
    
    // Se chegou até aqui é porque não conseguiu colocar rainha em nenhum lugar
    return false;
}

void printBoard(QueensBoard& QB);

int main()
{
    // Realiza um teste com n = 3
    int n = 3;
    QueensBoard QB(n);
    bool res = nQueens_bt(QB);
    // caso resulte em uma solução, imprime o board; else informe o user
    if (res) {
        cout << "Para n = " << n << " a solucao eh:" << endl;
        printBoard(QB);
    }
    else { cout << "Para n = " << n << " nao existe solucao" << endl; }
    
    // Realiza outro teste com n = 8
    n = 8;
    QueensBoard QB2(n);
    res = nQueens_bt(QB2);
    if (res) {
        cout << "Para n = " << n << " a solucao eh:" << endl;
        printBoard(QB2);
    }
    else { cout << "Para n = " << n << " nao existe solucao" << endl; }
}

// Imprime tabuleiro
void printBoard(QueensBoard& QB) {
    // Extrai o Board
    vector<vector<bool>> Board = QB.get_Board();

    // Itera todas linhas e colunas
    for (vector<bool> linha : Board) {
        for (bool casa : linha) {
            // Imprime Q se true, ou _ se false
            if (casa) { cout << "Q "; }
            else { cout << "_ "; }
        }
        cout << endl;
    }
}
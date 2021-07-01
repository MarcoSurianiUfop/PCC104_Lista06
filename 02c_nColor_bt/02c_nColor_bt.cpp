/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                 LISTA 06 - ATIVIDADES PRÁTICAS - EXERCÍCIO 02C
                              M COLORS - BACKTRACKING
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <iomanip>  // setw
#include <vector>

using namespace std;

class Mapa {
private:
    // Matriz com Conexões
    vector<vector<bool>> MC;

    // Check Cores e Nós (Cores permitidas)
    vector<vector<bool>> CP;

    // Progresso
    vector<int> ColorsVector;
    int numcolored;

public:
    // Números de nós e de cores, variáveis públicas para acesso rápido
    int n, m;

    // Construtor da classe
    Mapa(vector<vector<bool>>& mapa, int kn, int km) {
        // Atualiza tamanhos
        n = kn;
        m = km;

        // Mapa: se nós i, j conectados, entao MC[i][j] = MC[j][i] = true
        MC = mapa;

        // Check Cores e Nós (Cores permitidas)
        // Possui m (cores) e n (nós) linhas
        // Caso CP[i][j] seja true, o nó j está liberado para usar a cor i
        // Caso false, o nó j está proibido de usar a cor i
        CP = vector<vector<bool>>(m, vector<bool>(n, true));

        // Progresso
        // Vetor com as cores de cada nó: -1 = sem cor
        ColorsVector = vector<int>(n, -1);
        // Quantidade de nós coloridos 
        numcolored = 0;
    }

    // Colore o nó in com a cor im
    void color_node(int in, int im) {
        // Todo nó i conectado a in tem a cor im bloqueada
        for (int i = 1; i <= n; i++) {
            if (MC[i - 1][in - 1]) { CP[im - 1][i - 1] = false; }
        }

        // Atualiza vetor com cores dos nós e incrementa nós coloridos
        ColorsVector[in - 1] = im;
        numcolored += 1;
    }

    // Descolore o nó in com a cor im
    void uncolor_node(int in, int im) {
        // Todo nó i conectado a in tem a cor im desbloqueada
        for (int i = 1; i <= n; i++) {
            if (MC[i - 1][in - 1]) { CP[im - 1][i - 1] = true; }
        }

        // Atualiza vetor com cores dos nós e decrementa nós coloridos
        ColorsVector[in - 1] = -1;
        numcolored -= 1;
    }

    // Checa nó in para cor im
    // Se nó já colorido, retorna false
    // Caso a cor im esteja bloqueada para nó in, retorna false, 
    // caso contrário retorna true
    bool check_nodecolor(int in, int im) {
        if (ColorsVector[in - 1] > 0) { return false; }
        return CP[im - 1][in - 1];
    }

    // Retorna matriz de conexões (mapa)
    vector<vector<bool>> get_matrix() { return MC; }

    // Retorna lista com cores por nó
    vector<int> get_Colors() { return ColorsVector; }

    // Retorna a quantidade de nós já coloridos
    int get_number() { return numcolored; }
};


bool mColors_bt(Mapa& M) {
    /*  Implementação do M-COLORS com BACKTRACKING
    * Tenta colorir n nós com m cores
    * ENTRADA:
    * Ponteiro M para objeto da classe Mapa contendo nós,
    *    cores dos nós e funções de manipulação
    * SAÍDA:
    * Booleano res com true se achou solução, e false se não achou
    * Ponteiro M atualizado com a solução, caso haja alguma
    */

    // Caso tenha colorido os n nós, retorna verdadeiro
    if (M.get_number() == M.n) { return true; }

    // Itera todos nós e cores
    for (int i = 1; i <= M.n; i++) {
        for (int j = 1; j <= M.m; j++) {
            // Se par nó, cor estiver livre
            if (M.check_nodecolor(i, j)) {
                // Aplica tal cor ao nó
                M.color_node(i, j);
                // Tenta colorir mais um nó
                // Se não conseguir, descolore o prsente nó e prossegue busca
                // Caso consiga, retorna true
                if (!mColors_bt(M)) { M.uncolor_node(i, j); }
                else { return true; }
            }
        }
    }

    // Se chegou até aqui é porque não conseguiu colorir nenhum nó
    return false;
}

void printMap(Mapa& M);
void printCor(Mapa& M);

int main()
{
    // Cria um mapa para testes
    int n = 4;
    vector<vector<bool>> mapa = {   {false, true,  true,  true },
                                    {true,  false, true,  false},
                                    {true,  true,  false, true },
                                    {true,  false, true,  false} };
    
    // Realiza um teste com m = 2
    int m = 2;
    Mapa M2(mapa, n, m);
    bool res = mColors_bt(M2);
    cout << "Mapa:" << endl;
    printMap(M2);

    cout << endl;
    // caso resulte em uma solução, imprime o resposta; else informe o user
    if (res) {
        cout << "Para m = " << m << " cores a solucao eh:" << endl;
        printCor(M2);
    }
    else { cout << "Para m = " << m << " cores nao existe solucao" << endl; }

    // Realiza outro teste com m = 3
    m = 3;
    Mapa M3(mapa, n, m);
    res = mColors_bt(M3);

    cout << endl;
    // caso resulte em uma solução, imprime o resposta; else informe o user
    if (res) {
        cout << "Para m = " << m << " cores a solucao eh:" << endl;
        printCor(M3);
    }
    else { cout << "Para m = " << m << " cores nao existe solucao" << endl; }
}

// Imprime mapa
void printMap(Mapa& M) {
    // Extrai o Board
    vector<vector<bool>> mapa = M.get_matrix();

    // Itera todas linhas e colunas
    for (vector<bool> linha : mapa) {
        for (bool casa : linha) {
            // Imprime 1 se true, ou _ se false
            if (casa) { cout << "1 "; }
            else { cout << "_ "; }
        }
        cout << endl;
    }
}

// Imprime cores
void printCor(Mapa& M) {
    // Extrai o Board
    vector<int> mapa = M.get_Colors();
    int in = 1;

    // Itera todas linhas e colunas
    for (int im : mapa) {
        cout << "Node " << setw(2) << in << " : color " << setw(2) << im << endl;
        in += 1;
    }
    cout << endl;
}
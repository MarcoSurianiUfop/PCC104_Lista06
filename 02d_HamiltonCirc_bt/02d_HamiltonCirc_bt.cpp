/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                 LISTA 06 - ATIVIDADES PRÁTICAS - EXERCÍCIO 02D
                       HAMILTONIAN CIRCUIT - BACKTRACKING
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <iomanip>  // setw
#include <vector>

using namespace std;

class HamiltonianCircuit {
private:
    // Matriz com Conexões
    vector<vector<bool>> MC;

    // Check Quantidade de conexões
    vector<int> QC;

    // Progresso
    vector<int> Conexoes;
    int numconexoes;

public:
    // Numero de nós, variável pública para acesso rápido
    int n;

    // Construtor da classe
    HamiltonianCircuit(vector<vector<bool>>& mapa, int k) {
        // Atualiza tamanho
        n = k;

        // Mapa: se nós i, j conectados, entao MC[i][j] = MC[j][i] = true
        MC = mapa;

        // Check Quantidade de conexões
        // Cada nó pode ter 0, 1 ou 2 conexões em um dado momento
        QC = vector<int>(n, 0);

        // Progresso
        // Vetor com a sequência de nós (n+1 pois deve voltar no primeiro)
        Conexoes = vector<int>(n + 1, -1);
        // Quantidade de conexões
        numconexoes = 0;
    }

    // Estabelece nó inicial
    void initial_node(int k) { Conexoes[0] = k; }

    // Informa último nó da sequência
    int last_node() { return Conexoes[numconexoes]; }

    // Conecta nó de origem o ao nó de destino d
    void connect_nodes(int o, int d) {
        // Acrescenta uma conexão a cada nó
        QC[o - 1] += 1;
        QC[d - 1] += 1;

        // Acrescenta d à sequencia e incrementa numconexoes
        numconexoes += 1;
        Conexoes[numconexoes] = d;
    }

    // Desconecta nó de origem o ao nó de destino d
    void disconnect_nodes(int o, int d) {
        // Retira uma conexão a cada nó
        QC[o - 1] -= 1;
        QC[d - 1] -= 1;

        // Decrementa numconexoes
        numconexoes -= 1;
    }

    // Checa conexão entre nós o, d
    // Primeiramente, deve haver um caminho entre eles
    // Depois se origem é o primeiro nó (neste caso, o deve ter 0 conexão): pode
    // ou se destino é o primeiro nó (neste caso, d deve ter 1 conexão): pode
    // Conexão permitida se origem tiver 1 conexão e destino tiver 0 conexões
    // Caso conexão esteja bloqueada, retorna false, caso contrário retorna true
    bool check_Conexao(int o, int d) {
        if (!MC[o - 1][d - 1]) { return false; }
        if (o == Conexoes[0] and QC[o - 1] == 0 and QC[d - 1] == 0) { return true; }
        if (d == Conexoes[0] and QC[o - 1] == 1 and QC[d - 1] == 1) { return true; }
        return (QC[o - 1] == 1 and QC[d - 1] == 0);
    }

    // Retorna lista com sequencia de conexões
    vector<int> get_Conexoes() { return Conexoes; }

    // Retorna tabuleiro (true se há rainha na casa, false se casa vazia)
    vector<vector<bool>> get_matrix() { return MC; }

    // Retorna a quantidade de conexões
    int get_number() { return numconexoes; }
};


bool HamiltonianCircuit_bt(HamiltonianCircuit& HC) {
    /*  Implementação do HAMILTONIAN CIRCUIT com BACKTRACKING
    * Tenta encontrar um caminho que passa por n nós e retorna ao primeiro
    * ENTRADA:
    * Ponteiro HC para objeto da classe HamiltonianCircuit contendo nós,
    *    mapa, conexões e funções de manipulação
    * SAÍDA:
    * Booleano res com true se achou solução, e false se não achou
    * Ponteiro HC atualizado com a solução, caso haja alguma
    */

    // Caso tenha realizado n conexões, retorna verdadeiro
    if (HC.get_number() == HC.n) { return true; }

    // Caso não haja nenhum nó na sequência, acrescente um (qualquer um)
    if (HC.last_node() == -1) { HC.initial_node(1); }

    int origem = HC.last_node();

    // Itera todos nós
    for (int i = 1; i <= HC.n; i++) {
        // Se a conexão entre o último nó da lista e o atual estiver liberada
        if (origem != i and HC.check_Conexao(origem, i)) {
            // Conecta os nós
            HC.connect_nodes(origem, i);
            // Tenta colocar mais uma conexão na sequência
            // Se não conseguir, desfaz última conexão e prossegue busca
            // Caso consiga, retorna true
            if (!HamiltonianCircuit_bt(HC)) { HC.disconnect_nodes(origem, i); }
            else { return true; }
        }
    }

    // Se chegou até aqui é porque não conseguiu fazer nenhuma conexão
    return false;
}

void printMap(HamiltonianCircuit& HC);
void printSeq(HamiltonianCircuit& HC);

int main()
{
    // Cria um mapa para testes
    int n = 5;
    vector<vector<bool>> mapa = {   {false, true,  false, true,  false },
                                    {true,  false, true,  true,  true},
                                    {false, true,  false, true, true },
                                    {true,  true,  true, false, false},
                                    {false, true,  true,  false, false} };

    HamiltonianCircuit HC1(mapa, n);
    bool res = HamiltonianCircuit_bt(HC1);
    cout << "Mapa:" << endl;
    printMap(HC1);

    // caso resulte em uma solução, imprime o resposta; else informe o user
    if (res) {
        cout << "Para mapa acima, a solucao eh:" << endl;
        printSeq(HC1);
    }
    else { cout << "Para mapa acima, nao existe solucao" << endl; }

    // Realiza outro teste 
    mapa = {{false, true,  false, true,  false },
            {true,  false, true,  true,  true},
            {false, true,  false, false, true },
            {true,  true,  false, false, true },
            {false, true,  true,  true , false} };

    HamiltonianCircuit HC2(mapa, n);
    res = HamiltonianCircuit_bt(HC2);
    cout << endl << "Mapa:" << endl;
    printMap(HC2);

    // caso resulte em uma solução, imprime o resposta; else informe o user
    if (res) {
        cout << "Para mapa acima, a solucao eh:" << endl;
        printSeq(HC2);
    }
    else { cout << "Para mapa acima, nao existe solucao" << endl; }
}

// Imprime mapa
void printMap(HamiltonianCircuit& HC) {
    // Extrai o Board
    vector<vector<bool>> mapa = HC.get_matrix();

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

// Imprime sequencia de conexões
void printSeq(HamiltonianCircuit& HC) {
    // Extrai a sequencia
    vector<int> seq = HC.get_Conexoes();

    // Itera todos nós
    for (int node : seq) { cout << setw(2) << node << " - "; }
    cout << endl;
}
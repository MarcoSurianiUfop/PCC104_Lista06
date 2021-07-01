/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                 LISTA 06 - ATIVIDADES PRÁTICAS - EXERCÍCIO 03B
                             CAIXEIRO BRANCH & BOUND 
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <fstream>  // ifstream
#include <sstream>  // stringstream
#include <iomanip>  // setw
#include <string>
#include <vector>

using namespace std;

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

// Imprime um vetor
void printv(vector<int> v, int c) {
    for (int e : v) { cout << setw(2) << e << "  "; }
    cout << setw(2) << v[0] << " - ";
    cout << "Custo: " << c << endl;
}

// Heurística: retorna 0 para subestimar (não poder superestimar)
int h(vector<int> sol) { return 0; }

// Retorna o custo da rota em "sol", dados os custos em cost_matrix
int cost(vector<int> sol, vector<vector<int>> cost_matrix) {
    int cost = 0;
    int nsol = sol.size();

    // Para cada nó, calcule o custo de ir até o próximo
    // Caso i seja o último elemento (i+1)%nsol faz voltar ao primeiro nó 
    for (int i = 0; i < nsol; i++) {
        cost += cost_matrix[sol[i]][sol[(i + 1) % nsol]];
    }

    return cost;
}

void search(vector<int>& sol, vector<int>& best_sol, int n, int& bound,
    vector<vector<int>>& cost_matrix, vector<int>& domain) {
    /* Busca o caminho ótimo
    * ENTRADAS:
    * Vetor sol: solução incompleto (em construção)
    * Vetor best_sol: melhor solução completa encontrada até o momento
    * Inteiro n: Quantidade de nós
    * Inteiro bound: limiar para prosseguir com buscas (soluções com custo
    *                maior que bound são podadas)
    * Matriz cost_matrix: Matriz com custos de deslocamento entre nós
    * Vetor domain: lista de nós
    * 
    * SAÍDA:
    * Vetor best_sol atualizado com a melhor rota (com custo mínimo)
    */

    // Se o custo esperado da solução em construção não exceder o limiar bound, prossiga
    // Custo esperado = soma entre o custo da solução sol (dada a matriz de custos) e a 
    // heurística h 
    if (cost(sol, cost_matrix) + h(sol) < bound) {
        // Caso a solução em construção "sol" estiver completa (possuir n nós),
        // atualize a melhor solução com ela
        if (sol.size() == n) { 
            // Melhor solução é a solução descoberta (seu custo é menor quer bound)
            best_sol = sol;

            // Novo bound é o custo da nova solução
            bound = cost(sol, cost_matrix);

            // Imprime a solução e seu custo
            printv(best_sol, bound);
        }
        // Caso a solução em construção "sol" não estiver completa (possuir menos que n nós),
        // acrescente mais um nó a tal solução e prossiga com a busca
        else {
            // Itere cada nó "d" do domínio
            for (int d : domain) {
                // Verifica se o nó "d" já foi acrescentado à solução 
                // (retorna 'true' caso "d" não esteja em "sol")
                if (find(sol.begin(), sol.end(), d) == sol.end()) {
                    // Cria uma cópia de sol e acrescenta nó "d" à cópia
                    vector<int> new_sol(sol);
                    new_sol.push_back(d);

                    // Prossegue a busca
                    search(new_sol, best_sol, n, bound, cost_matrix, domain);
                }
            }
        }
    }
}

// Função que prepara os dados e começa a busca
vector<int> Caixeiro_bb(vector<int>& domain, int n, int bound,
    vector<vector<int>>& cost_matrix) {

    // Cria um vetor com a solução final que será retornada ao usuário
    vector<int> best_path;

    // Cria uma vetor para armazenar soluções intermediárias
    // Deve começar em um nó qualquer (não faz diferença qual)
    // Para simplificar, começa no nó 0 (primeiro)
    vector<int> sol = { 0 };

    // Começa a busca. Ela irá atualizar o vetor best_path
    search(sol, best_path, n, bound, cost_matrix, domain);

    return best_path;
}


int main()
{
    // Nome do arquivo
    string tsp_file = "myTSP11.tsp"; // opções: brazil58 e gr17
    /* myTSP11: 0  7  4  3  9  5  2  6  1 10  8  0 - Custo: 253 */

    // Cabeçalho tem 7 linhas, matriz tem 11 cidades (nós)
    // Caso altere o arquivo, não esqueça de atualizar nhead e nnodes
    int nhead = 7;
    int nnodes = 11;

    // Lê o arquivo e guarda distâncias em cost_matrix 
    vector<vector<int>> cost_matrix = readMatrix(tsp_file, nhead, nnodes);

    // Domínio: nós a ser percorridos
    vector<int> domain;
    for (int i = 0; i < nnodes; i++) { domain.push_back(i); }
    int n = domain.size(); 

    // Limite inicial para selecionar candidatos a solução
    int bound = 1000;

    // Chama a função Caixeiro_bb: procura a melhor rota e imprime as
    // soluções paricias. Melhor rota é a última
    vector<int> best_path = Caixeiro_bb(domain, n, bound, cost_matrix);
    
    return 0;
}

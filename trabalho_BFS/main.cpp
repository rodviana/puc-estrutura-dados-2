#include <iostream>
#include <queue>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>

void BFS(int **E, int start, int *D, int *P, int N);
void caminho(std::string *vet,int origem,int destino,int *P,bool *visitado);

void lerArquivo(int &N,int &qntObj,
                std::queue<std::string> &aux,
                std::vector<std::string> &adjString,
                std::vector<std::string> &objetivo);

void setar(int N,int **adj, std::string *vertice,int *start, int *end,int qntObj,
           std::queue<std::string> &aux,
           std::vector<std::string> &adjString,
           std::vector<std::string> &objetivo);
int main()
{
    std::string *vertice;
    int *P,*D;
    int **adj;
    int N=0;
    int *start,*end;
    int qntObj;

    std::vector<std::string> adjString;
    std::vector<std::string> objetivo;
    std::queue<std::string> aux;

    lerArquivo(N,qntObj, aux, adjString, objetivo);

    vertice = new std::string[N];
    P= new int[N];
    D= new int[N];
    adj= new int *[N];
    start = new int[qntObj];
    end = new int [qntObj];
    bool visitado[N];
    std::vector<std::pair<int,int>> dv;

    setar(N, adj, vertice, start, end, qntObj ,aux, adjString, objetivo);

/*
    for(int i=0;i<N;i++) // imprimir matriz adj
    {
        for(int j=0;j<N;j++)
        {
            std::cout<<adj[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
*/


    for(int i=0;i<qntObj;i++) // imprimir caminho
    {
        BFS(adj,start[i],D,P,N);

        if(start[i] != -1 && end[i] != -1) // se for -1 é broadcast
        {
            caminho(vertice,start[i],end[i],P,visitado);
            std::cout<<std::endl;
        }
        else // entra broadcast
        {
            for(int i=0;i<N;i++) // pair com distancia e vertice correspondente
            {
                dv.push_back(std::make_pair(D[i],i));
            }
            std::sort(dv.begin(),dv.end());// ordena para rodar broadcast primeiro nos mais longes

            for(int j=0;j<N;j++) visitado[j] = false; // prevenção: não repetir vertices já visitados
            for(int j=N-1;j>=0;j--)
            {
                if( start[i]!=j && !visitado[dv[j].second] )
                {
                    caminho(vertice,start[i],dv[j].second,P,visitado);
                }
            }
            std::cout<<std::endl;
        }
    }

    return 0;
}


void BFS(int **E, int start, int *D, int *P, int N)
{
    int u;
    char C[N];

    std::queue<int> Q;
    for(int i=0; i<N; i++)
    {
        C[i]='w';
        P[i]= -1;
        D[i] = INT_MAX;
    }
    Q.push(start);
    C[start]='g';
    D[start]=0;
    for(int i=0;i<N;i++)
        while(!Q.empty())
        {
            u = Q.front();
            Q.pop();

            for(int v=0;v<N;v++) // passar por adjacentes de u
            {  if(E[u][v]==1)
                {
                    if(C[v]=='w')
                    {
                        C[v] = 'g';
                        D[v] = D[u] + 1;
                        P[v]= u;
                        Q.push(v);
                    }
                }
                C[u] = 'b';
            }
        }
}
void caminho(std::string *vet, int origem,int destino, int *P,bool *visitado)
{
    if(P[destino] == -1)
    {
        std::cout<<vet[origem]<<" nao alcanca "<<vet[destino]<<std::endl;
        return;
    }

    std::stack<int> caminho;
    caminho.push(destino);
    visitado[destino] = true;
    int comparador = destino;

    while(P[comparador] != origem && P[comparador] != -1)
    {
        caminho.push(P[comparador]);
        visitado[P[comparador]] = true;
        comparador = P[comparador];
    }

    caminho.push(origem);
    visitado[origem] = true;

    while(!caminho.empty())
    {
        std::cout<<vet[caminho.top()];
        caminho.pop();
        if(caminho.empty()) break;
        else std::cout<<" ,";
    }
    std::cout<<std::endl;
}

void lerArquivo(int &N,int &qntObj,
                std::queue<std::string> &aux,
                std::vector<std::string> &adjString,
                std::vector<std::string> &objetivo){

    std::string nomeArquivo = "teste2.txt";
    std::ifstream arquivoEntrada(nomeArquivo.c_str());
    std::string linha;
    std::string aux1,aux2;

    while(!arquivoEntrada.eof()) // leitura IP
    {
        getline(arquivoEntrada, linha);
        if(linha.size() <= 14 && linha!="") // IP
        {
            aux.push(linha);
            N++;
        }
        else break;
    }

    if(linha[12] == '-' || linha [13] == '-'|| linha [14] == '-') // leitura adj
    {
        adjString.push_back(linha);
    }
    else // leitura origem e destino
    {
        objetivo.push_back(linha);
    }

    while(!arquivoEntrada.eof()) // leitura IP e ADJ
    {
        getline(arquivoEntrada, linha);
        if(linha[12] == '-' || linha [13] == '-'|| linha [14] == '-'|| linha [15] == '-') // adj
        {
            adjString.push_back(linha);
        }
        else // origem e destino
        {
            objetivo.push_back(linha);
        }
    }

    qntObj = objetivo.size();
    arquivoEntrada.close();

}

void setar(int N, int **adj, std::string *vertice,int *start, int *end, int qntObj,
           std::queue<std::string> &aux,
           std::vector<std::string> &adjString,
           std::vector<std::string> &objetivo)
{
    int linhaAdj=-1,colunaAdj=-1;
    int fimAnterior;
    unsigned int x;

    std::string aux1,aux2;
    unsigned int j;

    for(int i=0;i<N;i++) // vértices e inicialização matriz adj
    {
        vertice[i] = aux.front();
        aux.pop();
        adj[i]= new int[N];
        for(int j=0;j<N;j++) adj[i][j] = 0;
    }

    for(unsigned int i=0;i<adjString.size(); i++) // setar matriz adj
    {
        aux1.clear();

        for(x=0;x<adjString[i].size();x++) // encontra o fim do primeiro IP
        {
            if(adjString[i][x] == '-') break;
        }
        for(j=0;j<x-1;j++)//adiciona IP em uma string separada
        {
            aux1.push_back(adjString[i][j]);
        }
        for(j=0;j<=N;j++) // descobre posição do IP no vetor de vértice
        {
            if(aux1 == vertice[j]) linhaAdj = j;
        }

        fimAnterior = x;


        for(x=x+2;x<=adjString[i].size();x++)
        {
            aux1.clear();
            if(adjString[i][x] == ',' || adjString[i].size() == x)
            {
                for(j=fimAnterior+2;adjString[i][j]!=' ' && j<adjString[i].size();j++)
                {
                    aux1.push_back(adjString[i][j]);
                }
                for(j=0;j<N;j++)
                {
                    if(aux1 == vertice[j])
                    {
                        colunaAdj = j;
                        break;
                    }
                }
                adj[colunaAdj][linhaAdj] = 1;
                adj[linhaAdj][colunaAdj] = 1;
                fimAnterior = x;
            }
        }

    }

    for(int i=0;i<qntObj;i++)
    {
        start[i] = -1;
        end[i] = -1;
    }

    for(int i=0;i<qntObj;i++)
    {
        aux1.clear();
        aux2.clear();
        for(j=0;j<objetivo[i].size();j++)
        {
            if(objetivo[i][j]==',') break;
        }
        for(x=0;x<j-1;x++)
        {
            aux1.push_back(objetivo[i][x]);
        }
        for(x=j+2;x<objetivo[i].size();x++)
        {
            aux2.push_back(objetivo[i][x]);
        }
        for(x=0;x<N;x++)
        {
            if(aux1 == vertice[x]) start[i] = x;
            if(aux2 == vertice[x]) end[i] = x;
        }
    }

}

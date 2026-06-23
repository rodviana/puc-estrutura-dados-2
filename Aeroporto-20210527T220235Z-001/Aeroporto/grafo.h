#ifndef GRAFO_H
#define GRAFO_H
#include <list>
#include <utility>
#include <algorithm>
#include <PriorityQueueModificada.h>
#include <queue>
#include<functional>
#include <vector>

class grafo
{
public:
    grafo(int tam);
    void caminho(int s, int *d, int *p);
    void insert_aresta(int u, int v, int w);
    std::list<std::pair<int,int>> *adjacentes(int u);
    std::list<std::pair<int,int>> *lista_de_adjacencia;
private:
    int N;

    void relaxacao(int u,int v,int *d,int *p,int w, priority_queue<pair<int,int>, std::vector<pair<int,int>>, std::greater<pair<int,int>>> *Q);
    void inicializar(int s,int *d,int *p);
    bool search(int u,int v);
};

#endif // GRAFO_H



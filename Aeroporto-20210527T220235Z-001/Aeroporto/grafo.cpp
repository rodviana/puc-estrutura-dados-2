#include "grafo.h"
#include "queue"
#include "functional"
grafo::grafo(int tam)
{
    this->N=tam;
    lista_de_adjacencia=new std::list<std::pair<int,int>>[N];
}

void grafo::caminho(int s, int *d, int *p)
{
    priority_queue<pair<int,int>, std::vector<pair<int,int>>, std::greater<pair<int,int>>> Q;
    inicializar(s,d,p);
    //Q.Alterar(s,0);
    Q.push({d[s]=0,s});
    int u;
    //std::list<std::pair<int,int>>::iterator it;
    while(!Q.empty()){
        u=Q.top().first;
        for(auto it: lista_de_adjacencia[u]){
            if(d[it.first]>d[u]+it.second){
                d[it.first]=d[u]+it.second;
                p[it.first]=u;
                Q.push({d[it.first],it.first});
                //Q.Alterar(it.first,d[u]+it.second);
            }
        }
        Q.pop();
    }
}


void grafo::insert_aresta(int u, int v, int w)
{
   if(!search(u,v)){
       lista_de_adjacencia[u].push_back(std::make_pair(v,w));
   }
}

void grafo::relaxacao(int u, int v, int *d, int *p, int w,priority_queue<pair<int,int>, std::vector<pair<int,int>>, std::greater<pair<int,int>>> *Q)
{
    if(d[v]>d[u]+w){
        d[v]=d[u]+w;
        p[v]=u;
        Q->push({v,d[u]+w});
        //Q->Alterar(v,d[u]+w);
    }
}

void grafo::inicializar(int s, int *d, int *p)
{
    for(int i=0;i<N;i++){
        d[i]=INT_MAX;
        p[i]=-1;
    }
    d[s]=0;
}

bool grafo::search(int u, int v)
{
    std::list<std::pair<int,int>>::iterator i;
    for(i=lista_de_adjacencia[u].begin();i!=lista_de_adjacencia[u].end();i++){
        if(i->first==v){return true;}
    }
    return false;
}

std::list<std::pair<int, int> > *grafo::adjacentes(int u)
{
    return &lista_de_adjacencia[u];
}

#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;
struct vertice
{
    float x,y;
};
struct aresta
{
    int verticeA;
    int verticeB;
    float distancia;
};
void inicializa(int* pai, int n);
int Union_find(int* pai, int a);
void Union_set(int* pai, int a, int b);
int kruskal(aresta *aresta, struct::aresta *A, int N, int e);
void leitura(vertice *vertice, aresta *aresta, int &numVertices, int N);
int main()
{
    int N, numVertices=0;
    float custoTotal=0;
    cin>>N;
    vertice vertice[2*N];
    aresta aresta[N];
    struct::aresta A[N];

    leitura(vertice, aresta, numVertices,N);
    int numArestaMin = kruskal(aresta,A,numVertices,N);

    for(int i=0;i<numArestaMin;i++)
    {
        custoTotal+=A[i].distancia;
    }

    std::cout<<fixed<<setprecision(2)<<"Custo total: "<<custoTotal<<"\n";

    for(int i=0;i<numArestaMin;i++)
    {
        std::cout<<vertice[A[i].verticeA].x<<" "<<vertice[A[i].verticeA].y<<" - ";
        std::cout<<vertice[A[i].verticeB].x<<" "<<vertice[A[i].verticeB].y<<" -> (peso): "<<A[i].distancia<<"\n";
    }

    return 0;
}
void leitura(vertice *vertice, aresta *aresta, int &numVertices, int N)
{
    int j;
    int aux1,aux2,aux3,aux4;
    char ignore;
    for(int i=0;i<N;i++)
    {
        cin>>aux1>>aux2>>ignore>>aux3>>aux4;

        if(numVertices!=0) // se já existem vertices anotados, evitar duplicidade
        {
            for(j=0;j<numVertices;j++)
            {
                if(vertice[j].x == aux1 && vertice[j].y == aux2) break; // vertice já foi anotado
            }
            if(j==numVertices) // não encontrou
            {
                vertice[numVertices].x = aux1;
                vertice[numVertices].y = aux2;
                numVertices++;
            }
            aresta[i].verticeA=j; // posição do vertice que compoem aresta

        }
        else // se não coloca no primeiro
        {
            vertice[0].x=aux1;
            vertice[0].y=aux2;
            aresta[i].verticeA=0;
            numVertices++;
        }

        for(j=0;j<numVertices;j++)
        {
            if(vertice[j].x == aux3 && vertice[j].y == aux4) break; // vertice ja foi anotado
        }
        if(j==numVertices) // não encontrou
        {
            vertice[numVertices].x = aux3;
            vertice[numVertices].y = aux4;
            numVertices++;
        }

        aresta[i].verticeB = j; // posição do vertice que compoem aresta
        aresta[i].distancia = sqrt(pow(aux3-aux1,2) + pow(aux4-aux2,2)); // peso aresta
    }
}
void inicializa(int* pai, int n){
    for(int i=0; i<n; i++)
    {
        pai[i]=i;
    }

}
int Union_find(int* pai, int a)
{
    if(pai[a]==a)
        return a;
    pai[a]=Union_find(pai, pai[a]);
    return pai[a];
}
void Union_set(int* pai, int a, int b)
{
    a=Union_find(pai, a);
    b=Union_find(pai, b);
    pai[a]=b;
}
int kruskal(aresta *aresta,struct::aresta *A, int N, int e)
{
    struct::aresta aux;
    int j=0,u,v;
    int pai[N];
    inicializa(pai, N);

    for(int z=0;z<e;z++) // ordena aresta pelo peso
    {
        for(int w=0;w<e;w++)
        {
            if(aresta[z].distancia<aresta[w].distancia)
            {
                aux = aresta[z];
                aresta[z] = aresta[w];
                aresta[w]= aux;
            }
        }
    }

    for(int i=0;i<e;i++)
    {

        u=aresta[i].verticeA;
        v=aresta[i].verticeB;
        if(Union_find(pai,u) != Union_find(pai,v))
        {
            A[j] = aresta[i];
            j++;
            Union_set(pai, u, v);
        }
    }
    return j;
}


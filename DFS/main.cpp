#include <iostream>

void DFS(int *V, int *E,int *P,int *I,int *F,int N, char *A);
void DFS_Visit(int u, int *V, int *E,int *P,int *I,int *F,char *C,int &t,int N,char **A);
int main()
{

    return 0;
}
void DFS_Visit(int u, int *V, int *E,int *P,int *I,int *F,char *C,int &t,int N,char **A)
{
    C[u]='g';
    I[u]=++t;
    for(int v=0;v<N;v++) // passa por todos os adjacentes de u
    {
        if(C[v] == 'w')
        {
            A[u][v] = 'l';
            P[v]=u;
            DFS_Visit(v,V,E,P,I,F,C,t,N,A);
        }
        else if(C[v] == 'g') A[u][v] = 'r';
        else A[u][v] = 'a';
    }
    F[u] = ++t;
    C[u] = 'b';
}
void DFS(int *V, int *E,int *P,int *I,int *F,int N, char **A)
{
    char C[N];
    int t;
    for(int i=0;i<N;i++)
    {
        P[i]=1;
        C[i]='w';
    }
    t=0;
    for(int u=0;u<N;u++)
    {
        if(C[u]=='w') DFS_Visit(u,V,E,P,I,F,C,t,N,A);
    }

}


#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <functional>
#include <stack>


struct voo
{
    int N=1;
    std::string codigo;
    std::string origem;
    std::vector<std::string> destino;
    std::vector<std::string> hPartida;
    std::vector<std::string> hChegada;
};

struct vertice
{
    int indice;
    int aeroporto; // voos da mesma cidade
    std::string codigo;
    std::string cidade;
    std::string horario; // de chegada ou partida
    char tipo; // Chegada = 'c' ou Partida= 'p'
};
int dijkstra(std::vector<vertice> &V,std::vector<std::pair<int,int>> *E, int s, int end, int N, int *d, int *p);

float converteHora(std::string horario);

int existeAeroporto(std::vector<std::string> &aeroporto, std::string cidade);

void leitura(struct::voo *voo);

void inicializa(voo *voo,int N, std::vector<vertice> &V, std::vector<std::string> &aeroporto);

int numLinhas();

int main()
{
    std::stack<int> pilha;
    std::string ultimoCodigo;
    int start, end;
    int N = numLinhas();
    struct::voo voo[N];
    leitura(voo);
    std::vector<std::string> aeroporto;
    std::vector<vertice> V;

    inicializa(voo, N,V,aeroporto);

    std::vector<std::pair<int,int>> E[V.size()];
    int p[V.size()];
    int d[V.size()];

    int j=1,i=0;
    int peso;
    while(j<V.size())
    {
       peso =  converteHora(V[j].horario)- converteHora(V[i].horario);
       E[i].push_back({peso,j});
       i=i+2;
       j=j+2;
    }

    for(i=0;i<V.size();i++)
    {
        for(j=0;j<V.size();j++)
        {
            if((V[i].aeroporto == V[j].aeroporto )&& (V[i].tipo == 'c' && V[j].tipo == 'p'))
            {
                peso =   converteHora(V[j].horario)- converteHora(V[i].horario) ;
                if(V[i].codigo != V[j].codigo)
                {
                    if(peso<30)
                    {
                         peso+=1440;
                    }
                }
                E[i].push_back({peso,j});
            }
        }
    }


    /*
    for(int i=0;i<V.size();i++)
    {
        for(j=0;j<E[i].size();j++)
        {
            std::cout<<V[i].cidade<<" "<<V[E[i][j].first].cidade<<"    "<<E[i][j].second<<"  ";
        }
        std::cout<<"\n";
    }
*/

/*
    for(int i=0;i<N;i++)
    {
        std::cout<<voo[i].codigo<<" ";
        std::cout<<voo[i].origem<<" ";
        for(int j=0;j<voo[i].N;j++)
        {
            std::cout<<voo[i].hPartida[j]<<" "<<voo[i].destino[j]<<" "<<voo[i].hChegada[j]<<" ";
        }
        std::cout<<std::endl;
    }
*/

    for(i=1;i<aeroporto.size()+1;i++)
    {
        std::cout<<i<<" - "<<aeroporto[i-1]<<"\n";
    }
    std::cout<<"Digite o numero da Origem: ";
    std::cin>>start;
    start--;
    std::cout<<"Digite o numero do Destino: ";
    std::cin>>end;
    end--;


    int aux = start;
    for(i=0;i<V.size();i++)
    {
        if(V[i].aeroporto == aux && V[i].tipo == 'p')
        {
            d[i]=0;
            start=V[i].indice;
        }
        else d[i] = INT_MAX;
    }


    end = dijkstra(V,E, start , end,V.size(), d ,p);



    //---------------------------------------------------impressao
    if(end == -1)
    {
        std::cout<<"Nao ha conexao entre esses aeroportos\n";
        return 0;
    }
    while(end!=-1)
    {
        pilha.push(end);
        end = p[end];
    }
    ultimoCodigo = "";
    while(!pilha.empty())
    {
        if(ultimoCodigo!=V[pilha.top()].codigo)
        {
            std::cout<<std::endl;
            std::cout<<V[pilha.top()].codigo<<" ";
            ultimoCodigo = V[pilha.top()].codigo;
        }
        std::cout<<V[pilha.top()].cidade<<" "<<V[pilha.top()].horario<<" ";
        pilha.pop();
    }


    std::cout<<"\n";

    return 0;
}


int numLinhas()
{
    std::string nomeArquivo = "teste.txt";
    std::ifstream arquivoEntrada(nomeArquivo.c_str());
    int numero=0;
    std::string aux;
    while(!arquivoEntrada.eof())
    {
        getline(arquivoEntrada, aux);
        numero++;
    }
    arquivoEntrada.close();
    return numero;
}
void leitura(struct::voo *voo)
{
    std::string nomeArquivo = "teste.txt";
    std::ifstream arquivoEntrada(nomeArquivo.c_str());
    std::string linha,aux;
    int i,N=0,j;
    while(!arquivoEntrada.eof())
    {
        N++;

        getline(arquivoEntrada, linha);
        for(i=0;i<=linha.size() && linha[i]!=' ';i++) // código
        {
            voo[N-1].codigo.push_back(linha[i]);
        }

        for(i=i+1;i<=linha.size() && linha[i]!=' ';i++) // origem
        {
            voo[N-1].origem.push_back(linha[i]);
        }

        for(i=i+1;i<=linha.size() && linha[i]!=' ';i++) // hpartida
        {
            aux.push_back(linha[i]);
        }
        voo[N-1].hPartida.push_back(aux);
        aux="";

        for(i=i+1;i<=linha.size() && linha[i]!=' ';i++) // destino
        {
            aux.push_back(linha[i]);
        }
        voo[N-1].destino.push_back(aux);
        aux="";

        for(i=i+1;i<=linha.size() && linha[i]!=' ';i++) // hChegada
        {
            aux.push_back(linha[i]);
        }
        voo[N-1].hChegada.push_back(aux);
        aux="";


        j=0;
        while(i<=linha.size())
        {
            for(i=i+1;i<=linha.size() && linha[i]!=' ';i++) // hpartida
            {
                aux.push_back(linha[i]);
            }

            voo[N-1].hPartida.push_back(aux);
            aux="";

            for(i=i+1;i<=linha.size() && linha[i]!=' ';i++) // destino
            {
                aux.push_back(linha[i]);
            }
            voo[N-1].destino.push_back(aux);
            aux="";

            for(i=i+1;i<=linha.size() && linha[i]!=' ';i++) // hChegada
            {
                aux.push_back(linha[i]);
            }
            voo[N-1].hChegada.push_back(aux);
            aux="";
            voo[N-1].N++;
            j++;
        }
    }
}

void inicializa(voo *voo,int N, std::vector<vertice> &V,std::vector<std::string> &aeroporto)
{
    int indice=0;
    int id;
    struct::vertice aux;
    for(int i=0;i<N;i++)
    {// partida
        aux.codigo = voo[i].codigo;
        aux.cidade = voo[i].origem;
        aux.horario = voo[i].hPartida[0];
        aux.tipo = 'p';
        aux.indice=indice++;
        id = existeAeroporto(aeroporto, aux.cidade);
        if(id == -1)
        {
            aeroporto.push_back(aux.cidade);
            aux.aeroporto = aeroporto.size() - 1;
        }
        else aux.aeroporto = id;

        V.push_back(aux);
        //•------------------------------------- chegada
        aux.codigo = voo[i].codigo;
        aux.cidade = voo[i].destino[0];
        aux.horario = voo[i].hChegada[0];
        aux.tipo = 'c';
        aux.indice=indice++;
        id = existeAeroporto(aeroporto, aux.cidade);
        if(id == -1)
        {
            aeroporto.push_back(aux.cidade);
            aux.aeroporto = aeroporto.size() - 1;
        }
        else aux.aeroporto = id;

        V.push_back(aux);
        //•------------------------------------- conexões
        for(int j=1; j<voo[i].N; j++)
        {// partida
            aux.codigo = V.back().codigo;
            aux.cidade = V.back().cidade;
            aux.horario = voo[i].hPartida[j];
            aux.tipo = 'p';
            aux.indice=indice++;
            id = existeAeroporto(aeroporto, aux.cidade);
            if(id == -1)
            {
                aeroporto.push_back(aux.cidade);
                aux.aeroporto = aeroporto.size() - 1;
            }
            else aux.aeroporto = id;
            V.push_back(aux);
            //•------------------------------------- chegada
            aux.codigo = V.back().codigo;
            aux.cidade = voo[i].destino[j];
            aux.horario = voo[i].hChegada[j];
            aux.tipo = 'c';
            aux.indice=indice++;
            id = existeAeroporto(aeroporto, aux.cidade);
            if(id == -1)
            {
                aeroporto.push_back(aux.cidade);
                aux.aeroporto = aeroporto.size() - 1;
            }
            else aux.aeroporto = id;

            V.push_back(aux);
        }
    }


/*
    for(int i=0;i<V.size();i++)
    {
        std::cout<<"Vertice "<<V[i].indice<<"\n";
        std::cout<<"Aertoporto: "<<V[i].aeroporto<<"\n";
        std::cout<<"codigo: "<<V[i].codigo<<"\n";
        std::cout<<"cidade: "<<V[i].cidade<<"\n";
        std::cout<<"horario: "<<V[i].horario<<"\n";
        std::cout<<"tipo: "<<V[i].tipo<<"\n";
        std::cout<<"\n\n";
    }
    */
}

void inicialize_Single_Source(int *d, int*p, int N, int s)
{
    for(int v=0; v< N;v++)
    {
        p[v] = -1;
    }
}

void relax(int u, int v, int w, int *d, int *p, std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> &Q)
{
    if(d[v] > w)
    {
        d[v] = w;
        p[v] = u;
        Q.push(std::make_pair(d[v],v));
    }
}

int dijkstra(std::vector<vertice> &V,std::vector<std::pair<int,int>> *E, int s, int end, int N, int *d, int *p)
{
    std::pair<int, int> pair;
    int u;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> Q;
    inicialize_Single_Source(d, p, N, s);

    Q.push({d[s],s});
    while(!Q.empty())
    {
        u = Q.top().second;//retirar o menor elemento da fila de prioridade
        if(V[u].aeroporto==end) return u;
        Q.pop();
        for(auto v:E[u])
        {
            relax(u ,v.second, d[u]+v.first, d, p, Q);

        }
    }
    return -1;
}

int existeAeroporto(std::vector<std::string> &aeroporto, std::string cidade)
{
    for(int i=0;i<aeroporto.size();i++)
    {
        if(aeroporto[i] == cidade) return i;
    }
    return -1;
}

float converteHora(std::string horario)
{
    float hora = stoi(horario.substr(0,2));
    float minuto = stoi(horario.substr(3,2));

    return (60*hora)+minuto;

}














/*
TP1982 Porto 09:00  Madrid 11:00
IB8717 Madrid 12:00 LasPalmasGranCanaria 15:00 15:30 SantaCruzTenerife 16:20
TP1985 Porto 09:30 Lisboa 10:30
PGA102 Lisboa 12:40 SantaCruzTenerife 16:00 16:30 LasPalmasGranCanaria 17:20
*/

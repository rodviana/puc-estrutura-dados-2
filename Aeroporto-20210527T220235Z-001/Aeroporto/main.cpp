#include "grafo.h"
#include "voo.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <QStringList>


int HparaM(QString hora){//converte horas em string para minutos
    string horas=hora.toStdString();//hh:mm
    return (((char(horas[0])-48)*10)+(char(horas[1])-48))*60+
            (((char(horas[3])-48)*10)+(char(horas[4])-48));
}

string MparaH(int hora){//converte minutos para horas em string
    string ret;
    int horas=hora/60,minutos=hora%60;
    if(horas<10)ret="0"+to_string(horas);
    else ret=to_string(horas);
    if(minutos<10)ret+=":0"+to_string(minutos);
    else ret+=":"+to_string(minutos);
    return ret;
}

int buscaVoo(vector<voo> *vetor,voo *valor){//busca um voo na lista de voos
    for (unsigned int i=0;i<vetor->size();i++){
        if(vetor->at(i)==*valor){
            return i;
        }
    }
    return -1;
}

int buscaAeroporto(QStringList *aero,string &valor){//busca um aeroporto na lista de aeroportos
    for (int i=0;i<aero->size();i++){
        if(aero->at(i)==QString::fromStdString(valor)){
            return i;
        }
    }
    return -1;
}

int main()
{
    ifstream arquivo;
    string linha;
    //-----------------------Caminho do arquivo-----------------------
    string path="C:\\Users\\rodri\\Desktop\\Aeroporto-20210527T220235Z-001\\Aeroporto\\dados.txt";
    //----------------------------------------------------------------
    arquivo.open(path);
    QStringList aeroportos;
    vector<voo> voos;
    voo *v;
    if(arquivo.fail()){//leitura do arquivo
        throw("Arquivo não existe!");
    }else{
            while(!arquivo.eof()){
                getline(arquivo,linha);
                if(linha.size()>1){
                    QString aux=QString::fromStdString(linha);//transforma a linha extraida pelo getline para Qstring
                    QStringList lista=aux.split(' ');//divide a QString para QStringList pelos " "
                    v=new voo(lista[0].toStdString(),lista[1].toStdString(),HparaM(lista[2]),lista[3].toStdString(),HparaM(lista[4]));
                    voos.push_back(*v);
                    for(int i=5;i<lista.size();i+=3){
                        v=new voo(lista[0].toStdString(),lista[i-2].toStdString(),HparaM(lista[i]),lista[i+1].toStdString(),HparaM(lista[i+2]));
                        voos.push_back(*v);
                    }
                    lista.clear();
                }
            }
        arquivo.close();
        for(unsigned int i=0;i<voos.size();i++){
            aeroportos<<QString::fromStdString(voos[i].origem)<<QString::fromStdString(voos[i].destino);//gera uma QStringList de aeroportos
        }
        aeroportos.removeDuplicates();//funcao da QStringLIst para remover valores duplicados

        grafo G(voos.size()+aeroportos.size()*2);

        for(unsigned int i=0;i<voos.size();i++){
            G.insert_aresta(buscaAeroporto(&aeroportos,voos[i].origem),i+aeroportos.size()*2,0);// aresta da origem p/ o voo com peso 0
                G.insert_aresta(i+aeroportos.size()*2,buscaAeroporto(&aeroportos,voos[i].destino)+aeroportos.size(),voos[i].tempoVoo());// aresta do voo para o destino com peso "tempo decorrido"
        }
        for(unsigned int i=0;i<voos.size();i++){
            std::list<std::pair<int, int>> *lista=G.adjacentes(buscaAeroporto(&aeroportos,voos[i].destino));
            std::list<std::pair<int, int>>::iterator it;
            for(it=lista->begin();it!=lista->end();it++){
                if(voos[i].chegada+30 <= voos[it->first-aeroportos.size()*2].saida){
                    G.insert_aresta(i+aeroportos.size()*2,it->first,voos[it->first-aeroportos.size()*2].saida-voos[i].chegada+voos[i].tempoVoo());//voo que chega do aeroporto -> voo que sai no min 30 min depois
                }else{
                    G.insert_aresta(i+aeroportos.size()*2,it->first,voos[it->first-aeroportos.size()*2].saida+1440-voos[i].chegada+voos[i].tempoVoo());//voo que chega do aeroporto -> voo que sai no antes dos 30 min
                }
            }
        }


        while(true){
            int pai[aeroportos.size()*2+voos.size()], peso[aeroportos.size()*2+voos.size()];
            string origem,destino;

            cout<<"Aeroportos:\n"<<endl;

            for(int i=0;i<aeroportos.size();i++)
                cout<<aeroportos[i].toStdString()<<endl;
            do{
                cout<<"\nDigite o aeroporto de Origem valido:"<<endl;
                cin>>origem;
            }while(buscaAeroporto(&aeroportos,origem)==-1);

            do{
                cout<<"\nDigite o aeroporto de Destino valido:"<<endl;
                cin>>destino;
            }while(buscaAeroporto(&aeroportos,origem)==-1);

            G.caminho(buscaAeroporto(&aeroportos,origem),peso,pai);

            int busca=buscaAeroporto(&aeroportos,destino)+aeroportos.size();
            stack<int> P;

            while(pai[busca]!=-1){
                P.push(busca);
                busca=pai[busca];
            }
            cout<<endl;
            for(unsigned int i=0;i<P.size();i++){
                int pos=P.top()-aeroportos.size()*2;
                cout<<voos[pos].codigo<<" "
                    <<voos[pos].origem<<" "
                    <<MparaH(voos[pos].saida)<<" "
                    <<voos[pos].destino<<" "
                    <<MparaH(voos[pos].chegada)<<endl;
                P.pop();
            }

            getchar();
            cout<<"Pressione para continuar"<<endl;
            getchar();
            system("cls");
        }
    }
}

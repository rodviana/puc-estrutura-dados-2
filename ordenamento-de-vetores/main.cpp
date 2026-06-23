#include <iostream>
#include <math.h>
#include <fstream>
#include <chrono>
#include <iomanip>


void selectionSort(int *v, int n)
{
    long long int i,m,aux,j;
    for(i=0;i<n-1;i++)
    {
        m=i;
        for(j=i+1;j<n;j++)
        {
            if(v[j]<v[m])
            {
                m=j;
            }
        }
        aux = v[i];
        v[i]=v[m];
        v[m] = aux;
    }
}

void insertionSort(int *v, int n)
{
    long long int aux,i,j;

    for(i=1;i<n;i++)
    {
        aux = v[i];
        for(j=i-1;j>=0 && aux < v[j];j--)
        {
            v[j+1]=v[j];
        }
        v[j+1] = aux;
    }
}

void bubbleSort(int *v, int n)
{
    long long int aux;
    for(int i=n-1;i>0;i--)
    {
        for(int j=0;j<i;j++)
        {
            if(v[j]>v[j+1])
            {
                aux = v[j+1];
                v[j+1] = v[j];
                v[j] = aux;
            }
        }

    }
}

void merge(int *v, int pi, int pf)
{
    int m = (pf+pi)/2;
    int vet[pf-pi+1];
    int i=pi,j=m+1,k=0;
    //pressupõem-se que cada metade está ordenada
    for(;i<=m && j<=pf;k++) // compara até uma das metades "acabar"
    {
        if(v[i]>v[j]) // se elemento da metade da esquerda for maior do que elemento da metade direita
        {
            vet[k] = v[j]; // insere no novo vetor ordenado elemento da metade da direita
            j++;
        }
        else // sempre elemento da metade esquerda for menor OU IGUAL ao da metade direita
        {
            vet[k] = v[i]; //insere no novo vetor ordenado elemento da metade da esquerda
            i++;
        }
    }

    for(;i<=m;i++,k++) // termina de colcocar a metade ordenanda que sobrou, na frente de todos
    {
        vet[k]=v[i];
    }

    for(;j<=pf;j++,k++) // termina de colcocar a metade ordenanda que sobrou, na frente de todos
    {
        vet[k] = v[j];
    }

    for(k=0,i=pi;i<=pf;k++,i++) // sobreescreve vetor original nas posições analisadas, com o novo vetor
    {
        v[i] = vet[k];
    }
}
void mergeSort(int *v, int pi, int pf)
{
    int m;
    if(pi<pf)
    {
        m = (pf + pi)/2; // obtem o indice da metade do vetor
        mergeSort(v, pi, m); // particiona a metade da esquerda
        mergeSort(v, m+1, pf);// particiona a metade da direita
        merge(v, pi,pf); // mistura,ordenando, duas metades já ordenadas anteriormente
    }
}

int partition(int *vet,int l,int r)
{
    int p=vet[l];
    int i=l;
    int j=r+1;
    while(i<j)
    {
        for(j=j-1;vet[j]>=p && i<j;j--);

        if(i<j) vet[i] = vet[j];
        else break;

        for(i=i+1; vet[i]<=p && i<j ;i++);

        if(i<j) vet[j] = vet[i];
        else break;
    }
    vet[i]=p;
    return i;
}
void quickSort(int *vet, int l,int r)
{
    int q;
    if(l<r)
    {
        q = partition(vet ,l ,r);
        quickSort(vet,l, q-1);
        quickSort(vet,q+1,r);
    }
}

void heapfy(int *vet,int i,int n)
{
    int l=2*i+1;
    int r = 2*i+2;
    int m, aux;
    if(l<n && vet[l]>vet[i]) m = l;
    else m = i;

    if(r<n && vet[r]>vet[m]) m = r;

    if(m != i)
    {
        aux = vet[i];
        vet[i] = vet[m];
        vet[m] = aux;
        heapfy(vet, m, n);
    }
}
void buildHeap(int *vet, int n)
{
    for(int i = (n-1)/2; i>=0;i--)
    {
        heapfy(vet, i,n);
    }
}
void heapSort(int *vet, int n)
{
    long long int aux;
     buildHeap(vet,n);
     for(int i=n-1;i>0;)
     {
         aux = vet[i];
         vet[i] = vet[0];
         vet[0] = aux;
         i--;
         heapfy(vet,0,i);

     }
}

void countingSort(int *a,int n,int d)
{
    int b[n],x;
    int i,c[10];
    for(i=0;i<=9;i++)
    {
        c[i]=0;
    }
    for(i=0;i<n;i++)
    {
        b[i]=-10;
        x=a[i]/pow(10,d-1);
        x=x%10;
        c[x]++;
    }
    for(i=1;i<=9;i++)
    {

        c[i] += c[i-1];
    }
    for(i=n-1;i>=0;i--)
    {
        x=a[i]/pow(10,d-1);
        x=x%10;
        b[c[x]-1] = a[i];
        c[x]--;
    }
    for(i=0;i<n;i++)
    {
        if( b[i]!=-10) a[i] = b[i];
    }
}
void radixSort(int *vet, int n, int d)
{
    for(int i=1;i<=d;i++)
    {
        countingSort(vet,n,i);
    }
}

void inicializaDez(int *a,int *b)
{
    //inicializa vetor 10 posições
    for(int i=0;i<10;i++)
    {
        a[i] = i;
        b[9-i] = i;
    }
}
void inicializaMil(int *a,int *b,int *c)
{
    int j =1000;
    std::string nomeArquivo = "milA.txt";
    std::string aux;
    std::ifstream arquivoEntrada(nomeArquivo.c_str());
    for(int i=0;i<1000;i++, j++)
    {
        a[i] = j;
        b[999-i] = j;
        arquivoEntrada>>aux;
        c[i]=std::stoi(aux);
    }
    arquivoEntrada.close();

}
void inicializa100Mil(int *a,int *b,int *c)
{
    std::string nomeArquivo = "milA.txt";
    std::string aux;
    std::ifstream arquivoEntrada(nomeArquivo.c_str());
    for(int i=0;i<100000;i++)
    {
        a[i] = i;
        b[99999-i] = i;
        arquivoEntrada>>aux;
        c[i]=std::stoi(aux);
    }
    arquivoEntrada.close();
}
void inicializaMilhao(int *a,int *b,int *c)
{

    std::string nomeArquivo = "milhaoA.txt";
    std::string aux;
    std::ifstream arquivoEntrada(nomeArquivo.c_str());
    int j=0;
    for(int i=0;i<1000000;i++,j++)
    {
        if(j>100000) j=0;
        a[i] = j;
        b[999999-i] = j;
        arquivoEntrada>>aux;
        c[i]=std::stoi(aux);
    }
    arquivoEntrada.close();
}


int main()
{

    std::chrono::high_resolution_clock::time_point inicio;

    int *vetOrd;
    int *vetDec;
    int *vetA;

     std::chrono::duration<double> aux;
     double ordS[4], ordI[4], ordB[4],ordM[4],ordQ[4],ordH[4],ordR[4];
     double decS[4], decI[4], decB[4],decM[4],decQ[4],decH[4],decR[4];
     double aS[4], aI[4], aB[4],aM[4],aQ[4],aH[4],aR[4];



    for(int i=0;i<4;i++)
    {
        ordS[i]=0; ordI[i]=0; ordB[i]=0; ordM[i]=0; ordQ[i]=0; ordH[i]=0; ordR[i]=0;
        decS[i]=0; decI[i]=0; decB[i]=0; decM[i]=0; decQ[i]=0; decH[i]=0; decR[i]=0;
        aS[i]=0; aI[i]=0; aB[i]=0; aM[i]=0; aQ[i]=0; aH[i]=0; aR[i]=0;
    }

    //dez selection


    vetOrd = new int [10];
    vetDec = new int [10];
    vetA = new int [10] {1,7,4,0,9,4,8,8,2,4};
    inicializaDez(vetOrd,vetDec);


    inicio = std::chrono::high_resolution_clock::now();
    selectionSort(vetOrd,10);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordS[0] = aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    selectionSort(vetDec,10);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decS[0] = aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    selectionSort(vetA,10);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aS[0] = aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;

    //dez insertion


    vetOrd = new int [10];
    vetDec = new int [10];
    vetA = new int [10] {1,7,4,0,9,4,8,8,2,4};
    inicializaDez(vetOrd,vetDec);

    inicio = std::chrono::high_resolution_clock::now();
    insertionSort(vetOrd,10);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordI[0]= aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    insertionSort(vetDec,10);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decI[0] = aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    insertionSort(vetA,10);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aI[0]=aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;

    //dez bubble
    vetOrd = new int [10];
    vetDec = new int [10];
    vetA = new int [10] {1,7,4,0,9,4,8,8,2,4};
    inicializaDez(vetOrd,vetDec);

    inicio = std::chrono::high_resolution_clock::now();
    bubbleSort(vetOrd,10);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordB[0]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    bubbleSort(vetDec,10);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decB[0]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    bubbleSort(vetA,10);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aB[0]=aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;

    // dez merge
    vetOrd = new int [10];
    vetDec = new int [10];
    vetA = new int [10] {1,7,4,0,9,4,8,8,2,4};
    inicializaDez(vetOrd,vetDec);

    inicio = std::chrono::high_resolution_clock::now();
    mergeSort(vetOrd,0,9);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordM[0]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    mergeSort(vetDec,0,9);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decM[0]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    mergeSort(vetA,0,9);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aM[0]=aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;

    // dez quick
    vetOrd = new int [10];
    vetDec = new int [10];
    vetA = new int [10] {1,7,4,0,9,4,8,8,2,4};
    inicializaDez(vetOrd,vetDec);

    inicio = std::chrono::high_resolution_clock::now();
    quickSort(vetOrd,0,9);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordQ[0]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    quickSort(vetDec,0,9);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decQ[0]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    quickSort(vetA,0,9);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aQ[0]=aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;

    // dez heap
    vetOrd = new int [10];
    vetDec = new int [10];
    vetA = new int [10] {1,7,4,0,9,4,8,8,2,4};
    inicializaDez(vetOrd,vetDec);

    inicio = std::chrono::high_resolution_clock::now();
    heapSort(vetOrd,10);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordH[0]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    heapSort(vetDec,10);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decH[0]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    heapSort(vetA,10);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aH[0]=aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;

    //dez radix
    vetOrd = new int [10];
    vetDec = new int [10];
    vetA = new int [10] {1,7,4,0,9,4,8,8,2,4};
    inicializaDez(vetOrd,vetDec);

    inicio = std::chrono::high_resolution_clock::now();
    radixSort(vetOrd,10,1);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordR[0]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    radixSort(vetDec,10,1);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decR[0]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    radixSort(vetA,10,1);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aR[0]=aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;

    //-----------------------------------------------------------------------

    //mil selection


    vetOrd = new int [1000];
    vetDec = new int [1000];
    vetA = new int [1000];
    inicializaMil(vetOrd,vetDec,vetA);

    inicio = std::chrono::high_resolution_clock::now();
    selectionSort(vetOrd,1000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordS[1] = aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    selectionSort(vetDec,1000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decS[1] = aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    selectionSort(vetA,1000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aS[1] = aux.count() * 1000;



    delete vetOrd; delete vetDec; delete vetA;

    //mil insertion


    vetOrd = new int [1000];
    vetDec = new int [1000];
    vetA = new int [1000];
    inicializaMil(vetOrd,vetDec,vetA);

    inicio = std::chrono::high_resolution_clock::now();
    insertionSort(vetOrd,1000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordI[1]= aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    insertionSort(vetDec,1000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decI[1] = aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    insertionSort(vetA,1000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aI[1]=aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;

    //mil bubble
    vetOrd = new int [1000];
    vetDec = new int [1000];
    vetA = new int [1000];
    inicializaMil(vetOrd,vetDec,vetA);

    inicio = std::chrono::high_resolution_clock::now();
    bubbleSort(vetOrd,1000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordB[1]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    bubbleSort(vetDec,1000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decB[1]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    bubbleSort(vetA,1000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aB[1]=aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;

    // mil merge
    vetOrd = new int [1000];
    vetDec = new int [1000];
    vetA = new int [1000];
    inicializaMil(vetOrd,vetDec,vetA);

    inicio = std::chrono::high_resolution_clock::now();
    mergeSort(vetOrd,0,999);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordM[1]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    mergeSort(vetDec,0,999);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decM[1]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    mergeSort(vetA,0,999);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aM[1]=aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;

    // mil quick
    vetOrd = new int [1000];
    vetDec = new int [1000];
    vetA = new int [1000];
    inicializaMil(vetOrd,vetDec,vetA);

    inicio = std::chrono::high_resolution_clock::now();
    quickSort(vetOrd,0,999);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordQ[1]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    quickSort(vetDec,0,999);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decQ[1]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    quickSort(vetA,0,999);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aQ[1]=aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;

    // mil heap
    vetOrd = new int [1000];
    vetDec = new int [1000];
    vetA = new int [1000];
    inicializaMil(vetOrd,vetDec,vetA);

    inicio = std::chrono::high_resolution_clock::now();
    heapSort(vetOrd,1000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordH[1]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    heapSort(vetDec,1000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decH[1]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    heapSort(vetA,1000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aH[1]=aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;

    //mil radix
    vetOrd = new int [1000];
    vetDec = new int [1000];
    vetA = new int [1000];
    inicializaMil(vetOrd,vetDec,vetA);

    inicio = std::chrono::high_resolution_clock::now();
    radixSort(vetOrd,1000,3);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordR[1]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    radixSort(vetDec,1000,3);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decR[1]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    radixSort(vetA,1000,3);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aR[1]=aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;
//-----------------------------------------------------------------------------------------------------
    //100mil selection

        vetOrd = new int [100000];
        vetDec = new int [100000];
        vetA = new int [100000];
        inicializa100Mil(vetOrd,vetDec,vetA);


        inicio = std::chrono::high_resolution_clock::now();
        selectionSort(vetOrd,100000);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        ordS[2] = aux.count() * 1000;

        inicio = std::chrono::high_resolution_clock::now();
        selectionSort(vetDec,100000);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        decS[2] = aux.count() * 1000;

        inicio = std::chrono::high_resolution_clock::now();
        selectionSort(vetA,100000);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        aS[2] = aux.count() * 1000;


        delete vetOrd; delete vetDec; delete vetA;

        //cem mil insertion


        vetOrd = new int [100000];
        vetDec = new int [100000];
        vetA = new int [100000];
        inicializa100Mil(vetOrd,vetDec,vetA);

        inicio = std::chrono::high_resolution_clock::now();
        insertionSort(vetOrd,100000);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        ordI[2]= aux.count() * 1000;

        inicio = std::chrono::high_resolution_clock::now();
        insertionSort(vetDec,100000);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        decI[2] = aux.count() * 1000;

        inicio = std::chrono::high_resolution_clock::now();
        insertionSort(vetA,100000);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        aI[2]=aux.count() * 1000;

        delete vetOrd; delete vetDec; delete vetA;

        //cem mil bubble

        vetOrd = new int [100000];
        vetDec = new int [100000];
        vetA = new int [100000];
        inicializa100Mil(vetOrd,vetDec,vetA);

        inicio = std::chrono::high_resolution_clock::now();
        bubbleSort(vetOrd,100000);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        ordB[2]=aux.count() * 1000;

        inicio = std::chrono::high_resolution_clock::now();
        bubbleSort(vetDec,100000);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        decB[2]=aux.count() * 1000;

        inicio = std::chrono::high_resolution_clock::now();
        bubbleSort(vetA,100000);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        aB[2]=aux.count() * 1000;

        delete vetOrd; delete vetDec; delete vetA;

        // cem mil merge

        vetOrd = new int [100000];
        vetDec = new int [100000];
        vetA = new int [100000];
        inicializa100Mil(vetOrd,vetDec,vetA);

        inicio = std::chrono::high_resolution_clock::now();
        mergeSort(vetOrd,0,99999);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        ordM[2]=aux.count() * 1000;

        inicio = std::chrono::high_resolution_clock::now();
        mergeSort(vetDec,0,99999);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        decM[2]=aux.count() * 1000;

        inicio = std::chrono::high_resolution_clock::now();
        mergeSort(vetA,0,99999);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        aM[2]=aux.count() * 1000;

        delete vetOrd; delete vetDec; delete vetA;

/*
        // cem mil quick

        vetOrd = new int [100000];
        vetDec = new int [100000];
        vetA = new int [100000];
        inicializa100Mil(vetOrd,vetDec,vetA);

        inicio = std::chrono::high_resolution_clock::now();
        quickSort(vetOrd,0,99999);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        ordQ[2]=aux.count() * 1000;

        inicio = std::chrono::high_resolution_clock::now();
        quickSort(vetDec,0,99999);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        decQ[2]=aux.count() * 1000;

        inicio = std::chrono::high_resolution_clock::now();
        quickSort(vetA,0,99999);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        aQ[2]=aux.count() * 1000;

        delete vetOrd; delete vetDec; delete vetA;
*/
        // cem mil heap

        vetOrd = new int [100000];
        vetDec = new int [100000];
        vetA = new int [100000];
        inicializa100Mil(vetOrd,vetDec,vetA);

        inicio = std::chrono::high_resolution_clock::now();
        heapSort(vetOrd,100000);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        ordH[2]=aux.count() * 1000;

        inicio = std::chrono::high_resolution_clock::now();
        heapSort(vetDec,100000);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        decH[2]=aux.count() * 1000;

        inicio = std::chrono::high_resolution_clock::now();
        heapSort(vetA,100000);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        aH[2]=aux.count() * 1000;

        delete vetOrd; delete vetDec; delete vetA;

        //cem mil radix

        vetOrd = new int [100000];
        vetDec = new int [100000];
        vetA = new int [100000];
        inicializa100Mil(vetOrd,vetDec,vetA);

        inicio = std::chrono::high_resolution_clock::now();
        radixSort(vetOrd,100000,6);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        ordR[2]=aux.count() * 1000;

        inicio = std::chrono::high_resolution_clock::now();
        radixSort(vetDec,100000,6);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        decR[2]=aux.count() * 1000;

        inicio = std::chrono::high_resolution_clock::now();
        radixSort(vetA,100000,6);
        aux = std::chrono::high_resolution_clock::now() - inicio;
        aR[2]=aux.count() * 1000;

        delete vetOrd; delete vetDec; delete vetA;


//--------------------------------------------------------------------------------------------------------------
    //milhao selection

    vetOrd = new int [1000000];
    vetDec = new int [1000000];
    vetA = new int [1000000];
    inicializaMilhao(vetOrd,vetDec,vetA);

    inicio = std::chrono::high_resolution_clock::now();
    selectionSort(vetOrd,1000000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordS[3] = aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    selectionSort(vetDec,1000000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decS[3] = aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    selectionSort(vetA,1000000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aS[3] = aux.count() * 1000;



    delete vetOrd; delete vetDec; delete vetA;

    //milhao insertion


    vetOrd = new int [1000000];
    vetDec = new int [1000000];
    vetA = new int [1000000];
    inicializaMilhao(vetOrd,vetDec,vetA);

    inicio = std::chrono::high_resolution_clock::now();
    insertionSort(vetOrd,1000000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordI[3]= aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    insertionSort(vetDec,1000000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decI[3] = aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    insertionSort(vetA,1000000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aI[3]=aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;

    //milhao bubble

    vetOrd = new int [1000000];
    vetDec = new int [1000000];
    vetA = new int [1000000];
    inicializaMilhao(vetOrd,vetDec,vetA);

    inicio = std::chrono::high_resolution_clock::now();
    bubbleSort(vetOrd,1000000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordB[3]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    bubbleSort(vetDec,1000000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decB[3]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    bubbleSort(vetA,1000000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aB[3]=aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;



/*
    // milhao merge

    vetOrd = new int [1000000];
    vetDec = new int [1000000];
    vetA = new int [1000000];
    inicializaMilhao(vetOrd,vetDec,vetA);

    inicio = std::chrono::high_resolution_clock::now();
    mergeSort(vetOrd,0,999999);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordM[3]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    mergeSort(vetDec,0,999999);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decM[3]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    mergeSort(vetA,0,999999);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aM[3]=aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;

    // milhao quick

    vetOrd = new int [1000000];
    vetDec = new int [1000000];
    vetA = new int [1000000];
    inicializaMilhao(vetOrd,vetDec,vetA);

    inicio = std::chrono::high_resolution_clock::now();
    quickSort(vetOrd,0,999999);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordQ[3]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    quickSort(vetDec,0,999999);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decQ[3]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    quickSort(vetA,0,999999);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aQ[3]=aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;
*/
   // milhao heap

    vetOrd = new int [1000000];
    vetDec = new int [1000000];
    vetA = new int [1000000];
    inicializaMilhao(vetOrd,vetDec,vetA);

    inicio = std::chrono::high_resolution_clock::now();
    heapSort(vetOrd,1000000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordH[3]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    heapSort(vetDec,1000000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decH[3]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    heapSort(vetA,1000000);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aH[3]=aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;

    //milhao radix
/*
    vetOrd = new int [1000000];
    vetDec = new int [1000000];
    vetA = new int [1000000];
    inicializaMilhao(vetOrd,vetDec,vetA);

    inicio = std::chrono::high_resolution_clock::now();
    radixSort(vetOrd,1000000,6);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    ordR[3]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    radixSort(vetDec,1000000,6);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    decR[3]=aux.count() * 1000;

    inicio = std::chrono::high_resolution_clock::now();
    radixSort(vetA,1000000,6);
    aux = std::chrono::high_resolution_clock::now() - inicio;
    aR[3]=aux.count() * 1000;

    delete vetOrd; delete vetDec; delete vetA;
*/


    std::cout<<"          |                         ordenado                         |                 ordenado decrescente                    |                     aleatorio            "<<std::endl;
    std::cout<<"          |      10     |     10^3     |     10^5     |     10^6     |     10     |     10^3     |     10^5     |     10^6     |     10     |    10^3    |    10^5    |     10^6     "<<std::endl;
    std::cout<<std::fixed<<std::setprecision(6)<<"selection |"<<ordS[0]<<"     |"<<ordS[1]<<"      |"<<ordS[2]<<"     |"<<ordS[3]<<"  |"<<decS[0]<<"    |"<<decS[1]<<"      |"<<decS[2]<<"      |"<<decS[3]<<"  |"<<aS[0]<<"    |"<<aS[1]<<"    |"<<aS[2]<<"    |"<<aS[3]<<"          "<<std::endl;
    std::cout<<std::fixed<<std::setprecision(6)<<"insertion |"<<ordI[0]<<"     |"<<ordI[1]<<"      |"<<ordI[2]<<"     |"<<ordI[3]<<"     |"<<decI[0]<<"    |"<<decI[1]<<"      |"<<decI[2]<<"      |"<<decI[3]<<"  |"<<aI[0]<<"    |"<<aI[1]<<"    |"<<aI[2]<<"    |"<<aI[3]<<"          "<<std::endl;
    std::cout<<std::fixed<<std::setprecision(6)<<"bubble    |"<<ordB[0]<<"     |"<<ordB[1]<<"      |"<<ordB[2]<<"     |"<<ordB[3]<<" |"<<decB[0]<<"    |"<<decB[1]<<"      |"<<decB[2]<<"      |"<<decB[3]<<" |"<<aB[0]<<"    |"<<aB[1]<<"    |"<<aB[2]<<"    |"<<aB[3]<<"          "<<std::endl;
    std::cout<<std::fixed<<std::setprecision(6)<<"merge     |"<<ordM[0]<<"     |"<<ordM[1]<<"      |"<<ordM[2]<<"     |"<<ordM[3]<<"      |"<<decM[0]<<"    |"<<decM[1]<<"      |"<<decM[2]<<"      |"<<decM[3]<<"      |"<<aM[0]<<"    |"<<aM[1]<<"    |"<<aM[2]<<"    |"<<aM[3]<<"          "<<std::endl;
    std::cout<<std::fixed<<std::setprecision(6)<<"quick     |"<<ordQ[0]<<"     |"<<ordQ[1]<<"      |"<<ordQ[2]<<"      |"<<ordQ[3]<<"      |"<<decQ[0]<<"    |"<<decQ[1]<<"      |"<<decQ[2]<<"      |"<<decQ[3]<<"      |"<<aQ[0]<<"    |"<<aQ[1]<<"    |"<<aQ[2]<<"    |"<<aQ[3]<<"          "<<std::endl;
    std::cout<<std::fixed<<std::setprecision(6)<<"heap      |"<<ordH[0]<<"     |"<<ordH[1]<<"      |"<<ordH[2]<<"    |"<<ordH[3]<<"    "<<decH[0]<<"    |"<<decH[1]<<"      |"<<decH[2]<<"     |"<<decR[3]<<"   |"<<aH[0]<<"    |"<<aH[1]<<"    |"<<aH[2]<<"    |"<<aH[3]<<"          "<<std::endl;
    std::cout<<std::fixed<<std::setprecision(6)<<"radix     |"<<ordR[0]<<"     |"<<ordR[1]<<"      |"<<ordR[2]<<"     |"<<ordR[3]<<"      |"<<decR[0]<<"    |"<<decR[1]<<"      |"<<decR[2]<<"      |"<<decH[3]<<"      |"<<aR[0]<<"    |"<<aR[1]<<"    |"<<aR[2]<<"    |"<<aR[3]<<"          "<<std::endl;
    return 0;
}

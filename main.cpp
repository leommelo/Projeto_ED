#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

struct trade{
    int year;
    char accountType [50];
    char code [50];
    char paisCode [10];
    char productType [50];
    double valor;
    char status [10];
};

class Arquivo {
    public:
        Arquivo();
        ~Arquivo();
        void imprimir(int i);
        void imprimirTodos();
        void imprimirTrecho(int x, int y);
        void adicionarPos();
        void alterar();
    private:
        fstream arquivo;
        int tamanho;
};

Arquivo::Arquivo(){
    arquivo = fstream("arquivo_binario.bin", ios::binary | ios::in | ios::out | ios::ate);
    streampos fileSize = arquivo.tellg();
    tamanho = fileSize / sizeof(trade);
    cout << "Número total de registros : " << tamanho << endl << endl;
};

Arquivo::~Arquivo(){
    arquivo.close();
};

void Arquivo::imprimir(int i){
    trade trades;

    arquivo.seekg(sizeof(trade)*i);
    arquivo.read((char*) &trades, sizeof(trade));
    cout << "Ano: " << trades.year << endl
         << "Conta: " << trades.accountType << endl
         << "Código: " << trades.code << endl
         << "Código do país" << trades.paisCode << endl
         << "Tipo do produto: " << trades.productType << endl
         << "Valor: " << trades.valor << endl
         << "Status: " << trades.status << endl << endl;
};

void Arquivo::imprimirTodos(){
    for (int i = 0; i < tamanho; i++)
    {
        imprimir(i);
    }
}

void Arquivo::imprimirTrecho(int x,int y){
    for (int i = x; i < y+1; i++)
    {
        imprimir(i);
    }
}

void Arquivo::adicionarPos(){
    trade aux, novoTrade;
    int posicao, posFinal = tamanho, contador = 0;

    cout << "Informe a posição onde será inserido o novo registro: " << endl;
    cin >> posicao;

    /*cout << "Informe os dados do novo registro" << endl
         << "Ano: " << endl;
    cin >> novoTrade.year;
    cout << "Tipo: " << endl;
    cin.getline(novoTrade.accountType, 50);
    cout << "Code: " << endl;
    cin.getline(novoTrade.code,50);
    cout << "País: " << endl;
    cin.getline(novoTrade.paisCode,10);
    cout << "Tipo do produto: " << endl;
    cin.getline(novoTrade.productType,50);
    cout << "Valor: " << endl;
    cin >> novoTrade.valor;
    cout << "Status: " << endl;
    cin.getline(novoTrade.status,10); */

    while ((posFinal - contador) >= posicao)
    {
        arquivo.seekg((posFinal-contador)*sizeof(trade));
        arquivo.read((char*) &aux, sizeof(trade));

        arquivo.seekp((posFinal - contador + 1)*sizeof(trade));
        arquivo.write((const char*) &aux, sizeof(trade));

        contador++;
    }
    

    novoTrade.year= 6969;
    novoTrade.valor = 10;

    arquivo.seekp(posicao*sizeof(trade));
    arquivo.write(reinterpret_cast<const char*>(&novoTrade), sizeof(trade));

    tamanho++;
}

void Arquivo::alterar(){
    int posicao;

    cout << "Informe a posicao: " << endl;
    cin >> posicao;

    arquivo
}

int main(){
    Arquivo minhalista;


    minhalista.imprimirTrecho(8, 12);

    return 0;
}
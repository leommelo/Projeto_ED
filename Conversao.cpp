#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

struct trade{
    int year;
    char accountType [50];
    char code [50];
    char paisCode [10];
    char productType [50];
    long double valor;
    char status [10];
};


trade leitura(ifstream& arq){
    trade trades;
    char lixo;
    string nome;
    //getline(arq,trades.year, ',');

    arq >> trades.year;
    arq >> lixo;

    getline(arq, nome, ',');
    strncpy(trades.accountType, nome.c_str(), sizeof(trades.accountType) - 1);

    getline(arq, nome, ',');
    strncpy(trades.code, nome.c_str(), sizeof(trades.code) - 1);

    getline(arq, nome, ',');
    strncpy(trades.paisCode, nome.c_str(), sizeof(trades.paisCode) - 1);

    getline(arq, nome, ',');
    strncpy(trades.productType, nome.c_str(), sizeof(trades.productType) - 1);

    getline(arq, nome, ',');
    if (nome != "")
    {
        trades.valor = stod(nome);
    }
    else{
        trades.valor = 0;
    }

    getline(arq, nome);
    strncpy(trades.status, nome.c_str(), sizeof(trades.status) - 1); 

    return trades;
};


int main(){
    ifstream arq("international-trade-june-2022-quarter-csv (1).csv");

    trade teste;
    if (arq.is_open())
    {
        string lixo;
        getline(arq, lixo);

        fstream arqv("arquivo_binario.bin", ios::binary | ios:: app | ios::in);

        while (!arq.eof())
        {
            teste = leitura(arq);
            arqv.write((char*) &teste, sizeof(trade));
        }

        cout << "Conversão realizada com sucesso!" << endl;      
    }else{
        cout << "Não foi possível abrir o arquivo! :(";
    }
    
}
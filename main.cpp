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


int main(){
    fstream arq;
    trade trades;

    arq.open("arquivo_binario.bin", ios::binary | ios::in | ios::out);
    arq.seekg(sizeof(trade)*1884089);
    arq.read((char*) &trades, sizeof(trade));

    cout << trades.paisCode << endl;


    return 0;
}
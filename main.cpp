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
    long double valor;
    char status [10];
};

class Arquivo {
    public:
        Arquivo();
        ~Arquivo();
        void imprimir(int i);
        void imprimirTodos();
        void imprimirTrecho();
        void adicionarPos();
        void alterar();
        void troca();
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
         << "Código do país: " << trades.paisCode << endl
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

void Arquivo::imprimirTrecho(){
    int comeco, fim;
    cout << "Informe o trecho que deseja exibir:\n De: ";
    cin >> comeco;
    cout << "\n Até:";
    cin >> fim;
    for (int i = comeco; i < fim+1; i++)
    {
        imprimir(i);
    }
}

void Arquivo::adicionarPos(){
    trade aux, novoTrade;
    int posicao, posFinal = tamanho, contador = 1;

    cout << "Informe a posição onde será inserido o novo registro: " << endl;
    cin >> posicao;

    cout << "Informe os dados do novo registro" << endl
         << "Ano: " << endl;
    cin >> novoTrade.year;
    cout << "Tipo: " << endl;
    cin.ignore();
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
    cin.ignore();
    cin.getline(novoTrade.status,10); 

    while ((posFinal - contador) >= posicao)
    {
        arquivo.seekg((posFinal-contador)*sizeof(trade));
        arquivo.read((char*) &aux, sizeof(trade));

        arquivo.seekp((posFinal - contador + 1)*sizeof(trade));
        arquivo.write((const char*) &aux, sizeof(trade));

        contador++;
    }

    arquivo.seekp(posicao*sizeof(trade));
    arquivo.write(reinterpret_cast<const char*>(&novoTrade), sizeof(trade));

    tamanho++;
}


void Arquivo::alterar(){
    int posicao;
    trade alteraTrade;

    cout << "Informe a posicao: " << endl;
    cin >> posicao;

    cout << "Informe os dados do novo registro" << endl
         << "Ano: " << endl;
    cin >> alteraTrade.year;
    cout << "Tipo: " << endl;
    cin.ignore();
    cin.getline(alteraTrade.accountType, 50);
    cout << "Code: " << endl;
    cin.getline(alteraTrade.code,50);
    cout << "País: " << endl;
    cin.getline(alteraTrade.paisCode,10);
    cout << "Tipo do produto: " << endl;
    cin.getline(alteraTrade.productType,50);
    cout << "Valor: " << endl;
    cin >> alteraTrade.valor;
    cout << "Status: " << endl;
    cin.ignore();
    cin.getline(alteraTrade.status,10); 

    arquivo.seekg(posicao*sizeof(trade));
    arquivo.write((char*) &alteraTrade, sizeof(trade));
}

void Arquivo::troca(){
    int p1, p2;
    
    cout<<"Insira as posições da troca"<<endl;
    cin>>p1>>p2;

    trade troca1;
    trade troca2;

    arquivo.seekg(sizeof(trade)*p1);
    arquivo.read(reinterpret_cast<char*>(&troca1), sizeof(trade));

    arquivo.seekg(sizeof(trade)*p2);
    arquivo.read(reinterpret_cast<char*>(&troca2), sizeof(trade));

    arquivo.seekp(sizeof(trade)*p1);
    arquivo.write(reinterpret_cast<const char*>(&troca2), sizeof(trade));

    arquivo.seekp(sizeof(trade)*p2);
    arquivo.write(reinterpret_cast<const char*>(&troca1), sizeof(trade));
}

int main(){
    Arquivo minhalista;
    int h;
    cout << endl << "########## Bem-Vindo(a) ##########" << endl << endl;

        do {
            try{
                cout << "1: Mostrar os registros\n2: Inserir um Registro\n3: Editar um registro\n4: Trocar Registros de poisições\n0: Sair" << endl << endl;
                cin >> h;

                switch (h){
                case 1:
                    int opcao;
                    cout << "De que maneira deseja exibir os registros? \n1: A lista completa\n2: Apenas um trecho" << endl;
                    cin >> opcao;
                    if (opcao == 1){
                        minhalista.imprimirTodos();
                    } else if (opcao == 2){
                        minhalista.imprimirTrecho();
                    }else{
                        cout << "Opção inválida!" << endl;
                    }
                    cout << endl;
                    break;
                           
                case 2:
                    minhalista.adicionarPos();
                    break;
                
                case 3:
                    minhalista.alterar();
                    break;
                

                case 4:
                    minhalista.troca();
                    break;
                

                case 0:
                    break;
                
                default:
                    cerr << "Opção inválida\n";
                    
                }
            }
            catch (runtime_error& e) {
            cout << e.what() << endl;
            }
        }while(h != 0);

        cout << endl << "Até logo!! :D" << endl;

    return 0;
}
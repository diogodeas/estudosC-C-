#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*
------------------------------------------------------------------------------------------------------------------------------------------
Lógica:
-salvar cada numero do arquivo numa posiçao de um vetor                                                                                                                                  
-Vericar uma linha de caixas.
-Caso não haja caixas com 0, pode somar as caixas acima. Guardar isso numa variável.
-Caso haja uma caixa com 0, parar a verificação. Pegar a variável da soma e comparar para ver se essa é a maior soma.
-Se ela for a maior da soma, guardar numa variável separada.
-Repetir isso para linha seguinte.
------------------------------------------------------------------------------------------------------------------------------------------
*/

int maiorSoma = 0;
int primeiraSoma = 0;
int fileiraDaMaiorSoma = 0;
int caixaDaMaiorSoma = 0;

void verificarSoma(int somaAtual, int fileira, int caixa) {
    // se essa função for chamada pela primeira vez, a maior soma será a própria "somaAtual"
    if(primeiraSoma == 0){
        primeiraSoma++;
        maiorSoma = somaAtual;
        fileiraDaMaiorSoma = fileira;
        caixaDaMaiorSoma = caixa;
    }
    // se a soma atual for maior de a maior soma prévia
    if(somaAtual>maiorSoma){
        maiorSoma = somaAtual;
        fileiraDaMaiorSoma = fileira;
        caixaDaMaiorSoma = caixa;
    }
}


int main () {
    string entrada;
    int somaAtual, contadorParaSoma, numero = 0;
    int i, j, Nfileiras; 
    int matriz [20][20] = {};
    cout << "Digite o nome do arquivo de entrada: ";
    cin>>entrada;
    ifstream arquivo(entrada);
    if(arquivo.is_open()) { // conferindo se os dados foram extraídos do arquivo
        arquivo >> Nfileiras; //passando a quantidade de fileiras para uma variavel
        arquivo >> matriz[0][0]; //guardando o primeiro numero do arquivo na primeira posição do vetor
        //cout << matriz[0][0] << endl;
        for (i = 1; i < Nfileiras; i++) { //percorrendo todas fileiras do arquivo
            for (j = 0; j <= i; j++) { //percorrendo cada numero de cada fileira
                arquivo >> numero; //salvando cada variavel do arquivo numa posição do vetor
                //cout << numero << ' ';
                matriz[i][j] = numero;
            } 
            //cout<<endl;
        }
    } else { //encerra o programa se não há dados no arquivo
        //cerr <<"Não foi possível abrir o arquivo";
        exit(1);
    }

    for(i = 0; i<Nfileiras; i++) {
        contadorParaSoma = 0;
        for (j=0; j<=i; j++) {
            // faz a verificação do 0 na caixa
            if(matriz[i][j]==0 && contadorParaSoma == 0)
                verificarSoma(somaAtual, i+1, j+1);
            // com todas as caixas verificadas, podemos começar a somar o conteúdo de cada caixa à variável "somaAtual"
            if(j == i && contadorParaSoma == 0){
                contadorParaSoma++; // evita que entre nesse if novamente 
                j = 0; // zera o j(apenas uma vez) para podermos somar o conteúdo das caixas da linha i analisada
            }
            if(contadorParaSoma == 1) // adiciona o conteúdo da caixa à variável "somaAtual" (caso já tenha ocorrido a verificação dos zeros em todas as caixas)
                somaAtual = somaAtual + matriz[i][j];
        }        
    }
    cout<<"Resposta: fileira "<< fileiraDaMaiorSoma << ", caixa " << caixaDaMaiorSoma << "."<<endl;
    return 0;
}
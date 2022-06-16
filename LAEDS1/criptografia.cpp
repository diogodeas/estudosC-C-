#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <cmath>
using namespace std;

/*
------------------------------------------------------------------------------------------------------------------------------------------
Lógica:
- Extrair o texto do arquivo e executar cada passada em sequência
- função 1: transformo os binários em inteiro e apago o caracter na psoição desse valor inteiro com uma função do c++
- função 2: reverter a subdivisão de 2, a permutação;
- funcao 3: fazer o espelhamento; //tá espelhando errado.
- função 4: desfazer a cifra de César com rotação de 5 posições a esquerda;
- função 5: substituir tudo que for igual espaço por #
------------------------------------------------------------------------------------------------------------------------------------------
*/

string funcao5 (string mensagem) {
    int i;
    int j =  mensagem.length();
    for(i=0; i<j; i++) {
        if(mensagem[i]== '#') {
            mensagem[i] = ' ';
        }
    }
    return mensagem;
}

string funcao4 (string mensagem) {
    int j = mensagem.length();
        for(int i=0; i<j; i++){
            if((('a' <= mensagem[i]) && (mensagem[i] <='z')) ){
                mensagem[i] = mensagem[i]-5;
                if(mensagem[i]<'a'){
                    mensagem[i] += 26;
                }
            }
            else if (('A'<= mensagem[i]) && (mensagem[i] <='Z')) {
                mensagem[i] = mensagem[i]-5;
                if (mensagem[i] < 'A'){
                    mensagem[i] = mensagem[i]+26;
                }
            }  
        }
    return mensagem;
}
string funcao3 (string mensagem) {
    char refletido1, refletido2;
    int j =  mensagem.length()-1;
    for(int i=0; i<j; i+=2) { //condição pra espelhar o vetor
        refletido1 = mensagem[i];
        refletido2 = mensagem[i+1];
        mensagem[i+1] = refletido1;
        mensagem[i] = refletido2;
    }
    return mensagem;
}
string funcao2 (string mensagem) {
    char primeiro, segundo;
    int j = (mensagem.length()-1), i=0;
    
    //condição para permutar os blocos com o último.
    while(i<(j-2)){
        primeiro = mensagem[i];
        segundo = mensagem[i+1];
        mensagem[i] = mensagem[j-2];
        mensagem[i+1] = mensagem[j-1];
        mensagem[j-2] = primeiro;
        mensagem[j-1] = segundo;
        i = i+4;
        j = j-4;
    }
    return mensagem;
}


string funcao1 (string mensagem) {
    int binario [5];
    int posicaoBinaria=0, k;
    for(int j=0; j<5; j++){
        binario[j] = mensagem [j];
        binario[j] = binario[j]-'0';
    }
    for(int i=4; i>=0; i--){
        posicaoBinaria += binario[i]*pow(2, k);
        k++;
    }  
    mensagem.erase(0, 5);
    mensagem.erase(mensagem.begin() + posicaoBinaria - 1);
    return mensagem;
}


int main() {
    string entrada;
    string descriptando;
    string printada;
    cout << "Digite o nome do arquivo:";
    cin >> entrada;
    ifstream arquivo(entrada);
    if(arquivo.is_open()) {
        string mensagem((istreambuf_iterator<char>(arquivo)), istreambuf_iterator<char>());
        printada = mensagem;
        descriptando = funcao1(mensagem);
        descriptando = funcao2(descriptando);
        descriptando = funcao3(descriptando);
        descriptando = funcao4(descriptando);
        descriptando = funcao5(descriptando);

    } else { //encerra o programa se não há dados no arquivo
        exit(1);
    }
    cout<< "\n--------------------"<<endl;
    cout << "Mensagem codificada:"<<endl;
    cout << "--------------------"<<endl;
    cout << printada <<endl;
    cout << "----------------------"<<endl;
    cout << "Mensagem decodificada:" <<endl;
    cout << "----------------------"<<endl;
    cout << descriptando; 
    return 0;
}
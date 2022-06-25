#include <bits/stdc++.h>
using namespace std;
/*struct myclass {
  bool operator() (int i,int j) { return (i<j);}
} myobject;*/
int main (){
    vector<int> vetor;
    vector<int> vetorNdiferentes;
    vector<int> vetorContador;
    vector<int> copiaVetor;
    vector<int> saidaErrada;

    int N, elemento, contador=1, aux=1, apoio=1;
    string entrada;
    cout<<"Digite o nome do arquivo: ";
    cin>>entrada;
    ifstream arquivo(entrada);
    if(arquivo.is_open()) {
        arquivo >> N;

        for(int i=0; i<N; i++) {
            arquivo >> elemento;
            vetor.push_back(elemento);
        }
	    aux++;
        for(int i=0; i<N-1; i++) {
            if(vetor[i] == vetor[i+1]) {
                contador++; 
            }
            else {
                vetorNdiferentes.push_back(vetor[i]);
                aux++;
                vetorContador.push_back(contador);
                contador = 1;
            }
        }
        vetorContador.push_back(contador);
        vetorNdiferentes.push_back(vetor[N-1]);
        for(int i=0; i<aux-1; i++) {
            copiaVetor.push_back(vetorNdiferentes[i]);
        }

        sort (copiaVetor.begin(), copiaVetor.end());
        for(int i=0; i<aux-1; i++) {
            if(copiaVetor[i]==copiaVetor[i+1]) {
                saidaErrada.push_back(apoio);
            }else{
                saidaErrada.push_back(apoio);
                apoio++;
            }
        }

        int Matriz[aux][2];
        int Matriz2[aux][2];
        for(int i=0; i<aux-1; i++) {
            Matriz[i][0] = saidaErrada[i]; 
            Matriz[i][1] = copiaVetor[i];
        }
    
        for (int i=0; i<aux-1; i++){
            Matriz2[i][1] = vetorNdiferentes[i];
        }

        cout<<"Matriz:"<<endl;
        for (int i=0; i<aux-1; i++){
            if(Matriz[i][1] == Matriz2[i][1]){
                Matriz2[i][0] = Matriz[i][0];
            }

            else {
                for(int j=0; j<aux-1; j++){
                    if(Matriz2[i][1] == Matriz[j][1]){
                        Matriz2[i][0] = Matriz[j][0];
                    }
                }
            }

            cout<<Matriz2[i][0]<<' ';
        }

        cout<<endl;
        for (int i=0; i<aux-1; i++){
            Matriz2[i][1] = vetorContador[i]; 
            cout<<Matriz2[i][1]<<' '; 
        }

        cout<<endl;
    }

    return 0;
}
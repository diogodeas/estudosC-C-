#include <bits/stdc++.h>

using namespace std;

int main() {
    //sequencias das notas dadas pelo enunciado:
    string sequencia = {"C, C#, D, D#, E, F, F#, G, G#, A, A#, B, C, C#, D, D#, E, F, F#, G, G#, A, A#, B"};
    string sequencia2 = {"B#, Db, D, Eb, Fb, E#, Gb, G, Ab, A, Bb, Cb, B#, Db, D, Eb, Fb, E#, Gb, G, Ab, A, Bb, A#"};

    int nNotas, nTrechoPlagio;
    cin >> nNotas;
    cin >> nTrechoPlagio;

    do {
        //inicializando todas strings que eu usarei
//        string notas, trechoPlagio;
        string notas(nNotas, ' ');
        string trechoPlagio(nTrechoPlagio, ' ');
        string anteriores, posteriores;
        string anteriores2, posteriores2;

//        getchar(); //para receber os dados do usuario corretamente tenho que usar esse getchar
//        getline(cin, notas);  //usuario insere as notas que suspeita
        for (int i = 0; i < nNotas; i++) { //imprimo a fim de testes
            cin >> notas[i];
            cout << notas[i];
        }
        cout << endl;

//        getline(cin, trechoPlagio); //usuario insere as notas que suspeita
        for (int i = 0; i < nTrechoPlagio; i++) {//imprimo a fim de testes
            cin >> trechoPlagio[i];
            cout << trechoPlagio[i];
        }
        cout << endl;

        bool found = notas.find(trechoPlagio) != string::npos; //comparo se a plágio no mesmo tom
        cout << "Plágio encontrado: " << found << endl;

        //criei uma lógica que percorre as notas suspeitas e as sequencias e cria novas notas com tons diferentes,
        //cada nota tem duas notas anterioes e duas posteriores que poodem ser novos tons
        for (int i = 0; i < nNotas; i++) {
            for (int j = 0; j < 24; j++) {
                if (notas[i] == sequencia[j] || notas[i] == sequencia2[j]) {
                    posteriores[i] = sequencia[j + 1];
                    posteriores2[i] = sequencia2[j + 1];
                    anteriores[i] = sequencia[j - 1];
                    anteriores2[i] = sequencia2[j - 1];
                    if (sequencia[j] == sequencia[0]) {
                        anteriores[i] = sequencia[23];
                    }
                    if (sequencia[j] == sequencia[23]) {
                        posteriores[i] = sequencia[0];
                    }
                    if (sequencia[j] == sequencia2[0]) {
                        anteriores2[i] = sequencia2[23];
                    }
                    if (sequencia[j] == sequencia2[23]) {
                        posteriores2[i] = sequencia2[0];
                    }
                }
            }
        }

        bool found1 = anteriores.find(trechoPlagio) != string::npos;
        bool found2 = anteriores2.find(trechoPlagio) != string::npos;
        bool found3 = posteriores.find(trechoPlagio) != string::npos;
        bool found4 = posteriores2.find(trechoPlagio) != string::npos;


        //testo se algum deu igual, se sim o print é sim
        if (found || found1 || found2 || found3 || found4) {
            cout << "S" << endl;
        } else {
            cout << "N" << endl;
        }

        cin >> nNotas;
        cin >> nTrechoPlagio;


    } while (nNotas != 0 && nTrechoPlagio != 0);

    return 0;
}

/*
Código com getline meio bugado:
-------------------------------------------------------------
#include <bits/stdc++.h>

using namespace std;

int main () {
    int nNotas, nTrechoPlagio;
    
    //sequencias das notas dadas pelo enunciado:
    string sequencia = {"C, C#, D, D#, E, F, F#, G, G#, A, A#, B, C, C#, D, D#, E, F, F#, G, G#, A, A#, B"};
    string sequencia2 = {"B#, Db, D, Eb, Fb, E#, Gb, G, Ab, A, Bb, Cb, B#, Db, D, Eb, Fb, E#, Gb, G, Ab, A, Bb, A#"};
    
    while(1) {
        //usuario diz o tamanho dos vetores
        cin>>nNotas;
        cin>> nTrechoPlagio;

        //inicializando todas strings que eu usarei
        string notas, trechoPlagio;
        string anteriores, posteriores;
        string anteriores2, posteriores2;

        if(nNotas != 0) { //crio condição de parada como enunciado pede
            getchar(); //para receber os dados do usuario corretamente tenho que usar esse getchar
            getline(cin, notas);  //usuario insere as notas que suspeita
            for(int i=0; i<nNotas; i++) { //imprimo a fim de testes
                cout<<notas[i];
            }
            cout<<endl;
            getline(cin, trechoPlagio); //usuario insere as notas que suspeita
            for(int i=0; i<nTrechoPlagio; i++) {//imprimo a fim de testes
                cout<<trechoPlagio[i];
            }
            cout<<endl;
            
            bool found = notas.find(trechoPlagio) != string::npos; //comparo se a plágio no mesmo tom

            //criei uma lógica que percorre as notas suspeitas e as sequencias e cria novas notas com tons diferentes, 
            //cada nota tem duas notas anterioes e duas posteriores que poodem ser novos tons
            for(int i=0; i<nNotas; i++) {
                for(int j=0; j<24; j++) {
                    if(notas[i]==sequencia[j] || notas[i]==sequencia2[j]){
                        posteriores[i] = sequencia[j+1];
                        posteriores2[i] = sequencia2[j+1];
                        anteriores[i] = sequencia[j-1];
                        anteriores2[i] = sequencia2[j-1];
                        if(sequencia[j] == sequencia[0]) {
                            anteriores[i] = sequencia[23];
                        }
                        if(sequencia[j] == sequencia[23]) {
                            posteriores[i] = sequencia[0];
                        } 
                        if(sequencia[j] == sequencia2[0]) {
                            anteriores2[i] = sequencia2[23];
                        }
                        if(sequencia[j] == sequencia2[23]) {
                            posteriores2[i] = sequencia2[0];
                        } 
                    }
                }
            }

            bool found1 = anteriores.find(trechoPlagio) != string::npos;
            bool found2 = anteriores2.find(trechoPlagio) != string::npos;
            bool found3 = posteriores.find(trechoPlagio) != string::npos;
            bool found4 = posteriores2.find(trechoPlagio) != string::npos;


            //testo se algum deu igual, se sim o print é sim
            if (found || found1 || found2 || found3 || found4) {
                cout << "S" <<endl;
            }
            else {
                cout << "N" <<endl;
            }  
        }
    }
    return 0;
}
-------------------------------------------------------------




Código em C comparação bugada
--------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h>

int main() {
    int nNotas, nTrechoPlagio;
    //sequencias das notas dadas pelo enunciado:
    char sequencia[24] = {"C, C#, D, D#, E, F, F#, G, G#, A, A#, B, C, C#, D, D#, E, F, F#, G, G#, A, A#, B"};
    char sequencia2[24] = {"B#, Db, D, Eb, Fb, E#, Gb, G, Ab, A, Bb, Cb, B#, Db, D, Eb, Fb, E#, Gb, G, Ab, A, Bb, A#"};
    while(1) {
        scanf("%d %d", &nNotas, &nTrechoPlagio); //usuario diz o tamanho dos vetores
        //inicializando todas strings que eu usarei
        char notas[nNotas], trechoPlagio[nTrechoPlagio]; 
        char anteriores[nNotas], posteriores[nNotas];
        char anteriores2[nNotas], posteriores2[nNotas];
        if(nNotas != 0) { //crio condição de parada como enunciado pede
            getchar(); //para receber os dados do usuario corretamente tenho que usar esse getchar
            fgets(notas, 100000, stdin); //usuario insere as notas que suspeita
            fgets(trechoPlagio, 100000, stdin); // e o trecho possa ter sido plagiado
            printf("notas: %s", notas); //imprimo a fim de testes
            printf("plagio: %s", trechoPlagio); 

            //comparações não estão funcionando corretamente e isso que estou tentando corrigir
            char *tem = strstr(notas, trechoPlagio); //comparo se a plágio no mesmo tom
            

            //criei uma lógica que percorre as notas suspeitas e as sequencias e cria novas notas com tons diferentes, 
            //cada nota tem duas notas anterioes e duas posteriores que poodem ser novos tons
            for(int i=0; i<nNotas; i++) {
                for(int j=0; j<strlen(sequencia); j++) {
                    if(notas[i]==sequencia[j] || notas[i]==sequencia2[j]){
                        posteriores[i] = sequencia[j+1];
                        posteriores2[i] = sequencia2[j+1];
                        anteriores[i] = sequencia[j-1];
                        anteriores2[i] = sequencia2[j-1];
                        if(sequencia[j] == sequencia[0]) {
                            anteriores[i] = sequencia[23];
                        }
                        if(sequencia[j] == sequencia[23]) {
                            posteriores[i] = sequencia[0];
                        } 
                        if(sequencia[j] == sequencia2[0]) {
                            anteriores2[i] = sequencia2[23];
                        }
                        if(sequencia[j] == sequencia2[23]) {
                            posteriores2[i] = sequencia2[0];
                        } 
                    }
                }
            }

            //comparo todos esses novos tons de msm melodia com o trecho em suspeita
            //pórem essas comparações que não funcionam ainda
            char *tem2 = strstr(anteriores, trechoPlagio);
            char *tem3 = strstr(anteriores2, trechoPlagio);
            char* tem4 = strstr(posteriores, trechoPlagio);
            char* tem5 = strstr(posteriores2, trechoPlagio);


            //testo se algum deu igual, se sim o print é sim
            if(tem || tem2 || tem3 || tem4 || tem5) {
                printf("S\n");
            }else {
                printf("N\n");
            }

        } else {
            break;
        }
    }
}
--------------------------------------------------------------
*/
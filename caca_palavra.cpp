#include <iostream>
#include <iomanip>
#include <cstring>
#define M 10

using namespace std;

int countPalavrasAchadas = 0;

struct Palavras{
    char palavra[100];
};

bool procuraNaHorizontal(char matriz[][M], Palavras palavra, int linha, int coluna){

    bool achouPalavra = false;
    int letra = 0, countAndarColuna = 1;
    
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            if(matriz[i][j] == palavra.palavra[letra]){
                letra++;
                while(true){
                    if(matriz[i][j+countAndarColuna] == palavra.palavra[letra] && palavra.palavra[letra] != '\0'){
                        letra++;
                        countAndarColuna++;
                    }else if(palavra.palavra[letra] == '\0'){
                        cout << "A palavra '"<< palavra.palavra <<"' foi localizada horizontalmente a partir da linha " << i << " e da coluna " << j << endl;
                        achouPalavra = true;
                        break;
                    }else{
                        letra = 0;
                        countAndarColuna = 1;
                        break;
                    }    
                }       
            }
        }
    }

    if(achouPalavra){
        return true;
    }else{
        return false;
    }
}

bool procuraNaVertical(char matriz[][M], Palavras palavra, int linha, int coluna){

    bool achouPalavra = false;
    int letra = 0, countAndarLinha = 1;

    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            if(matriz[i][j] == palavra.palavra[letra]){
                letra++;
                while(true){
                    if(matriz[i+countAndarLinha][j] == palavra.palavra[letra] && palavra.palavra[letra] != '\0'){
                        letra++;
                        countAndarLinha++;
                    }else if(palavra.palavra[letra] == '\0'){
                        cout << "A palavra '"<< palavra.palavra <<"' foi localizada verticalmente a partir da linha " << i << " e da coluna " << j << endl;
                        achouPalavra = true;
                        letra = 0;
                        countAndarLinha = 1;
                        break;
                    }else{
                        letra = 0;
                        countAndarLinha = 1;
                        break;
                    }    
                }       
            }
        }
    }

    if(achouPalavra){
        return true;
    }else{
        return false;
    }
}

bool procuraNaDiagonal(char matriz[][M], Palavras palavra, int linha, int coluna){
    
    bool achouPalavra = false;
    int letra = 0, countAndarDiagonal = 1;
    
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            if(matriz[i][j] == palavra.palavra[letra]){
                letra++;
                while(true){
                    if(matriz[i+countAndarDiagonal][j+countAndarDiagonal] == palavra.palavra[letra] && palavra.palavra[letra] != '\0'){
                        letra++;
                        countAndarDiagonal++;
                    }else if(palavra.palavra[letra] == '\0'){
                        cout << "A palavra '"<< palavra.palavra <<"' foi localizada diagonalmente a partir da linha " << i  << " e da coluna " << j << endl;
                        achouPalavra = true;
                        break;
                    }else{
                        letra = 0;
                        countAndarDiagonal = 1;
                        break;
                    }    
                }       
            }
        }
    }

    if(achouPalavra){
        return true;
    }else{
        return false;
    }    
}

char transformaEmMinuscula(char letra){
    if(letra >= 'A' && letra <= 'Z'){
        return letra + 'a' - 'A';
    }else{
        return letra;
    }
}

int main(){
    int n_palavras, linha, coluna;
    
    cout << "Insira o numero de palavras a serem caçadas:" << endl;
    cin >> n_palavras;
    while(n_palavras < 1 || n_palavras > 100) {
        cout << "O numero de palavras deve estar entre 1 e 100. Por favor, tente novamente." << endl;
        cin >> n_palavras;
    }
    
    cout << "Insira o numero de linhas da matriz:" << endl;
    cin >> linha;
    cout << "Insira o numero de colunas da matriz:" << endl;
    cin >> coluna;
    
    cin.ignore();
    
    Palavras palavras[n_palavras];
    for(int i=0; i<n_palavras; i++){
        cout << "Insira a " << i+1 << "ª palavra a ser caçada:" << endl;
        cin.getline(palavras[i].palavra,100);
        while(strlen(palavras[i].palavra) < 4){
            cout << "Palavra inválida, insira outra palavra com pelo menos 4 letras: " << endl;
            cin.getline(palavras[i].palavra,100);
        }
        for(int j = 0; palavras[i].palavra[j] != '\0'; j++){
            palavras[i].palavra[j] = transformaEmMinuscula(palavras[i].palavra[j]);  
        }
    }

    char matriz[M][M];
    cout << "Insira os elementos da matriz:" << endl;
    for(int i=0; i<linha; i++){
        for(int j=0; j<coluna; j++){
            cin >> matriz[i][j];
            matriz[i][j] = transformaEmMinuscula(matriz[i][j]);
        }
    }
    cout << "A matriz inserida foi:" << endl;
    for(int i=0; i<linha; i++){
        for(int j=0; j<coluna; j++){
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    for(int i = 0; i < n_palavras; i++){

        int countNaoAchou = 0;

        if(procuraNaHorizontal(matriz, palavras[i], linha, coluna) == false){
            countNaoAchou++;
        }if(procuraNaVertical(matriz, palavras[i], linha, coluna) == false){
            countNaoAchou++;
        }if(procuraNaDiagonal(matriz, palavras[i], linha, coluna) == false){
            countNaoAchou++;
        }if(countNaoAchou == 3){
            cout << "A palavra '" << palavras[i].palavra << "' não foi encontrada" << endl;
        }

        countNaoAchou = 0;  
    }
    return 0;
}
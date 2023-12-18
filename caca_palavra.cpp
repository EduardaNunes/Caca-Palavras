#include <iostream>
#include <iomanip>
#include <cstring>
#define M 100

using namespace std;

struct Palavras{
    char palavra[100];
};

void destacarPalavra(char matrizCopia[][M], int tamanho, int linha, int coluna, bool horizontal, bool vertical, bool diagonal){
    if(vertical){
        for(int i = 0; i < tamanho; i++){
            if(matrizCopia[linha+i][coluna] >= 'a' && matrizCopia[linha+i][coluna] <= 'z'){
                matrizCopia[linha+i][coluna] = matrizCopia[linha+i][coluna] - 'a' + 'A';
            }
        }
    }else if(horizontal){
        for(int i = 0; i < tamanho; i++){
            if(matrizCopia[linha][coluna+i] >= 'a' && matrizCopia[linha][coluna+i] <= 'z'){
                matrizCopia[linha][coluna+i] = matrizCopia[linha][coluna+i] - 'a' + 'A';
            }
        }
    }else if(diagonal){
        for(int i = 0; i < tamanho; i++){
            if(matrizCopia[linha+i][coluna+i] >= 'a' && matrizCopia[linha+i][coluna+i] <= 'z'){
                matrizCopia[linha+i][coluna+i] = matrizCopia[linha+i][coluna+i] - 'a' + 'A';
            }
        }
    }
}

bool procuraNaHorizontal(char matriz[][M], char matrizCopia[][M], Palavras palavra, int linha, int coluna){

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
                        cout << "A palavra '"<< palavra.palavra <<"' foi localizada horizontalmente a partir da " << i+1 << "ª linha e da " << j+1 << "ª coluna " << endl;
                        achouPalavra = true;
                        letra = 0;
                        countAndarColuna = 1;
                        destacarPalavra(matrizCopia, strlen(palavra.palavra), i, j, true, false, false);
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

bool procuraNaVertical(char matriz[][M], char matrizCopia[][M], Palavras palavra, int linha, int coluna){

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
                        cout << "A palavra '"<< palavra.palavra <<"' foi localizada verticalmente a partir da " << i+1 << "ª linha e da " << j+1 << "ª coluna " << endl;
                        achouPalavra = true;
                        letra = 0;
                        countAndarLinha = 1;
                        destacarPalavra(matrizCopia, strlen(palavra.palavra), i, j, false, true, false);
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

bool procuraNaDiagonal(char matriz[][M], char matrizCopia[][M], Palavras palavra, int linha, int coluna){
    
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
                        cout << "A palavra '"<< palavra.palavra <<"' foi localizada diagonalmente a partir da " << i+1 << "ª linha e da " << j+1 << "ª coluna " << endl;
                        achouPalavra = true;
                        letra = 0;
                        countAndarDiagonal = 1;
                        destacarPalavra(matrizCopia, strlen(palavra.palavra), i, j, false, false, true);
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

    while(linha != coluna || linha < 10 || linha > M){
        cout << "Valores Inválidos, a matriz deve ser quadrada e estar entre 10 e " << M << " de tamanho, por favor insira novos valores." << endl;
        cout << "Insira o novo numero de linhas da matriz:" << endl;
        cin >> linha;
        cout << "Insira o novo numero de colunas da matriz:" << endl;
        cin >> coluna;
    }
    
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
    char matrizCopia[M][M];
    cout << "Insira os elementos da matriz:" << endl;
    for(int i=0; i<linha; i++){
        for(int j=0; j<coluna; j++){
            cin >> matriz[i][j];
            matriz[i][j] = transformaEmMinuscula(matriz[i][j]);
            matrizCopia[i][j] = matriz[i][j];
        }
    }

    cout << endl << "-------------------------------------------------------------------------------" << endl;
    for(int i = 0; i < n_palavras; i++){

        int countNaoAchou = 0;

        if(procuraNaHorizontal(matriz, matrizCopia, palavras[i], linha, coluna) == false){
            countNaoAchou++;
        }
        if(procuraNaVertical(matriz, matrizCopia, palavras[i], linha, coluna) == false){
            countNaoAchou++;
        }
        if(procuraNaDiagonal(matriz, matrizCopia, palavras[i], linha, coluna) == false){
            countNaoAchou++;
        }
        if(countNaoAchou == 3){
            cout << "A palavra '" << palavras[i].palavra << "' não foi encontrada" << endl;
        }

        countNaoAchou = 0;  
    }
    cout << "--------------------------------------------------------------------------------" << endl << endl;

    cout << "O caça-palavras ficou assim com as palavras encontradas em maiúsculo: " << endl << endl;

    for(int k = 0; k < coluna*2.4; k++){
        cout << "-";
    }
    cout << endl;
    for(int i=0; i<linha; i++){
        cout << "| ";
        for(int j=0; j<coluna; j++){
            cout << matrizCopia[i][j] << " ";                
        }
        cout << " |" << endl;
    }
    for(int k = 0; k < coluna*2.4; k++){
        cout << "-";
    }

    return 0;
}
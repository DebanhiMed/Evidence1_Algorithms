#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Función que calcula el arreglo LPS (Longest Prefix Suffix) para un patrón dado.
// El arreglo LPS se utiliza en el algoritmo KMP para evitar comparaciones innecesarias.
vector<int> lps(string patron) {
    int n = patron.size(); // Longitud del patrón.
    vector<int> lpsv(n, 0); // Vector para almacenar los valores LPS, inicializado en 0.
    int len = 0; // Longitud del prefijo más largo que también es sufijo.
    int i = 1; // Índice para recorrer el patrón.

    // Calcular los valores LPS para el patrón.
    while (i < n) {
        // Si hay coincidencia, incrementa la longitud del prefijo y guarda en LPS.
        if (patron[i] == patron[len]) {
            lpsv[i++] = ++len;
        } 
        else {
            // Si no hay coincidencia
            if (len == 0) {
                lpsv[i] = 0; // No hay prefijo que sea sufijo.
                i++;
            } 
            else {
                // Vuelve a comparar con el último prefijo.
                len = lpsv[len - 1];
            }
        }
    }
    return lpsv; // Retorna el vector LPS.
}

// Función que implementa el algoritmo KMP para encontrar todas las posiciones de coincidencia
// de un patrón en un texto.
vector<int> kmp(string texto, string patron) {
    vector<int> posMatch; // Vector para almacenar las posiciones de coincidencia.
    vector<int> lpsv = lps(patron); // Calcular el arreglo LPS del patrón.
    
    int i = 0; // Índice para recorrer el texto.
    int j = 0; // Índice para recorrer el patrón.

    int n = texto.length(); // Longitud del texto.
    int m = patron.length(); // Longitud del patrón.

    // Recorrer el texto para buscar coincidencias con el patrón.
    while (i < n) {
        // Si hay coincidencia, avanza en ambos índices.
        if (patron[j] == texto[i]) {
            i++;
            j++;
            // Si se encontró una coincidencia completa del patrón.
            if (j == m) {
                posMatch.push_back(i - m); // Guarda la posición de inicio de la coincidencia.
                j = lpsv[j - 1]; // Actualiza j usando el LPS.
            } 
        }
        else {
            // Si no hay coincidencia
            if (j == 0) {
                i++; // Avanza en el texto.
            }
            else {
                j = lpsv[j - 1]; // Vuelve al último prefijo usando LPS.
            }
        }
    }
    return posMatch; // Retorna las posiciones de coincidencia.
}

int main(){
    string file1 = "transmission1.txt";
    string file2 = "transmission2.txt";
    string file3 = "transmission3.txt";
    string malicious = "mcode.txt";
    string outputFile = "checking.txt";

    vector<string> mcode;

    string T1;
    string T2;
    string T3;
    string code;
    
    ifstream inputFile1(file1);
    getline(inputFile1, T1);

    ifstream inputFile2(file2);
    getline(inputFile2, T2);

    ifstream inputFile3(file3);
    getline(inputFile3, T3);

    ifstream mcodeFile(malicious);
    while(getline(mcodeFile, code)) {
        mcode.push_back(code);
    }
    mcodeFile.close();

    for(int i = 0; i < mcode.size(); i++){
        cout << "Código: " << mcode[i] << endl;

        vector<int> debanhilesabekaemepe = kmp(T1, mcode[i]);
        int size = debanhilesabekaemepe.size();
        cout << "Transmission"  << ".txt ==> " << size << " veces" << endl;
        for(int j = 0; j < size; j++){
            cout << debanhilesabekaemepe[j] << ", ";
        }
        cout << endl;
    }

    return 0;
}
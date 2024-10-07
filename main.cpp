//Debanhi Monserrath Medina Elizondo A0083550
//Alejandra Yeray Peña Meza A01722539
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>
using namespace std;

// Complejidad O(m)
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

// Complejidad O(n+m)
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

// Complejidad O(n)
// Función que preprocesa la cadena original al insertar un carácter '#' entre cada carácter.
string preprocess(const string &s) {
    string modified = "#"; // Comienza con un símbolo de separación.
    for (size_t i = 0; i < s.size(); i++) {
        modified += s[i]; // Agrega el carácter actual de la cadena original.
        modified += "#"; // Agrega el símbolo de separación después de cada carácter.
    }
    return modified; // Retorna la cadena modificada.
}

// Complejidad O(n)
// Función que implementa el algoritmo de Manacher para encontrar el palíndromo más largo en una cadena.
pair<string, int> manacher(const string &s) {
    string modified = preprocess(s);  // Preprocesa la cadena original.
    int n = modified.size(); // Longitud de la cadena preprocesada.
    vector<int> P(n, 0);  // Vector para almacenar los radios de los palíndromos.
    int C = 0, R = 0; // C: Centro actual, R: Límite derecho.

    // Aplicar el algoritmo de Manacher.
    for (int i = 0; i < n; ++i) {
        int mirror = 2 * C - i; // Encuentra el espejo del índice actual respecto al centro.

        if (i < R) // Si i está dentro del rango del palíndromo actual.
            P[i] = min(R - i, P[mirror]); // Establece un valor inicial para P[i] usando el palíndromo espejo.

        // Expande el palíndromo alrededor del índice i.
        while (i + P[i] + 1 < n && i - P[i] - 1 >= 0 && modified[i + P[i] + 1] == modified[i - P[i] - 1]) {
            P[i]++; // Aumenta el tamaño del palíndromo si los extremos coinciden.
        }

        // Si se encuentra un nuevo palíndromo que se extiende más allá del límite derecho.
        if (i + P[i] > R) {
            C = i; // Actualiza el centro.
            R = i + P[i]; // Actualiza el límite derecho.
        }
    }

    // Busca el palíndromo más largo encontrado.
    int max_len = 0, center_index = 0;
    for (int i = 0; i < n; ++i) {
        if (P[i] > max_len) {
            max_len = P[i]; // Actualiza la longitud máxima.
            center_index = i; // Guarda el índice del centro del palíndromo más largo.
        }
    }

    // Calcula la posición de inicio del palíndromo más largo en la cadena original.
    int start = (center_index - max_len) / 2;
    return make_pair(s.substr(start, max_len), start); // Retorna el palíndromo más largo.
}


// Complejidad O(n*m)
// Función que encuentra la longitud de la subcadena más larga común entre s1 y s2
string longestSubstring(string s1, string s2) {
    int posEnd;
    string output;
    int n = s1.size(), m = s2.size(); // n -> longitud de s1, m -> longitud de s2
    int max = 0; // Variable para almacenar la longitud máxima encontrada

    // Crear una tabla 2D para almacenar longitudes de subcadenas comunes
    vector<vector<int> > lcs(n, vector<int>(m, 0));
    
    // Inicializar la primera columna de la tabla
    for (int i = 0; i < n; i++) {
        if (s1[i] == s2[0]) {
            lcs[i][0] = 1; // Si hay coincidencia con el primer carácter de s2
            max = 1; // Actualizar el máximo
        } else {
            lcs[i][0] = 0; // No hay coincidencia
        }
    }

    // Inicializar la primera fila de la tabla
    for (int j = 0; j < m; j++) {
        if (s1[0] == s2[j]) {
            lcs[0][j] = 1; // Si hay coincidencia con el primer carácter de s1
            max = 1; // Actualizar el máximo
        } else {
            lcs[0][j] = 0; // No hay coincidencia
        }
    }

    // Rellenar la tabla utilizando programación dinámica
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (s1[i] == s2[j]) {
                // Si hay coincidencia, sumar 1 a la longitud de la subcadena anterior
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
                // Actualizar el máximo si se encuentra una longitud mayor
                if (lcs[i][j] > max) {
                    max = lcs[i][j];
                    posEnd = i;
                }
            } else {
                // Si no hay coincidencia, reiniciar la longitud a 0
                lcs[i][j] = 0;
            }
        }
    }

    if(posEnd != -1){
        return s1.substr(posEnd - max + 1, max);
    }

    return "";
}

// Complejidad O(n^2)
// Función para generar subsecuencias de longitud n-1 a partir de una cadena de entrada
void generateSubsequences(string input, vector<string> &result) {
     // Variable para construir subsecuencias
    string h;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input.size(); j++) {
            // Si el índice es diferente lo agrega a la subsecuencia
            if (i != j) {
                h += input[j];
            }
        }
        // Almacena la subsecuencia generada
        result.push_back(h);
        // Reinicia para la próxima subsecuencia
        h = "";
    }
}

// Complejidad O(k)
// Función para filtrar subsecuencias a una longitud específica y eliminar duplicados
void filterSubsequences(vector<string> subsequences, vector<string> &filteredResult, int newSize) {
    // Conjunto para almacenar subsecuencias 
    unordered_set<string> uniqueSet;
    for (int i = 0; i < subsequences.size(); i++) {
        //Si la longitud coincide con el tamaño deseado
        if (subsequences[i].length() == newSize) {
            //agregar la subsecuencia al conjunto
            uniqueSet.insert(subsequences[i]);
        }
    }
     // Asigna las subsecuencias únicas al resultado
    filteredResult.assign(uniqueSet.begin(), uniqueSet.end());
}


// Complejidad O(n*k)
// Función para encontrar la subsecuencia más frecuente entre los tres archivos
void findMostFrequentSubsequence(string trans1, string trans2, string trans3, string code, string &mostFound, int &maxMatches, string &bestFile) {
    vector<string> subsequences, filteredSubsequences;
    // Genera todas las subsecuencias
    generateSubsequences(code, subsequences);
    // Filtra las subsecuencias 
    filterSubsequences(subsequences, filteredSubsequences, code.length() - 1);
    
    // Inicializa el máximo de coincidencias a 0
    maxMatches = 0;

    for (int i = 0; i < filteredSubsequences.size(); i++) {
        string subseq = filteredSubsequences[i];
        // Cuenta coincidencias en trans1
        int count1 = kmp(trans1, subseq).size();
        // Cuenta coincidencias en trans2
        int count2 = kmp(trans2, subseq).size();
        // Cuenta coincidencias en trans3
        int count3 = kmp(trans3, subseq).size();

        // Actualiza el máximo de coincidencias y el archivo donde se encuentra
        if (count1 > maxMatches) {
            maxMatches = count1;
            mostFound = subseq;
            bestFile = "Transmission1.txt";
        }
        if (count2 > maxMatches) {
            maxMatches = count2;
            mostFound = subseq;
            bestFile = "Transmission2.txt";
        }
        if (count3 > maxMatches) {
            maxMatches = count3;
            mostFound = subseq;
            bestFile = "Transmission3.txt";
        }
    }
}

int main(){
    string file1 = "transmission1.txt";
    string file2 = "transmission2.txt";
    string file3 = "transmission3.txt";
    string malicious = "mcode.txt";
    string outputFile = "checking.txt";

    vector<string> mcode;
    vector<string> transmissions;

    string T1, T2, T3, code;
    
    ifstream inputFile1(file1);
    getline(inputFile1, T1);
    transmissions.push_back(T1);

    ifstream inputFile2(file2);
    getline(inputFile2, T2);
    transmissions.push_back(T2);

    ifstream inputFile3(file3);
    getline(inputFile3, T3);
    transmissions.push_back(T3);

    ifstream mcodeFile(malicious);

    while(getline(mcodeFile, code)) {
        mcode.push_back(code);
    }
    mcodeFile.close();
    
    ofstream output(outputFile);

    for(int i = 0; i < mcode.size(); i++){
        output << "Código: " << mcode[i] << endl;

        for(int j = 0; j < 3; j++){
            vector<int> kmpVector = kmp(transmissions[j], mcode[i]);
            int size = kmpVector.size();

            output << "Transmission" << j + 1 << ".txt ==> " << size << " veces" << endl;

            for(int k = 0; k < size; k++){
                output << kmpVector[k];
                if (k < size - 1) output << ", ";
            }

            output << endl;
        }
        
        string mostFound, bestFile;
        int maxMatches;
        findMostFrequentSubsequence(T1, T2, T3, mcode[i], mostFound, maxMatches, bestFile);

        if (maxMatches > 0) {
            output << "La subsecuencia más encontrada es: " << mostFound 
                   << " con " << maxMatches << " veces en el archivo " << bestFile << endl;
        } else {
            output << "No se encontró ninguna subsecuencia con coincidencias." << endl;
        }

        output << "- - - - - - - - - - - - - -" << endl;
    }

    output << "==============" << endl;
    output << "Palíndromo más grande:" << endl;

    for(int j = 0; j < 3; j++){
        pair<string, int> palindrome = manacher(transmissions[j]);

        output << "Transmission" << j + 1 << ".txt ==> " << "Posición: " << palindrome.second << endl;
        output << palindrome.first << endl;
        output << "----" << endl;
    }

    output << "==============" << endl;
    output << "Los Substring más largos son:" << endl;

    for(int i = 0; i < 3; i++){
        for(int j = i + 1; j < 3; j++){
            output << "T" << i + 1 << "-T" <<  j + 1 << " ==> " << longestSubstring(transmissions[i], transmissions[j]) << endl;
        }
    }

    output.close();
    return 0;
}
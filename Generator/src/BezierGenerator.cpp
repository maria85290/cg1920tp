#include "BezierGenerator.h"

#include <iostream>
#include <string>



bool BezierGenerator::ParseArguments(int argc, char* argv[]) {

    if (argc < 5 ) {
        cerr << "Faltam argumentos!" << endl;
        cerr << "Utilização: " << argv[0] << " bezier  <file_read> <tessellation_level> <filename>" << endl;

        return false;
    }

    SetFilename(argv[4]); //nome do ficheiro, onde será guardado

    file_read = argv[2];
    tesselation = stoi(argv[3]);
    return true;
}

// Funçao que multiplica duas matrizes
// mat2 - matrzi 4x1
// mat1 - matriz 1x4
void mulMatrixMatrix(double *mat1, double *mat2, double res) {
    int i = 0;
    res = 0;
    for (i = 0; i < 4; i++){
           res += mat2[i] * mat1[i];
        }
}


// Funçao que multiplica uma matriz e um vetor
void multMatrixVector(double* v, double* m, double* res) {
    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }

}

double calculos_bezier(double par_u, double par_v, int indices[16], double pontos[290][3])
{ 
  
    // Matriz de Bezier (a matriz transposta é a mesma)
    double m[4][4] = { {-1.0f,  3.0f, -3.0f,  1.0f},
                       { 3.0f, -6.0f,  3.0f,  0.0f},
                       {-3.0f,  3.0f,  0.0f,  0.0f},
                       { 1.0f,  0.0f,  0.0f,  0.0f} };

    // vetores u e v, definidos a custa dos parametros u e v, que por usa vez dependem do valor obtido de acordo com a tecelagem
    double u[1][4] = { {par_u * par_u * par_u, par_u * par_u, par_u, 1} };

    double v[4][1] = { {par_v * par_v * par_v},
                       { par_v * par_v},
                        {par_v},
                        {1} };

    // X_pontos contem a matriz com o valor das abcissas dos pontos de controlo 
    double X_pontos[4][4],Y_pontos[4][4], Z_pontos[4][4];

    // queremos ir buscar as coordenadas dos pontos para cada patch
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // O array indice tem os numeros dos indices do patch
            // vamor percorrer todos os pontos, 
            X_pontos[i][j] = pontos[indices[i * 4 + j]][0];   //matriz com as abcissas do pontos de controlo
            Y_pontos[i][j] = pontos[indices[i * 4 + j]][1];;  //matriz com as coordenadas EM Y, do pontos de controlo
            Z_pontos[i][j] = pontos[indices[i * 4 + j]][2];; // matriz com as coordenadas EM Z, do pontos de controlo
        }
    }

    double res[1][4];
    double X[1][4],Y[1][4],Z[1][4];      

    multMatrixVector(*u, &m[0][0], *res);  // U*MatrizBezier
   
    // Tenho de multiplicar cada valor de res pela matriz dos pontos
    // Temos 3 matrizes de pontos. A matriz com as abcissas, ordenadas e a cordenada em Z

    multMatrixVector(*res, &X_pontos[0][0], *X);  // X será a matriz (1 por 4) que resulta do produto de U*MatrizBezier pelas abcissas ds pontos. Origina uma matriz 4*4
    multMatrixVector(*res, &Y_pontos[0][0], *Y);  
    multMatrixVector(*res, &Z_pontos[0][0], *Z);

    double aux[4][4]; // // (Matrz transposta == M) * V
    multMatrixVector(*v, &m[0][0], *aux);     // aux é uma matriz 4 por 1

    double ponto[3];   // cordenadas na curva
     // Multiplicaçao de 2 matrizes (1x4 por 4x1) -> Origina o ponto na curva
    mulMatrixMatrix(*aux,*X, ponto[0]);
    mulMatrixMatrix(*aux, *Y, ponto[1]);
    mulMatrixMatrix(*aux,*Z, ponto[2]);
   
    return *ponto;
}

void BezierGenerator::GenerateVertices() {
    /*
    Formato do ficheiro, "patchs":
    1º - numero de patches
    2 - reprentaçao de todos os patchs (cada um tem 16 indices)
    3º - Numero total de pontos de controlo
    4º - Lista com todas as coordenadas dos pontos de controlo
    */
    const int num_Patches = 1;
    int ponto;
    int ind_Pontos_Controlo = 0;
    int valor;

    int ind;
    string linha;
    string numero;
    string divisao = ", ";

    // Primeiro fazer a leitura do ficheiro

    ifstream fRead;
    fRead.open(file_read);

    if (fRead.is_open()) {
        getline(fRead, linha);

        const int nPatches = stoi(linha); // ler a linha inicial, que tem o numero total
    }
    

    int indices[num_Patches][16]; // Matriz que contém os indices .dos patchs

    // fazer a leitura do ficheiro
    for (int i = 0; i < num_Patches; i++) {
        getline(fRead, linha);

        while ((ind = linha.find(divisao))) {
            numero = linha.substr(0, ind);  // substring que esta nessa posiçao
            linha.erase(0, ind + 3);   // apagar essa substring, incluindo a virgula e o espaço
            try
            {
                valor = stoi(numero);
            }
            catch (std::invalid_argument & e) {
                std::cout << e.what();
            }
            indices[i][ind_Pontos_Controlo] =valor;

            ind_Pontos_Controlo++;
        }

        try
        {
            valor = stoi(numero);
        }
        catch (std::invalid_argument & e) {
            std::cout << e.what();
        }

        indices[i][ind_Pontos_Controlo] = valor;

        ind_Pontos_Controlo = 0;
    }

    getline(fRead, linha);
    int pontos_controlo = 290;   // numero de pontos de controlo

    double pontos[290][3]; // Matriz que contem todas as coordenadas dos pontos de controlo
    int indice = 0;
 // Construir a matrzi pontos

    for (int i = 0; i < pontos_controlo; i++) {
        getline(fRead, linha);   // ler a linha

        while ((ind = linha.find(divisao))) {
            numero = linha.substr(0, ind);    // 
            linha.erase(0, ind + 3);

            ponto = std::stoi(numero);      // coordenada do ponto
            pontos[i][indice] = ponto;

            indice++;
        }

        ponto = stoi(linha);
        pontos[i][indice] = ponto;

        indice = 0;
    }

    double res[3];      // vetor com o resultados

   // Calcular os pontos (tendo como referencia os varios valores de u e v de acordo com o nivel de tecellation
    int i, u, v;
    double u_aux, v_aux;
    for (i = 0; i < num_Patches; i++) {
        for (u = 0; u < tesselation; u++) {
            for (v = 0; v < tesselation; v++) {
                // para obter o u e o v de acordo com os niveis de tecelaçao 
                u_aux = u / tesselation;
                v_aux = v / tesselation;
                *res = calculos_bezier(u_aux, v_aux, indices[i], pontos);

                AddVertex(res[0], res[1], res[2]);
            }
        }
    }
   
}

#include <iostream>

#include "SphereGenerator.h"

bool SphereGenerator::ParseArguments(int argc, char *argv[]) {
    if(argc < 6) {
        cerr << "Erro: Faltam argumentos!" << endl;
        cerr << "Utilização: " << argv[0] << " sphere <radius> <slices> <stacks> <fileName>" << endl;

        return false;
    }

    SetFilename(argv[5]);

  radius = stoi(argv[2]);
  slices = stoi(argv[3]);
  stacks = stoi(argv[4]);

    return true;
}


void SphereGenerator::GenerateVertices() {
    double angAlfa = 0;
    double angBeta = 0;

    // ponto P , ponto principal
    double xP;
    double yP;
    double zP;

    double xA;
    double yA;
    double zA;

    double xB;
    double yB;
    double zB;

    double xC;
    double yC;
    double zC;


    double alfa = 2 * M_PI / slices;
    double beta = (M_PI) / stacks;
    int i = 0;


    for (int i = 1; i <= stacks; i++) {

        angBeta = M_PI /2 - (beta * i);    //Cálculo do ângulo Beta

        for (int j = 0; j <= slices; j++) {

            angAlfa = (alfa * j);        //Cálculo do ângulo Alfa

            // para o ponto P (canto inferior esquerdo)

            xP = radius * cos(angBeta) * sin(angAlfa);
            yP = radius * sin(angBeta);
            zP = radius * cos(angBeta) * cos(angAlfa);

            // para o ponto A (canto inferior direito)

            xA = radius * cos(angBeta) * sin(angAlfa + alfa);
            yA = radius * sin(angBeta );
            zA = radius * cos(angBeta) * cos(angAlfa + alfa);

            // Para o ponto B (canto superior esquerdo)

            xB = radius * cos(angBeta + beta) * sin(angAlfa );
            yB = radius * sin(angBeta + beta);
            zB = radius * cos(angBeta + beta) * cos(angAlfa );

            // para o ponto C (canto superior direito)

            xC = radius * cos(angBeta + beta) * sin(angAlfa + alfa);
            yC = radius * sin(angBeta + beta);
            zC = radius * cos(angBeta + beta) * cos(angAlfa + alfa);

            AddVertex(xC, yC, zC);
            AddVertex(xP, yP, zP);
            AddVertex(xA, yA, zA);

            AddVertex(xB, yB, zB);
            AddVertex(xP, yP, zP);
            AddVertex(xC, yC, zC);


        }
    }

}
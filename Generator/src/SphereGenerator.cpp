#include <iostream>

#include "SphereGenerator.h"

bool SphereGenerator::ParseArguments(int argc, char *argv[]) {
    if(argc < 6) {
        cerr << "Erro: Faltam argumentos!" << endl;
        cerr << "Utilização: " << argv[0] << " sphere <radius> <slices> <stacks> <fileName>" << endl;

        return false;
    }

    SetFilename(argv[5]);

    radius_ = stoi(argv[2]);
    slices_ = stoi(argv[3]);
    stacks_ = stoi(argv[4]);

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


    double alfa = 2 * M_PI / slices_;
    double beta = (M_PI) / stacks_;
    int i = 0;


    for (int i = 1; i <= stacks_; i++) {

        angBeta = M_PI /2 - (beta * i);    //Cálculo do ângulo Beta

        for (int j = 0; j <= slices_; j++) {

            angAlfa = (alfa * j);        //Cálculo do ângulo Alfa

            // para o ponto P

            xP = radius_ * cos(angBeta) * sin(angAlfa);
            yP = radius_ * sin(angBeta);
            zP = radius_ * cos(angBeta) * cos(angAlfa);

            // para o ponto A:

            xA = radius_ * cos(angBeta) * sin(angAlfa + alfa);
            yA = radius_ * sin(angBeta );
            zA = radius_ * cos(angBeta) * cos(angAlfa + alfa);

            // Para o ponto B:

            xB = radius_ * cos(angBeta + beta) * sin(angAlfa );
            yB = radius_ * sin(angBeta + beta);
            zB = radius_ * cos(angBeta + beta) * cos(angAlfa );

            // para o ponto C:

            xC = radius_ * cos(angBeta + beta) * sin(angAlfa + alfa);
            yC = radius_ * sin(angBeta + beta);
            zC = radius_ * cos(angBeta + beta) * cos(angAlfa + alfa);

            AddVertex(xC, yC, zC);
            AddVertex(xP, yP, zP);
            AddVertex(xA, yA, zA);

            AddVertex(xB, yB, zB);
            AddVertex(xP, yP, zP);
            AddVertex(xC, yC, zC);


        }
    }

}
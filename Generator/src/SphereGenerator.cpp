#include <iostream>

#include "SphereGenerator.h"

bool SphereGenerator::ParseArguments(int argc, char* argv[]) {

    
   if (argc < 6) { // Número incorreto de argumentos passado
        cerr << "Faltam argumentos!" << endl
            << "Utilização: ./Gerador  sphere <radius> <slices> <stacks> " << endl;

        return false;
    }
    

    SetFilename(argv[5]);

    radius_ = stoi(argv[2]);
    slices_ = stoi(argv[3]);
    stacks_ = stoi(argv[3]);

    
    return true;
}


void SphereGenerator::GenerateVertices() {

    float angAlfa = 0;
    float angBeta = 0;

    // ponto P , ponto principal
    float xP;
    float yP;
    float zP;

    float xA;
    float yA;
    float zA;

    float xB;
    float yB;
    float zB;

    float xC;
    float yC;
    float zC;

    float alfa = 2 * M_PI / slices_;
    float beta = (M_PI- (M_PI / 2)) / stacks_;
    // Para encontrar a metade inferior da esfera

    for (int i = 0; i < stacks_; i++) {

        angBeta = (beta * i);			//Cálculo do ângulo Beta

        for (int j = 0; j < slices_; j++) {

            angAlfa = (alfa * j);		//Cálculo do ângulo Alfa

        // para o ponto "principal"

            xP = radius_ * cos(angBeta) * sin(angAlfa);
            yP = radius_ * sin(angBeta);
            zP = radius_ * cos(angBeta) * cos(angAlfa);

            // para o ponto A:

            xA = radius_ * cos(angBeta + beta) * sin(angAlfa);
            yA = radius_ * sin(angBeta + beta);
            zA = radius_ * cos(angBeta + beta) * cos(angAlfa);

            // Para o ponto B:

            xB = radius_ * cos(angBeta) * sin(angAlfa + alfa);
            yB = radius_ * sin(angBeta);
            zB = radius_ * cos(angBeta) * cos(angAlfa + alfa);

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
    
    // Para encontrar a metade inferior da esfera

    alfa = 2 * M_PI / slices_;
    beta = ( (M_PI / 2) - M_PI) / stacks_;
    angBeta = 0;
    angAlfa = 0;

    for (int i = 0; i < stacks_; i++) {

        angBeta = (beta * i);			//Cálculo do ângulo Beta

        for (int j = 0; j < slices_; j++) {

            angAlfa = (alfa * j);		//Cálculo do ângulo Alfa

        // para o ponto "principal"

            xP = radius_ * cos(angBeta) * sin(angAlfa);
            yP = radius_ * sin(angBeta);
            zP = radius_ * cos(angBeta) * cos(angAlfa);

            // para o ponto A:

            xA = radius_ * cos(angBeta + beta) * sin(angAlfa);
            yA = radius_ * sin(angBeta + beta);
            zA = radius_ * cos(angBeta + beta) * cos(angAlfa);

            // Para o ponto B:

            xB = radius_ * cos(angBeta) * sin(angAlfa + alfa);
            yB = radius_ * sin(angBeta);
            zB = radius_ * cos(angBeta) * cos(angAlfa + alfa);

            // para o ponto C:

            xC = radius_ * cos(angBeta + beta) * sin(angAlfa + alfa);
            yC = radius_ * sin(angBeta + beta);
            zC = radius_ * cos(angBeta + beta) * cos(angAlfa + alfa);

            AddVertex(xA, yA, zA);
            AddVertex(xP, yP, zP);
            AddVertex(xC, yC, zC);
            
            
            AddVertex(xC, yC, zC);
            AddVertex(xP, yP, zP);
            AddVertex(xB, yB, zB);
            
            

        }

    }
}
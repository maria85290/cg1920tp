#include <iostream>
#define _USE_MATH_DEFINES

#include <tinyxml2/tinyxml2.h>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc!=2) {
        cerr << "Engine requer exatamente 1 argumento, o ficheiro de configuração XML." << endl;
        cerr << "Uso ./engine <file.xml>" << endl;
        return 1;
    }

    tinyxml2::XMLDocument config;

    /*
    tinyxml2::XMLError result = config.LoadFile(argv[2]);
    if (result != tinyxml2::XML_SUCCESS) {
        cerr << "Ocorreu um erro na leitura do ficheiro de configuração XML fornecido." << endl;
        return 1;
    }
    cout << "YAY" << endl;*/
    return 0;
}

#include <iostream>
#include <stdexcept>
#include "designer.h"
#include "shape.h"

using namespace std;

int main() {
    try {
        // dimensoes usadas para montar a bandeira
        Designer grecia(810, 540);

        // fundo azul inteiro
        grecia.include(Rectangle(13, 94, 175, 1, true, 0, 810, 0, 540));

        // faixas brancas horizontais
        grecia.include(Rectangle(255, 255, 255, 1, true, 0, 810, 60, 120));
        grecia.include(Rectangle(255, 255, 255, 1, true, 0, 810, 180, 240));
        grecia.include(Rectangle(255, 255, 255, 1, true, 0, 810, 300, 360));
        grecia.include(Rectangle(255, 255, 255, 1, true, 0, 810, 420, 480));

        // quadrado azul do canto, sobrepondo parte das faixas
        grecia.include(Rectangle(13, 94, 175, 1, true, 0, 300, 0, 300));

        // cruz branca dentro do quadrado
        grecia.include(Rectangle(255, 255, 255, 1, true, 120, 180, 0, 300));
        grecia.include(Rectangle(255, 255, 255, 1, true, 0, 300, 120, 180));

        // geracao do arquivo final
        grecia.save("grecia.svg");

        cout << "Arquivo grecia.svg gerado com sucesso!" << endl;

    } catch(exception& e) {
        cerr << "Erro ao gerar a bandeira: " << e.what() << endl;
    }

    return 0;
}


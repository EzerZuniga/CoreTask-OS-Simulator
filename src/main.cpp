#include <iostream>

#include "SistemaOperativo.h"

int main() {
    try {
        SistemaOperativo sistema;
        sistema.iniciar();
    } catch (const std::exception& ex) {
        std::cerr << "Error critico: " << ex.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "Error critico desconocido.\n";
        return 1;
    }

    return 0;
}

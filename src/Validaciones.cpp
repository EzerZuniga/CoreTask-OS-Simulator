#include "Validaciones.h"

#include <cctype>

bool Validaciones::esNumeroPositivoRecursivo(const std::string& texto) {
    if (texto.empty()) {
        return false;
    }

    return esNumeroPositivoRecursivoImpl(texto, 0);
}

bool Validaciones::esNombreProcesoValidoRecursivo(const std::string& texto) {
    if (texto.empty()) {
        return false;
    }

    return esNombreAlfanumericoRecursivo(texto, 0);
}

bool Validaciones::esNombreArchivoValidoRecursivo(const std::string& texto) {
    if (texto.empty()) {
        return false;
    }

    return esNombreAlfanumericoRecursivo(texto, 0);
}

bool Validaciones::confirmarSiNo(const std::string& texto) {
    return texto == "s" || texto == "S" || texto == "y" || texto == "Y";
}

bool Validaciones::esNumeroPositivoRecursivoImpl(const std::string& texto, std::size_t indice) {
    if (indice >= texto.size()) {
        return true;
    }

    if (!std::isdigit(static_cast<unsigned char>(texto[indice]))) {
        return false;
    }

    return esNumeroPositivoRecursivoImpl(texto, indice + 1);
}

bool Validaciones::esNombreAlfanumericoRecursivo(const std::string& texto, std::size_t indice) {
    if (indice >= texto.size()) {
        return true;
    }

    const unsigned char c = static_cast<unsigned char>(texto[indice]);
    const bool permitido = std::isalnum(c) || c == '_' || c == '-' || c == ' ';

    if (!permitido) {
        return false;
    }

    return esNombreAlfanumericoRecursivo(texto, indice + 1);
}

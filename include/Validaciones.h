#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <cstddef>
#include <string>

class Validaciones {
public:
    static bool esNumeroPositivoRecursivo(const std::string& texto);
    static bool esNombreProcesoValidoRecursivo(const std::string& texto);
    static bool esNombreArchivoValidoRecursivo(const std::string& texto);
    static bool confirmarSiNo(const std::string& texto);

private:
    static bool esNumeroPositivoRecursivoImpl(const std::string& texto, std::size_t indice);
    static bool esNombreAlfanumericoRecursivo(const std::string& texto, std::size_t indice);
};

#endif

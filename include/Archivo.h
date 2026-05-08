#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <cstddef>
#include <string>

class Archivo {
public:
    Archivo();
    Archivo(const std::string& nombre, const std::string& extension, std::size_t tamanoKB, const std::string& fechaCreacion);

    const std::string& getNombre() const;
    const std::string& getExtension() const;
    std::size_t getTamanoKB() const;
    const std::string& getFechaCreacion() const;

    std::string getNombreCompleto() const;
    std::string toString() const;

private:
    std::string nombre_;
    std::string extension_;
    std::size_t tamanoKB_;
    std::string fechaCreacion_;
};

#endif

#include "Archivo.h"

#include <sstream>

Archivo::Archivo() : nombre_("sin_nombre"), extension_("txt"), tamanoKB_(0), fechaCreacion_("N/A") {}

Archivo::Archivo(const std::string& nombre, const std::string& extension, std::size_t tamanoKB, const std::string& fechaCreacion)
    : nombre_(nombre), extension_(extension), tamanoKB_(tamanoKB), fechaCreacion_(fechaCreacion) {}

const std::string& Archivo::getNombre() const {
    return nombre_;
}

const std::string& Archivo::getExtension() const {
    return extension_;
}

std::size_t Archivo::getTamanoKB() const {
    return tamanoKB_;
}

const std::string& Archivo::getFechaCreacion() const {
    return fechaCreacion_;
}

std::string Archivo::getNombreCompleto() const {
    return nombre_ + "." + extension_;
}

std::string Archivo::toString() const {
    std::ostringstream oss;
    oss << getNombreCompleto()
        << " | Tamano: " << tamanoKB_ << " KB"
        << " | Creado: " << fechaCreacion_;
    return oss.str();
}

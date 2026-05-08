#ifndef EXPLORADORARCHIVOS_H
#define EXPLORADORARCHIVOS_H

#include <cstddef>
#include <string>

#include "Archivo.h"

class ExploradorArchivos {
public:
    struct NodoArchivo {
        explicit NodoArchivo(const Archivo& archivoRef) : archivo(archivoRef), siguiente(nullptr) {}
        Archivo archivo;
        NodoArchivo* siguiente;
    };

    ExploradorArchivos();
    ~ExploradorArchivos();

    bool crearArchivo(const Archivo& archivo);
    bool eliminarArchivo(const std::string& nombreCompleto);

    Archivo* buscarArchivoRecursivo(const std::string& nombreCompleto);
    const Archivo* buscarArchivoRecursivo(const std::string& nombreCompleto) const;

    void mostrarArchivos() const;
    std::size_t obtenerCantidad() const;

    const NodoArchivo* obtenerCabeza() const;

private:
    NodoArchivo* cabeza_;
    std::size_t cantidad_;

    NodoArchivo* buscarNodoRecursivo(NodoArchivo* nodo, const std::string& nombreCompleto) const;
    bool eliminarRecursivo(NodoArchivo*& nodo, const std::string& nombreCompleto);
    void mostrarRecursivo(const NodoArchivo* nodo) const;
    void liberarRecursivo(NodoArchivo* nodo);
};

#endif

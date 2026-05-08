#include "ExploradorArchivos.h"

#include <iostream>

#include "Utils.h"

ExploradorArchivos::ExploradorArchivos() : cabeza_(nullptr), cantidad_(0) {}

ExploradorArchivos::~ExploradorArchivos() {
    liberarRecursivo(cabeza_);
}

bool ExploradorArchivos::crearArchivo(const Archivo& archivo) {
    if (buscarArchivoRecursivo(archivo.getNombreCompleto()) != nullptr) {
        return false;
    }

    NodoArchivo* nuevo = new NodoArchivo(archivo);
    nuevo->siguiente = cabeza_;
    cabeza_ = nuevo;
    ++cantidad_;
    return true;
}

bool ExploradorArchivos::eliminarArchivo(const std::string& nombreCompleto) {
    return eliminarRecursivo(cabeza_, nombreCompleto);
}

Archivo* ExploradorArchivos::buscarArchivoRecursivo(const std::string& nombreCompleto) {
    NodoArchivo* nodo = buscarNodoRecursivo(cabeza_, nombreCompleto);
    return nodo != nullptr ? &nodo->archivo : nullptr;
}

const Archivo* ExploradorArchivos::buscarArchivoRecursivo(const std::string& nombreCompleto) const {
    NodoArchivo* nodo = buscarNodoRecursivo(cabeza_, nombreCompleto);
    return nodo != nullptr ? &nodo->archivo : nullptr;
}

void ExploradorArchivos::mostrarArchivos() const {
    if (cabeza_ == nullptr) {
        std::cout << Utils::AMARILLO << "No existen archivos virtuales." << Utils::RESET << '\n';
        return;
    }

    Utils::imprimirSubtitulo("EXPLORADOR DE ARCHIVOS");
    mostrarRecursivo(cabeza_);
}

std::size_t ExploradorArchivos::obtenerCantidad() const {
    return cantidad_;
}

const ExploradorArchivos::NodoArchivo* ExploradorArchivos::obtenerCabeza() const {
    return cabeza_;
}

ExploradorArchivos::NodoArchivo* ExploradorArchivos::buscarNodoRecursivo(NodoArchivo* nodo, const std::string& nombreCompleto) const {
    if (nodo == nullptr) {
        return nullptr;
    }

    if (nodo->archivo.getNombreCompleto() == nombreCompleto) {
        return nodo;
    }

    return buscarNodoRecursivo(nodo->siguiente, nombreCompleto);
}

bool ExploradorArchivos::eliminarRecursivo(NodoArchivo*& nodo, const std::string& nombreCompleto) {
    if (nodo == nullptr) {
        return false;
    }

    if (nodo->archivo.getNombreCompleto() == nombreCompleto) {
        NodoArchivo* temporal = nodo;
        nodo = nodo->siguiente;
        delete temporal;
        --cantidad_;
        return true;
    }

    return eliminarRecursivo(nodo->siguiente, nombreCompleto);
}

void ExploradorArchivos::mostrarRecursivo(const NodoArchivo* nodo) const {
    if (nodo == nullptr) {
        return;
    }

    std::cout << "  - " << nodo->archivo.toString() << '\n';
    mostrarRecursivo(nodo->siguiente);
}

void ExploradorArchivos::liberarRecursivo(NodoArchivo* nodo) {
    if (nodo == nullptr) {
        return;
    }

    liberarRecursivo(nodo->siguiente);
    delete nodo;
}

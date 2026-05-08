#include "PilaHistorial.h"

#include <iostream>

#include "Utils.h"

PilaHistorial::PilaHistorial() : cima_(nullptr), tamano_(0) {}

PilaHistorial::~PilaHistorial() {
    limpiar();
}

void PilaHistorial::push(const std::string& accion) {
    NodoHistorial* nuevo = new NodoHistorial(accion);
    nuevo->siguiente = cima_;
    cima_ = nuevo;
    ++tamano_;
}

bool PilaHistorial::pop(std::string& accion) {
    if (cima_ == nullptr) {
        return false;
    }

    NodoHistorial* temporal = cima_;
    accion = temporal->accion;

    cima_ = cima_->siguiente;
    delete temporal;
    --tamano_;
    return true;
}

bool PilaHistorial::estaVacia() const {
    return tamano_ == 0;
}

std::size_t PilaHistorial::tamano() const {
    return tamano_;
}

void PilaHistorial::mostrarHistorial() const {
    if (cima_ == nullptr) {
        std::cout << Utils::AMARILLO << "No hay acciones registradas en historial." << Utils::RESET << '\n';
        return;
    }

    Utils::imprimirSubtitulo("HISTORIAL DEL SISTEMA (LIFO)");

    NodoHistorial* actual = cima_;
    int indice = 1;
    while (actual != nullptr) {
        std::cout << "  (" << indice << ") " << actual->accion << '\n';
        actual = actual->siguiente;
        ++indice;
    }
}

void PilaHistorial::limpiar() {
    std::string accionTemporal;
    while (pop(accionTemporal)) {
    }
}

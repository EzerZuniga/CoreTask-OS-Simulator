#include "ColaCPU.h"

#include <iostream>

#include "Utils.h"

ColaCPU::ColaCPU() : frente_(nullptr), final_(nullptr), tamano_(0) {}

ColaCPU::~ColaCPU() {
    limpiar();
}

void ColaCPU::encolar(const Proceso& proceso) {
    NodoCola* nuevo = new NodoCola(proceso);

    if (final_ == nullptr) {
        frente_ = nuevo;
        final_ = nuevo;
    } else {
        final_->siguiente = nuevo;
        final_ = nuevo;
    }

    ++tamano_;
}

bool ColaCPU::desencolar(Proceso& proceso) {
    if (frente_ == nullptr) {
        return false;
    }

    NodoCola* temporal = frente_;
    proceso = temporal->proceso;

    frente_ = frente_->siguiente;
    if (frente_ == nullptr) {
        final_ = nullptr;
    }

    delete temporal;
    --tamano_;
    return true;
}

bool ColaCPU::frente(Proceso& proceso) const {
    if (frente_ == nullptr) {
        return false;
    }

    proceso = frente_->proceso;
    return true;
}

bool ColaCPU::eliminarPorPID(int pid) {
    NodoCola* anterior = nullptr;
    NodoCola* actual = frente_;

    while (actual != nullptr) {
        if (actual->proceso.getPID() == pid) {
            if (anterior == nullptr) {
                frente_ = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }

            if (actual == final_) {
                final_ = anterior;
            }

            delete actual;
            --tamano_;
            return true;
        }

        anterior = actual;
        actual = actual->siguiente;
    }

    return false;
}

bool ColaCPU::estaVacia() const {
    return tamano_ == 0;
}

std::size_t ColaCPU::tamano() const {
    return tamano_;
}

void ColaCPU::mostrarCola() const {
    if (frente_ == nullptr) {
        std::cout << Utils::AMARILLO << "La cola CPU esta vacia." << Utils::RESET << '\n';
        return;
    }

    Utils::imprimirSubtitulo("COLA DE EJECUCION CPU (FIFO)");

    NodoCola* actual = frente_;
    int posicion = 1;
    while (actual != nullptr) {
        std::cout << "  [" << posicion << "] " << actual->proceso.toString() << '\n';
        actual = actual->siguiente;
        ++posicion;
    }
}

void ColaCPU::limpiar() {
    Proceso temporal;
    while (desencolar(temporal)) {
    }
}

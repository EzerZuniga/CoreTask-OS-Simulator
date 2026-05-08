#include "MemoriaRAM.h"

#include <iomanip>
#include <iostream>

#include "Utils.h"

MemoriaRAM::MemoriaRAM(std::size_t capacidadTotalMB)
    : capacidadTotalMB_(capacidadTotalMB), memoriaUsadaMB_(0), cabeza_(nullptr) {}

MemoriaRAM::~MemoriaRAM() {
    limpiar();
}

bool MemoriaRAM::reservar(int pid, std::size_t cantidadMB) {
    if (cantidadMB == 0 || cantidadMB > memoriaDisponible()) {
        return false;
    }

    NodoMemoria* actual = cabeza_;
    while (actual != nullptr) {
        if (actual->pid == pid) {
            actual->cantidadMB += cantidadMB;
            memoriaUsadaMB_ += cantidadMB;
            return true;
        }
        actual = actual->siguiente;
    }

    NodoMemoria* nuevo = new NodoMemoria(pid, cantidadMB);
    nuevo->siguiente = cabeza_;
    cabeza_ = nuevo;
    memoriaUsadaMB_ += cantidadMB;
    return true;
}

bool MemoriaRAM::liberar(int pid, std::size_t* memoriaLiberada) {
    NodoMemoria* anterior = nullptr;
    NodoMemoria* actual = cabeza_;

    while (actual != nullptr) {
        if (actual->pid == pid) {
            if (anterior == nullptr) {
                cabeza_ = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }

            memoriaUsadaMB_ -= actual->cantidadMB;

            if (memoriaLiberada != nullptr) {
                *memoriaLiberada = actual->cantidadMB;
            }

            delete actual;
            return true;
        }

        anterior = actual;
        actual = actual->siguiente;
    }

    return false;
}

std::size_t MemoriaRAM::memoriaDisponible() const {
    return capacidadTotalMB_ - memoriaUsadaMB_;
}

std::size_t MemoriaRAM::memoriaUsada() const {
    return memoriaUsadaMB_;
}

std::size_t MemoriaRAM::capacidadTotal() const {
    return capacidadTotalMB_;
}

double MemoriaRAM::porcentajeUso() const {
    if (capacidadTotalMB_ == 0) {
        return 0.0;
    }

    return (static_cast<double>(memoriaUsadaMB_) / static_cast<double>(capacidadTotalMB_)) * 100.0;
}

std::size_t MemoriaRAM::obtenerUsoProceso(int pid) const {
    NodoMemoria* actual = cabeza_;
    while (actual != nullptr) {
        if (actual->pid == pid) {
            return actual->cantidadMB;
        }
        actual = actual->siguiente;
    }

    return 0;
}

void MemoriaRAM::mostrarEstado() const {
    Utils::imprimirSubtitulo("ESTADO DE MEMORIA RAM");

    std::cout << "Capacidad total: " << capacidadTotalMB_ << " MB\n";
    std::cout << "Memoria usada:  " << memoriaUsadaMB_ << " MB\n";
    std::cout << "Disponible:     " << memoriaDisponible() << " MB\n";

    const double uso = porcentajeUso();
    std::cout << "Uso porcentual: " << std::fixed << std::setprecision(2) << uso << "%\n";
    std::cout << "Barra de uso:   " << Utils::barraProgreso(uso) << '\n';

    if (cabeza_ == nullptr) {
        std::cout << Utils::AMARILLO << "No hay bloques de RAM asignados." << Utils::RESET << '\n';
        return;
    }

    std::cout << "\nBloques asignados por proceso:\n";
    NodoMemoria* actual = cabeza_;
    while (actual != nullptr) {
        std::cout << "  - PID " << actual->pid << " -> " << actual->cantidadMB << " MB\n";
        actual = actual->siguiente;
    }
}

void MemoriaRAM::limpiar() {
    NodoMemoria* actual = cabeza_;
    while (actual != nullptr) {
        NodoMemoria* temporal = actual;
        actual = actual->siguiente;
        delete temporal;
    }

    cabeza_ = nullptr;
    memoriaUsadaMB_ = 0;
}

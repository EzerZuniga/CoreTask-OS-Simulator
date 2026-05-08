#include "ListaProcesos.h"

#include <iostream>

#include "Utils.h"

ListaProcesos::ListaProcesos() : cabeza_(nullptr), cantidad_(0) {}

ListaProcesos::~ListaProcesos() {
    liberarRecursivo(cabeza_);
}

bool ListaProcesos::agregarProceso(const Proceso& proceso) {
    if (existePID(proceso.getPID())) {
        return false;
    }

    NodoProceso* nuevo = new NodoProceso(proceso);
    if (cabeza_ == nullptr) {
        cabeza_ = nuevo;
    } else {
        NodoProceso* actual = cabeza_;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }

    ++cantidad_;
    return true;
}

bool ListaProcesos::eliminarProceso(int pid, Proceso* procesoEliminado) {
    return eliminarRecursivo(cabeza_, pid, procesoEliminado);
}

Proceso* ListaProcesos::buscarProceso(int pid) {
    NodoProceso* nodo = buscarNodoRecursivo(cabeza_, pid);
    return nodo != nullptr ? &nodo->proceso : nullptr;
}

const Proceso* ListaProcesos::buscarProceso(int pid) const {
    NodoProceso* nodo = buscarNodoRecursivo(cabeza_, pid);
    return nodo != nullptr ? &nodo->proceso : nullptr;
}

bool ListaProcesos::existePID(int pid) const {
    return existePIDRecursivo(cabeza_, pid);
}

bool ListaProcesos::actualizarEstado(int pid, EstadoProceso estado) {
    Proceso* proceso = buscarProceso(pid);
    if (proceso == nullptr) {
        return false;
    }

    proceso->setEstado(estado);
    return true;
}

void ListaProcesos::mostrarProcesos() const {
    if (cabeza_ == nullptr) {
        std::cout << Utils::AMARILLO << "No hay procesos activos." << Utils::RESET << '\n';
        return;
    }

    Utils::imprimirSubtitulo("PROCESOS ACTIVOS");
    mostrarRecursivo(cabeza_);
}

std::size_t ListaProcesos::obtenerCantidad() const {
    return cantidad_;
}

const NodoProceso* ListaProcesos::obtenerCabeza() const {
    return cabeza_;
}

bool ListaProcesos::existePIDRecursivo(const NodoProceso* nodo, int pid) const {
    if (nodo == nullptr) {
        return false;
    }

    if (nodo->proceso.getPID() == pid) {
        return true;
    }

    return existePIDRecursivo(nodo->siguiente, pid);
}

NodoProceso* ListaProcesos::buscarNodoRecursivo(NodoProceso* nodo, int pid) const {
    if (nodo == nullptr) {
        return nullptr;
    }

    if (nodo->proceso.getPID() == pid) {
        return nodo;
    }

    return buscarNodoRecursivo(nodo->siguiente, pid);
}

bool ListaProcesos::eliminarRecursivo(NodoProceso*& nodo, int pid, Proceso* procesoEliminado) {
    if (nodo == nullptr) {
        return false;
    }

    if (nodo->proceso.getPID() == pid) {
        NodoProceso* temporal = nodo;
        nodo = nodo->siguiente;

        if (procesoEliminado != nullptr) {
            *procesoEliminado = temporal->proceso;
        }

        delete temporal;
        --cantidad_;
        return true;
    }

    return eliminarRecursivo(nodo->siguiente, pid, procesoEliminado);
}

void ListaProcesos::mostrarRecursivo(const NodoProceso* nodo) const {
    if (nodo == nullptr) {
        return;
    }

    std::cout << "  - " << nodo->proceso.toString() << '\n';
    mostrarRecursivo(nodo->siguiente);
}

void ListaProcesos::liberarRecursivo(NodoProceso* nodo) {
    if (nodo == nullptr) {
        return;
    }

    liberarRecursivo(nodo->siguiente);
    delete nodo;
}

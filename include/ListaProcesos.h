#ifndef LISTAPROCESOS_H
#define LISTAPROCESOS_H

#include <cstddef>
#include <string>

#include "NodoProceso.h"

class ListaProcesos {
public:
    ListaProcesos();
    ~ListaProcesos();

    bool agregarProceso(const Proceso& proceso);
    bool eliminarProceso(int pid, Proceso* procesoEliminado = nullptr);

    Proceso* buscarProceso(int pid);
    const Proceso* buscarProceso(int pid) const;

    bool existePID(int pid) const;
    bool actualizarEstado(int pid, EstadoProceso estado);

    void mostrarProcesos() const;
    std::size_t obtenerCantidad() const;

    const NodoProceso* obtenerCabeza() const;

private:
    NodoProceso* cabeza_;
    std::size_t cantidad_;

    bool existePIDRecursivo(const NodoProceso* nodo, int pid) const;
    NodoProceso* buscarNodoRecursivo(NodoProceso* nodo, int pid) const;
    bool eliminarRecursivo(NodoProceso*& nodo, int pid, Proceso* procesoEliminado);

    void mostrarRecursivo(const NodoProceso* nodo) const;
    void liberarRecursivo(NodoProceso* nodo);
};

#endif

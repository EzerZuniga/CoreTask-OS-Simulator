#ifndef COLACPU_H
#define COLACPU_H

#include <cstddef>

#include "Proceso.h"

class ColaCPU {
public:
    ColaCPU();
    ~ColaCPU();

    void encolar(const Proceso& proceso);
    bool desencolar(Proceso& proceso);
    bool frente(Proceso& proceso) const;

    bool eliminarPorPID(int pid);

    bool estaVacia() const;
    std::size_t tamano() const;

    void mostrarCola() const;
    void limpiar();

private:
    struct NodoCola {
        explicit NodoCola(const Proceso& p) : proceso(p), siguiente(nullptr) {}
        Proceso proceso;
        NodoCola* siguiente;
    };

    NodoCola* frente_;
    NodoCola* final_;
    std::size_t tamano_;
};

#endif

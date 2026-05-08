#ifndef MEMORIARAM_H
#define MEMORIARAM_H

#include <cstddef>

class MemoriaRAM {
public:
    explicit MemoriaRAM(std::size_t capacidadTotalMB = 8192);
    ~MemoriaRAM();

    bool reservar(int pid, std::size_t cantidadMB);
    bool liberar(int pid, std::size_t* memoriaLiberada = nullptr);

    std::size_t memoriaDisponible() const;
    std::size_t memoriaUsada() const;
    std::size_t capacidadTotal() const;
    double porcentajeUso() const;

    std::size_t obtenerUsoProceso(int pid) const;
    void mostrarEstado() const;
    void limpiar();

private:
    struct NodoMemoria {
        NodoMemoria(int p, std::size_t mb) : pid(p), cantidadMB(mb), siguiente(nullptr) {}
        int pid;
        std::size_t cantidadMB;
        NodoMemoria* siguiente;
    };

    std::size_t capacidadTotalMB_;
    std::size_t memoriaUsadaMB_;
    NodoMemoria* cabeza_;
};

#endif

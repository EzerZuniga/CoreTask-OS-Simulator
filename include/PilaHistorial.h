#ifndef PILAHISTORIAL_H
#define PILAHISTORIAL_H

#include <cstddef>
#include <string>

class PilaHistorial {
public:
    PilaHistorial();
    ~PilaHistorial();

    void push(const std::string& accion);
    bool pop(std::string& accion);

    bool estaVacia() const;
    std::size_t tamano() const;

    void mostrarHistorial() const;
    void limpiar();

private:
    struct NodoHistorial {
        explicit NodoHistorial(const std::string& a) : accion(a), siguiente(nullptr) {}
        std::string accion;
        NodoHistorial* siguiente;
    };

    NodoHistorial* cima_;
    std::size_t tamano_;
};

#endif

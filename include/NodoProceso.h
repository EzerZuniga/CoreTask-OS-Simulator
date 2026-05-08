#ifndef NODOPROCESO_H
#define NODOPROCESO_H

#include "Proceso.h"

class NodoProceso {
public:
    explicit NodoProceso(const Proceso& proceso);

    Proceso proceso;
    NodoProceso* siguiente;
};

#endif

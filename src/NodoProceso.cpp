#include "NodoProceso.h"

NodoProceso::NodoProceso(const Proceso& procesoRef)
    : proceso(procesoRef), siguiente(nullptr) {}

#ifndef SISTEMAOPERATIVO_H
#define SISTEMAOPERATIVO_H

#include "ColaCPU.h"
#include "ExploradorArchivos.h"
#include "ListaProcesos.h"
#include "MemoriaRAM.h"
#include "PilaHistorial.h"

class SistemaOperativo {
public:
    SistemaOperativo();

    void iniciar();

private:
    ListaProcesos listaProcesos_;
    ColaCPU colaCPU_;
    MemoriaRAM memoriaRAM_;
    PilaHistorial historial_;
    ExploradorArchivos explorador_;

    void mostrarMenuPrincipal() const;

    void crearProcesoInteractivo();
    void mostrarProcesos() const;
    void eliminarProcesoInteractivo();

    void ejecutarCPUInteractivo();
    void mostrarColaCPU() const;

    void menuMemoriaRAM();
    void menuExploradorArchivos();

    void mostrarHistorialInteractivo();
    void busquedaRecursivaInteractiva() const;
    void mostrarEstadisticasSistema() const;

    void registrarAccion(const std::string& accion);
    int generarPIDDisponibleRecursivo(int candidato) const;
};

#endif

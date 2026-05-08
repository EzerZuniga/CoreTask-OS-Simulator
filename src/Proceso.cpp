#include "Proceso.h"

#include <sstream>

Proceso::Proceso()
    : pid_(0), nombre_("SinNombre"), usoRamMB_(0), estado_(EstadoProceso::Nuevo), prioridad_(1) {}

Proceso::Proceso(int pid, const std::string& nombre, std::size_t usoRamMB, EstadoProceso estado, int prioridad)
    : pid_(pid), nombre_(nombre), usoRamMB_(usoRamMB), estado_(estado), prioridad_(prioridad) {}

int Proceso::getPID() const {
    return pid_;
}

const std::string& Proceso::getNombre() const {
    return nombre_;
}

std::size_t Proceso::getUsoRamMB() const {
    return usoRamMB_;
}

EstadoProceso Proceso::getEstado() const {
    return estado_;
}

int Proceso::getPrioridad() const {
    return prioridad_;
}

void Proceso::setNombre(const std::string& nombre) {
    nombre_ = nombre;
}

void Proceso::setUsoRamMB(std::size_t usoRamMB) {
    usoRamMB_ = usoRamMB;
}

void Proceso::setEstado(EstadoProceso estado) {
    estado_ = estado;
}

void Proceso::setPrioridad(int prioridad) {
    prioridad_ = prioridad;
}

std::string Proceso::toString() const {
    std::ostringstream oss;
    oss << "PID=" << pid_
        << " | Nombre=" << nombre_
        << " | RAM=" << usoRamMB_ << " MB"
        << " | Estado=" << estadoToString(estado_)
        << " | Prioridad=" << prioridad_;
    return oss.str();
}

std::string Proceso::estadoToString(EstadoProceso estado) {
    switch (estado) {
        case EstadoProceso::Nuevo:
            return "Nuevo";
        case EstadoProceso::Listo:
            return "Listo";
        case EstadoProceso::EnEjecucion:
            return "En ejecucion";
        case EstadoProceso::Bloqueado:
            return "Bloqueado";
        case EstadoProceso::Finalizado:
            return "Finalizado";
        default:
            return "Desconocido";
    }
}

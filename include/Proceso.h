#ifndef PROCESO_H
#define PROCESO_H

#include <cstddef>
#include <string>

enum class EstadoProceso {
    Nuevo,
    Listo,
    EnEjecucion,
    Bloqueado,
    Finalizado
};

class Proceso {
public:
    Proceso();
    Proceso(int pid, const std::string& nombre, std::size_t usoRamMB, EstadoProceso estado, int prioridad);

    int getPID() const;
    const std::string& getNombre() const;
    std::size_t getUsoRamMB() const;
    EstadoProceso getEstado() const;
    int getPrioridad() const;

    void setNombre(const std::string& nombre);
    void setUsoRamMB(std::size_t usoRamMB);
    void setEstado(EstadoProceso estado);
    void setPrioridad(int prioridad);

    std::string toString() const;
    static std::string estadoToString(EstadoProceso estado);

private:
    int pid_;
    std::string nombre_;
    std::size_t usoRamMB_;
    EstadoProceso estado_;
    int prioridad_;
};

#endif

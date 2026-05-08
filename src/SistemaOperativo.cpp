#include "SistemaOperativo.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "Utils.h"
#include "Validaciones.h"

SistemaOperativo::SistemaOperativo() : memoriaRAM_(8192) {
    Utils::registrarLog("Sistema iniciado");
}

void SistemaOperativo::iniciar() {
    bool enEjecucion = true;

    while (enEjecucion) {
        Utils::limpiarPantalla();
        mostrarMenuPrincipal();

        const int opcion = Utils::leerEntero("Seleccione una opcion: ", 0, 10);

        switch (opcion) {
            case 1:
                crearProcesoInteractivo();
                break;
            case 2:
                mostrarProcesos();
                break;
            case 3:
                eliminarProcesoInteractivo();
                break;
            case 4:
                ejecutarCPUInteractivo();
                break;
            case 5:
                mostrarColaCPU();
                break;
            case 6:
                menuMemoriaRAM();
                break;
            case 7:
                menuExploradorArchivos();
                break;
            case 8:
                mostrarHistorialInteractivo();
                break;
            case 9:
                busquedaRecursivaInteractiva();
                break;
            case 10:
                mostrarEstadisticasSistema();
                break;
            case 0:
                enEjecucion = false;
                registrarAccion("Cierre del sistema");
                break;
            default:
                break;
        }

        if (enEjecucion) {
            Utils::pausa();
        }
    }

    std::cout << Utils::VERDE << "\nSistema finalizado correctamente.\n" << Utils::RESET;
}

void SistemaOperativo::mostrarMenuPrincipal() const {
    Utils::imprimirTitulo("CORETASK OS SIMULATOR");
    std::cout << "1. Create Process\n";
    std::cout << "2. Show Processes\n";
    std::cout << "3. Delete Process\n";
    std::cout << "4. Execute CPU\n";
    std::cout << "5. Show CPU Queue\n";
    std::cout << "6. Manage RAM\n";
    std::cout << "7. File Explorer\n";
    std::cout << "8. Show History\n";
    std::cout << "9. Recursive Search\n";
    std::cout << "10. System Statistics\n";
    std::cout << "0. Exit\n";
    Utils::imprimirLinea('=');
}

void SistemaOperativo::crearProcesoInteractivo() {
    Utils::imprimirSubtitulo("CREAR PROCESO");

    const int pidSugerido = generarPIDDisponibleRecursivo(1000);
    const std::string nombre = Utils::leerLinea("Nombre del proceso: ");

    if (!Validaciones::esNombreProcesoValidoRecursivo(nombre)) {
        std::cout << Utils::ROJO << "Nombre invalido. Use caracteres alfanumericos, espacio, _ o -." << Utils::RESET << '\n';
        return;
    }

    const std::size_t ram = Utils::leerSizeT("RAM requerida (MB): ", 1, memoriaRAM_.capacidadTotal());
    const int prioridad = Utils::leerEntero("Prioridad (1-10): ", 1, 10);

    if (ram > memoriaRAM_.memoriaDisponible()) {
        std::cout << Utils::ROJO << "RAM insuficiente. Disponible: " << memoriaRAM_.memoriaDisponible() << " MB." << Utils::RESET << '\n';
        return;
    }

    Proceso proceso(pidSugerido, nombre, ram, EstadoProceso::Listo, prioridad);

    if (!listaProcesos_.agregarProceso(proceso)) {
        std::cout << Utils::ROJO << "No fue posible registrar el proceso." << Utils::RESET << '\n';
        return;
    }

    memoriaRAM_.reservar(pidSugerido, ram);
    colaCPU_.encolar(proceso);

    registrarAccion("Proceso creado PID=" + std::to_string(pidSugerido) + " Nombre=" + nombre);

    std::cout << Utils::VERDE << "Proceso creado correctamente con PID " << pidSugerido << "." << Utils::RESET << '\n';
}

void SistemaOperativo::mostrarProcesos() const {
    listaProcesos_.mostrarProcesos();
}

void SistemaOperativo::eliminarProcesoInteractivo() {
    Utils::imprimirSubtitulo("ELIMINAR PROCESO");

    if (listaProcesos_.obtenerCantidad() == 0) {
        std::cout << Utils::AMARILLO << "No hay procesos para eliminar." << Utils::RESET << '\n';
        return;
    }

    const int pid = Utils::leerEntero("PID a eliminar: ", 1, 999999);
    Proceso eliminado;

    if (!listaProcesos_.eliminarProceso(pid, &eliminado)) {
        std::cout << Utils::ROJO << "No se encontro el PID indicado." << Utils::RESET << '\n';
        return;
    }

    std::size_t memoriaLiberada = 0;
    memoriaRAM_.liberar(pid, &memoriaLiberada);
    colaCPU_.eliminarPorPID(pid);

    registrarAccion("Proceso eliminado PID=" + std::to_string(pid) + " RAM liberada=" + std::to_string(memoriaLiberada) + "MB");

    std::cout << Utils::VERDE << "Proceso eliminado. RAM liberada: " << memoriaLiberada << " MB." << Utils::RESET << '\n';
}

void SistemaOperativo::ejecutarCPUInteractivo() {
    Utils::imprimirSubtitulo("PLANIFICADOR CPU");

    if (colaCPU_.estaVacia()) {
        std::cout << Utils::AMARILLO << "No hay procesos en cola de ejecucion." << Utils::RESET << '\n';
        return;
    }

    std::cout << "1. Ejecutar siguiente proceso (FIFO)\n";
    std::cout << "2. Simular Round Robin (cola completa)\n";

    const int opcion = Utils::leerEntero("Opcion: ", 1, 2);

    if (opcion == 1) {
        Proceso proceso;
        colaCPU_.desencolar(proceso);

        listaProcesos_.actualizarEstado(proceso.getPID(), EstadoProceso::EnEjecucion);
        std::cout << Utils::CIAN << "Ejecutando: " << proceso.toString() << Utils::RESET << '\n';

        for (int avance = 20; avance <= 100; avance += 20) {
            std::this_thread::sleep_for(std::chrono::milliseconds(140));
            std::cout << "  CPU " << Utils::barraProgreso(static_cast<double>(avance), 20) << '\n';
        }

        listaProcesos_.actualizarEstado(proceso.getPID(), EstadoProceso::Finalizado);
        registrarAccion("Proceso ejecutado FIFO PID=" + std::to_string(proceso.getPID()));

        std::cout << Utils::VERDE << "Proceso finalizado correctamente." << Utils::RESET << '\n';
        return;
    }

    const int quantum = Utils::leerEntero("Quantum de simulacion (ms, 50-1000): ", 50, 1000);
    const std::size_t ciclos = colaCPU_.tamano();

    for (std::size_t i = 0; i < ciclos; ++i) {
        Proceso proceso;
        if (!colaCPU_.desencolar(proceso)) {
            break;
        }

        listaProcesos_.actualizarEstado(proceso.getPID(), EstadoProceso::EnEjecucion);
        std::cout << Utils::MAGENTA << "[RR] Ejecutando PID " << proceso.getPID() << "..." << Utils::RESET << '\n';

        std::this_thread::sleep_for(std::chrono::milliseconds(quantum));

        listaProcesos_.actualizarEstado(proceso.getPID(), EstadoProceso::Listo);
        colaCPU_.encolar(proceso);
    }

    registrarAccion("Round Robin simulado con quantum=" + std::to_string(quantum) + "ms");
    std::cout << Utils::VERDE << "Simulacion Round Robin completada." << Utils::RESET << '\n';
}

void SistemaOperativo::mostrarColaCPU() const {
    colaCPU_.mostrarCola();
}

void SistemaOperativo::menuMemoriaRAM() {
    bool salir = false;

    while (!salir) {
        Utils::imprimirSubtitulo("GESTION DE MEMORIA RAM");
        std::cout << "1. Mostrar estado RAM\n";
        std::cout << "2. Reservar RAM manual\n";
        std::cout << "3. Liberar RAM por PID\n";
        std::cout << "0. Volver\n";

        const int opcion = Utils::leerEntero("Opcion: ", 0, 3);

        switch (opcion) {
            case 1:
                memoriaRAM_.mostrarEstado();
                break;
            case 2: {
                const int pid = Utils::leerEntero("PID: ", 1, 999999);
                const std::size_t mb = Utils::leerSizeT("Cantidad MB: ", 1, memoriaRAM_.capacidadTotal());

                if (memoriaRAM_.reservar(pid, mb)) {
                    registrarAccion("Reserva manual de RAM PID=" + std::to_string(pid) + " MB=" + std::to_string(mb));
                    std::cout << Utils::VERDE << "RAM reservada." << Utils::RESET << '\n';
                } else {
                    std::cout << Utils::ROJO << "No fue posible reservar RAM (capacidad insuficiente)." << Utils::RESET << '\n';
                }
                break;
            }
            case 3: {
                const int pid = Utils::leerEntero("PID: ", 1, 999999);
                std::size_t memoriaLiberada = 0;

                if (memoriaRAM_.liberar(pid, &memoriaLiberada)) {
                    registrarAccion("Liberacion manual de RAM PID=" + std::to_string(pid) + " MB=" + std::to_string(memoriaLiberada));
                    std::cout << Utils::VERDE << "RAM liberada: " << memoriaLiberada << " MB." << Utils::RESET << '\n';
                } else {
                    std::cout << Utils::ROJO << "PID sin bloques de memoria." << Utils::RESET << '\n';
                }
                break;
            }
            case 0:
                salir = true;
                break;
            default:
                break;
        }

        if (!salir) {
            Utils::pausa();
        }
    }
}

void SistemaOperativo::menuExploradorArchivos() {
    bool salir = false;

    while (!salir) {
        Utils::imprimirSubtitulo("EXPLORADOR DE ARCHIVOS");
        std::cout << "1. Crear archivo\n";
        std::cout << "2. Eliminar archivo\n";
        std::cout << "3. Buscar archivo (recursivo)\n";
        std::cout << "4. Mostrar archivos\n";
        std::cout << "0. Volver\n";

        const int opcion = Utils::leerEntero("Opcion: ", 0, 4);

        switch (opcion) {
            case 1: {
                const std::string nombre = Utils::leerLinea("Nombre (sin extension): ");
                const std::string extension = Utils::leerLinea("Extension (txt, cpp, pdf, etc.): ");

                if (!Validaciones::esNombreArchivoValidoRecursivo(nombre)
                    || !Validaciones::esNombreArchivoValidoRecursivo(extension)) {
                    std::cout << Utils::ROJO << "Nombre o extension invalida." << Utils::RESET << '\n';
                    break;
                }

                const std::size_t tamano = Utils::leerSizeT("Tamano (KB): ", 1, 500000);
                Archivo archivo(nombre, extension, tamano, Utils::obtenerTimestamp());

                if (explorador_.crearArchivo(archivo)) {
                    registrarAccion("Archivo creado: " + archivo.getNombreCompleto());
                    std::cout << Utils::VERDE << "Archivo creado correctamente." << Utils::RESET << '\n';
                } else {
                    std::cout << Utils::ROJO << "Ya existe un archivo con ese nombre." << Utils::RESET << '\n';
                }
                break;
            }
            case 2: {
                const std::string nombreCompleto = Utils::leerLinea("Nombre completo (ejemplo: nota.txt): ");
                if (explorador_.eliminarArchivo(nombreCompleto)) {
                    registrarAccion("Archivo eliminado: " + nombreCompleto);
                    std::cout << Utils::VERDE << "Archivo eliminado." << Utils::RESET << '\n';
                } else {
                    std::cout << Utils::ROJO << "No existe ese archivo." << Utils::RESET << '\n';
                }
                break;
            }
            case 3: {
                const std::string nombreCompleto = Utils::leerLinea("Archivo a buscar: ");
                const Archivo* archivo = explorador_.buscarArchivoRecursivo(nombreCompleto);

                if (archivo != nullptr) {
                    std::cout << Utils::VERDE << "Encontrado: " << archivo->toString() << Utils::RESET << '\n';
                } else {
                    std::cout << Utils::ROJO << "Archivo no encontrado." << Utils::RESET << '\n';
                }
                break;
            }
            case 4:
                explorador_.mostrarArchivos();
                break;
            case 0:
                salir = true;
                break;
            default:
                break;
        }

        if (!salir) {
            Utils::pausa();
        }
    }
}

void SistemaOperativo::mostrarHistorialInteractivo() {
    historial_.mostrarHistorial();

    if (!historial_.estaVacia()) {
        const std::string respuesta = Utils::leerLinea("Desea deshacer la ultima accion? (s/n): ");
        if (Validaciones::confirmarSiNo(respuesta)) {
            std::string accion;
            historial_.pop(accion);
            Utils::registrarLog("Undo historial: " + accion);
            std::cout << Utils::AMARILLO << "Accion retirada del historial: " << accion << Utils::RESET << '\n';
        }
    }
}

void SistemaOperativo::busquedaRecursivaInteractiva() const {
    Utils::imprimirSubtitulo("BUSQUEDAS RECURSIVAS");
    std::cout << "1. Buscar proceso por PID\n";
    std::cout << "2. Buscar archivo por nombre\n";

    const int opcion = Utils::leerEntero("Opcion: ", 1, 2);

    if (opcion == 1) {
        const int pid = Utils::leerEntero("PID a buscar: ", 1, 999999);
        const Proceso* proceso = listaProcesos_.buscarProceso(pid);

        if (proceso != nullptr) {
            std::cout << Utils::VERDE << "Proceso encontrado: " << proceso->toString() << Utils::RESET << '\n';
        } else {
            std::cout << Utils::ROJO << "No existe un proceso con ese PID." << Utils::RESET << '\n';
        }
        return;
    }

    const std::string archivo = Utils::leerLinea("Archivo (nombre.extension): ");
    const Archivo* encontrado = explorador_.buscarArchivoRecursivo(archivo);

    if (encontrado != nullptr) {
        std::cout << Utils::VERDE << "Archivo encontrado: " << encontrado->toString() << Utils::RESET << '\n';
    } else {
        std::cout << Utils::ROJO << "No se encontro el archivo." << Utils::RESET << '\n';
    }
}

void SistemaOperativo::mostrarEstadisticasSistema() const {
    Utils::imprimirSubtitulo("PANEL DE ESTADISTICAS");

    const int cpu = Utils::generarPorcentajeCPU();

    std::cout << "Procesos totales: " << listaProcesos_.obtenerCantidad() << '\n';
    std::cout << "Cola CPU:         " << colaCPU_.tamano() << " procesos\n";
    std::cout << "Archivos:         " << explorador_.obtenerCantidad() << '\n';
    std::cout << "Historial:        " << historial_.tamano() << " acciones\n";
    std::cout << "RAM usada:        " << memoriaRAM_.memoriaUsada() << " / " << memoriaRAM_.capacidadTotal() << " MB\n";
    std::cout << "RAM:              " << Utils::barraProgreso(memoriaRAM_.porcentajeUso()) << '\n';
    std::cout << "CPU simulada:     " << Utils::barraProgreso(static_cast<double>(cpu)) << '\n';
}

void SistemaOperativo::registrarAccion(const std::string& accion) {
    const std::string marca = "[" + Utils::obtenerTimestamp() + "] " + accion;
    historial_.push(marca);
    Utils::registrarLog(accion);
}

int SistemaOperativo::generarPIDDisponibleRecursivo(int candidato) const {
    if (!listaProcesos_.existePID(candidato)) {
        return candidato;
    }

    return generarPIDDisponibleRecursivo(candidato + 1);
}

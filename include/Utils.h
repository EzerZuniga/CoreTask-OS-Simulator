#ifndef UTILS_H
#define UTILS_H

#include <string>

class Utils {
public:
    static const std::string RESET;
    static const std::string ROJO;
    static const std::string VERDE;
    static const std::string AMARILLO;
    static const std::string AZUL;
    static const std::string CIAN;
    static const std::string MAGENTA;
    static const std::string NEGRITA;

    static void limpiarPantalla();
    static void pausa();

    static std::string obtenerTimestamp();
    static std::string barraProgreso(double porcentaje, int ancho = 30);
    static int generarPorcentajeCPU();

    static void registrarLog(const std::string& mensaje, const std::string& ruta = "data/system.log");

    static void imprimirTitulo(const std::string& titulo);
    static void imprimirSubtitulo(const std::string& subtitulo);
    static void imprimirLinea(char caracter = '=', int ancho = 56);

    static std::string leerLinea(const std::string& prompt);
    static int leerEntero(const std::string& prompt, int minimo, int maximo);
    static std::size_t leerSizeT(const std::string& prompt, std::size_t minimo, std::size_t maximo);
};

#endif

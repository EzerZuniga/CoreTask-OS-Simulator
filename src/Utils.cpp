#include "Utils.h"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>

#include "Validaciones.h"

const std::string Utils::RESET = "\033[0m";
const std::string Utils::ROJO = "\033[31m";
const std::string Utils::VERDE = "\033[32m";
const std::string Utils::AMARILLO = "\033[33m";
const std::string Utils::AZUL = "\033[34m";
const std::string Utils::CIAN = "\033[36m";
const std::string Utils::MAGENTA = "\033[35m";
const std::string Utils::NEGRITA = "\033[1m";

void Utils::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Utils::pausa() {
    std::cout << "\nPresione ENTER para continuar...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

std::string Utils::obtenerTimestamp() {
    const auto ahora = std::chrono::system_clock::now();
    const std::time_t tiempo = std::chrono::system_clock::to_time_t(ahora);

    const std::tm* tmLocal = std::localtime(&tiempo);
    if (tmLocal == nullptr) {
        return "1970-01-01 00:00:00";
    }

    char buffer[20] = {};
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tmLocal);
    return std::string(buffer);
}

std::string Utils::barraProgreso(double porcentaje, int ancho) {
    if (porcentaje < 0.0) {
        porcentaje = 0.0;
    }
    if (porcentaje > 100.0) {
        porcentaje = 100.0;
    }

    const int completado = static_cast<int>((porcentaje / 100.0) * static_cast<double>(ancho));

    std::ostringstream oss;
    oss << "[";
    for (int i = 0; i < ancho; ++i) {
        oss << (i < completado ? '#' : '-');
    }
    oss << "] " << std::fixed << std::setprecision(1) << porcentaje << "%";

    return oss.str();
}

int Utils::generarPorcentajeCPU() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(8, 96);
    return dist(gen);
}

void Utils::registrarLog(const std::string& mensaje, const std::string& ruta) {
    std::ofstream archivo(ruta, std::ios::app);
    if (!archivo.is_open()) {
        return;
    }

    archivo << "[" << obtenerTimestamp() << "] " << mensaje << '\n';
}

void Utils::imprimirTitulo(const std::string& titulo) {
    imprimirLinea('=');
    std::cout << NEGRITA << CIAN << "        " << titulo << RESET << '\n';
    imprimirLinea('=');
}

void Utils::imprimirSubtitulo(const std::string& subtitulo) {
    std::cout << '\n' << NEGRITA << AZUL << "--- " << subtitulo << " ---" << RESET << '\n';
}

void Utils::imprimirLinea(char caracter, int ancho) {
    for (int i = 0; i < ancho; ++i) {
        std::cout << caracter;
    }
    std::cout << '\n';
}

std::string Utils::leerLinea(const std::string& prompt) {
    std::cout << prompt;
    std::string valor;
    std::getline(std::cin, valor);
    return valor;
}

int Utils::leerEntero(const std::string& prompt, int minimo, int maximo) {
    while (true) {
        const std::string entrada = leerLinea(prompt);
        if (!Validaciones::esNumeroPositivoRecursivo(entrada)) {
            std::cout << ROJO << "Entrada invalida. Solo se permiten enteros positivos." << RESET << '\n';
            continue;
        }

        try {
            const int valor = std::stoi(entrada);
            if (valor < minimo || valor > maximo) {
                std::cout << ROJO << "Valor fuera de rango [" << minimo << ", " << maximo << "]." << RESET << '\n';
                continue;
            }

            return valor;
        } catch (...) {
            std::cout << ROJO << "Numero fuera de limite permitido." << RESET << '\n';
        }
    }
}

std::size_t Utils::leerSizeT(const std::string& prompt, std::size_t minimo, std::size_t maximo) {
    while (true) {
        const std::string entrada = leerLinea(prompt);
        if (!Validaciones::esNumeroPositivoRecursivo(entrada)) {
            std::cout << ROJO << "Entrada invalida. Solo se permiten enteros positivos." << RESET << '\n';
            continue;
        }

        try {
            const std::size_t valor = static_cast<std::size_t>(std::stoull(entrada));
            if (valor < minimo || valor > maximo) {
                std::cout << ROJO << "Valor fuera de rango [" << minimo << ", " << maximo << "]." << RESET << '\n';
                continue;
            }

            return valor;
        } catch (...) {
            std::cout << ROJO << "Numero fuera de limite permitido." << RESET << '\n';
        }
    }
}

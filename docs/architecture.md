# Architecture Notes

CoreTask OS Simulator follows a layered modular structure:

1. Domain entities: `Proceso`, `Archivo`.
2. Data structures: linked lists (`ListaProcesos`, `ExploradorArchivos`, `MemoriaRAM`), queue (`ColaCPU`), stack (`PilaHistorial`).
3. Application service: `SistemaOperativo` orchestrates all modules.
4. UI and utility layer: `Utils` and menu handlers.

The design intentionally demonstrates dynamic memory management and recursive algorithms for educational purposes.

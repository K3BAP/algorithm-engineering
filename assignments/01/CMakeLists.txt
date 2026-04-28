cmake_minimum_required(VERSION 3.15)
project(LedaProject CXX)

# Export compile commands so VSCode/clangd can find include paths
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 1. Modernen C++ Standard für DEIN Projekt wählen (z.B. C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. XQuartz-Abhängigkeiten auf dem Mac finden
find_package(X11 REQUIRED)
find_library(XFT_LIBRARY NAMES Xft PATHS /opt/X11/lib REQUIRED)

# 3. LEDA Root-Verzeichnis definieren
set(LEDA_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../LEDA-7")

# 4. LEDA als "Importiertes Ziel" (Imported Target) definieren
add_library(LEDA STATIC IMPORTED)

# LEDA sagen, wo die Bibliothek und die Header-Dateien liegen
set_target_properties(LEDA PROPERTIES
    IMPORTED_LOCATION "${LEDA_ROOT_DIR}/libleda.a"
    INTERFACE_INCLUDE_DIRECTORIES "${LEDA_ROOT_DIR}/incl"
)

# X11, Xft und Math als feste Abhängigkeiten an LEDA binden.
# Das "INTERFACE" bedeutet: Wer LEDA nutzt, nutzt automatisch auch diese.
target_link_libraries(LEDA INTERFACE
    ${X11_LIBRARIES}
    ${XFT_LIBRARY}
    m
)

# Auch die XQuartz Include-Pfade an LEDA hängen
target_include_directories(LEDA INTERFACE
    ${X11_INCLUDE_DIR}
    /opt/X11/include/freetype2
)

# ==========================================
# Dein eigentliches Programm
# ==========================================

# Erstelle dein ausführbares Programm
add_executable(task1 task1.cpp)
add_executable(task2 task2.cpp)
add_executable(task3 task3.cpp)

# Stelle LEDA-Header sicher sichtbar für das Ziel (für IntelliSense/clangd)
target_include_directories(task1 PRIVATE "${LEDA_ROOT_DIR}/incl")
target_include_directories(task2 PRIVATE "${LEDA_ROOT_DIR}/incl")
target_include_directories(task3 PRIVATE "${LEDA_ROOT_DIR}/incl")

# Binde LEDA ein
target_link_libraries(task1 PRIVATE LEDA)
target_link_libraries(task2 PRIVATE LEDA)
target_link_libraries(task3 PRIVATE LEDA)
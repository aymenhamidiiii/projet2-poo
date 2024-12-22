cmake_minimum_required(VERSION 3.10)
project(SimulationLaplace)

# Choix du standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ajout d'options de compilation pour les messages d'erreur détaillés et l'optimisation (facultatif)
option(ENABLE_WARNINGS "Enable compiler warnings" ON)
option(ENABLE_OPTIMIZATIONS "Enable optimizations" ON)

# Fichiers sources
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(SimulationLaplace ${SOURCES})

# Inclure les fichiers d'en-tête
target_include_directories(SimulationLaplace PUBLIC include)

# Activer les warnings si activé
if (ENABLE_WARNINGS)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(SimulationLaplace PRIVATE -Wall -Wextra -Wpedantic)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(SimulationLaplace PRIVATE /W4)
    endif()
endif()

# Activer les optimisations si activé
if (ENABLE_OPTIMIZATIONS)
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(SimulationLaplace PRIVATE -O3)
    endif()
endif()

# Ajout de la bibliothèque pour les threads
find_package(Threads REQUIRED)
target_link_libraries(SimulationLaplace PRIVATE Threads::Threads)

# Ajout de la définition pour le mode Debug
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(SimulationLaplace PRIVATE DEBUG)
endif()

# Lien avec stdc++fs pour les anciennes versions de GCC
target_link_libraries(SimulationLaplace PRIVATE stdc++fs)
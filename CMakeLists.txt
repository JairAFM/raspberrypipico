# Se define version minima de cmake
cmake_minimum_required(VERSION 3.13)

# Se define el entorno para el pico
include(pico_sdk_import.cmake)

# Se valida que PICO_SDK_PATH exista
if (NOT PICO_SDK_PATH)
    message(FATAL_ERROR "?PICO_SDK_PATH?")
endif()

# Se define nombre del proyecto
project(rtosRpico C CXX ASM)

# Se estandariza C y CXX
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Se inicializa el sdk
pico_sdk_init()

# Se genera ejecutable
add_executable(rtosRpico main.c)

# crea archivos adicionales para el ejecutable
pico_add_extra_outputs(rtosRpico)

# Se agregan las librerias necesarias
target_link_libraries(rtosRpico pico_stdlib)

# Se activa el usb output y se desactiva el uart output
pico_enable_stdio_usb(rtosRpico 1)
pico_enable_stdio_uart(rtosRpico 0)
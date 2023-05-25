# Documentacion

Antes de leer es importante aclarar que para el proyecot se trabajo en el sistema operativo ubuntu 22.04

Para la creación del CMakeLists se consulto la siguiente documentacion:

- https://forums.raspberrypi.com/viewtopic.php?t=342703

- Debido a la variable PICO_TOOLCHAIN_PATH utilizada en la compilación de cmake es necesario instalar gcc-arm-none-eabi, se puede instalar con el comando sudo apt-get update && sudo apt-get -y install gcc-arm-none-eabi

- Debido a la variable CMAKE_CXX_COMPILER utilizada en la compilación de cmake es necesario instalar build-essential, se puede instalar con el comando sudo apt-get update && sudo apt-get install -y build-essential 
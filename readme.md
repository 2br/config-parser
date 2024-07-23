# Config-Parser
Overview
Config-parser is a lightweight C project designed to read and process configuration data from a file. It demonstrates basic file I/O, string parsing, and handling comments in configuration files. The project uses pre-set configuration variables (hardcoded), so it does not require dynamic memory allocation or freeing memory.

## Features
- Reads configuration data from a file
- Parses key-value pairs separated by colons
- Skips commented lines starting with //
- Handles empty lines and lines with leading spaces

## Examples

The `examples` folder contains a sample program that demonstrate how to use the configuration parser.

  **`example.c`**: 
   - This example shows how to read configuration settings from a file and use the configuration parser to populate various data types such as boolean, string, integer, float, and short.

   - **How it works**:
     - It initializes configuration structures.
     - Reads and parses a configuration file.
     - Prints the parsed values to the console.

   - **Configuration File**:
     - Place a configuration file named `config.conf` in the same directory as `example.c` or adjust the file path in the code.


> Config parser criado para um projeto de multi servidores, devido a necessidade de configurar variaveis sem alocação dinâmica e de forma simples e para ser rápido e com um formato unificado, evitando elseifs e estruturas específicas.
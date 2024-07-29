cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Função para comparar versões
function(version_compare ver1 op ver2 result)
    if(op STREQUAL "LESS")
        if(ver1 VERSION_LESS ver2)
            set(${result} TRUE PARENT_SCOPE)
        else()
            set(${result} FALSE PARENT_SCOPE)
        endif()
    elseif(op STREQUAL "GREATER")
        if(ver1 VERSION_GREATER ver2)
            set(${result} TRUE PARENT_SCOPE)
        else()
            set(${result} FALSE PARENT_SCOPE)
        endif()
    elseif(op STREQUAL "EQUAL")
        if(ver1 VERSION_EQUAL ver2)
            set(${result} TRUE PARENT_SCOPE)
        else()
            set(${result} FALSE PARENT_SCOPE)
        endif()
    endif()
endfunction()

# Verifica a versão do g++
execute_process(
    COMMAND g++ --version
    OUTPUT_VARIABLE GPP_VERSION_OUTPUT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" GPP_VERSION "${GPP_VERSION_OUTPUT}")
message(STATUS "Detected g++ version: ${GPP_VERSION}")

# Define a versão mínima
set(MIN_VERSION "13.1.1")
version_compare(${GPP_VERSION} "LESS" ${MIN_VERSION} VERSION_TOO_LOW)

if(VERSION_TOO_LOW)
    # Verifica se g++-13 está instalado
    find_program(GPP_13 NAMES g++-13)
    if(NOT GPP_13)
        message(FATAL_ERROR "g++ version ${MIN_VERSION} or higher is required and g++-13 is not installed.")
    else()
        set(CMAKE_CXX_COMPILER ${GPP_13})
        message(STATUS "Using g++-13: ${GPP_13}")
    endif()
else()
    set(CMAKE_CXX_COMPILER g++)
    message(STATUS "Using g++: g++")
endif()

# Define as flags do compilador
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Adiciona o executável
add_executable(MyProject test.cpp aux.cpp matrix.cpp aux.h)

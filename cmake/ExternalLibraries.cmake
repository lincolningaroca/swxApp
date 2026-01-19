# cmake/ExternalLibraries.cmake

# --- Validación de archivos físicos ---
set(_REQUIRED_LIBS 
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/libQXlsxQt6.a"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/libcrypto.lib"
)

foreach(_LIB_PATH IN LISTS _REQUIRED_LIBS)
    if(NOT EXISTS "${_LIB_PATH}")
        message(FATAL_ERROR 
            "\n[Error de Dependencia]: No se encontró el archivo:\n  ${_LIB_PATH}\n"
            "Verifica que las librerías estén en la carpeta /lib.")
    endif()
endforeach()

# --- Definición de Targets ---

# QXlsx
add_library(QXlsx::QXlsx STATIC IMPORTED GLOBAL)
set_target_properties(QXlsx::QXlsx PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/libQXlsxQt6.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include/QXlsx/QXlsxQt6"
)

# OpenSSL Crypto
add_library(Crypto::Crypto STATIC IMPORTED GLOBAL)
set_target_properties(Crypto::Crypto PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/libcrypto.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
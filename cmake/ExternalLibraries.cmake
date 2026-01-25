# ============================================================================
# Configuración de Dependencias Externas
# ============================================================================

message(STATUS "=== Configurando dependencias externas ===")

set(THIRD_PARTY_DIR "${PROJECT_SOURCE_DIR}/third_party")

# ============================================================================
# OpenSSL
# ============================================================================

# Buscar OpenSSL primero en el sistema
find_package(OpenSSL QUIET)

# Si no se encuentra en el sistema, usar la versión incluida
if(NOT OpenSSL_FOUND)
    message(STATUS "OpenSSL: Usando versión incluida en third_party/")

    set(OPENSSL_ROOT_DIR "${THIRD_PARTY_DIR}/openssl")
    set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")

    # Verificar que los headers existan
    if(NOT EXISTS "${OPENSSL_INCLUDE_DIR}/openssl/ssl.h")
        message(FATAL_ERROR
            "OpenSSL no encontrado en: ${OPENSSL_ROOT_DIR}\n"
            "Estructura esperada:\n"
            "  third_party/openssl/bin/     (DLLs)\n"
            "  third_party/openssl/lib/     (archivos .lib o .dll.a)\n"
            "  third_party/openssl/include/ (headers)"
        )
    endif()

    if(WIN32)
        # Intentar primero con .lib (MSVC/MinGW compatible)
        set(OPENSSL_CRYPTO_LIBRARY "${OPENSSL_ROOT_DIR}/lib/libcrypto.lib")
        set(OPENSSL_SSL_LIBRARY "${OPENSSL_ROOT_DIR}/lib/libssl.lib")

        # Si no existen .lib, intentar con .dll.a (MinGW)
        if(NOT EXISTS "${OPENSSL_CRYPTO_LIBRARY}")
            set(OPENSSL_CRYPTO_LIBRARY "${OPENSSL_ROOT_DIR}/lib/libcrypto.dll.a")
            set(OPENSSL_SSL_LIBRARY "${OPENSSL_ROOT_DIR}/lib/libssl.dll.a")
        endif()

        set(OPENSSL_CRYPTO_DLL "${OPENSSL_ROOT_DIR}/bin/libcrypto-3-x64.dll")
        set(OPENSSL_SSL_DLL "${OPENSSL_ROOT_DIR}/bin/libssl-3-x64.dll")

        # Verificar DLLs
        if(NOT EXISTS "${OPENSSL_CRYPTO_DLL}" OR NOT EXISTS "${OPENSSL_SSL_DLL}")
            message(FATAL_ERROR
                "DLLs de OpenSSL no encontradas:\n"
                "  Esperado: ${OPENSSL_CRYPTO_DLL}\n"
                "  Esperado: ${OPENSSL_SSL_DLL}"
            )
        endif()

        # Verificar archivos de importación
        if(NOT EXISTS "${OPENSSL_CRYPTO_LIBRARY}" OR NOT EXISTS "${OPENSSL_SSL_LIBRARY}")
            message(FATAL_ERROR
                "Archivos de importación de OpenSSL no encontrados:\n"
                "  Buscando: ${OPENSSL_CRYPTO_LIBRARY}\n"
                "  Buscando: ${OPENSSL_SSL_LIBRARY}\n"
                "  En carpeta: ${OPENSSL_ROOT_DIR}/lib/"
            )
        endif()

        # Crear targets importados
        add_library(OpenSSL::Crypto SHARED IMPORTED GLOBAL)
        set_target_properties(OpenSSL::Crypto PROPERTIES
            IMPORTED_LOCATION "${OPENSSL_CRYPTO_DLL}"
            IMPORTED_IMPLIB "${OPENSSL_CRYPTO_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_INCLUDE_DIR}"
        )

        add_library(OpenSSL::SSL SHARED IMPORTED GLOBAL)
        set_target_properties(OpenSSL::SSL PROPERTIES
            IMPORTED_LOCATION "${OPENSSL_SSL_DLL}"
            IMPORTED_IMPLIB "${OPENSSL_SSL_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_INCLUDE_DIR}"
            INTERFACE_LINK_LIBRARIES OpenSSL::Crypto
        )

        set(OpenSSL_FOUND TRUE)
        set(OPENSSL_VERSION "3.x (bundled)")
    endif()

    message(STATUS "OpenSSL: Configurado desde third_party/")
    message(STATUS "  Include: ${OPENSSL_INCLUDE_DIR}")
    message(STATUS "  Crypto Lib: ${OPENSSL_CRYPTO_LIBRARY}")
    message(STATUS "  SSL Lib: ${OPENSSL_SSL_LIBRARY}")
    message(STATUS "  Crypto DLL: ${OPENSSL_CRYPTO_DLL}")
    message(STATUS "  SSL DLL: ${OPENSSL_SSL_DLL}")
else()
    message(STATUS "OpenSSL: Encontrado en el sistema")
    message(STATUS "  Version: ${OPENSSL_VERSION}")
    message(STATUS "  Include: ${OPENSSL_INCLUDE_DIR}")
endif()

# ============================================================================
# QXlsx
# ============================================================================

set(QXLSX_ROOT_DIR "${THIRD_PARTY_DIR}/qxlsx")
set(QXLSX_LIBRARY "${QXLSX_ROOT_DIR}/lib/libQXlsxQt6.a")
set(QXLSX_INCLUDE_DIR "${QXLSX_ROOT_DIR}/include/QXlsx/QXlsxQt6")

# Verificar que QXlsx exista
if(NOT EXISTS "${QXLSX_LIBRARY}")
    message(FATAL_ERROR
        "QXlsx no encontrado en: ${QXLSX_LIBRARY}\n"
        "Estructura esperada:\n"
        "  third_party/qxlsx/lib/libQXlsxQt6.a\n"
        "  third_party/qxlsx/include/QXlsx/QXlsxQt6/"
    )
endif()

if(NOT EXISTS "${QXLSX_INCLUDE_DIR}")
    message(FATAL_ERROR "Headers de QXlsx no encontrados en: ${QXLSX_INCLUDE_DIR}")
endif()

# Crear target para QXlsx
add_library(QXlsx::QXlsx STATIC IMPORTED GLOBAL)
set_target_properties(QXlsx::QXlsx PROPERTIES
    IMPORTED_LOCATION "${QXLSX_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${QXLSX_INCLUDE_DIR}"
)

message(STATUS "QXlsx: Configurado desde third_party/")
message(STATUS "  Library: ${QXLSX_LIBRARY}")
message(STATUS "  Include: ${QXLSX_INCLUDE_DIR}")

message(STATUS "=== Dependencias configuradas correctamente ===")

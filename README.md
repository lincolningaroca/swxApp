# SWUrlManager

**Gestor de URLs inteligente** - Aplicación de escritorio para Windows que permite organizar, guardar y acceder rápidamente a tus direcciones web favoritas con sistema multiusuario.

![License](https://img.shields.io/badge/license-GPL--3.0-blue.svg)
![Qt](https://img.shields.io/badge/Qt-6.5%2B-green.svg)
![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)

## 📋 Descripción

SWUrlManager es una aplicación desarrollada en Qt6 que te permite gestionar eficientemente tus URLs. Con una interfaz intuitiva, puedes:

- 📌 **Guardar URLs** con descripciones personalizadas
- 🗂️ **Organizar por categorías** para mejor gestión
- 🚀 **Abrir directamente en el navegador** con un solo clic
- 🔍 **Buscar y filtrar** tus enlaces guardados
- 📊 **Exportar a Excel** tus colecciones de URLs
- 👥 **Sistema multiusuario** con autenticación segura
- 🔐 **URLs privadas y públicas** - Cada usuario tiene sus propias URLs privadas
- 🌐 **URLs compartidas** - URLs públicas visibles para todos los usuarios

## 🎯 Características principales

- **Sistema multiusuario completo:**
  - Creación de cuentas de usuario
  - Inicio de sesión seguro con encriptación OpenSSL
  - Recuperación de contraseña
  
- **Gestión inteligente de URLs:**
  - **URLs públicas:** Visibles para todos los usuarios al abrir la aplicación
  - **URLs privadas:** Solo visibles cuando inicias sesión con tu cuenta
  - Cada usuario mantiene su propia colección privada de URLs
  
- **Interfaz moderna:**
  - Adaptativa a tema claro y oscuro del sistema
  - Diseño intuitivo y fácil de usar
  
- **Organización avanzada:**
  - Sistema de categorías personalizables
  - Búsqueda instantánea de URLs
  - Exportación a Excel de tus colecciones
  
- **Seguridad robusta:**
  - Contraseñas encriptadas con OpenSSL
  - Separación de datos por usuario
  - Base de datos SQLite local

## 🛠️ Requisitos del sistema

### Para usuarios finales:
- Windows 10/11 (64-bit)
- Conexión a internet (solo para funcionalidad de apertura de URLs)

### Para desarrolladores:
- Windows 10/11 (64-bit)
- Qt 6.5 o superior con MinGW 64-bit
- CMake 3.19 o superior
- Git

## 🚀 Compilación del proyecto

### 1. Clonar el repositorio

```bash
git clone https://github.com/lincolningaroca/swxApp.git
cd swxApp
```

### 2. Configurar herramientas SQLite (Opcional)

La carpeta `tools/` no está incluida en el repositorio por contener binarios. Si necesitas las herramientas SQLite:

1. Descarga SQLite tools desde: https://www.sqlite.org/download.html
2. Busca "sqlite-tools-win-x64" (última versión)
3. Extrae el contenido en: `swxApp/tools/sqlite-tools-win-x64-3450100/`

**Estructura esperada:**
```
tools/
└── sqlite-tools-win-x64-3450100/
    ├── sqlite3.exe
    ├── sqldiff.exe
    └── sqlite3_analyzer.exe
```

> **Nota:** Las herramientas SQLite son opcionales y solo necesarias para mantenimiento avanzado de la base de datos.

### 3. Compilar con Qt Creator

1. Abre Qt Creator
2. Abre el archivo `CMakeLists.txt`
3. Selecciona el kit: **Desktop Qt 6.x.x MinGW 64-bit**
4. Presiona **Build → Build Project** (Ctrl+B)

### 4. Compilar desde línea de comandos

```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=C:/Qt/6.8.3/mingw_64 ..
cmake --build . --config Release
```

## 📦 Dependencias incluidas

Este proyecto incluye todas las dependencias necesarias en la carpeta `third_party/`:

### OpenSSL 3.x
- **Ubicación:** `third_party/openssl/`
- **Propósito:** Encriptación de contraseñas y conexiones seguras
- **Licencia:** Apache License 2.0
- **Documentación:** https://www.openssl.org/

**Estructura:**
```
openssl/
├── bin/          # libcrypto-3-x64.dll, libssl-3-x64.dll
├── include/      # Headers de OpenSSL
└── lib/          # Bibliotecas de importación (.lib)
```

### QXlsx
- **Ubicación:** `third_party/qxlsx/`
- **Propósito:** Exportación de datos a formato Excel (.xlsx)
- **Licencia:** MIT License
- **Repositorio:** https://github.com/QtExcel/QXlsx

**Estructura:**
```
qxlsx/
├── include/      # Headers de QXlsx
└── lib/          # libQXlsxQt6.a (biblioteca estática)
```

> **No necesitas instalar nada adicional.** Todas las dependencias están incluidas y configuradas automáticamente.

## 🏗️ Estructura del proyecto

```
swxApp/
├── cmake/
│   └── ExternalLibraries.cmake    # Configuración de dependencias
├── helperdatabase/
│   └── helperdb.cpp/hpp           # Gestión de base de datos
├── swwidgets/
│   └── sw*.cpp/hpp                # Widgets personalizados
├── util/
│   ├── excelexporter.cpp/hpp      # Exportación a Excel
│   ├── helper.cpp/hpp             # Funciones auxiliares
│   └── systemthemewatcher.cpp/hpp # Detección de tema del sistema
├── third_party/
│   ├── openssl/                   # OpenSSL 3.x
│   └── qxlsx/                     # QXlsx
├── tools/                         # Herramientas SQLite (no incluidas)
├── main.cpp                       # Punto de entrada
├── mainform.cpp/hpp/ui            # Ventana principal
├── *.cpp/hpp/ui                   # Diálogos y formularios
├── rsc.qrc                        # Recursos Qt
├── appIcon.rc                     # Icono de la aplicación
└── CMakeLists.txt                 # Configuración de compilación
```

## 🚀 Uso de la aplicación

### Primera vez - Vista sin autenticar

Al abrir la aplicación por primera vez, verás:
- **URLs públicas:** Enlaces compartidos por todos los usuarios
- Opción para **Iniciar sesión** o **Crear cuenta**

### Crear una cuenta

1. Haz clic en **"Crear cuenta"** o **"Registro"**
2. Ingresa tu nombre de usuario y contraseña
3. Confirma la contraseña
4. ¡Listo! Tu cuenta está creada

### Iniciar sesión

1. Haz clic en **"Iniciar sesión"**
2. Ingresa tu usuario y contraseña
3. Al autenticarte, verás:
   - 🌐 **URLs públicas** (compartidas con todos)
   - 🔒 **Tus URLs privadas** (solo visibles para ti)

### Gestionar URLs

**URLs públicas:**
- Cualquiera puede ver estas URLs sin iniciar sesión
- Útil para compartir enlaces comunes del equipo o empresa

**URLs privadas:**
- Solo tú puedes verlas cuando inicias sesión
- Perfectas para tus enlaces personales o confidenciales
- Se mantienen sincronizadas con tu cuenta

### Funciones adicionales

- **Categorizar URLs:** Organiza tus enlaces en categorías personalizadas
- **Buscar:** Encuentra rápidamente cualquier URL por nombre o descripción
- **Exportar a Excel:** Descarga tus URLs en formato .xlsx
- **Abrir en navegador:** Un clic para abrir cualquier URL
- **Recuperar contraseña:** Opción disponible si olvidas tu contraseña

## 💾 Base de datos

La aplicación utiliza SQLite para almacenar:
- **Usuarios:** Información de cuentas con contraseñas encriptadas
- **URLs públicas:** Enlaces visibles para todos los usuarios
- **URLs privadas:** Enlaces asociados a cada usuario específico
- **Categorías:** Personalizadas por cada usuario
- **Configuraciones:** Preferencias de la aplicación

La base de datos se crea automáticamente en la primera ejecución en:
```
%APPDATA%/SWUrlManager/data.db
```

### Estructura de datos

**Tabla usuarios:**
- ID de usuario
- Nombre de usuario (único)
- Contraseña (encriptada con OpenSSL)
- Fecha de creación

**Tabla urls:**
- ID de URL
- Título/Descripción
- Dirección URL
- ID de categoría
- ID de usuario (NULL para URLs públicas)
- Fecha de creación
- Fecha de modificación

> **URLs públicas:** Cuando `usuario_id` es NULL, la URL es visible para todos
> 
> **URLs privadas:** Cuando `usuario_id` tiene un valor, solo ese usuario puede verla

## 🔧 Configuración de CMake

El proyecto usa CMake con las siguientes características:

- **C++20** como estándar
- **Qt 6.5+** con módulos Core, Widgets, Sql, Network
- **Compilación con warnings estrictos** para código de alta calidad
- **Auto-copia de DLLs** al directorio de salida
- **Generación automática** de scripts de deployment

## 📝 Actualización de dependencias

### Actualizar OpenSSL

Si necesitas actualizar OpenSSL a una versión más reciente:

1. Descarga desde: https://slproweb.com/products/Win32OpenSSL.html
2. O copia desde: `C:\Qt\Tools\OpenSSLv3\win_x64\`
3. Reemplaza los archivos en `third_party/openssl/`

```bash
# Copiar desde Qt
xcopy /E /I /Y C:\Qt\Tools\OpenSSLv3\win_x64\bin\*.dll third_party\openssl\bin\
xcopy /E /I /Y C:\Qt\Tools\OpenSSLv3\win_x64\lib\*.lib third_party\openssl\lib\
xcopy /E /I /Y C:\Qt\Tools\OpenSSLv3\win_x64\include\openssl third_party\openssl\include\openssl\
```

### Actualizar QXlsx

Si necesitas recompilar QXlsx con una versión más reciente de Qt:

1. Clona el repositorio: `git clone https://github.com/QtExcel/QXlsx.git`
2. Compila con tu versión de Qt
3. Reemplaza `libQXlsxQt6.a` en `third_party/qxlsx/lib/`
4. Actualiza los headers en `third_party/qxlsx/include/`

## 🐛 Solución de problemas

### Error: "No se puede encontrar OpenSSL"

Verifica que exista la carpeta `third_party/openssl/` con la estructura correcta. Ejecuta:
```bash
Build → Run CMake
```

### Error: "QXlsx no encontrado"

Asegúrate de que la carpeta se llame exactamente `qxlsx` (no `qxslx`).

### Error al abrir URLs en el navegador

Verifica que tienes un navegador predeterminado configurado en Windows.

### La aplicación no inicia

Verifica que las DLLs de OpenSSL estén en la misma carpeta que el ejecutable:
- `libcrypto-3-x64.dll`
- `libssl-3-x64.dll`

### No puedo iniciar sesión

1. Verifica que estás usando el nombre de usuario y contraseña correctos
2. Si olvidaste tu contraseña, usa la opción **"Recuperar contraseña"**
3. Asegúrate de que la base de datos no esté corrupta

### No veo mis URLs privadas

Verifica que hayas iniciado sesión correctamente. Las URLs privadas solo son visibles cuando estás autenticado.

### ¿Puedo convertir una URL pública en privada?

Sí, edita la URL y asigna un usuario propietario. Solo ese usuario podrá verla después de iniciar sesión.

## 📄 Licencia

Este proyecto está licenciado bajo la GNU General Public License v3.0 - ver el archivo [LICENSE](LICENSE) para más detalles.

**Licencias de dependencias:**
- OpenSSL: Apache License 2.0
- QXlsx: MIT License
- Qt: LGPL v3 / Commercial

## 👥 Contribuciones

Las contribuciones son bienvenidas. Por favor:

1. Haz fork del proyecto
2. Crea una rama para tu feature (`git checkout -b feature/AmazingFeature`)
3. Commit tus cambios (`git commit -m 'Add some AmazingFeature'`)
4. Push a la rama (`git push origin feature/AmazingFeature`)
5. Abre un Pull Request

## 📧 Autor

**Lincoln Ingaroca De La Cruz**

Link del proyecto: [https://github.com/lincolningaroca/swxApp](https://github.com/lincolningaroca/swxApp)

## 🙏 Agradecimientos

- [Qt Framework](https://www.qt.io/) - Framework de aplicaciones multiplataforma
- [OpenSSL](https://www.openssl.org/) - Biblioteca de criptografía
- [QXlsx](https://github.com/QtExcel/QXlsx) - Biblioteca de Excel para Qt
- [SQLite](https://www.sqlite.org/) - Motor de base de datos embebido

---

**⭐ Si este proyecto te resulta útil, considera darle una estrella en GitHub!**
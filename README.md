# swxApp 🚀

![Estado](https://img.shields.io/badge/Estado-Alpha%201%20--%20Hacia%20Beta%201-blue)
![Lenguaje](https://img.shields.io/badge/Lenguaje-C%2B%2B%2017-00599C)
![Framework](https://img.shields.io/badge/Framework-Qt-41CD52)
![Database](https://img.shields.io/badge/Base%20de%20Datos-PostgreSQL-4169E1)

**swxApp** es una aplicación de escritorio desarrollada en **C++ (Qt)** integrada con **PostgreSQL**, enfocada en la gestión segura de usuarios, control de acceso y almacenamiento cifrado de datos.

---

## 📌 Estado Actual del Proyecto

Actualmente el proyecto se encuentra al cierre de la etapa **Alpha 1** y en proceso de empaquetado/estabilización para el lanzamiento de la **Beta 1**.

### 🛠️ Características Implementadas (Alpha 1)
- **Capa de Persistencia en PostgreSQL:** Migración exitosa de la base de datos a PostgreSQL.
- **Gestión Segura de Usuarios:**
  - Autenticación con cifrado Blowfish (`crypt`) y SHA-512.
  - Mecanismos de rescate de clave con cifrado PGP simétrico (`pgp_sym_encrypt`).
  - Procedimientos almacenados y funciones en PL/pgSQL para operaciones de login y registro.
- **Firma e Integridad:** Validación de hashes y credenciales desde la capa del servidor.

---

## 🗺️ Hoja de Ruta (Roadmap)

### 📦 Beta 1 (Próximo Lanzamiento)
- [ ] Empaquetado portable de la aplicación (`windeployqt` + dependencias `libpq`, OpenSSL).
- [ ] Pruebas de estabilidad de conexión a la base de datos.
- [ ] Corrección de errores y refinamiento de la interfaz de usuario en Qt.

### 🔮 Futuras Versiones (v1.1 / v2.0)
- [ ] Sistema de auditoría de inicio/cierre de sesión (`sys_audit`).
- [ ] Control de acceso basado en roles (`user_priv`: `ADMIN` / `USER`).
- [ ] Módulo de administración de usuarios y reportes.

---

## 💻 Requisitos para Compilación y Desarrollo

- **C++:** Estándar C++17 o superior.
- **Framework:** Qt 6.x (o Qt 5.x según versión).
- **Base de Datos:** PostgreSQL 13+ con extensiones `pgcrypto`.
- **Librerías de Enlace:** `libpq`, `libcrypto`, `libssl`.

---

## ⚙️ Configuración Inicial de la Base de Datos

El archivo SQL con las estructuras principales se encuentra dentro de los recursos del proyecto. Para desplegar el esquema de la base de datos:

1. Asegúrate de tener activa la extensión `pgcrypto`:
   ```sql
   CREATE EXTENSION IF NOT EXISTS pgcrypto;
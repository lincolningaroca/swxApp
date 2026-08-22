# swxApp 🚀

[![Estado](https://img.shields.io/badge/Estado-Alpha%201%20--%20Beta%201-blue)](#)
[![Lenguaje](https://img.shields.io/badge/Lenguaje-C%2B%2B17-00599C)](#)
[![Framework](https://img.shields.io/badge/Framework-Qt-41CD52)](#)
[![Database](https://img.shields.io/badge/Base%20de%20Datos-PostgreSQL-4169E1)](#)

**swxApp** es una aplicación de escritorio desarrollada en **C++ (Qt)** integrada con **PostgreSQL**, enfocada en la gestión segura de usuarios, control de acceso y almacenamiento cifrado de datos.

---

## 📌 Estado Actual del Proyecto

La **migración de la base de datos a PostgreSQL ya se completó** — la aplicación ya no depende de SQLite en ningún punto. El proyecto se encuentra en fase de estabilización previa al lanzamiento de **Beta 1**.

### 🛠️ Características Implementadas

**Gestión Segura de Usuarios**
- Autenticación con hash seguro de contraseñas y verificación en el servidor.
- Mecanismo de rescate de clave con los datos protegidos mediante cifrado.
- Procedimientos almacenados en PL/pgSQL para login, registro y gestión de sesiones.

**Gestión de URLs**
- Organización por categorías, con soporte de usuario público (URLs visibles sin necesidad de iniciar sesión) y usuarios autenticados con sus propias categorías privadas.
- Datos cifrados en el servidor, con verificación de existencia sin necesidad de descifrar.
- Importación desde Excel (`.xlsx`), CSV, TSV y texto plano, con detección de duplicados (omitir o reemplazar) y arrastrar-y-soltar (drag & drop) directo sobre la tabla.
- Exportación a los mismos formatos.
- Importación y exportación corren en segundo plano (`QtConcurrent`) con diálogo de progreso — la interfaz no se congela con archivos grandes.
- Carga paginada de la tabla de URLs para categorías con gran volumen de registros.

**Copias de Seguridad**
- Backup y restauración de la base de datos completa vía `pg_dump`/`pg_restore` (formato `--format=custom`), invocados como procesos externos desde la app.
- Reinicio automático de la aplicación tras una restauración exitosa.
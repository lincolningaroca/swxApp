-- Script de inicialización de datos
-- Este script se ejecuta solo si el usuario 'public' no existe

INSERT INTO users (user_name, user_password, user_profile, rescue_type, first_value, confirm_value)
VALUES ('public', 'public', 'PUBLIC', 'PUBLIC', 'PUBLIC', 'PUBLIC');
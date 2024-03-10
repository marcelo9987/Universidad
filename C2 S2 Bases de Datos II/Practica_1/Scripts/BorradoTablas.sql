START TRANSACTION ;

-- Drop the tables
DELETE FROM prestamo CASCADE;
DROP TABLE IF EXISTS prestamo CASCADE;

DELETE FROM usuario ;
DROP TABLE IF EXISTS usuario;

DELETE FROM ejemplar;
DROP TABLE IF EXISTS ejemplar;

DELETE FROM cat_tiene_libro;
DROP TABLE IF EXISTS cat_tiene_libro;

DELETE FROM autor;
DROP TABLE IF EXISTS autor;

DELETE FROM libro;
DROP TABLE IF EXISTS libro;

DELETE FROM categoria;
DROP TABLE IF EXISTS categoria;

-- -- Drop the sequence
DROP SEQUENCE IF EXISTS seq_libro_id_libro;

-- Drop the triggers
DROP TRIGGER IF EXISTS beforeInsertEjemplares ON ejemplar;
DROP TRIGGER IF EXISTS afterLibros ON libro;

-- Drop the functions
DROP FUNCTION IF EXISTS introduce_num_ejemplar();
DROP FUNCTION IF EXISTS controla_secuencias_libro();

commit;

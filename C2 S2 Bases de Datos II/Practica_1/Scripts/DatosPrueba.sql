Insert into categoria values ('Bases de Datos', 'Libros con contenidos relacionados con la tecnología de Sistemas Gestores de Bases de Datos');
Insert into categoria values ('Programación', 'Libros relacionados con lenguajes y técnicas de programación');
Insert into categoria values ('Sistemas Operativos', 'Libros relacionados con sistemas operativos');
Insert into categoria values ('Novela', 'Libros de ficción');
Insert into categoria values ('Clasicos', 'Libros clásicos de la literatura');
Insert into categoria values ('Paper', 'Artículos científicos');
Insert into categoria values ('Psicología', 'Libros de psicología');
Insert into categoria values ('Sociología', 'Libros de sociología');
Insert into categoria values ('Recursos Humanos', 'Libros de recursos humanos');
Insert into categoria values ('Economía', 'Libros de economía');
Insert into categoria values ('Filosofía', 'Libros de filosofía');

Insert into libro (titulo, isbn, editorial, paginas, ano) values ('Fundamentos de bases de datos', '8448136543', 'McGraw Hill', 787, '2002');
Insert into autor (nombre, orden) values ('A. Silberschatz', 1);
Insert into autor (nombre, orden) values ('H.F. Korth', 2);
Insert into autor (nombre, orden) values ('S. Sudarshan', 3);
Insert into cat_tiene_libro (categoria) values ('Bases de Datos');
Insert into ejemplar (ano_compra, localizador) 
	values ('2004', 'prxd34');
Insert into ejemplar (ano_compra, localizador) 
	values ('2005', 'prxd45');

Insert into libro (titulo, isbn, editorial, paginas, ano) values ('An introduction to database systems', '0321189566', 'Pearson/Addison-Wesley', 983, '2003');
Insert into autor (nombre, orden) values ('C.J. Date', 1);
Insert into cat_tiene_libro (categoria) values ('Bases de Datos');
Insert into ejemplar (ano_compra, localizador) 
	values ('2004', 'dsadt3');
Insert into ejemplar (ano_compra, localizador) 
	values ( '2008', 'dsadt56');

Insert into libro (titulo, isbn, editorial, paginas, ano) values ('Programación en Java', '1235253456', 'Springer', 300, '2005');
Insert into autor (nombre, orden) values ('A.P. Sanchez', 1);
Insert into autor (nombre, orden) values ('N. Theodoridou', 2);
Insert into cat_tiene_libro (categoria) values ('Programación');
Insert into ejemplar (ano_compra, localizador) 
	values ('2010', 'fgf5457');

Insert into libro (titulo, isbn, editorial, paginas, ano) values ('Desarrollo de aplicaciones con PHP y PostgreSQL', '0123123456', 'Idea Group Inc.', 120,  '2004');
Insert into autor (nombre, orden) values ('N. Theodoridou', 1);
Insert into cat_tiene_libro (categoria) values ('Bases de Datos');
Insert into cat_tiene_libro (categoria) values ('Programación');
Insert into ejemplar (ano_compra, localizador) 
	values ( '2005', 'dsa3g65');
Insert into ejemplar( ano_compra, localizador) 
	values ('2011', 'dsa3g89');

INSERT into libro(titulo, isbn, editorial, paginas, ano) values('Cien años de soledad', '9788420471839', 'Real Academia Española', 609, '2007');
INSERT into autor(nombre, orden) values('Gabriel García Márquez', 1);
INSERT into cat_tiene_libro(categoria) values('Novela');
INSERT into cat_tiene_libro(categoria) values('Clasicos');
INSERT into ejemplar(ano_compra, localizador) values('2009', 'ltr9563');

INSERT into libro(titulo, isbn, editorial, paginas, ano) values('Sistemas operativos modernos', '9786074420463', 'Pearson Education', 1076, '2009');
INSERT into autor(nombre, orden) values('Andrew S. Tanenbaum', 1);
INSERT into cat_tiene_libro(categoria) values('Sistemas Operativos');
INSERT into cat_tiene_libro(categoria) values('Programación');
INSERT into ejemplar(ano_compra, localizador) values('2009', 'ar18223');
INSERT into ejemplar(ano_compra, localizador) values('2010', 'ar19563');
INSERT into ejemplar(ano_compra, localizador) values('2011', 'ar19564');
INSERT into ejemplar(ano_compra, localizador) values('2012', 'ar19565');
INSERT into ejemplar(ano_compra, localizador) values('2013', 'ar19566');

INSERT into libro(titulo, isbn, editorial, paginas, ano) values('Una teoría sobre la motivación humana', '9781627554671', 'Martino Fine Books', 40, '1943');
INSERT into autor(nombre, orden) values('Abraham H. Maslow', 1);
INSERT into cat_tiene_libro(categoria) values('Psicología');
INSERT into cat_tiene_libro(categoria) values('Sociología');
INSERT into cat_tiene_libro(categoria) values('Recursos Humanos');
INSERT into ejemplar(ano_compra, localizador) values('2010', 'ar19567');
INSERT into ejemplar(ano_compra, localizador) values('2011', 'ar19568');

INSERT into libro(titulo, isbn, editorial, paginas, ano) values('El capital', '8480364025', 'Pirámide', 434, '1984');
INSERT into autor(nombre, orden) values('Karl Marx', 1);
INSERT into cat_tiene_libro(categoria) values('Sociología');
INSERT into cat_tiene_libro(categoria) values('Clasicos');
INSERT into cat_tiene_libro(categoria) values('Economía');
INSERT into cat_tiene_libro(categoria) values('Filosofía');

INSERT into ejemplar(ano_compra, localizador) values('2010', 'ar19569');
INSERT into ejemplar(ano_compra, localizador) values('2011', 'ar19570');

INSERT into libro(titulo, isbn, editorial, paginas, ano) values('Refactoring: Improving the Design of Existing Code', '9780134757599', 'Addison-Wesley',418, '2019');
INSERT into autor(nombre, orden) values('Martin Fowler', 1);
INSERT into cat_tiene_libro(categoria) values('Programación');

INSERT into libro(titulo, isbn, editorial, paginas, ano) values('Structured Programming', '9780122005503', 'Academic Press', 418, '1997');
INSERT into autor(nombre, orden) values('O. J. Dahl', 1);
INSERT into autor(nombre, orden) values('E. W. Dijkstra', 2);
INSERT into autor(nombre, orden) values('C. A. R. Hoare', 3);
INSERT into cat_tiene_libro(categoria) values('Programación');

INSERT into ejemplar(ano_compra, localizador) values('2010', 'ar19571');
INSERT into ejemplar(ano_compra, localizador) values('2011', 'ar19572');
INSERT into ejemplar(ano_compra, localizador) values('2012', 'ar19573');
INSERT into ejemplar(ano_compra, localizador) values('2013', 'ar19574');

INSERT into libro(titulo, isbn, editorial, paginas, ano) values('The UNIX Programming Environment', '9780139376818', 'Prentice Hall', 416, '1984');
INSERT into autor(nombre, orden) values('Brian W. Kernighan', 1);
INSERT into autor(nombre, orden) values('Rob Pike', 2);
INSERT into cat_tiene_libro(categoria) values('Sistemas Operativos');
INSERT into cat_tiene_libro(categoria) values('Programación');

INSERT into ejemplar(ano_compra, localizador) values('2010', 'ar19575');


INSERT into libro(titulo, isbn, editorial, paginas, ano) values('The Psychology of Computer Programming', '9780932633422', 'Dorset House Publishing', 256, '1971');
INSERT into autor(nombre, orden) values('Gerald M. Weinberg', 1);
INSERT into cat_tiene_libro(categoria) values('Programación');
INSERT into cat_tiene_libro(categoria) values('Psicología');

INSERT into ejemplar(ano_compra, localizador) values('2010', 'ar19576');


INSERT into libro(titulo, isbn, editorial, paginas, ano) values ('La inteligencia fracasada', '8433962175', 'Anagrama',174,'2004');
INSERT into autor(nombre, orden) values ('Jose Antonio Marina', 1);
INSERT into cat_tiene_libro(categoria) values ('Psicología');
INSERT into cat_tiene_libro(categoria) values ('Filosofía');
INSERT into ejemplar(ano_compra, localizador) values ('2010', 'ar19577');
INSERT into ejemplar(ano_compra, localizador) values ('2011', 'ar19578');


insert into usuario values ('JAlvarez', 'bvm', 'Juan Alvarez', 'C Blanco Amor', 'JAlvarez@bibdb.es', 'Administrador');                      --descifrada: pja
insert into usuario values ('FEngels', 'xoa', 'Friedrich  Engels','C de la libertad', 'friedrich.engels@hu-berlin.de', 'Administrador');    --descifrada: lco
insert into usuario values ('ERomero', 'bqd', 'Elisa Romero', 'C Rosalia de Castro', 'ERomero@comp1.com', 'Normal');                        --descifrada: per
insert into usuario values ('FPerez', 'brb', 'Francisco Perez', 'C del olvido', 'novotom@locamost.org', 'Normal');                          --descifrada: pfp
insert into usuario values ('SSuarez', 'bee', 'Sara Suarez', 'C de la rosa', 'ss34@alo.com', 'Normal');                                     --descifrada: pss

insert into prestamo(fecha_prestamo,id_usuario,id_libro,num_ejemplar) values('2010-01-01','JAlvarez','1','1');
insert into prestamo(fecha_prestamo,id_usuario,id_libro,num_ejemplar) values('2010-01-01','FEngels','2','1');
insert into prestamo(fecha_prestamo,id_usuario,id_libro,num_ejemplar) values('2010-01-01','ERomero','3','1');
insert into prestamo(fecha_prestamo,id_usuario,id_libro,num_ejemplar) values('2010-01-01','FPerez','4','1');
insert into prestamo(fecha_prestamo,id_usuario,id_libro,num_ejemplar) values('2010-01-01','SSuarez','5','1');
insert into prestamo(fecha_prestamo,id_usuario,id_libro,num_ejemplar) values('2010-01-01','JAlvarez','6','1');
insert into prestamo(fecha_prestamo,id_usuario,id_libro,num_ejemplar) values('2010-01-01','FEngels','7','1');
insert into prestamo(fecha_prestamo,id_usuario,id_libro,num_ejemplar) values('2010-01-01','ERomero','8','1');
insert into prestamo(fecha_prestamo,id_usuario,id_libro,num_ejemplar) values('2010-01-01','SSuarez','10','2');
insert into prestamo(fecha_prestamo,id_usuario,id_libro,num_ejemplar) values('2010-01-01','JAlvarez','11','1');
insert into prestamo(fecha_prestamo,id_usuario,id_libro,num_ejemplar) values('2010-01-01','FEngels','12','1');
insert into prestamo(fecha_prestamo,id_usuario,id_libro,num_ejemplar) values('2010-01-01','ERomero','13','1');
insert into prestamo(fecha_prestamo,id_usuario,id_libro,num_ejemplar) values('2010-01-01','FPerez','13','2');
insert into prestamo(fecha_prestamo,id_usuario,id_libro,num_ejemplar) values('2010-01-01','SSuarez','7','2');
insert into prestamo(fecha_prestamo,id_usuario,id_libro,num_ejemplar) values('2010-01-01','JAlvarez','2','2');





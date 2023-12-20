    --Benef < 15M
begin transaction;

--Cerramos las plantas que generen menos de 15M de beneficios
delete from planta 
where beneficios < 15000000

--A los ingenieros afectados por el cierre los llevamos a la plataforma con más trabajo (mayor nº de litros de petróleo)
update ingenieros 
set idplataforma = (select p.idplataforma 
					from plataforma p 
					where p.litrosextraidospetroleo = (select max(p3.litrosextraidospetroleo) 	
														from plataforma p3 ))
where idplataforma is null 



--Jubilamos a los ingenieros químicos mayores de 40 años debido a radiaciones
delete from ingenieros i
where i.fechanacimiento < '1983-12-18' and i.titulacion = 'Ingeniero Químico' ;

--Añadimos trabajadores nuevos en su sitio
insert into Ingenieros (nombre, apellidos, dni, salario, fechanacimiento, titulacion) values ('William', 'Jones', '39485778A', 9818, '2000-10-19', 'Ingeniero Químico');
insert into Ingenieros (nombre, apellidos, dni, salario, fechanacimiento, titulacion) values ('Harry', 'Smith', '99911155L', 13288, '2000-06-20', 'Ingeniero Químico');
insert into Ingenieros (nombre, apellidos, dni, salario, fechanacimiento, titulacion) values ('Olivia', 'Taylor', '23232323J', 4413, '2000-10-08', 'Ingeniero Químico');
insert into Ingenieros (nombre, apellidos, dni, salario, fechanacimiento, titulacion) values ('Ava', 'Brown', '76764545K', 6920, '2001-05-12', 'Ingeniero Químico');
insert into Ingenieros (nombre , apellidos , dni, salario, fechanacimiento, titulacion) values ('Jessica', 'Wilson', '12344321M', 4218, '2001-04-20', 'Ingeniero Químico');

--Hacemos igualdad en los salarios para los ingenieros informáticos y subimos un 10% del sueldo más pequeño
update ingenieros 
set salario =  (select  max(salario)+(0.1*min(salario)) from ingenieros  where  titulacion  = 'Ingeniero Informático');
--Tecnicos le subimos el salario (plus por reparacion de 100 euros) y el nivel de acceso a los que hayan hecho más de 3 reparaciones 
update  tecnicomantenimiento 
set salario = salario + 100*(select count(*)
    						from registroservicio r
  						  	where r.dni = tecnicomantenimiento.dni
						    group by r.dni
						    having count(*) > 3),
    gradoacceso = 'Absoluto'
where dni in (
    select  r.dni
    from registroservicio r
    where  r.dni = tecnicomantenimiento.dni
    group by  r.dni
    having count(*) > 3
);
commit;

    


Create table categoria
(
  nombre varchar(60) not null primary key,
  descripcion varchar(500)
);

Create sequence seq_libro_id_libro;

Create table libro
(
  id_libro integer default nextval('seq_libro_id_libro') not null primary key,
  titulo varchar(150) not null,
  isbn char(13) not null,
  editorial varchar(100),
  paginas integer,
  ano varchar(4)
);


create or replace function controla_secuencias_libro() returns trigger as $csl$
declare
	ejemplar integer;
begin
  case TG_OP
    when 'INSERT' then
      execute 'create sequence seq_ejemplares_libro_'||cast(NEW.id_libro as text);
      return new;
    when 'UPDATE' then
      IF OLD.id_libro <> NEW.id_libro THEN
	     ejemplar:=nextval('seq_ejemplares_libro_'||cast(OLD.id_libro as text));
	     execute 'drop sequence seq_ejemplares_libro_'||cast(OLD.id_libro as text);
	     execute 'create sequence seq_ejemplares_libro_'||cast(NEW.id_libro as text)|| ' start '||cast(ejemplar as text);
      END IF;
      return new;
    when 'DELETE' then 
      execute 'drop sequence seq_ejemplares_libro_'||cast(OLD.id_libro as text);
      return old;
    else null;
  end case;
end;
$csl$ Language plpgsql;


create trigger afterLibros after insert or update or delete on libro
for each row execute procedure controla_secuencias_libro();



Create table autor
(
 id_libro integer default currval('seq_libro_id_libro') not null,
 nombre varchar(60) not null, -- Cambio de 100 a 60
 orden integer not null,

 primary key (id_libro, nombre),
 foreign key (id_libro) references libro(id_libro)
   on delete cascade on update cascade
);

Create table cat_tiene_libro
(
  categoria varchar(60) not null,
  id_libro integer default currval('seq_libro_id_libro') not null,

  primary key (categoria,id_libro),
  foreign key (categoria) references categoria(nombre)
    on delete restrict on update cascade,
  foreign key (id_libro) references libro(id_libro)
    on delete cascade on update cascade
);

create table ejemplar
(
 id_libro integer default currval('seq_libro_id_libro') not null,
 num_ejemplar integer not null,
 ano_compra varchar(4) not null,
 localizador varchar(25) not null,
 
 primary key (id_libro, num_ejemplar),
 foreign key (id_libro) references libro(id_libro)
   on delete restrict on update cascade
);


create or replace function introduce_num_ejemplar() returns trigger as $csl$
begin
  new.num_ejemplar:=nextval('seq_ejemplares_libro_'||cast(new.id_libro as text));
  return new;
end;
$csl$ Language plpgsql;


create trigger beforeInsertEjemplares before insert on ejemplar
for each row execute procedure introduce_num_ejemplar();



create table usuario
(
  id_usuario varchar(10) not null primary key,
  clave varchar(8) not null,
  nombre varchar(150) not null,
  direccion varchar(200),
  email varchar(30) not null,
  tipo_usuario varchar(15) Default 'Normal' CHECK (tipo_usuario IN ('Normal', 'Administrador'))
);

create table prestamo
(
    id_libro         integer default currval('seq_libro_id_libro'::regclass) not null,
    num_ejemplar     integer                                                 not null,
    id_usuario       varchar(10)                                             not null
        references usuario
            on update cascade on delete restrict,
    fecha_prestamo   date    default CURRENT_DATE                            not null,
    fecha_devolucion date,
    primary key (id_usuario, id_libro, num_ejemplar, fecha_prestamo),
    constraint prestamo_libro_ejemplar_fkey
        foreign key (id_libro, num_ejemplar) references ejemplar
            on update cascade on delete restrict
);


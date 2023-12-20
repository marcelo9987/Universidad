--POLITICA DE INTEGRIDAD PARA ACTUALIZACIONES
--CLAVE FORANEA INGENIEROS (PARA TRANSACCION)

--SE HAN CAMBIADO TIPOS DE DATOS EN LAS TABLAS, ALGUNOS NULL

create type Niveles_de_acceso as enum ('Nivel_1', 'Nivel_2', 'Nivel_3', 'Absoluto');

create table TecnicoMantenimiento
(
    nombre          varchar(45)       not null,
    apellidos       varchar(46)       null,
    dni             char(9) unique not null,
    salario         numeric(8, 3)     null,
    fechaNacimiento date              not null,
    ResidePlanta    bool              not null default false,
    GradoAcceso     Niveles_de_acceso not null,
    constraint tecnicos_pk primary key (dni) -- politica no action
);
comment on column TecnicoMantenimiento.nombre is 'Nombre del tecnico';
comment on column TecnicoMantenimiento.apellidos is 'Apellidos del tecnico';
comment on column TecnicoMantenimiento.dni is 'DNI del tecnico';
comment on column TecnicoMantenimiento.salario is 'Salario del tecnico';
comment on column TecnicoMantenimiento.fechaNacimiento is 'Fecha de nacimiento del tecnico';
comment on column TecnicoMantenimiento.residePlanta is 'Si el tecnico reside en la planta';
comment on column TecnicoMantenimiento.gradoAcceso is 'Grado de acceso del tecnico';

create table Transportistas
(
    Empresa           varchar(50)       not null,
    NumLicencia       numeric(9) unique not null,
    Nombre            varchar(45)       null,
    ModeloEmbarcacion varchar(30)       null,
    constraint transportista_pk primary key (NumLicencia) --politica no action
);
comment on column Transportistas.empresa is 'Empresa para la que trabaja el transportista';
comment on column Transportistas.numLicencia is 'Numero de licencia del transportista';
comment on column Transportistas.nombre is 'Nombre del transportista';
comment on column Transportistas.modeloEmbarcacion is 'Modelo de la embarcacion del transportista';

create table Refineria
(
    Nombre           varchar(50)        not null,
    Direccion        varchar(60) unique not null,
    LitrosProcesados int                null,
    --CIF              char(9) unique  not null,
    CIF              numeric(6) unique  not null,
    constraint refineria_pk primary key (CIF) --politica no action
);
comment on column Refineria.nombre is 'Nombre de la refineria';
comment on column Refineria.direccion is 'Direccion de la refineria';
comment on column Refineria.litrosProcesados is 'Litros procesados por la refineria';
comment on column Refineria.cif is 'Código de Identificación Fiscal de la refineria';

create table Inspectores
(
    NumInspector int unique    not null,
    Ministerio   varchar(50) not null,
    constraint inspectores_pk primary key (NumInspector) --politca no action
);
comment on column Inspectores.numInspector is 'Numero de inspector';
comment on column Inspectores.ministerio is 'Ministerio al que pertenece el inspector';

create table Planta
(
    NumeroID   int unique    not null,
    ubicacion  varchar(60)   not null,
    Ingresos   numeric(11, 3) not null default 0,
    Gastos     numeric(11, 3) not null default 0,
    Beneficios numeric(11, 3) generated ALWAYS AS ( Ingresos - Gastos ) stored,
    constraint planta_pk primary key (numeroID) --politica no action
);
comment on column Planta.numeroID is 'Numero de identificacion de la planta';
comment on column Planta.ubicacion is 'Ubicacion de la planta';
comment on column Planta.ingresos is 'Ingresos de la planta';
comment on column Planta.gastos is 'Gastos incurridos por la operación de la planta';


create table Plataforma
(
    IDPlataforma              int unique    not null,
    LitrosExtraidosPetroleo   int not null default 0,
    NumeroID   int     not null,
    constraint plataforma_pk primary key (IDPlataforma), --no action
    constraint plataforma_fk foreign key (NumeroID) references Planta (NumeroID) on delete cascade
);
comment on column Plataforma.idPlataforma is 'Identificador de la plataforma';
comment on column Plataforma.litrosExtraidosPetroleo is 'Litros de petroleo extraídos por la plataforma';
comment on column Plataforma.numeroID is 'Número de identificación de la planta a la que pertenece la plataforma';


create table RegistroServicio(
    FechaServicio       date  not null,
    CosteReparacion     numeric(7, 3) not null default 0,
    Dni                 char(9)  null,
    NumeroID            int      null,
    IDPlataforma        int     not null,
    constraint RegistroServicio_pk primary key (FechaServicio, Dni, IDPlataforma), --no action
    constraint tecnicodni_fk foreign key (Dni) references TecnicoMantenimiento(DNI) on delete set null,
    constraint numeroid_fk foreign key (NumeroID) references Planta(NumeroID) on delete set null, 
    constraint numeroidplataforma_fk foreign key (IDPlataforma) references Plataforma(IDPlataforma) on delete cascade
);
comment on column RegistroServicio.fechaServicio is 'Fecha del servicio';
comment on column RegistroServicio.costeReparacion is 'Coste de la reparacion';
comment on column RegistroServicio.dni is 'DNI del tecnico que ha realizado el servicio';
comment on column RegistroServicio.numeroID is 'Numero de identificacion de la planta';
comment on column RegistroServicio.idPlataforma is 'Identificador de la plataforma';

create table Inspeccionar
(
    NumInspeccion         int unique not null,
    NumInspector          int null,
    NumeroID              int   not null,
    Informe                bytea,
    FechaInspeccion       date  not null,
    constraint Inspeccionar_pk primary key (NumInspeccion, NumeroID, NumInspector),
    constraint NumInspector_fk foreign key (NumInspector) references Inspectores(NumInspector) on delete set null,
    constraint numeroid_fk foreign key (NumeroID) references Planta(NumeroID) on delete cascade
);
comment on column Inspeccionar.numInspeccion is 'Numero de inspeccion';
comment on column Inspeccionar.numInspector is 'Numero de inspector';
comment on column Inspeccionar.numeroID is 'Numero de identificacion de la planta';
comment on column Inspeccionar.informe is 'Informe de la inspeccion';
comment on column Inspeccionar.fechaInspeccion is 'Fecha de la inspeccion';

create table Comerciar
(
    CodigoTransaccion    char(10) not null,  
    FechaComercio        date not null,
    Precio               numeric(12, 2) not null default 0,
    CantidadPetroleo     int not null default 0,
    NumLicencia       numeric(9)   null,
    CIF              numeric(6)    null,
    NumeroID   int     not null,
    constraint Comerciar_pk primary key (CodigoTransaccion, CIF, NumLicencia, NumeroID),
    constraint Transporte_fk foreign key (NumLicencia) references Transportistas on delete set null,
    constraint IdRefineria_fk foreign key (CIF) references Refineria on delete set null,
    constraint IdPlanta_fk foreign key (NumeroID) references Planta on delete cascade
);
comment on column Comerciar.codigoTransaccion is 'Codigo de la transaccion';
comment on column Comerciar.fechaComercio is 'Fecha del comercio';
comment on column Comerciar.precio is 'Precio del comercio';
comment on column Comerciar.cantidadPetroleo is 'Cantidad de petroleo';
comment on column Comerciar.numLicencia is 'Numero de licencia del transportista';
comment on column Comerciar.cif is 'Codigo de identificacion fiscal de la refineria';
comment on column Comerciar.numeroID is 'Numero de identificacion de la planta';

create table Ingenieros
(
    Nombre          varchar(45)       not null,
    Apellidos       varchar(46)       null,
    Dni             char(9) unique not null,
    Salario         numeric(8, 3)     null,
    FechaNacimiento date              not null,
    Titulacion      varchar(50)       not null,
    IDPlataforma          int null,
    constraint ingenieros_pk primary key (dni), --politica no action
    constraint IDPlataforma_fk foreign key (IDPlataforma ) references Plataforma(IDPlataforma ) on delete set null on update cascade
);
comment on column Ingenieros.nombre is 'Nombre del ingeniero';
comment on column Ingenieros.apellidos is 'Apellidos del ingeniero';
comment on column Ingenieros.dni is 'DNI del ingeniero';
comment on column Ingenieros.salario is 'Salario del ingeniero';
comment on column Ingenieros.fechaNacimiento is 'Fecha de nacimiento del ingeniero';
comment on column Ingenieros.titulacion is 'Titulacion del ingeniero';
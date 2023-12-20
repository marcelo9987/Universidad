    
--Vista de beneficios y gastos generados por las plantas: Finalidad -> seguimiento del rendimiento de la planta
create view EconomiaPlanta as
select p.numeroid , p.ubicacion , p.beneficios, p.gastos 
from planta p ;

--Vista de inspecciones recientes (último mes): Finalidad -> vigilancia de seguridad
create view InspeccionesRecientes as
select i.informe, i.numinspector, i.fechainspeccion 
from inspeccionar i
where i.fechainspeccion  >= current_date - interval '30' day ;

--Vista para filtra ingenieros por salarios y por campo
create view SalarioIngenieros as
select i.nombre, i.apellidos, i.salario 
from ingenieros i 
where i.salario > 5000 and i.salario < 7500 and i.titulacion='Ingeniero Informático';

--Vista de Resumen comercio-transportista-refineria del último mes
create view VistaComerciosTransportistas as
select c.codigotransaccion , c.fechacomercio , t.nombre as Transportista, r.nombre as Refineria
from refineria r, transportistas t, comerciar c
where c.fechacomercio >= current_date - interval '30' day and c.numlicencia = t.numlicencia and r.cif = c.cif ;

--vista de costos totales por cada servicio de mantenimiento
create view VistaCostosMantenimiento as
select r.fechaservicio, r.dni, r.idplataforma,
       r.costereparacion, p.ingresos  as IngresosPlanta,
       (r.costereparacion / p.ingresos) * 100 as PorcentajeCostoIngresos
from registroservicio r , planta p 
where p.numeroid = r.numeroid;


    

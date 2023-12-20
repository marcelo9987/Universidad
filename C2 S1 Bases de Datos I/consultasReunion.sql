
--1. Gastos totales de reparacion por Planta
select p.ubicacion, sum(r.costereparacion) as TotalGastosReparacion
from planta p 
join registroservicio r on p.numeroid = r.numeroid 
group by p.ubicacion 
order by TotalGastosReparacion desc;

--2. Ingresos promedio de las plantas con inspecciones recientes
select p.numeroid  ,avg(p.ingresos) as ingresosPromedio
from planta p 
join inspeccionar i on p.numeroid = i.numeroid 
where i.fechainspeccion >= current_date - interval '30'day
group by p.numeroid  
order by ingresosPromedio desc;

--3. Inspectores que han inspeccionado plantas con altos ingresos (50M)
select distinct  i.NumInspector
from Inspeccionar i
join Planta p ON i.NumeroID = p.NumeroID
where p.Ingresos > 50000000;


--4. PLataformas con mayor extraccion de petroleo y sus inspectores
select p.idplataforma ,i.numinspector 
from plataforma p
join inspeccionar i on p.numeroid = i.numeroid 
where p.litrosextraidospetroleo > 400000;
 
--5. Total de petroleo de comercializado por cada refineria
select r.nombre, sum(c.cantidadpetroleo) as totalPetroleo
from comerciar c 
join refineria r on c.CIF = r.cif 
group by r.nombre
order by totalPetroleo desc;

--6. Plantas con mayor numero de inspecciones y sus ingresos
select p.numeroid, p.ingresos, count(i.numinspeccion) as TotalInspecciones
from planta p
join inspeccionar i on p.numeroid = i.numeroid 
group by p.numeroid , p.ingresos
order by p.ingresos desc;

--7. Relacion entre gastos recientes y gastos de una planta
select e.numeroid,e.ubicacion, e.gastos, COUNT(i.numinspector) as totalInspeccionesRecientes
from economiaplanta e
join inspeccionar i on e.numeroid =i.numeroid 
group by e.numeroid, e.ubicacion,e.gastos
order by totalinspeccionesrecientes;

--8. Cantidad de transacciones por transportista el ultimo mes
select t.nombre, count(v.codigotransaccion) as totalTransacciones
from vistacomerciostransportistas v 
join transportistas t on v.transportista = t.nombre 
group by t.nombre 
--9. Porcentaje de costes de reparación sobre ingresos por plataforma
select r.idplataforma, avg(v2.porcentajecostoingresos) as porcentajeTotal
from registroservicio r 
join vistacostosmantenimiento v2 on r.idplataforma = v2.idplataforma 
group by r.idplataforma
order by porcentajeTotal desc;
--10. Edad media de ingenieros vs tecnicos de mantenimiento
select 'ingenieros' as grupo, avg( extract (year from age(current_date, fechanacimiento))) as mediaEdad
from ingenieros i 
union
select 'tecnicosmantenimiento' as grupo, avg( extract (year from age(current_date, fechanacimiento))) as mediaEdad
from tecnicomantenimiento t
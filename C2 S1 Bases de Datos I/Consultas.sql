--1. Ratio beneficios/gastos a partir de la vista de EconomiaPlanta
select numeroid, 
       ubicacion, 
       beneficios / gastos as RatioBeneficiosGastos
from EconomiaPlanta
order by beneficios/gastos desc;

--2. Porcentaje de costoreparaciones por plataforma como porcentaje de los ingresos de la planta
select  idplataforma , avg(PorcentajeCostoIngresos) as CostoTotalPorcentaje
from VistaCostosMantenimiento
group by idplataforma
order by avg(porcentajecostoingresos ) ;

--3. Ultimas transaccciones por refinería
select Refineria, max(FechaComercio) as UltimaTransaccion
from VistaComerciosTransportistas
group by Refineria;

--4. Conteo de inspecciones por inspector en ultimo mes
select numinspector, count(*) as TotalInspecciones
from InspeccionesRecientes
group by numinspector
having count(*) > 1;

--5. Numero total de servicios de mantenimiento en una planta por año
select numeroid, 
       extract(year from fechaservicio) as Año, 
       count(*) as TotalServicios
from RegistroServicio
group by numeroid,año
order by TotalServicios desc;

--6. Total y promedio de litros de petróleo extraídos por planta
select numeroid, 
       sum(litrosextraidospetroleo) AS TotalLitrosExtraidos, 
       avg(litrosextraidospetroleo) AS PromedioLitrosExtraidos
from plataforma
group by numeroid ;

--7. Planta con mayor beneficio neto
select numeroid , ubicacion, ingresos  - gastos AS beneficioneto
from planta
where (ingresos  - gastos) = (select max(ingresos  - gastos) from planta);

--8. Numero total de transacciones por licencia
select numlicencia, 
       count(*) as totalTransacciones
from comerciar
group by Numlicencia
having count(*) > 1
order by TotalTransacciones desc;

--9. Promedio de costes de reparación por año
select extract (year from fechaservicio) as Año, 
       avg(costeReparacion) as PromedioCosteReparacion
from RegistroServicio
group by Año
order by avg(costeReparacion) desc

--10. Planta con mayor variación de ingresos
select numeroid, 
       ubicacion, 
       ingresos - (select avg(Ingresos) from Planta) as VariacionIngresos
from Planta
order by abs(Ingresos - (select avg(Ingresos) from Planta)) desc
limit 1;
clear all
clf
close all

%CARGA DE DATOS
prompt='Archivo a leer: ';
arch = input(prompt,"s");
t=load(arch); %Carga en memoria el fichero

x=t(:,1); %Eje x: n, primera columna
y_bs=t(:,2); %Eje y: tiempos t(n), segunda columna

pol=polyfit(x,y_bs,3); % ajustamos los puntos por minimos cuadrados a un polinomio de grado 3

yajustadas = polyval(pol,x);

%REPRESENTACIÓN GRÁFICA

plot(x, y_bs, '*b', x, yajustadas, '-r' ); 

legend('empírica','ajuste');


title('Multiplicación matrices ');
xlabel ('Tamaño de la matriz n*n');
ylabel ('Tiempo (segs)');



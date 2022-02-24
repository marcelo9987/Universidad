#Practica 1
.text
.globl main

main:
ADDI $a0,$zero, 4660 
ADDI $a1,$zero,65244
#addi significa add inmediate  y funciona: addi + memoria a usar , memoria a sumar1,const16 a sumar

ADD $a0,$a0,$a1   #$a0=$a0+$a1
 
ADDI $v0, $zero, 1 # Codigo syscall 1 = imprime el entero en $a0
                              #v0 es la variable que "decide lo que pasa"
syscall
ADDI $v0, $zero, 10 # Codigo syscall 10 = Finaliza ejecuci ?on
syscall # Llamada al sistema
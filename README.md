# Ensamblador
Catedra de Sistemas Operativos de la facultad UTN.BA

## Ensamblar
#### Flags

Opción | Nombre | Descripción | 
 ------------- | ------------- | -------------
v | *Verboso* | Imprime en la consola el resultado.
o | *Output* | Indica el archivo a donde guardar el resultado. De evitarlo y no ser verboso, se guarda en “out”.
d | *Decompile* | Intenta des-compilar el código de máquina.
c | *Compile* | Modo por defecto, compila.

## Ejemplos de uso
* `./so-ensamblador -o out.bc in.txt`: Transforma el texto `in.txt` en los bytecodes `out.bc`
* `./so-ensamblador -v -o out.bc in.txt`: Transforma el texto `in.txt` en los bytecodes `out.bc`; adicionalmente imprime por pantalla el compilado
* `./so-ensamblador -dv in.bc`: Decompila el archivo `in.bc` e imprime en la pantalla el contenido
* `./so-ensamblador -o out.txt -d -v in.bc`: Decompila el archivo `in.bc`, imprime en la pantalla el contenido y lo graba en el archivo `out.txt`

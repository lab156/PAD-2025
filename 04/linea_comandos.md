# Ejemplos del uso de la Linea de Comandos
La linea de comandos es de mucha importancia para aprender a usar el comando `gnu-parallel`. A continuacion damos algunos ejemplos de sus características más importantes.

Cuando decimos linea de comandos nos referimos a alguna *shell.* Un shell en Linux es un programa que actúa como interfaz entre el usuario y el sistema operativo. Permite ejecutar comandos, iniciar programas, automatizar tareas mediante scripts y administrar el sistema.

En otras palabras, es el "intérprete de comandos" que recibe las instrucciones del usuario, las interpreta y las ejecuta.

Algunas shell comunes son:
1. sh (Bourne Shell): El shell original, base de muchos otros.
   
2. Bash (Bourne Again SHell) (este es el que esta usando)
    * Es el más común y el predeterminado en muchas distribuciones de Linux.
    * Compatible con scripts del shell Bourne original (sh).
    * Soporta historial de comandos, autocompletado, y estructuras de control (if, for, while).
      
3. Zsh (Z Shell)
    * Muy personalizable.
    * Popular entre usuarios avanzados gracias a complementos como oh-my-zsh.
    * Incluye autocompletado mejorado, globbing avanzado y resaltado de sintaxis.

----------------------

# Los comandos más comunes
 
Echo 
------
Este comando repite el argumento ej. `$ echo "hola mundo"`
     `$ echo $PATH`
      
      
     ```
        $ Variable=hola
        $ echo $Variable
      ```
ls
-------

pwd
-------

mv, cp, mkdir
-------

------------------------

# Operadores de Control y Redireccion
1) `;` separa. `&` background y `|` pipe.
2) if else `&&` y `||`
3) reescribir `>` y append (agregar) `>>`


-------------------------

```bash
 seq -w 01 10 | xargs -I {} ./generate_write data/file-{}.csv
```

---------------

# Adios

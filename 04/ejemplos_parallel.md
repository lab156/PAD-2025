# Ejemplos del uso del comando gnu-parallel

Contar el número de lineas de todos los archivos en la carpeta `data`.
```
parallel wc -l  ::: data/*
```

Imprimir la última linea de la salida
```
parallel --ll ./lineal_args ::: data/*
```

Marcar con colores la salida de archivo individuales
(es mejor modificar los que imprime `lineal_args`)
La opcion `--tag` agrega el nombre del archivo

```
parallel --color --tag ./lineal_args ::: data/*
```

La opción `-j`  (jobs) controla el número de trabajadores.

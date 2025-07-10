# PAD 2025
## Programación de Alto Desempeño (MMM-680)

### Tareas
**Tarea 1**

* Modificar `laplace/serial.c` para que inicialice los datos de temperatura usando `malloc`. Comparar los resultados con y sin `malloc`.
* Implementar la *forma polar* del método de Box-Muller y comparar el desempeño con la versión *forma básica* que aparece en el archivo `lineal.c`.

**Tarea 2**

* Terminar la Tarea 1 (los dos ejercicios)
* Modificar `gradiente/lineal.c` para que acepte los siguientes argumentos:
    *  -n: numero de puntos de datos que hay que generar.
    *  -m: la pendiente de la recta de regresion.
    *  -b: el intercepto en el eje y.

**Tarea 3**

* Modificar el archivo `mutex_example.c` para que escriba a un archivo de texto el valor de de la variable `log_cnt`. 
     
     
 **Avance del Proyecto**

| Lunes  | Martes | Miercoles | Jueves |
|:------:|:------:|:---------:|:------:|
|  Aldo  | David  |  Gustavo  |        |
| Daniel | Sheila |  Lesman   |        |
| Miguel | Kilver |           |        |


-------------

### Apuntes de la clase

2025-05-26
* Ley de Amdahl https://upload.wikimedia.org/wikipedia/commons/e/ea/AmdahlsLaw.svg
* https://theartofhpc.com/
* https://github.com/stanfordnlp/GloVe 

2025-05-27
* Mencionamos Github y los libros de William Stein: https://github.com/williamstein/ant/blob/master/ant.pdf
* Nucleos (Cores) son los elementos de procesamiento de un procesador y  Nodos (Nodes) se refiere a varias computadoras conectadas (Cluster).
* Arquitecturas x86 y ARM.

2025-05-28
* https://www.mersenne.org/
* https://www.fujitsu.com/global/about/innovation/fugaku/
* https://en.wikipedia.org/wiki/Omics

2025-06-04
* https://en-m-wikipedia-org.translate.goog/wiki/Box%E2%80%93Muller_transform?_x_tr_sl=en&_x_tr_tl=es&_x_tr_hl=es&_x_tr_pto=tc
* https://www-geeksforgeeks-org.translate.goog/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/?_x_tr_sl=en&_x_tr_tl=es&_x_tr_hl=es&_x_tr_pto=tc

2025-06-10
* Google search: how to run sleep in a C program in windows
* Google search: cuantas veces mas rapido es la memoria ram que el nvme
* https://webassembly.org/
* https://en-m-wikipedia-org.translate.goog/wiki/Tom%C3%A1%C5%A1_Mikolov?_x_tr_sl=en&_x_tr_tl=es&_x_tr_hl=es&_x_tr_pto=tc
* https://mattmahoney.net/dc/textdata.html

2025-06-11
* Search: which is better dynamic libraries or static libraries in C
* https://www.gnu.org/software/parallel/
* https://github.com/imneme/pcg-c/blob/master/src/pcg-advance-8.c

2025-06-16
* https://www.gnu.org/software/parallel/
* https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
* Search "union in C"
* Search "C keywords"

2025-06-18
* https://www.gnu.org/software/parallel/parallel_examples.html

2025-06-23
* https://stackoverflow.com/questions/2364147/how-to-get-just-one-file-from-another-branch

Para traer solo un archivo de otra branch en git, haga
```
git checkout main                 # first get back to main
git checkout experiment -- app.js # then copy the version of app.js 
                                  # from branch "experiment"
```

2025-06-25
* https://www.geeksforgeeks.org/c/dynamically-allocate-2d-array-c/

2025-06-30
* https://es.wikipedia.org/wiki/POSIX
* https://en.wikipedia.org/wiki/Bubble_sort
* https://en.wikipedia.org/wiki/Quicksort#/media/File:Sorting_quicksort_anim.gif

2025-07-01
* https://es.wikipedia.org/wiki/Condici%C3%B3n_de_carrera

2025-07-07
* https://fastapi.tiangolo.com/
* https://github.com/projectdiscovery/httpx
* https://docs.astral.sh/uv/getting-started/installation/#standalone-installer
 
 
2025-07-09
* Search 'numpy polyfit get mse'
* https://docs.astral.sh/uv/guides/integration/jupyter/
* https://colab.research.google.com/
* https://marimo.io/

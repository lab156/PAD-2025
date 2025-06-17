/*
*
*  Algoritmo de la Criba de Eratostenes
*  https://www.geeksforgeeks.org/dsa/sieve-of-eratosthenes/
*
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

long int SieveOfEratosthenes(long int n)
{
    // Create a boolean array "prime[0..n]" and initialize
    // all entries it as true. A value in prime[i] will
    // finally be false if i is Not a prime, else true.
    bool prime[n + 1];
    // para inicializar un arreglo de datos
    memset(prime, true, sizeof(prime));

    //printf("%ld  --  ", n);
    for (long int p = 2; p * p <= n; p++) {
        // If prime[p] is not changed, then it is a prime
        if (prime[p] == true) {
            // Update all multiples of p greater than or
            // equal to the square of it numbers which are
            // multiple of p and are less than p^2 are
            // already been marked.
            for (long int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
    /*
    for (long int p = 2; p <= n; p++)
        if (prime[p])
            printf("%ld ",p);
    printf(" \n");
    */
    //
    // return the number of prime numbers found
    long int prime_count = 0;
    for (long int i=2; i<n; i++)
        if (prime[i])
            prime_count++;
    return prime_count;
}


int main(int argc, char *argv[])
{
    // num es el numero al que queremos encontrar los primos menores
    // prime_count es el numero de primos antes de num
    long int num, prime_count;
    // endPtr sirve para verificar que se lea bien de la line de comandos
    char *endPtr;
    for (int i=1; i<argc; i++) {
        // strtol : String to Long Int
        // 10 es la base en que hay que leer el numero
        num = strtol(argv[i], &endPtr, 10);
        prime_count = SieveOfEratosthenes(num);
        printf("El prime_count de %ld es %ld \n", num, prime_count);
        // Check if strtol found the Null pointer
        if (*endPtr != '\0')
            printf("ERROR, the end of argument %s was not found", argv[i]);
    }

    printf("The max Int is %d \n", INT_MAX);
    printf("The max Long Int is %ld \n", LONG_MAX);
    return 0;
}


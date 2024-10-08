#include <math.h>
int log2(int n) {
    int log_value = 0;

    if (n <= 0) {
        return -1; // Manejo de error para valores no positivos
    }

    while (n > 1) {
        n >>= 1;  // Desplazar a la derecha es equivalente a dividir por 2
        log_value++;
    }

    return log_value;
}
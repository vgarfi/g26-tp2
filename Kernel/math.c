// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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

double pow(double base, int exponent) {
    double result = 1.0;

    for (int i = 0; i < exponent; i++) {
        result *= base;
    }

    return result;
}
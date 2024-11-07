#include "include/ipc.h"
#include "include/stdio.h"
#include "include/colors.h"
#include "include/string.h"

int is_vocal(unsigned char c);

int64_t cat_process(int argc, char** argv) {
    char c = getchar();
    for (int i = 0; c != -1 && c != '\0' && i < MAXBUFLEN; i++) {
        if (c == '\n'){
            i = 0;
        }
        putchar(c);
        c = getchar();
    }

    return 0;
}

int64_t wc_process(int argc, char** argv) {
    int count = 0;
    char buffer[MAXBUFLEN] = {0};
    while (scanf(buffer, MAXBUFLEN) != EOF) {
        count++;
    }
    print("\nThere are ");
    char numBuf[10];
    itoa(count, numBuf, 10);
    printColor(numBuf, CYAN);
    print(" lines in input buffer");
    return 0;
}

int64_t filter_process(int argc, char** argv) {
    char c = getchar();
    for (int i = 0; c != -1 && c != '\0' && i < MAXBUFLEN; i++) {
        if (c == '\n'){
            i = 0;
        }
        if (!is_vocal(c)) {
            putchar(c);
        }
        c = getchar();
    }
    return 0;
}

int is_vocal(unsigned char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' 
    );
}
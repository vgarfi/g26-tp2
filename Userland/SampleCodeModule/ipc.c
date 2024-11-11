// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/ipc.h"
#include "include/stdio.h"
#include "include/colors.h"
#include "include/string.h"
#include "include/syscalls.h"


#define FILTER_VOCALS       1
#define NO_FILTER_VOCALS    0

void print_buffer(int filter_vocals);
int is_vocal(unsigned char c);
int is_printable(unsigned char c);


int64_t catProcess(int argc, char** argv) {
    print_buffer(NO_FILTER_VOCALS);
	return 0;
}

int64_t wcProcess(int argc, char** argv) {
    char c;
    int count = 0;
	while ((c = getchar()) != (char)EOF) {
		if (c == '\n') {
			putchar('\n');
			count++;
		} else if (is_printable(c)) {
			putchar(c);
		}
	}
    print("\nThere are ");
    char numBuf[10];
    itoa(count, numBuf, 10);
    printColor(numBuf, CYAN);
    print(" lines in input buffer\n");
    return 0;
}

int64_t filterProcess(int argc, char** argv) {
    print_buffer(FILTER_VOCALS);
    return 0;
}

void print_buffer(int filter_vocals) {
    char buff[MAXBUFLEN] = {0};
    char c;
    int readCursor = 0;
    int writeCursor = 0;
    while ((c = getchar()) !=  (char)EOF) {
        if (c == '\b') {
            if (readCursor != 0) {
                putchar('\b');
                readCursor--;
            }
        } else if (c == '\n') {
            putchar('\n');
            while (writeCursor < readCursor) {
                if (!filter_vocals || !is_vocal(buff[writeCursor])) {
                    putchar(buff[writeCursor]);
                }
                writeCursor++;
            }
            readCursor = 0;
            writeCursor = 0;
            putchar('\n');
        } else if (is_printable(c) && readCursor != MAXBUFLEN) {
            buff[readCursor] = c;
            putchar(buff[readCursor++]);
            
        }
    }
    if (sysGetReadFileDescriptor(sysGetCurrentPid()) == STDIN) {
        sysClearKbEntry();
    }
}

int is_vocal(unsigned char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' 
    );
}

int is_printable(unsigned char c) {
    return (c>=' ' && c<='~');
}
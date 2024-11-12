// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <ipc.h>
#include <stdio.h>
#include <colors.h>
#include <string.h>
#include <syscalls.h>


#define FILTER_VOCALS       1
#define NO_FILTER_VOCALS    0

void printBuffer(int filterVocals);
int isVocal(unsigned char c);
int isPrintable(unsigned char c);


int64_t catProcess(int argc, char** argv) {
    printBuffer(NO_FILTER_VOCALS);
	return 0;
}

int64_t wcProcess(int argc, char** argv) {
    char c;
    int count = 0;
	while ((c = getchar()) != (char)EOF) {
		if (c == '\n') {
			putchar('\n');
			count++;
		} else if (isPrintable(c)) {
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
    printBuffer(FILTER_VOCALS);
    return 0;
}

void printBuffer(int filterVocals) {
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
                if (!filterVocals || !isVocal(buff[writeCursor])) {
                    putchar(buff[writeCursor]);
                }
                writeCursor++;
            }
            readCursor = 0;
            writeCursor = 0;
            putchar('\n');
        } else if (isPrintable(c) && readCursor != MAXBUFLEN) {
            buff[readCursor] = c;
            putchar(buff[readCursor++]);
            
        }
    }
    if (sysGetReadFileDescriptor(sysGetCurrentPid()) == STDIN) {
        sysClearKbEntry();
    }
}

int isVocal(unsigned char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' 
    );
}

int isPrintable(unsigned char c) {
    return (c>=' ' && c<='~');
}
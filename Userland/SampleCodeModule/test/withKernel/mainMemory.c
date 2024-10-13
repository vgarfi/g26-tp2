#include <memory/test_mm.h>
#include "../../include/syscalls.h"

#define TEST_PROCESS        "test"

int main(int argc, char *argv[]) {
    char * test_args[] = {TEST_PROCESS, argv[1], argv[2], 0};
    return sysCreateProcess(TEST_PROCESS, 2, test_args, *test_mm_with_kernel);
}
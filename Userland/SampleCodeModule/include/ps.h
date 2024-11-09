#ifndef __PS_H__
#define __PS_H__

#include <stdint.h>

#define PS         "ps"

static char * ps_args[] = {PS, 0};

int64_t psProcess(int argc, char** argv);

#endif
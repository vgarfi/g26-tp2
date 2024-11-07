#ifndef __IPC_H__
#define __IPC_H__

#include <stdint.h>

#define CAT         "cat"
#define WC          "wc"
#define FILTER      "filter"

static char * cat_args[] = {CAT, 0};
static char * wc_args[] = {WC, 0};
static char * filter_args[] = {FILTER, 0};

int64_t cat_process(int argc, char** argv);
int64_t wc_process(int argc, char** argv);
int64_t filter_process(int argc, char** argv);

#endif
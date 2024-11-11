#ifndef __IPC_H__
#define __IPC_H__

#include <stdint.h>

#define CAT         "cat"
#define WC          "wc"
#define FILTER      "filter"

int64_t catProcess(int argc, char** argv);
int64_t wcProcess(int argc, char** argv);
int64_t filterProcess(int argc, char** argv);

#endif
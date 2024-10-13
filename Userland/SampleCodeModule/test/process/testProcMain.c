#include <test_proc.h>
#include <testing.h>

#define TEST_PROCESSES        "process"
#define TEST_PRIORITY        "priority"

void proc_test() {
  char * test_args_proc[] = {TEST_PROCESSES, 1, 100, 0}; //argc = 1, argv[0] = 100
  char * test_args_prio[] = {TEST_PRIORITY, 0};
  sysCreateProcess(TEST_PROCESSES, 0, test_args_proc, *test_processes);
  sysCreateProcess(TEST_PRIORITY, 0, test_args_prio, *test_prio);
}
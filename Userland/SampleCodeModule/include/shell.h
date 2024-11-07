#ifndef __SHELL_H_
#define __SHELL_H_

/**
 * Initializes Shell 
*/
#define SELECTED_MODE       0

#define IDLE_MODE           1
#define HELP_MODE           2
#define DIVBYZERO_MODE      3
#define INVALIDOPCODE_MODE  4
#define ZOOMIN_MODE         5
#define ZOOMOUT_MODE        6
#define TIME_MODE           7
#define DATE_MODE           8
#define ELIMINATOR_MODE     9
#define CLEAR_MODE          10
#define REGISTERS_MODE      11
#define EASTEREGG_MODE      12
#define TESTP_MODE          13
#define TESTPRIO_MODE       14
#define PS_MODE             15
#define TESTMEM_MODE        16
#define TEST_SYNC_MODE      17
#define BLOCKP_MODE         18
#define UNBLOCKP_MODE       19
#define KILLP_MODE          20
#define LOOP_MODE           21
#define CAT_MODE            22
#define WC_MODE             23
#define FILTER_MODE         24
#define PHYLOS              25
#define MEM                 26


static const char* modes[]  __attribute__((unused)) = {
    "shell", "idle", "help", "divbyzero", "invalidopcode", "zoomin", "zoomout", "time", "date", "eliminator", "clear", "registers", "easteregg",
    "testp", "testprio", "ps", "testmem", "testsync", "blockp", "unblockp", "killp", "loop", "cat", "wc", "filter", "phylo", "mem"
};

static char* helpText[]  __attribute__((unused)) = { "Command information is displayed below:\n\n",
"HELP                ->      Shows a description on each available command.\n",
"DIVBYZERO           ->      Shows handling in case of division by zero.\n",
"INVALIDOPCODE       ->      Shows handling in case of an invalid operation code.\n",
"ZOOMIN              ->      Enlarges text size on screen. In case maximum size is reached,\n",
"                            it is properly indicated without making any changes.\n",
"                            Can be alternatively activated with CTRL + i\n",
"ZOOMOUT             ->      Reduces text size on screen. In case minimum size is reached,\n",
"                            it is properly indicated without making any changes.\n", 
"                            Can be alternatively activated with CTRL + o\n",
"TIME                ->      Shows current time in HH:MM:SS format.\n",
"DATE                ->      Shows current date in DD/MM/YY format.\n",
"ELIMINATOR          ->      Opens ELIMINATOR game.\n",
"CLEAR               ->      Clears the screen\n",
"REGISTERS           ->      Prints registers values. To do this, first you need to save\n",
"                            your registers by pressing ALT.\n",
"PS                  ->      Prints current ongoing processes with their information\n",
"MEM                 ->      Prints a memory diagnostic\n",
"BLOCKP              ->      Blocks a process given it's PID\n",
"UNBLOCK             ->      Unblocks a process given it's PID\n",
"KILLP               ->      Kills a process given it's PID\n",
"LOOP                ->      Prints its PID and a greeting in loop\n",
"CAT                 ->      Prints standard input content\n",
"WC                  ->      Counts lines quantity in standard input\n",
"FILTER              ->      Prints its standard input, removing vocals\n",
"PHYLO               ->      Executes phylosophers function as a process\n",

"\n----------------------------------- TESTING -----------------------------------\n\n"
"TESTP               ->      Tests functionalities required for process administration.\n",
"TESTPRIO            ->      Tests processes priorities creation.\n",
"TESTMEM             ->      Tests memory manager required functionalities.\n",
"TESTSYNC            ->      Tests synchronization required functionalities.\n",
"end" 
};

int init();

#endif
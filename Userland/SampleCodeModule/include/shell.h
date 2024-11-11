/**
 * @file shell.h
 * @brief Definition of shell modes, commands, and related functions.
 */

#ifndef __SHELL_H_
#define __SHELL_H_

#define SHELL_MODE      1
#define SELECTED_MODE   0

/**
 * @brief List of built-in shell commands.
 */
static const char* builtinModes[] __attribute__((unused)) = {
    "help", "easteregg", "zoomin", "zoomout", "time", "date", "clear", "registers",
    "ps", "mem", "blockp", "unblockp", "nicep", "killp"
};

/**
 * @brief List of process commands.
 */
static const char* processModes[] __attribute__((unused)) = {
    "eliminator", "testp", "testprio", "testmem", "testsync", "loop", "cat", "wc", "filter", "phylo"
};

/**
 * @brief List of interactive modes.
 */
static const char* interactiveModes[] __attribute__((unused)) = {
    "testp", "testprio", "testmem", "testsync", "loop", "cat", "wc", "filter", "phylo"
};

/**
 * @brief Help text for shell commands.
 */
static char* helpText[]  __attribute__((unused)) = { "Command information is displayed below:\n\n",
"HELP                ->      Shows a description on each available command.\n",
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
"BLOCKP              ->      Blocks a process given its PID\n",
"UNBLOCK             ->      Unblocks a process given its PID\n",
"NICEP               ->      Changes the process' priority given its PID\n",
"KILLP               ->      Kills a process given its PID\n",
"LOOP                ->      Prints its PID and a greeting in loop\n",
"CAT                 ->      Prints standard input content\n",
"WC                  ->      Counts lines quantity in standard input\n",
"FILTER              ->      Prints its standard input, removing vocals\n",
"PHYLO               ->      Executes philosophers function as a process\n",

"\n----------------------------------- TESTING -----------------------------------\n\n"
"TESTP               ->      Tests functionalities required for process administration.\n",
"TESTPRIO            ->      Tests processes priorities creation.\n",
"TESTMEM             ->      Tests memory manager required functionalities.\n",
"TESTSYNC            ->      Tests synchronization required functionalities.\n",
"end" 
};

/**
 * @brief Initializes the shell.
 *
 * @return Status code of the initialization.
 */
int init();

#endif
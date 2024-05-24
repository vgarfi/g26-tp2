#include "include/shell.h"
#include "include/eliminatorGame.h"
#include "include/stdio.h"
#include "include/string.h"
#include "include/colors.h"
#include "include/syscalls.h"

#define HELPLENGTH 8

static char* helpText[]={"Command information is displayed below:\n\n",
"HELP                ->      Shows a description on each available command.\n"
"DIVBYZERO           ->      Shows handling in case of division by zero.\n",
"INVALIDOPCODE       ->      Shows handling in case of an invalid operation code.\n"
"ZOOMIN              ->      Enlarges text size on screen. In case maximum size is reached,\n                            it is properly indicated without making any changes.\n", // See if it can also be accesed via keyboard
"ZOOMOUT             ->      Reduces text size on screen. In case minimum size is reached,\n                            it is properly indicated without making any changes.\n", 
"TIME                ->      Shows current time in HH:MM:SS format.\n",
"DATE                ->      Shows current date in DD/MM/YY format.\n", // Check whether to show it in this format or DD/MM/YYYY
"ELIMINATOR          ->      Opens ELIMINATOR game.\n",
"CLEAR               ->      Clears the screen\n" 
};

int init(){
    printColor("Welcome to Shell! Type HELP for command information.\n\n", YELLOW);
    char commandPrompt[32]={0};
    char* aux;
    while(1){
        printColor("$", GREEN);
        print("> ");
        scanf(commandPrompt, 32);
        if(strcasecmp(commandPrompt, "help")==0){
            for(int i=0; i<HELPLENGTH; i++){
                print(helpText[i]);
            }
        }
        else if(strcasecmp(commandPrompt, "eliminator")==0){
            print("\nLoading eliminator...");
            sleep(2,0);
            eliminatorGame();
        }
        else if(strcasecmp(commandPrompt, "clear")==0){
            clearScreen();
        }
        else if(strcasecmp(commandPrompt, "time")==0){
            aux=getTime();
            print(aux);
            putchar('\n');
        }
        else if(strcasecmp(commandPrompt, "date")==0){
            aux=getDate();
            print(aux);
            putchar('\n');
        }
        else{
            print(commandPrompt); 
            print(": command not found.\n");
        }
    }
}
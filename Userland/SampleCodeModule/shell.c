#include "include/shell.h"
#include "include/eliminatorGame.h"
#include "include/stdio.h"
#include "include/string.h"
#include "include/colors.h"

#define HELPLENGTH 7

static char* helpText[]={"Command information is displayed below:\n",
"HELP                ->      Shows a description on each available command.\n\n"
"DIVBYZERO           ->      Shows handling in case of division by zero.\n\n",
"INVALIDOPCODE       ->      Shows handling in case of an invalid operation code.\n\n"
"ZOOMIN              ->      Enlarges text size on screen. In case maximum size is reached,\n                            it is properly indicated without making any changes.\n\n", // See if it can also be accesed via keyboard
"ZOOMOUT             ->      Reduces text size on screen. In case minimum size is reached,\n                            it is properly indicated without making any changes.\n\n", 
"TIME                ->      Shows current time in HH:MM:SS format.\n\n",
"DATE                ->      Shows current date in DD/MM/YY format.\n\n", // Check whether to show it in this format or DD/MM/YYYY
"ELIMINATOR          ->      Opens ELIMINATOR game.\n\n"
};    

int init(){
    printColor("Welcome to Shell! Type HELP for command information.\n\n", YELLOW);
    char commandPrompt[32]={0};
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
        else{
            print(commandPrompt); 
            print(": command not found.\n");
        }
    }
}
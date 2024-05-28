#include "include/shell.h"
#include "include/eliminatorGame.h"
#include "include/stdio.h"
#include "include/string.h"
#include "include/colors.h"
#include "include/syscalls.h"
#include "include/lib.h"
#include "include/exceptions.h"
#include "include/dateTime.h"

#define HELPLENGTH 13

void saveRegs(void);
int printRegs(void);

static char* helpText[]={"Command information is displayed below:\n\n",
"HELP                ->      Shows a description on each available command.\n"
"DIVBYZERO           ->      Shows handling in case of division by zero.\n",
"INVALIDOPCODE       ->      Shows handling in case of an invalid operation code.\n"
"ZOOMIN              ->      Enlarges text size on screen. In case maximum size is reached,\n",
"                            it is properly indicated without making any changes.\n", // See if it can also be accesed via keyboard
"ZOOMOUT             ->      Reduces text size on screen. In case minimum size is reached,\n",
"                            it is properly indicated without making any changes.\n", 
"TIME                ->      Shows current time in HH:MM:SS format.\n",
"DATE                ->      Shows current date in DD/MM/YY format.\n",
"ELIMINATOR          ->      Opens ELIMINATOR game.\n",
"CLEAR               ->      Clears the screen\n",
"REGISTERS           ->      Prints registers values. To do this, first you need to save\n",
"                            your registers by pressing ALT.\n" 
};

int init(){
    printColor("Welcome to Shell! Type HELP for command information.\n\n", YELLOW);
    char commandPrompt[32]={0};
    char* dateTimeAux;
    int zoomAux, regAux;
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
            hideCursor();
            eliminatorGame();
        }
        else if(strcasecmp(commandPrompt, "clear")==0){
            clearScreen();
        }
        else if(strcasecmp(commandPrompt, "time")==0){
            printTime();
        }
        else if(strcasecmp(commandPrompt, "date")==0){
            printDate();
        }
        else if(strcasecmp(commandPrompt, "zoomin")==0){
            zoomAux = incTextSize();
            if(zoomAux)
                print("Maximum size reached.\n");
        }
        else if(strcasecmp(commandPrompt, "zoomout")==0){
            zoomAux = decTextSize();
            if(zoomAux)
                print("Minimum size reached.\n");
        }
        else if(strcasecmp(commandPrompt, "divbyzero")==0){
            divZero();
        }
        else if(strcasecmp(commandPrompt, "invalidopcode")==0){
            invalidOpcode();
        }
        else if(strcasecmp(commandPrompt, "registers")==0){
            regAux = printRegs();
            if(regAux){
                print("You need to save registers first by pressing ALT\n");
            }
        }
        else{
            print(commandPrompt); 
            print(": command not found.\n");
        }
    }
}
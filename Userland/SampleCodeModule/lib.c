#include "include/lib.h"
#include "include/syscalls.h"

int incTextSize(){
    return zoomIn();
}

int decTextSize(){
    return zoomOut();
}
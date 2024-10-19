#include <stdint.h>
#include <defs.h>
#include <videoDriver.h>
#include "include/time.h"
#include <keyboard.h>
#include <scheduler/scheduler.h>
#include <interrupts.h>
#include <lib.h>
#include <stdio.h>
#include <syscallHandle.h>
#include <kernelManagement.h>
#include "speaker.h"
#include "fonts.h"

extern MemoryManagerADT memory_manager;

#define HANDLER_SIZE 36



static int (*syscallHandlers[])()={
    // Syscalls de Arqui
    read, write, printRegs, incSize, decSize, getZoomLevel, setZoomLevel, upArrowValue, leftArrowValue, downArrowValue,
    rightArrowValue, clearScreen, printSquare, printRect, setCursor, sound, msSleep, hideCursor,
    showCursor, printCursor, getCurrentSeconds, getCurrentMinutes, getCurrentHours, getCurrentDay,
    getCurrentMonth, getCurrentYear, isctrlPressed, cleanKbBuffer,
    // Syscalls de Procesos
    getCurrentPid, exitProcess, createProcess, (int (*)())blockProcess, (int (*)())unblockProcess, (int (*)())killProcess, (int (*)())nice, ps,
    memoryMalloc, memoryFree, memoryStatus
};

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax){         
    // int handlerSize = sizeof(syscallHandlers)/sizeof(syscallHandlers[0]);
    if(rax < 0 || rax > HANDLER_SIZE)
        return -1;

    return syscallHandlers[rax](rdi,rsi,rdx,r10,r8);
}

// TODO read debe poder ser bloqueante. Manejarlo con semáforos (?)
int read(uint64_t fd, char * buf, uint64_t count) {
    if(fd!=STDIN) {   // Only can read from standard input
        return 0;
    }
    uint64_t sizeRead=0;
    unsigned char lastRead='\0';
    while(sizeRead!=count && !kbisBufferEmpty()){
            lastRead = kbreadBuf();
            buf[sizeRead++] = lastRead;
    }
    return sizeRead == count? count : sizeRead;    // If we return sizeRead-1 it means we stopped at '\n'
}

int write(uint64_t fd, char * buf, uint64_t count, uint64_t hexColor){
    if(fd != STDOUT)  // Only can write in STDOUT
        return 0;
    int i;
    char toPrint[2]={0,0};
    for(i=0; i<count; i++){
        toPrint[0]=buf[i];
        vdPrint(toPrint, hexColor);
    }
    return i;
}

int incSize(){
    int zoomFail = sizeUp();
    if(!zoomFail)
        vdResize();
    return zoomFail;
}

int decSize(){
    int zoomFail = sizeDown();
    if(!zoomFail)
        vdResize();
    return zoomFail;
}

int getZoomLevel(){
    return getZoom();
}

int setZoomLevel(int zoomLevel) {
    return setZoom(zoomLevel);
}

int upArrowValue() {    
    return kbUpArrowValue();
}

int leftArrowValue() {
    return kbLeftArrowValue();
}

int downArrowValue() {
    return kbDownArrowValue();
}

int rightArrowValue() {
    return kbRightArrowValue();
}

int clearScreen() {
    vdClearScreen();
    vdClearBuffer();
    return 0;
}

int printRect(int x,int y,int base,int height,uint32_t hexColor) {
    vdPrintRect(x,y,base,height,hexColor);
    return 0;
}

int printSquare (int x, int y,int side, uint32_t hexColor){
    vdPrintSquare(x,y,side, hexColor);
    return 0;
}

int setCursor(uint64_t x, uint64_t y) {
    vdSetCursor(x, y);
    return 0;
}

/** registers are stored in a buffer of 18 qwords in the next order:
 *  RIP RFLAGS RSP RAX RBX RCX RDX RSI RDI RBP R8 R9 R10 R11 R12 R13 R14 R15
 */
int printRegs(){
    return regPrinting();
}

int sound(uint64_t ms, uint64_t freq){
    beep(ms, freq);
    return 0;
}

// rdi = seconds, rsi = ms
int msSleep(uint64_t secs, uint64_t ticks){
    if(secs < 0 || ticks < 0)
        return -1;
    int secondsToTicks = secs*18, msToTicks=ticks;
    int totalTicks = secondsToTicks + msToTicks;
    sleep(totalTicks);
    return 0;
}

int hideCursor(){
    vdSetCursorColor(0x00000000);
    return 0;
}

int showCursor(){
    vdSetCursorColor(0x00F0F0F0);
    return 0;
}

int printCursor(){
    vdPrintCursor();
    return 0;
}

int getCurrentSeconds(void){
    return rtc_get_seconds();
}

int getCurrentMinutes(void){
    return rtc_get_minutes();
}

int getCurrentHours(void){
    return rtc_get_hour();
}

int getCurrentDay(void){
    return rtc_get_day();
}

int getCurrentMonth(void){
    return rtc_get_month();
}

int getCurrentYear(void){
    return rtc_get_year();
}

int isctrlPressed(){
    return kbctrlPressed();
}

int cleanKbBuffer(){
    kbcleanBuffer();
    return 0;
}

int getCurrentPid(){
    return get_current_pid();
}

int exitProcess(){
    return kill_process(getCurrentPid());
}

int createProcess(char* name, uint64_t argc, char *argv[], int64_t (*code)(int, char**)){
    return create_process(name, argc, argv, 1, code);
}

int blockProcess(uint8_t pid){
    return block_process(pid);
}

int unblockProcess(uint8_t pid){
    return unblock_process(pid);
}

int killProcess(uint8_t pid) {
    return kill_process(pid);
}

int nice(uint8_t pid, uint8_t newPriority){
    return change_priority(pid, newPriority);
}

int ps(void){
    return processes_information();
}
void* memoryMalloc(uint64_t size){
    return malloc_mm(memory_manager, size);
}

int memoryFree(void* ptr) {
    free_mm(memory_manager, ptr);
    return 0;
}

int memoryStatus(void){
    // TODO preguntar si estas funciones deberian imprimir por su cuenta (a nivel kernel) o hacer que userland imprima
    get_diagnostic_mm(memory_manager);
    return 0;
}

int yield(void){
    return yield_process();
}
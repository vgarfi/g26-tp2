
/**
 *  0   =   =   =   0   =   =   =   0   =   =   =   0   =   =   =   0   =   =   =   0
 *                              General purpose library
 *  0   =   =   =   0   =   =   =   0   =   =   =   0   =   =   =   0   =   =   =   0
*/


#ifndef __LIB_H_
#define __LIB_H_

/**
 * Increments text size on screen. 
 * Returns 0 if increment was successful, 1 if not (In case max. size has been reached).
*/
int incTextSize(void);

/**
 * Decrements text size on screen.
 * Returns 0 if decrement was successful, 1 if not (In case min. size has been reached).
 * 
*/
int decTextSize(void);

#endif
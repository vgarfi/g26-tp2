/**
 * @file utils.h
 * @brief Definition of utility constants and types.
 */

#ifndef __UTILS_H_
#define __UTILS_H_

#define DO 262        /**< Frequency of note DO */
#define DO_SOST 277   /**< Frequency of note DO# (DO sharp) */
#define RE 294        /**< Frequency of note RE */
#define MI 330        /**< Frequency of note MI */
#define FA 349        /**< Frequency of note FA */
#define FA_SOST 370   /**< Frequency of note FA# (FA sharp) */
#define SOL 392       /**< Frequency of note SOL */
#define SOL_SOST 415  /**< Frequency of note SOL# (SOL sharp) */
#define LA 440        /**< Frequency of note LA */
#define SI 494        /**< Frequency of note SI */
#define DO_PRIMA 523  /**< Frequency of note DO' (DO prime) */

/**
 * @enum TScope
 * @brief Enumeration of process scopes.
 */
enum {
    FOREGROUND,  /**< Foreground process */
    BACKGROUND   /**< Background process */
};

/**
 * @typedef TScope
 * @brief Type representing the scope of a process.
 */
typedef int TScope;

#endif
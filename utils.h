/**
 * @file utils.h
 * @brief Utility structures and helper functions for date and time operations.
 */
#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "debugmalloc.h"

 /**
  * @brief Represents a span of time.
  */
typedef struct TimeSpan {
    int hours;   /**< Number of hours in the time span. */
    int minutes; /**< Number of minutes in the time span. */
    int seconds; /**< Number of seconds in the time span. */
} TimeSpan;

/**
 * @brief Represents a full date with a nested TimeSpan.
 */
typedef struct Date {
    int year;   /**< Year component of the date. */
    int month;  /**< Month component of the date. */
    int day;    /**< Day component of the date. */
    struct TimeSpan;
} Date;
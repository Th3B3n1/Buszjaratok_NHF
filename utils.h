/**
 * @file utils.h
 * @brief Utility structures and helper functions for date, time and input operations.
 */

#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "debugmalloc.h"

/**
 * @brief Represents a span of time.
 */
typedef struct TimeSpan
{
    int hours;   /**< Hours component of the time span. */
    int minutes; /**< Minutes component of the time span. */
    int seconds; /**< Seconds component of the time span. */
} TimeSpan;

/**
 * @brief Represents a full date with time included.
 */
typedef struct Date
{
    int years;  /**< Years component. */
    int months; /**< Months component. */
    int days;   /**< Days component. */

    /**
     * @brief Embedded time information for the date.
     */
    struct TimeSpan;
} Date;

/**
 * @brief Node structure used for dynamically reading characters into a string.
 */
typedef struct String
{
    char c;              /**< The stored character. */
    struct String *next; /**< Pointer to next character node. */
} String;

/**
 * @brief Initializes a Date structure with all fields set to zero.
 * @return A Date struct with default-initialized values.
 */
Date init_date();

/**
 * @brief Compares two Date objects chronologically.
 *
 * @param a Pointer to the first date.
 * @param b Pointer to the second date.
 * @return -1 if @p a is earlier than @p b,
 *          1 if @p a is later than @p b,
 *          0 if the dates are identical.
 */
int compare_dates(const Date *a, const Date *b);

/**
 * @brief Prints a Date in the format YYYY-MM-DD-hh:mm:ss.
 *
 * @param date Pointer to the Date to print.
 */
void print_date(const Date *date);

/**
 * @brief Adds hours, minutes and seconds to a TimeSpan.
 *
 * Handles overflow automatically (seconds → minutes, minutes → hours, hours → 24h wrap).
 *
 * @param time Pointer to the TimeSpan to modify.
 * @param hours Hours to add.
 * @param minutes Minutes to add.
 * @param seconds Seconds to add.
 */
void add_time_to_timespan(TimeSpan *time, const int hours, const int minutes, const int seconds);

/**
 * @brief Adds years, months, days, hours, minutes and seconds to a Date.
 *
 * Handles overflow automatically.
 *
 * @param date Pointer to the Date to modify.
 * @param years Years to add.
 * @param months Months to add.
 * @param days Days to add.
 * @param hours Hours to add.
 * @param minutes Minutes to add.
 * @param seconds Seconds to add.
 */
void add_time_to_date(Date *date, const int years, const int months, const int days, const int hours, const int minutes, const int seconds);

/**
 * @brief Reads a positive integer from stdin until a newline.
 *
 * Only digits are accepted; any other character resets the value to 0.
 *
 * @return The parsed integer, or -1 if the line was empty.
 */
int read_positive_number_from_stdin();

/**
 * @brief Removes trailing newline characters from a string.
 *
 * @param s The string to trim. If NULL, nothing happens.
 */
void trim_line(char *s);

/**
 * @brief Reads a single non-newline character from stdin.
 *
 * @return The character read, or '\\0' if the input was empty.
 */
char read_char_from_stdin();

/**
 * @brief Dynamically reads an entire line from stdin until newline or EOF.
 *
 * Uses a temporary linked list, then flattens it into a null-terminated C string.
 *
 * @return A newly allocated string that must be freed by the caller,
 *         or NULL on allocation failure or empty input.
 */
char *read_string_from_stdin();

void free_stringlist(String *first);
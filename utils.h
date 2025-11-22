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
typedef struct TimeSpan
{
    int hours;   /**< Number of hours in the time span. */
    int minutes; /**< Number of minutes in the time span. */
    int seconds; /**< Number of seconds in the time span. */
} TimeSpan;

/**
 * @brief Represents a full date with a nested TimeSpan.
 */
typedef struct Date
{
    int year;  /**< Year component of the date. */
    int month; /**< Month component of the date. */
    int day;   /**< Day component of the date. */
    struct TimeSpan;
} Date;

typedef struct String {
    char c;
    struct String *next;
} String;

Date init_date();

int compare_dates(const Date *a, const Date *b);

void print_date(const Date *date);

int read_positive_number_from_stdin();

void trim_line(char *s);

char read_char_from_stdin();

char *read_string_from_stdin();
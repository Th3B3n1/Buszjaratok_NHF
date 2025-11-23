/**
 * @file line.h
 * @brief Data structures and functions for handling bus lines and line lists.
 */
#pragma once
#include "utils.h"
#include "stop.h"

/**
 * @brief Represents a stop with timing information from the terminus.
 */
typedef struct LineStop
{
    Stop *stop;                  /**< Pointer to the stop. */
    TimeSpan time_from_terminus; /**< Time taken to reach this stop from the terminus. */
} LineStop;

typedef struct LineStopList
{
    LineStop *stops;
    int count;    /**< Current number of stop entries. */
    int capacity; /**< Allocated capacity of the structure. */
} LineStopList;

/**
 * @brief Represents a single bus line.
 */
typedef struct Line
{
    int line_num;           /**< The line's identification number. */
    int version;            /**< The version of the line. */
    LineStopList *stoplist; /**< Pointer to the list of stops belonging to this line. */
} Line;

/**
 * @brief A dynamic list of Line objects.
 */
typedef struct LineList
{
    Line *lines;  /**< Pointer to dynamically allocated array of lines. */
    int count;    /**< Current number of stored lines. */
    int capacity; /**< Allocated capacity of the list. */
} LineList;

/**
 * @brief Initializes an empty LineList.
 * @return A new LineList instance with zero elements.
 */
void init_linelist(LineList *linelist);

void init_linestoplist(LineStopList *linestoplist);

void free_linelist(LineList *linelist);

void free_linestoplist(LineStopList *linestoplist);

int process_lines(LineList *linelist, const StopList *stoplist, const char *filepath);

int ensure_linelist_capacity(LineList *linelist);

int ensure_linestoplist_capacity(LineStopList *linestoplist);

/**
 * @brief Prints all lines in the list.
 * @param linelist Pointer to the LineList to display.
 */
void list_lines(const LineList *linelist);

void list_line(const LineList *linelist, const int line_num, const int version);

int reorder_linelist_without_a_specific_item(LineList *linelist, const int index);

/**
 * @brief Finds the index of a given Line inside a LineList.
 * @param line Pointer to the Line being searched.
 * @param linelist Pointer to the LineList to search within.
 * @return Index of the line, or -1 if not found.
 */
int find_line_index(const LineList *linelist, const Line *line);

int find_stop_index_in_linestoplist(const LineStopList *linestoplist, const char *stopname);

int find_stop_index_in_linelist(const LineList *linelist, const char *stopname);

int compare_lines(const Line *a, const Line *b);

/**
 * @brief Adds a new Line to a LineList.
 * @param line Pointer to the Line to insert.
 * @param linelist Pointer to the target LineList.
 * @return 0 on success, -1 on failure.
 */
int create_line(LineList *linelist, const Line *line);

/**
 * @brief Deletes a Line from a LineList.
 * @param line Pointer to the Line to remove.
 * @param linelist Pointer to the list from which the line is removed.
 * @return 0 on success, -1 if the line was not found.
 */
int delete_line(LineList *linelist, const Line *line);

/**
 * @brief Retrieves the last stop of a Line.
 * @param line Pointer to the Line whose final stop is requested.
 * @return Pointer to the last Stop, or NULL if none exist.
 */
Stop *get_last_stop(const Line *line);
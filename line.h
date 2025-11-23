/**
 * @file line.h
 * @brief Data structures and functions for handling bus lines, stops within lines,
 *        and file processing related to line definitions.
 */
#pragma once
#include "utils.h"
#include "stop.h"

/**
 * @brief Represents a stop with timing information from the terminus.
 */
typedef struct LineStop {
    Stop *stop;                  /**< Pointer to the stop. */
    TimeSpan time_from_terminus; /**< Time taken to reach this stop from the terminus. */
} LineStop;

/**
 * @brief Dynamic list of LineStop elements.
 */
typedef struct LineStopList {
    LineStop *stops; /**< Dynamically allocated array of LineStop items. */
    int count;       /**< Current number of items in the list. */
    int capacity;    /**< Allocated capacity of the list. */
} LineStopList;

/**
 * @brief Represents a single bus line.
 */
typedef struct Line {
    int line_num;           /**< The line's identification number. */
    int version;            /**< The version of the line. */
    LineStopList *stoplist; /**< Pointer to the list of stops belonging to this line. */
} Line;

/**
 * @brief A dynamic list of Line objects.
 */
typedef struct LineList {
    Line *lines;  /**< Dynamically allocated array of Line items. */
    int count;    /**< Current number of stored lines. */
    int capacity; /**< Allocated capacity of the list. */
} LineList;

/**
 * @brief Initializes an empty LineList.
 * @param linelist Pointer to the LineList to initialize.
 */
void init_linelist(LineList *linelist);

/**
 * @brief Initializes an empty LineStopList.
 * @param linestoplist Pointer to the LineStopList to initialize.
 */
void init_linestoplist(LineStopList *linestoplist);

/**
 * @brief Frees all memory associated with a LineList, including nested stoplists.
 * @param linelist Pointer to the LineList to free.
 */
void free_linelist(LineList *linelist);

/**
 * @brief Frees memory allocated for a LineStopList.
 * @param linestoplist Pointer to the LineStopList to free.
 */
void free_linestoplist(LineStopList *linestoplist);

/**
 * @brief Loads and processes line definitions from a file.
 *        File format: line_num;version;stop#HH:MM;stop#HH:MM;...
 *
 * @param linelist Pointer to the LineList to populate.
 * @param stoplist Pointer to the global StopList used for validation.
 * @param filepath Path to the input file.
 * @return 0 on success, -2 on error.
 */
int process_lines(LineList *linelist, const StopList *stoplist, const char *filepath);

/**
 * @brief Writes the contents of a LineList to a file.
 * @param linelist Pointer to the LineList to serialize.
 * @param filepath Path of the output file.
 * @return 0 on success, -2 on failure.
 */
int write_lines_to_file(const LineList *linelist, const char *filepath);

/**
 * @brief Ensures that the LineList has enough capacity to store additional items.
 * @param linelist Pointer to the LineList.
 * @return 0 on success, -2 on allocation failure.
 */
int ensure_linelist_capacity(LineList *linelist);

/**
 * @brief Ensures that a LineStopList has enough capacity to store additional items.
 * @param linestoplist Pointer to the LineStopList.
 * @return 0 on success, -2 on allocation failure.
 */
int ensure_linestoplist_capacity(LineStopList *linestoplist);

/**
 * @brief Prints all lines in the list.
 * @param linelist Pointer to the LineList to display.
 */
void list_lines(const LineList *linelist);

/**
 * @brief Prints a specific line identified by number and version.
 * @param linelist Pointer to the list containing the line.
 * @param line_num Line number to print.
 * @param version Version to print.
 */
void list_line(const LineList *linelist, const int line_num, const int version);

/**
 * @brief Removes an item from the LineList by index and shifts remaining elements.
 * @param linelist Pointer to the LineList.
 * @param index Index of the line to remove.
 * @return 0 on success, -2 on error.
 */
int reorder_linelist_without_a_specific_item(LineList *linelist, const int index);

/**
 * @brief Finds the index of a given Line inside a LineList.
 * @param linelist Pointer to the LineList.
 * @param line Pointer to the Line being searched.
 * @return Index of the line, -1 if not found, -2 on error.
 */
int find_line_index(const LineList *linelist, const Line *line);

/**
 * @brief Searches for a stop inside a LineStopList by name.
 * @param linestoplist Pointer to the LineStopList.
 * @param stopname Name of the stop.
 * @return Index of the stop, -1 if not found, -2 on error.
 */
int find_stop_index_in_linestoplist(const LineStopList *linestoplist, const char *stopname);

/**
 * @brief Searches for a line that contains a given stop.
 * @param linelist Pointer to the LineList.
 * @param stopname Name of the stop.
 * @return Index of the line, -1 if not found, -2 on error.
 */
int find_stop_index_in_linelist(const LineList *linelist, const char *stopname);

/**
 * @brief Compares two Line objects by number and version.
 * @param a First line.
 * @param b Second line.
 * @return 0 if equal, -1 otherwise.
 */
int compare_lines(const Line *a, const Line *b);

/**
 * @brief Adds a new Line to a LineList.
 * @param linelist Pointer to the LineList.
 * @param line Pointer to the Line to insert.
 * @return 0 on success, -1 if already exists, -2 on error.
 */
int create_line(LineList *linelist, const Line *line);

/**
 * @brief Deletes a Line from a LineList.
 * @param linelist Pointer to the list.
 * @param line Pointer to the Line to delete.
 * @return 0 on success, -1 if not found, -2 on error.
 */
int delete_line(LineList *linelist, const Line *line);

/**
 * @brief Retrieves the time-from-terminus associated with a specific stop in a line.
 * @param line Pointer to the line.
 * @param stopname Name of the stop.
 * @return The corresponding TimeSpan, or {-1,-1,-1} if not found.
 */
TimeSpan get_time_from_terminus(const Line *line, const char *stopname);

/**
 * @brief Retrieves the last stop of a Line.
 * @param line Pointer to the Line.
 * @return Pointer to the last Stop.
 */
Stop *get_last_stop(const Line *line);

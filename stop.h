/**
 * @file stop.h
 * @brief Data structures and operations for handling stops and stop lists.
 */
#pragma once
#include "utils.h"

/**
 * @brief Represents a single bus stop.
 */
typedef struct Stop
{
    char *name; /**< Name of the stop. Dynamically allocated string. */
} Stop;

/**
 * @brief A dynamic list of Stop objects.
 */
typedef struct StopList
{
    Stop *stops;  /**< Pointer to dynamically allocated array of stops. */
    int count;    /**< Number of stored stops. */
    int capacity; /**< Allocated capacity of the stop list. */
} StopList;

/**
 * @brief Initializes an empty StopList.
 *
 * Sets the internal array pointer to NULL, and resets count and capacity.
 *
 * @param stoplist Pointer to an allocated StopList.
 */
void init_stoplist(StopList *stoplist);

/**
 * @brief Frees a StopList and all dynamically allocated stop names.
 *
 * This function frees:
 * - all stop name strings
 * - the internal stop array
 * - the StopList structure itself
 *
 * @param stoplist Pointer to the StopList to free. NULL is ignored.
 */
void free_stoplist(StopList *stoplist);

/**
 * @brief Loads stops from a text file into the StopList.
 *
 * The file must contain one stop name per line.
 * Each stop name is dynamically allocated and stored in the list.
 *
 * @param stoplist Pointer to the StopList to fill.
 * @param filepath Path to the file containing the stop names.
 * @return 0 on success, -2 on file or memory error.
 */
int process_stops(StopList *stoplist, const char *filepath);

/**
 * @brief Writes all stops in the list to a file, one per line.
 *
 * @param stoplist Pointer to the StopList containing the stops.
 * @param filepath Output file path.
 * @return 0 on success, -2 on file error.
 */
int write_stops_to_file(const StopList *stoplist, const char *filepath);

/**
 * @brief Ensures the StopList has enough allocated space to store a new item.
 *
 * If capacity is insufficient, the internal array is reallocated with doubled size.
 *
 * @param stoplist Pointer to the StopList.
 * @return 0 on success, -2 on memory allocation failure.
 */
int ensure_stoplist_capacity(StopList *stoplist);

/**
 * @brief Prints all stops in the list to stdout.
 *
 * Each stop name is printed on a separate line.
 *
 * @param stoplist Pointer to the StopList. NULL is ignored.
 */
void list_stops(const StopList *stoplist);

/**
 * @brief Removes a stop from the list at a given index.
 *
 * Frees the stop's name, shifts remaining elements left, and decreases count.
 *
 * @param stoplist Pointer to the StopList.
 * @param index Index of the stop to remove.
 * @return 0 on success, -2 on invalid StopList.
 */
int reorder_stoplist_without_a_specific_item(StopList *stoplist, const int index);

/**
 * @brief Searches for a stop by name.
 *
 * Performs a linear search through the list.
 *
 * @param stoplist Pointer to the StopList.
 * @param stopname Name of the stop to search for.
 * @return Index of the stop, -1 if not found, -2 if stoplist is NULL.
 */
int find_stop_index(const StopList *stoplist, const char *stopname);

/**
 * @brief Adds a new stop to the list.
 *
 * The stopname pointer is stored directly without copying.
 * Caller must allocate the memory for the stop name.
 *
 * @param stoplist Pointer to the StopList.
 * @param stopname Dynamically allocated string containing the stop name.
 * @return 0 on success, -1 if already exists, -2 on allocation error.
 */
int create_stop(StopList *stoplist, char *stopname);

/**
 * @brief Deletes a stop from the list by name.
 *
 * Searches the stop by name, then removes and frees it.
 *
 * @param stoplist Pointer to the StopList.
 * @param stopname Name of the stop to remove.
 * @return 0 on success, -1 if not found, -2 on error.
 */
int delete_stop(StopList *stoplist, const char *stopname);
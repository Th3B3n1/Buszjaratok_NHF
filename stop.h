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
 * @return A new StopList instance.
 */
void init_stoplist(StopList *stoplist);

void free_stoplist(StopList *stoplist);

int process_stops(StopList *stoplist, const char *filepath);

/**
 * @brief Ensures the StopList has enough capacity for adding new items.
 * @param stoplist Pointer to the StopList.
 * @return 0 on success, -1 on allocation failure.
 */
int ensure_stoplist_capacity(StopList *stoplist);

/**
 * @brief Prints all stops in the list to stdout.
 * @param stoplist Pointer to the StopList to print.
 */
void list_stops(const StopList *stoplist);

/**
 * @brief Reorders the list by removing a specific index.
 * @param stoplist Pointer to the StopList to modify.
 * @param index Index of the element to remove.
 * @return 0 on success, -1 if index is invalid.
 */
int reorder_stoplist_without_a_specific_item(StopList *stoplist, const int index);

/**
 * @brief Finds the index of a stop by its name.
 * @param stoplist Pointer to the StopList.
 * @param stopname Name of the stop to search.
 * @return Index of the stop, or -1 if not found.
 */
int find_stop_index(const StopList *stoplist, const char *stopname);

/**
 * @brief Adds a new stop to the StopList.
 * @param stoplist Pointer to the StopList.
 * @param stopname Name of the stop to add.
 * @return 0 on success, -1 on failure.
 */
int create_stop(StopList *stoplist, const char *stopname);

/**
 * @brief Removes a stop from the StopList.
 * @param stoplist Pointer to the StopList.
 * @param stopname Name of the stop to remove.
 * @return 0 on success, -1 if the stop is not found.
 */
int delete_stop(StopList *stoplist, const char *stopname);
/**
 * @file schedule.h
 * @brief Data structures and functions for handling schedules.
 */
#pragma once
#include "utils.h"
#include "line.h"

/**
 * @brief Represents a scheduled bus departure.
 */
typedef struct Schedule
{
    Line *line; /**< Pointer to the associated bus line. */
    Date start; /**< The starting date and time of the schedule. */
} Schedule;

/**
 * @brief Dynamic list of Schedule objects.
 */
typedef struct ScheduleList
{
    Schedule *schedules; /**< Pointer to dynamically allocated array of schedules. */
    int count;           /**< Current number of stored schedules. */
    int capacity;        /**< Allocated capacity of the list. */
} ScheduleList;

/**
 * @brief Initializes an empty ScheduleList.
 * @param schedulelist Pointer to the ScheduleList to initialize.
 */
void init_schedulelist(ScheduleList *schedulelist);

/**
 * @brief Frees all memory used by a ScheduleList.
 * @param schedulelist Pointer to the ScheduleList to free.
 */
void free_schedulelist(ScheduleList *schedulelist);

/**
 * @brief Loads schedules from a file and processes them into a ScheduleList.
 *
 * File format example:
 *   line_num;version;YYYY-MM-DD HH:MM:SS
 *
 * @param schedulelist Pointer to the target ScheduleList.
 * @param linelist Pointer to the list of lines used for schedule validation.
 * @param filepath Path to the input file.
 * @return 0 on success, -2 on file or memory error.
 */
int process_schedules(ScheduleList *schedulelist, const LineList *linelist, const char *filepath);

/**
 * @brief Writes schedules to a file in the standard format.
 * @param schedulelist Pointer to the ScheduleList to write.
 * @param filepath Path to the output file.
 * @return 0 on success, -2 on error.
 */
int write_schedules_to_file(const ScheduleList *schedulelist, const char *filepath);

/**
 * @brief Ensures capacity for inserting a new schedule.
 * @param schedulelist Pointer to the ScheduleList to resize if needed.
 * @return 0 on success, -2 on allocation failure.
 */
int ensure_schedulelist_capacity(ScheduleList *schedulelist);

/**
 * @brief Prints all schedules in the list to stdout.
 * @param schedulelist Pointer to the ScheduleList to display.
 */
void list_schedules(const ScheduleList *schedulelist);

/**
 * @brief Removes a schedule at a specific index and shifts the list.
 * @param schedulelist Pointer to the list.
 * @param index Index of the schedule to remove.
 * @return 0 on success, -2 on invalid parameters.
 */
int reorder_schedulelist_without_a_specific_item(ScheduleList *schedulelist, const int index);

/**
 * @brief Finds the index of a Schedule in a ScheduleList.
 * @param schedulelist Pointer to the list to search.
 * @param schedule Pointer to the Schedule being searched.
 * @return Index of the schedule, or -1 if not found.
 */
int find_schedule_index(const ScheduleList *schedulelist, const Schedule *schedule);

/**
 * @brief Adds a Schedule to a ScheduleList.
 * @param schedulelist Pointer to the target list.
 * @param schedule Pointer to the Schedule to add.
 * @return 0 on success, -1 on duplicate, -2 on error.
 */
int create_schedule(ScheduleList *schedulelist, const Schedule *schedule);

/**
 * @brief Removes a Schedule from a ScheduleList.
 * @param schedulelist Pointer to the list to update.
 * @param schedule Pointer to the Schedule to remove.
 * @return 0 on success, -1 if the schedule is not found, -2 on error.
 */
int delete_schedule(ScheduleList *schedulelist, const Schedule *schedule);

/**
 * @brief Attempts to find and print available routes between two stops at a given date.
 *
 * Handles direct routes and routes requiring one connection.
 *
 * @param schedulelist Pointer to the global schedule list.
 * @param linelist Pointer to the global line list.
 * @param startstop Name of the starting stop.
 * @param endstop Name of the destination stop.
 * @param date Pointer to the desired date.
 * @return 0 if route(s) were found, -1 if none exist, -2 on invalid parameters.
 */
int find_routes(ScheduleList *schedulelist, LineList *linelist, const char *startstop, const char *endstop, const Date *date);

/**
 * @brief Creates a new list containing all schedules for a line starting from a specific date.
 * @param schedulelist Pointer to the source list.
 * @param line Pointer to the line to filter by.
 * @param date Pointer to the minimum start date.
 * @return Newly allocated ScheduleList, or NULL on failure.
 */
ScheduleList *find_schedules_for_line_within_a_certain_date(const ScheduleList *schedulelist, const Line *line, const Date *date);

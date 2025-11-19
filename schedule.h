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
 * @return A new ScheduleList instance.
 */
void init_schedulelist(ScheduleList *schedulelist);

void free_schedulelist(ScheduleList *schedulelist);

int process_schedules(ScheduleList *schedulelist, char *filepath);

int ensure_schedulelist_capacity(ScheduleList *schedulelist);

/**
 * @brief Prints all schedules in the list to stdout.
 * @param schedulelist Pointer to the ScheduleList to display.
 */
void list_schedules(ScheduleList *schedulelist);

/**
 * @brief Finds the index of a Schedule in a ScheduleList.
 * @param schedulelist Pointer to the list to search.
 * @param schedule Pointer to the Schedule being searched.
 * @return Index of the schedule, or -1 if not found.
 */
int find_schedule_index(ScheduleList *schedulelist, Schedule *schedule);

/**
 * @brief Adds a Schedule to a ScheduleList.
 * @param schedulelist Pointer to the target list.
 * @param schedule Pointer to the Schedule to add.
 * @return 0 on success, -1 on failure.
 */
int create_schedule(ScheduleList *schedulelist, Schedule *schedule);

/**
 * @brief Removes a Schedule from a ScheduleList.
 * @param schedulelist Pointer to the list to update.
 * @param schedule Pointer to the Schedule to remove.
 * @return 0 on success, -1 if the schedule is not found.
 */
int delete_schedule(ScheduleList *schedulelist, Schedule *schedule);
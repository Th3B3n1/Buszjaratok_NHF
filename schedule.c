#include "schedule.h"

void init_schedulelist(ScheduleList *schedulelist)
{
	schedulelist->schedules = NULL;
	schedulelist->count = 0;
	schedulelist->capacity = 0;
}

void free_schedulelist(ScheduleList *schedulelist)
{
	free(schedulelist->schedules);
	free(schedulelist);
}

int process_schedules(ScheduleList *schedulelist, const LineList *linelist, const char *filepath)
{
	if (!linelist || linelist->count == 0)
		return -2;
	FILE *file = fopen(filepath, "r");
	if (file == NULL)
		return -2;
	char unprocessed[512];
	while (fgets(unprocessed, sizeof(unprocessed), file))
	{
		char *next;
		char *line_num = strtok_s(unprocessed, ";", &next);
		char *version = strtok_s(NULL, ";", &next);
		char *departure = strtok_s(NULL, ";", &next);
		Line line = {atoi(line_num), atoi(version), NULL};
		int line_index = find_line_index(linelist, &line);
		if (line_index > -1)
		{
			char *departure_next;
			char *year = strtok_s(departure, "-", &departure_next);
			char *month = strtok_s(NULL, "-", &departure_next);
			char *day = strtok_s(NULL, "-", &departure_next);
			char *hour = strtok_s(NULL, ":", &departure_next);
			char *minute = strtok_s(NULL, ":", &departure_next);
			char *second = strtok_s(NULL, ":", &departure_next);
			Date date = {atoi(year), atoi(month), atoi(day), {atoi(hour), atoi(minute), atoi(second)}};
			Schedule schedule = {&linelist->lines[line_index], date};
			if (ensure_schedulelist_capacity(schedulelist) == -2)
			{
				fclose(file);
				return -2;
			}
			schedulelist->schedules[schedulelist->count] = schedule;
			schedulelist->count++;
		}
		else
		{
			printf("Line %s not found. Will skip current schedule for it.", line_num);
		}
	}
	fclose(file);
	return 0;
}

int ensure_schedulelist_capacity(ScheduleList *schedulelist)
{
	if (schedulelist->count >= schedulelist->capacity)
	{
		int newcapacity = (schedulelist->capacity == 0) ? 16 : schedulelist->capacity * 2;
		Schedule *newschedules = (Schedule *)malloc(newcapacity * sizeof(Schedule));
		if (newschedules == NULL)
			return -2;
		for (int i = 0; i < schedulelist->count; i++)
		{
			newschedules[i] = schedulelist->schedules[i];
		}
		free(schedulelist->schedules);
		schedulelist->schedules = newschedules;
		schedulelist->capacity = newcapacity;
	}
	return 0;
}

int reorder_schedulelist_without_a_specific_item(ScheduleList *schedulelist, const int index)
{
	if (!schedulelist || schedulelist->count == 0)
		return -2;
	if (index < 0)
		return 0;
	for (int i = index; i < schedulelist->count - 1; i++)
	{
		schedulelist->schedules[i] = schedulelist->schedules[i + 1];
	}
	schedulelist->count--;
	return 0;
}

void list_schedules(const ScheduleList *schedulelist)
{
	for (int i = 0; i < schedulelist->count; i++)
	{
		printf("Jarat: %d\n", schedulelist->schedules[i].line->line_num);
		printf("Verzio: %d\n", schedulelist->schedules[i].line->version);
		printf("Vegallomas: %s\n", get_last_stop(schedulelist->schedules[i].line)->name);
		printf("Elso indulas: %2d:%2d:%2d\n", schedulelist->schedules[i].start.hours, schedulelist->schedules[i].start.minutes, schedulelist->schedules[i].start.seconds);
	}
}

int find_schedule_index(const ScheduleList *schedulelist, const Schedule *schedule)
{
	for (int i = 0; i < schedulelist->count; i++)
	{
		if ((compare_dates(&schedulelist->schedules[i].start, &schedule->start) == 0))
		{
			return i;
		}
	}
	return -1;
}

int create_schedule(ScheduleList *schedulelist, const Schedule *schedule)
{
	if (!schedulelist || schedulelist->count == 0)
		return -2;
	if (!schedule)
		return -2;
	if (find_schedule_index(schedulelist, schedule) > -1)
		return -1;
	if (ensure_schedulelist_capacity(schedulelist) == -2)
		return -2;
	schedulelist->schedules[schedulelist->count] = *schedule;
	schedulelist->count++;
	return 0;
}

int delete_schedule(ScheduleList *schedulelist, const Schedule *schedule)
{
	if (!schedulelist || schedulelist->count == 0)
		return -2;
	if (!schedule)
		return -2;
	int index = find_schedule_index(schedulelist, schedule);
	if (index == -1)
		return -1;
	if (reorder_schedulelist_without_a_specific_item(schedulelist, index) == -2)
		return -2;
	return 0;
}
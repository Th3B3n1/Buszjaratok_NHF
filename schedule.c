#include "schedule.h"

void init_schedulelist(ScheduleList* schedulelist)
{
	schedulelist->schedules = NULL;
	schedulelist->count = 0;
	schedulelist->capacity = 0;
}

void free_schedulelist(ScheduleList* schedulelist)
{
	free(schedulelist->schedules);
}

int process_schedules(ScheduleList* schedulelist, char* filepath)
{
	FILE* file = fopen(filepath, "r");
	if (file == NULL) return -1;
	char unprocessed[512];
	while (fgets(unprocessed, sizeof(unprocessed), file))
	{
		// Parsing logic to be implemented
	}
	fclose(file);
	return 0;
}

int ensure_schedulelist_capacity(ScheduleList* schedulelist)
{
	if (schedulelist->count >= schedulelist->capacity)
	{
		int newcapacity = (schedulelist->capacity == 0) ? 16 : schedulelist->capacity * 2;
		Schedule* newschedules = (Schedule*)malloc(newcapacity * sizeof(Schedule));
		if (newschedules == NULL)
			return -1;
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

void list_schedules(ScheduleList* schedulelist)
{
	for (int i = 0; i < schedulelist->count; i++)
	{
		printf("Jarat: %d\n", schedulelist->schedules[i].line->line_num);
		printf("Verzio: %d\n", schedulelist->schedules[i].line->version);
		printf("Verzio: %s\n", get_last_stop(schedulelist->schedules[i].line)->name);
		printf("Verzio: %d:%d\n", schedulelist->schedules[i].start.hours, schedulelist->schedules[i].start.minutes);
	}
}

int find_schedule_index(ScheduleList* schedulelist, Schedule* schedule)
{
	for (int i = 0; i < schedulelist->count; i++)
	{
		if (schedulelist->schedules[i].line->line_num == schedule->line->line_num &&
			schedulelist->schedules[i].line->version == schedule->line->version &&
			schedulelist->schedules[i].start.year == schedule->start.year &&
			schedulelist->schedules[i].start.month == schedule->start.month &&
			schedulelist->schedules[i].start.day == schedule->start.day)
		{
			return i;
		}
	}
	return -1;
}

int create_schedule(ScheduleList* schedulelist, Schedule* schedule)
{

}

int delete_schedule(ScheduleList* schedulelist, Schedule* schedule)
{

}
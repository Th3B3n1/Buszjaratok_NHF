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
			char *day = strtok_s(NULL, " ", &departure_next);
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

int write_schedules_to_file(const ScheduleList *schedulelist, const char *filepath)
{
	if (!schedulelist)
		return -2;
	FILE *file = fopen(filepath, "w");
	if (file == NULL)
		return -2;
	for (int i = 0; i < schedulelist->count; i++)
	{
		fprintf_s(file, "%d;%d;%4d-%02d-%02d %02d:%02d:%02d\n", schedulelist->schedules[i].line->line_num, schedulelist->schedules[i].line->version, schedulelist->schedules[i].start.years, schedulelist->schedules[i].start.months, schedulelist->schedules[i].start.days, schedulelist->schedules[i].start.hours, schedulelist->schedules[i].start.minutes, schedulelist->schedules[i].start.seconds);
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
		if ((compare_lines(schedulelist->schedules[i].line, schedule->line) == 0) && (compare_dates(&schedulelist->schedules[i].start, &schedule->start) == 0))
		{
			return i;
		}
	}
	return -1;
}

ScheduleList *find_schedules_for_line_within_a_certain_date(const ScheduleList *schedulelist, const Line *line, const Date *date)
{
	ScheduleList *new_schedulelist = (ScheduleList *)malloc(sizeof(ScheduleList));
	if (!new_schedulelist)
		return NULL;
	init_schedulelist(new_schedulelist);
	for (int i = 0; i < schedulelist->count; i++)
	{
		if ((compare_lines(schedulelist->schedules[i].line, line) == 0) && compare_dates(&schedulelist->schedules[i].start, date) >= 0)
		{
			if (ensure_schedulelist_capacity(new_schedulelist) == -2)
			{
				free_schedulelist(new_schedulelist);
				return NULL;
			}
			new_schedulelist->schedules[new_schedulelist->count] = schedulelist->schedules[i];
			new_schedulelist->count++;
		}
	}
	return new_schedulelist;
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

void print_route(Line *line, const char *startstop, const char *endstop, const Date *start_time, const Date *end_time)
{
	printf("%d: %s -> %s\n", line->line_num,
		   line->stoplist->stops[0].stop->name,
		   get_last_stop(line)->name);
	printf("\tFelszallas: %s (%02d:%02d)\n", startstop, start_time->hours, start_time->minutes);
	printf("\tLeszallas: %s (%02d:%02d)\n", endstop, end_time->hours, end_time->minutes);
}

int find_routes(ScheduleList *schedulelist, LineList *linelist, const char *startstop, const char *endstop, const Date *date)
{
	if (!startstop || !endstop || !date)
		return -2;
	Line *startline = NULL;
	Line *endline = NULL;
	for (int i = 0; i < linelist->count; i++)
	{
		for (int y = 0; y < linelist->lines[i].stoplist->count; y++)
		{
			if (strcmp(linelist->lines[i].stoplist->stops[y].stop->name, startstop) == 0)
			{
				startline = &linelist->lines[i];
			}
			if (strcmp(linelist->lines[i].stoplist->stops[y].stop->name, endstop) == 0)
			{
				endline = &linelist->lines[i];
			}
			if (startline && endline)
				break;
		}
		if (startline && endline)
			break;
	}
	if (!startline || !endline)
		return -1;

	if (compare_lines(startline, endline) == 0)
	{
		ScheduleList *schedules = find_schedules_for_line_within_a_certain_date(schedulelist, startline, date);
		if (!schedules || schedules->count == 0)
		{
			free_schedulelist(schedules);
			return -1;
		}
		Schedule schedule = schedules->schedules[0];
		Date start_date = schedule.start;
		TimeSpan start_time = get_time_from_terminus(startline, startstop);
		add_time_to_date(&start_date, 0, 0, 0, start_time.hours, start_time.minutes, start_time.seconds);

		Date end_date = schedule.start;
		TimeSpan end_time = get_time_from_terminus(startline, endstop);
		add_time_to_date(&end_date, 0, 0, 0, end_time.hours, end_time.minutes, end_time.seconds);
		print_route(startline, startstop, endstop, &start_date, &end_date);
		free_schedulelist(schedules);
		return 0;
	}

	int connection_index = -1;
	for (int i = 0; i < startline->stoplist->count; i++)
	{
		for (int y = 0; y < endline->stoplist->count; y++)
		{
			if (strcmp(startline->stoplist->stops[i].stop->name, endline->stoplist->stops[y].stop->name) == 0)
			{
				connection_index = i;
				break;
			}
		}
	}
	if (connection_index == -1)
	{
		return -1;
	}

	Stop *connection_stop = startline->stoplist->stops[connection_index].stop;

	ScheduleList *start_line_schedules = find_schedules_for_line_within_a_certain_date(schedulelist, startline, date);
	if (!start_line_schedules || start_line_schedules->count == 0)
	{
		free_schedulelist(start_line_schedules);
		return -1;
	}
	Schedule start_schedule = start_line_schedules->schedules[0];

	Date start_date = start_schedule.start;
	TimeSpan start_time = get_time_from_terminus(startline, startstop);
	add_time_to_date(&start_date, 0, 0, 0, start_time.hours, start_time.minutes, start_time.seconds);

	Date connection_date_startline = start_schedule.start;
	TimeSpan connection_time = get_time_from_terminus(startline, connection_stop->name);
	add_time_to_date(&connection_date_startline, 0, 0, 0, connection_time.hours, connection_time.minutes, connection_time.seconds);
	ScheduleList *end_line_schedules = find_schedules_for_line_within_a_certain_date(schedulelist, endline, &connection_date_startline);
	if (!end_line_schedules || end_line_schedules->count == 0)
	{
		free_schedulelist(end_line_schedules);
		return -1;
	}

	Schedule end_schedule = end_line_schedules->schedules[0];

	Date connection_date_endline = end_schedule.start;
	TimeSpan connection_time_endline = get_time_from_terminus(endline, connection_stop->name);
	add_time_to_date(&connection_date_endline, 0, 0, 0, connection_time_endline.hours, connection_time_endline.minutes, connection_time_endline.seconds);

	Date end_date = end_schedule.start;
	TimeSpan end_time = get_time_from_terminus(endline, endline->stoplist->stops[endline->stoplist->count - 1].stop->name);
	add_time_to_date(&end_date, 0, 0, 0, end_time.hours, end_time.minutes, end_time.seconds);

	print_route(startline, startstop, connection_stop->name, &start_date, &connection_date_startline);
	print_route(endline, connection_stop->name, endstop, &connection_date_endline, &end_date);

	free_schedulelist(start_line_schedules);
	free_schedulelist(end_line_schedules);

	return 0;
}
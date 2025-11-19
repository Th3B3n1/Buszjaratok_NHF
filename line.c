#include "line.h"

void init_linelist(LineList *linelist)
{
	linelist->lines = NULL;
	linelist->count = 0;
	linelist->capacity = 0;
}

void init_linestoplist(LineStopList *linestoplist)
{
	linestoplist->stops = NULL;
	linestoplist->count = 0;
	linestoplist->capacity = 0;
}

void free_linelist(LineList* linelist)
{
	for (int i = 0; i < linelist->count; i++)
	{
		free_linestoplist(linelist->lines[i].stoplist);
		free(linelist->lines[i].stoplist);
	}
	free(linelist->lines);
}

void free_linestoplist(LineStopList *linestoplist)
{
	free(linestoplist->stops);
}

int process_lines(LineList *linelist, StopList *stoplist, char *filepath)
{
	if (!stoplist || stoplist->count == 0)
		return -1;
	FILE *file = fopen(filepath, "r");
	if (file == NULL)
		return -1;
	char unprocessed[512];
	while (fgets(unprocessed, sizeof(unprocessed), file))
	{
		char *line_num = strtok(unprocessed, ";");
		char *version_str = strtok(NULL, ";");
		char *next = strtok(NULL, ";");
		printf("Next token: %s\n", next);
		Line line = {(*line_num - '0'), (*version_str - '0'), NULL};
		while (next != NULL)
		{
			if (line.stoplist == NULL)
			{
				line.stoplist = (LineStopList *)malloc(sizeof(LineStopList));
				init_linestoplist(line.stoplist);
			}
			char *key = strtok(next, "-");
			char *value = strtok(NULL, "-");
			printf("Key: %s, Value: %s\n", key, value);
			int stopindex = find_stop_index(stoplist, key);
			if (stopindex != -1)
			{
				Stop *stop = &stoplist->stops[stopindex];
				char *hour_str = strtok(value, ":");
				char *minute_str = strtok(NULL, ":");
				TimeSpan time = {(*hour_str - '0'), (*minute_str - '0'), 0};
				LineStop linestop = {stop, time};
				if (ensure_linestoplist_capacity(line.stoplist) != 0)
				{
					fclose(file);
					return -1;
				}
				line.stoplist->stops[line.stoplist->count] = linestop;
				line.stoplist->count++;
			}
			else
			{
				printf("Warning: Stop '%s' not found in stop list.\n", key);
			}
			next = strtok(NULL, ";");
			printf("Next token: %s\n", next);
		}
		if (ensure_linelist_capacity(linelist) != 0)
		{
			fclose(file);
			return -1;
		}
		linelist->lines[linelist->count] = line;
		linelist->count++;
	}
	fclose(file);
	return 0;
}

int ensure_linelist_capacity(LineList *linelist)
{
	if (linelist->count >= linelist->capacity)
	{
		int newcapacity = (linelist->capacity == 0) ? 16 : linelist->capacity * 2;
		Line *newlines = (Line *)malloc(newcapacity * sizeof(Line));
		if (newlines == NULL)
			return -1;
		for (int i = 0; i < linelist->count; i++)
		{
			newlines[i] = linelist->lines[i];
		}
		free(linelist->lines);
		linelist->lines = newlines;
		linelist->capacity = newcapacity;
	}
	return 0;
}

int ensure_linestoplist_capacity(LineStopList *linestoplist)
{
	if (linestoplist->count >= linestoplist->capacity)
	{
		int newcapacity = (linestoplist->capacity == 0) ? 16 : linestoplist->capacity * 2;
		LineStop *newlinestops = (LineStop *)malloc(newcapacity * sizeof(LineStop));
		if (newlinestops == NULL)
			return -1;
		for (int i = 0; i < linestoplist->count; i++)
		{
			newlinestops[i] = linestoplist->stops[i];
		}
		free(linestoplist->stops);
		linestoplist->stops = newlinestops;
		linestoplist->capacity = newcapacity;
	}
	return 0;
}

void list_lines(LineList *linelist)
{
	for (int i = 0; i < linelist->count; i++)
	{
		printf("Jarat: %d\n", linelist->lines[i].line_num);
		printf("Verzio: %d\n", linelist->lines[i].version);
		printf("Utvonal: %s -> %s\n", (linelist->lines[i].stoplist->count > 0) ? linelist->lines[i].stoplist->stops[0].stop->name : "", (linelist->lines[i].stoplist->count > 0) ? linelist->lines[i].stoplist->stops[linelist->lines[i].stoplist->count - 1].stop->name : "");
	}
}

int reorder_linelist_without_a_specific_item(LineList *linelist, int index)
{
	if (index < 0)
		return 0;
	for (int i = index; i < linelist->count - 1; i++)
	{
		linelist->lines[i] = linelist->lines[i + 1];
	}
	linelist->count--;
	return 0;
}

int find_line_index(LineList *linelist, Line *line)
{
	for (int i = 0; i < linelist->count; i++)
	{
		if (linelist->lines[i].line_num == line->line_num && linelist->lines[i].version == line->version)
		{
			return i;
		}
	}
	return -1;
}

int find_stop_index_in_linestoplist(LineStopList *linestoplist, char *stopname)
{
	for (int i = 0; i < linestoplist->count; i++)
	{
		if (strcmp(linestoplist->stops[i].stop->name, stopname) == 0)
		{
			return i;
		}
	}
	return -1;
}

int find_stop_index_in_linelist(LineList *linelist, char *stopname)
{
	for (int i = 0; i < linelist->count; i++)
	{
		if (find_stop_index_in_linestoplist(linelist->lines[i].stoplist, stopname) != -1)
		{
			return i;
		}
	}
	return -1;
}

int create_line(LineList *linelist, Line *line)
{
	if (linelist->count >= linelist->capacity)
	{
		int newcapacity = (linelist->capacity == 0) ? 16 : linelist->capacity * 2;
		Line *newlines = (Line *)realloc(linelist->lines, newcapacity * sizeof(Line));
		if (newlines == NULL)
			return -1;
		linelist->lines = newlines;
		linelist->capacity = newcapacity;
	}
	linelist->lines[linelist->count] = *line;
	linelist->count++;
	return 0;
}

int delete_line(LineList *linelist, Line *line)
{
	int index = find_line_index(linelist, line);
	if (index == -1)
		return -1;
	reorder_linelist_without_a_specific_item(linelist, index);
	return 0;
}

Stop *get_last_stop(Line *line)
{
	return line->stoplist->stops[line->stoplist->count].stop;
}
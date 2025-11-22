#include "stop.h"

void init_stoplist(StopList *stoplist)
{
	stoplist->stops = NULL;
	stoplist->count = 0;
	stoplist->capacity = 0;
}

void free_stoplist(StopList *stoplist)
{
	if (!stoplist)
		return;
	for (int i = 0; i < stoplist->count; i++)
	{
		free(stoplist->stops[i].name);
	}
	free(stoplist->stops);
	free(stoplist);
}

int process_stops(StopList *stoplist, const char *filepath)
{
	FILE *file = fopen(filepath, "r");
	if (file == NULL)
		return -2;
	char unprocessed[512];
	while (fgets(unprocessed, sizeof(unprocessed), file))
	{
		trim_line(unprocessed);
		int unprocessed_len = strlen(unprocessed) + 1;
		if (ensure_stoplist_capacity(stoplist) == -2)
		{
			fclose(file);
			return -2;
		}
		stoplist->stops[stoplist->count].name = (char *)malloc(unprocessed_len * sizeof(char));
		if (stoplist->stops[stoplist->count].name == NULL)
		{
			fclose(file);
			return -2;
		}
		strcpy_s(stoplist->stops[stoplist->count].name, unprocessed_len, unprocessed);
		stoplist->count++;
	}
	fclose(file);
	return 0;
}

int ensure_stoplist_capacity(StopList *stoplist)
{
	if (stoplist->count >= stoplist->capacity)
	{
		int newcapacity = (stoplist->capacity == 0) ? 16 : stoplist->capacity * 2;
		Stop *newstops = (Stop *)malloc(newcapacity * sizeof(Stop));
		if (newstops == NULL)
			return -2;
		for (int i = 0; i < stoplist->count; i++)
		{
			newstops[i] = stoplist->stops[i];
		}
		free(stoplist->stops);
		stoplist->stops = newstops;
		stoplist->capacity = newcapacity;
	}
	return 0;
}

void list_stops(const StopList *stoplist)
{
	if (!stoplist)
		return;
	for (int i = 0; i < stoplist->count; i++)
	{
		printf("%s\n", stoplist->stops[i].name);
	}
}

int reorder_stoplist_without_a_specific_item(StopList *stoplist, const int index)
{
	if (!stoplist)
		return -2;
	if (index < 0)
		return 0;
	for (int i = index; i < stoplist->count - 1; i++)
	{
		stoplist->stops[i] = stoplist->stops[i + 1];
	}
	stoplist->count--;
	return 0;
}

int find_stop_index(const StopList *stoplist, const char *stopname)
{
	if (!stoplist)
		return -2;
	for (int i = 0; i < stoplist->count; i++)
	{
		if (strcmp(stoplist->stops[i].name, stopname) == 0)
		{
			return i;
		}
	}
	return -1;
}

int create_stop(StopList *stoplist, const char *stopname)
{
	if (!stoplist)
		return -2;
	int stopindex = find_stop_index(stoplist, stopname);
	if (stopindex > -1)
		return -1;
	if (ensure_stoplist_capacity(stoplist) == -2)
		return -2;
	int stopname_len = strlen(stopname) + 1;
	stoplist->stops[stoplist->count].name = (char *)malloc(stopname_len * sizeof(char));
	if (stoplist->stops[stoplist->count].name == NULL)
		return -2;
	strcpy_s(stoplist->stops[stoplist->count].name, stopname_len, stopname);
	stoplist->count++;
	return 0;
}

int delete_stop(StopList *stoplist, const char *stopname)
{
	if (!stoplist)
		return -2;
	int stopindex = find_stop_index(stoplist, stopname);
	if (stopindex == -1)
		return -1;
	if (reorder_stoplist_without_a_specific_item(stoplist, stopindex) == -2)
		return -2;
	return 0;
}

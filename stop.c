#include "stop.h"

void init_stoplist(StopList* stoplist)
{
	stoplist->stops = NULL;
	stoplist->count = 0;
	stoplist->capacity = 0;
}

void free_stoplist(StopList* stoplist)
{
    if (!stoplist) return;
    for (int i = 0; i < stoplist->count; i++) {
        free(stoplist->stops[i].name);
    }
    free(stoplist->stops);
}

int process_stops(StopList* stoplist, char* filepath)
{
	FILE* file = fopen(filepath, "r");
	if (file == NULL) return -1;
	char unprocessed[512];
	while (fgets(unprocessed, sizeof(unprocessed), file))
	{
		unprocessed[strcspn(unprocessed, "\r\n")] = '\0';
		int unprocessed_len = strlen(unprocessed) + 1;
		if (ensure_stoplist_capacity(stoplist) != 0)
		{
			fclose(file);
			return -1;
		}
		stoplist->stops[stoplist->count].name = (char*)malloc(unprocessed_len * sizeof(char));
		if (stoplist->stops[stoplist->count].name == NULL)
		{
			fclose(file);
			return -1;
		}
		strcpy_s(stoplist->stops[stoplist->count].name, unprocessed_len, unprocessed);
		stoplist->count++;
	}
	fclose(file);
	return 0;
}

int ensure_stoplist_capacity(StopList* stoplist)
{
	if (stoplist->count >= stoplist->capacity)
	{
		int newcapacity = (stoplist->capacity == 0) ? 16 : stoplist->capacity * 2;
		Stop* newstops = (Stop*)malloc(newcapacity * sizeof(Stop));
		if (newstops == NULL) return -1;
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

void list_stops(StopList* stoplist)
{
	for (int i = 0; i < stoplist->count; i++)
	{
		printf("%s\n", stoplist->stops[i].name);
	}
}

int reorder_stoplist_without_a_specific_item(StopList* stoplist, int index)
{
	if (index < 0) return 0;
	for (int i = index; i < stoplist->count - 1; i++)
	{
		stoplist->stops[i] = stoplist->stops[i + 1];
	}
	stoplist->count--;
	return 0;
}

int find_stop_index(StopList* stoplist, const char* stopname)
{
	for (int i = 0; i < stoplist->count; i++)
	{
		if (strcmp(stoplist->stops[i].name, stopname) == 0)
		{
			return i;
		}
	}
	return -1;
}

int create_stop(StopList* stoplist, const char* stopname)
{
	int stopindex = find_stop_index(stoplist, stopname);
	if (stopindex != -1) return -2;
	if (ensure_stoplist_capacity(stoplist) != 0) return -1;
	int stopname_len = strlen(stopname) + 1;
	stoplist->stops[stoplist->count].name = (char*)malloc(stopname_len * sizeof(char));
	if (stoplist->stops[stoplist->count].name == NULL) return -1;
	strcpy_s(stoplist->stops[stoplist->count].name, stopname_len, stopname);
	stoplist->count++;
	return 0;
}

int delete_stop(StopList* stoplist, const char* stopname)
{
	int stopindex = find_stop_index(stoplist, stopname);
	if (stopindex == -1) return -2;
	if (reorder_stoplist_without_a_specific_item(stoplist, stopindex) == -1) return -1;
	return 0;
}

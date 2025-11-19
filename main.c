#include "menu.h"

int main()
{
	StopList *stoplist = (StopList *)malloc(sizeof(StopList));
	LineList *linelist = (LineList *)malloc(sizeof(LineList));
	ScheduleList *schedulelist = (ScheduleList *)malloc(sizeof(ScheduleList));

	init_stoplist(stoplist);
	init_linelist(linelist);
	init_schedulelist(schedulelist);

	process_stops(stoplist, "megallok.txt");
	process_lines(linelist, stoplist, "jaratok.txt");
	process_schedules(schedulelist, "menetrendek.txt");

	mainmenu(stoplist, linelist, schedulelist);

	free_stoplist(stoplist);
	free_linelist(linelist);
	free_schedulelist(schedulelist);
	return 0;
}
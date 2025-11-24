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
	process_schedules(schedulelist, linelist, "menetrendek.txt");

	mainmenu(stoplist, linelist, schedulelist);

	printf("Szeretne menteni a valtoztatasokat? (i/n)\n");
	char confirm = read_char_from_stdin();
	if (confirm == 'i' || confirm == 'I')
	{
		write_stops_to_file(stoplist, "megallok.txt");
		write_lines_to_file(linelist, "jaratok.txt");
		write_schedules_to_file(schedulelist, "menetrendek.txt");
		printf("Sikeres mentes.\n.");
	}
	else
	{
		printf("Nem tortent mentes.\n");
	}

	free_stoplist(stoplist);
	free_linelist(linelist);
	free_schedulelist(schedulelist);
	return 0;
}
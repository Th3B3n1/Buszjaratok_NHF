#include "menu.h"

void submenu_1(StopList *stoplist, LineList *linelist, int num)
{
	switch (num)
	{
	case 1:
		printf("Adja meg a megallo nevet: \n");
		char *stopname_to_create = read_string_from_stdin();
		int creation_code = create_stop(stoplist, stopname_to_create);
		if (creation_code > -1)
		{
			printf("Sikeres megallo letrehozas.\n");
		}
		else if (creation_code == -1)
		{
			printf("Sikertelen megallo letrehozas. Ez a megallo mar letezik.\n");
		}
		else
		{
			printf("Sikertelen megallo letrehozas.\n");
		}
		printf("\n%s", stopname_to_create);
		break;
	case 2:
		printf("\nA megallok listaja:\n");
		list_stops(stoplist);
		printf("-------------------\n");
		break;
	case 3:
		printf("Adja meg a torlendo megallo nevet: \n");
		char *stopname_to_delete = read_string_from_stdin();
		if (find_stop_index_in_linelist(linelist, stopname_to_delete) > -1)
		{
			printf("A megallo szerepel egy vagy tobb jaratban.\nBiztosan torli? (i/n)\n");
			char confirm = read_char_from_stdin();
			if (confirm != 'i' && confirm != 'I')
			{
				break;
			}
		}
		int deletion_code = delete_stop(stoplist, stopname_to_delete);
		if (deletion_code > -1)
		{
			printf("Sikeres megallo torles.\n");
		}
		else if (deletion_code == -1)
		{
			printf("Sikertelen megallo torles. Ilyen megallo nem letezik.\n");
		}
		else
		{
			printf("Sikertelen megallo torles.\n");
		}
		break;
	default:
		break;
	}
}

void submenu_2(StopList *stoplist, LineList *linelist, int num)
{
	switch (num)
	{
	case 1:
		Line line_to_create = {0, 0, NULL};
		printf("Adja meg a jarat szamat: \n");
		line_to_create.line_num = read_positive_number_from_stdin();
		printf("Adja meg a jarat verzioszamjat: \n");
		line_to_create.version = read_positive_number_from_stdin();
		if (find_line_index(linelist, &line_to_create) > -1)
		{
			printf("Mar letezik ilyen jarat ezzel a verzioval.\n");
			break;
		}
		line_to_create.stoplist = (LineStopList *)malloc(sizeof(LineStopList));
		init_linestoplist(line_to_create.stoplist);
		while (1)
		{
			printf("Adja meg a megallo nevet (befejezeshez 0-at irjon be): \n");
			char *stopname = read_string_from_stdin();
			if (strcmp(stopname, "0") == 0)
				break;
			int stopindex = find_stop_index(stoplist, stopname);
			if (stopindex == -1)
			{
				printf("A(z) %s megallo nem talalhato az adatbazisba, hozzaadjam uj megallokent? (i/n)", stopname);
				char confirm = read_char_from_stdin();
				if (confirm != 'i' && confirm != 'I')
				{
					break;
				}
				int code = create_stop(stoplist, stopname);
				if (code > -1)
				{
					printf("Sikeres megallo letrehozas.\n");
					stopindex = find_stop_index(stoplist, stopname);
				}
				else if (code == -1)
				{
					printf("Sikertelen megallo letrehozas. Ez a megallo mar letezik.\n");
				}
				else
				{
					printf("Sikertelen megallo letrehozas.\n");
				}
			}
			printf("Adja meg az idot a terminusztol (HH:MM): \n");
			int hour = 0;
			int minute = 0;
			scanf_s("%2d:%2d", &hour, &minute, 6);
			TimeSpan time = {hour, minute, 0};
			LineStop linestop = {&stoplist->stops[stopindex], time};
			if (ensure_linestoplist_capacity(line_to_create.stoplist) == -2)
			{
				break;
			}
			line_to_create.stoplist->stops[line_to_create.stoplist->count] = linestop;
			line_to_create.stoplist->count++;
		}
		int creation_code = create_line(linelist, &line_to_create);
		if (creation_code > -1)
		{
			printf("Sikeres jarat letrehozas.\n");
		}
		else
		{
			printf("Sikertelen jarat letrehozas.\n");
		}
		break;
	case 2:
		printf("\nA jaratok listaja:\n");
		list_lines(linelist);
		printf("------------------\n");
		break;
	case 3:
		Line line_to_delete = {0, 0, NULL};
		printf("Adja meg a torlendo jarat szamat: \n");
		line_to_delete.line_num = read_positive_number_from_stdin();
		printf("Adja meg a torlendo jarat verzioszamjat: \n");
		line_to_delete.version = read_positive_number_from_stdin();
		int deletion_code = delete_line(linelist, &line_to_delete);
		if (deletion_code > -1)
		{
			printf("Sikeres jarat torles.\n");
		}
		else if (deletion_code == -1)
		{
			printf("Sikertelen jarat torles. Ilyen jarat nem letezik.\n");
		}
		else
		{
			printf("Sikertelen jarat torles.\n");
		}
		break;
	case 4:
		int line_num = 0;
		int version = 0;
		printf("Adja meg a jarat szamat: \n");
		line_num = read_positive_number_from_stdin();
		printf("Adja meg a jarat verzioszamjat: \n");
		version = read_positive_number_from_stdin();
		list_line(linelist, line_num, version);
		break;
	default:
		break;
	}
}

void submenu_3(ScheduleList *schedulelist, LineList *linelist, int num)
{
	switch (num)
	{
	case 1:
		Line line_for_creation = {0, 0, NULL};
		printf("Adja meg a jarat szamat: \n");
		line_for_creation.line_num = read_positive_number_from_stdin();
		printf("Adja meg a jarat verzioszamjat: \n");
		line_for_creation.version = read_positive_number_from_stdin();
		int line_index = find_line_index(linelist, &line_for_creation);
		if (line_index > -1)
		{
			Date date = init_date();
			printf("Adja meg az indulasi datumot az alabbi formaba:\n");
			printf("[YYYY-MM-DD-HH:MM:SS]\n");
			char *date_str = read_string_from_stdin();
			if (sscanf_s(date_str, "%4d-%2d-%2d-%2d:%2d:%2d", &date.year, &date.month, &date.day, &date.hours, &date.minutes, &date.seconds) == EOF)
			{
				printf("Nem megfelelo formatum.");
				break;
			}
			Schedule schedule = {&linelist->lines[line_index], date};
			int creation_code = create_schedule(schedulelist, &schedule);
			if (creation_code > -1)
			{
				printf("Sikeres menetrend letrehozas.\n");
			}
			else if (creation_code == -1)
			{
				printf("Sikertelen menetrend letrehozas. Ilyen menetrend mar letezik.\n");
			}
			else
			{
				printf("Sikertelen menetrend letrehozas.\n");
			}
		}
		else
		{
			printf("Nem letezik ezzel a jaratszammal es verzioval jarat.\n");
		}
		break;
	case 2:
		printf("\nA menetrendek listaja:\n");
		list_schedules(schedulelist);
		printf("----------------------\n");
		break;
	case 3:
		Line line_for_deletion = {0, 0, NULL};
		printf("Adja meg a jarat szamat: \n");
		line_for_deletion.line_num = read_positive_number_from_stdin();
		printf("Adja meg a jarat verzioszamjat: \n");
		line_for_deletion.version = read_positive_number_from_stdin();
		Date date = init_date();
		printf("Adja meg az indulasi datumot az alabbi formaba:\n");
		printf("[YYYY-MM-DD-HH:MM:SS]\n");
		char *date_str = read_string_from_stdin();
		if (sscanf_s(date_str, "%4d-%2d-%2d-%2d:%2d:%2d", &date.year, &date.month, &date.day, &date.hours, &date.minutes, &date.seconds) == EOF)
		{
			printf("Nem megfelelo formatum.\n");
			break;
		}
		Schedule schedule = {&linelist->lines[line_index], date};
		int deletion_code = delete_schedule(schedulelist, &schedule);
		if (deletion_code > -1)
		{
			printf("Sikeres jarat torles.\n");
		}
		else if (deletion_code == -1)
		{
			printf("Sikertelen jarat torles. Ilyen jarat nem letezik.\n");
		}
		else
		{
			printf("Sikertelen jarat torles.\n");
		}
		break;
	default:
		break;
	}
}

void submenu_4(ScheduleList *schedulelist, LineList *linelist)
{
	printf("Adja meg a kiindulasi megallot: \n");
	char *startstop = read_string_from_stdin();
	printf("Adja meg a cel megallot: \n");
	char *endstop = read_string_from_stdin();
	Date date = init_date();
	printf("Adja meg az indulasi datumot az alabbi formaba:\n");
	printf("[YYYY-MM-DD-HH:MM:SS]\n");
	char *date_str = read_string_from_stdin();
	if (sscanf_s(date_str, "%4d-%2d-%2d-%2d:%2d:%2d", &date.year, &date.month, &date.day, &date.hours, &date.minutes, &date.seconds) == EOF)
	{
		printf("Nem megfelelo formatum.\n");
		return;
	}
	int code = find_routes(schedulelist, linelist, startstop, endstop, &date);
	if (code == -1)
	{
		printf("Nincsen megjelenitheto utvonal.\n");
	}
}

void submenu_5()
{
}

void mainmenu(StopList *stoplist, LineList *linelist, ScheduleList *schedulelist)
{
	int n = -1;
	int nn = -1;
	while (n != 0)
	{
		printf("\n1. Megallok kezelese\n2. Jaratok kezelese\n3. Menetrendek kezelese\n4. Utvonal keresese\n5. Adatok manualis mentese\n0. Kilepes\nValasszon menupontot :");
		n = read_positive_number_from_stdin();
		switch (n)
		{
		case 1:
			printf("\n1. Uj megallo letrehozasa\n2. Megallok listazasa\n3. Megallo torlese\n0. Vissza\nValasszon menupontot :");
			nn = read_positive_number_from_stdin();
			submenu_1(stoplist, linelist, nn);
			nn = -1;
			break;
		case 2:
			printf("\n1. Uj jarat letrehozasa\n2. Jaratok listazasa\n3. Jarat torlese\n4. Jarat adatainak listazasa\n0. Vissza\nValasszon menupontot :");
			nn = read_positive_number_from_stdin();
			submenu_2(stoplist, linelist, nn);
			nn = -1;
			break;
		case 3:
			printf("\n1. Uj menetrend letrehozasa\n2. Menetrendek listazasa\n3. Menetrend torlese\n0. Vissza\nValasszon menupontot :");
			nn = read_positive_number_from_stdin();
			submenu_3(schedulelist, linelist, nn);
			nn = -1;
			break;
		case 4:
			submenu_4(schedulelist, linelist);
			break;
		case 5:
			submenu_5();
			break;
		default:
			break;
		}
	}
}
#include "menu.h"

void submenu_1(StopList *stoplist, LineList *linelist, int num)
{
	char stopname[256];
	switch (num)
	{
	case 1:
		printf("Adja meg a megallo nevet: \n");
		scanf_s("%s", stopname, 256);
		int code = create_stop(stoplist, stopname);
		if (code == 0)
		{
			printf("Sikeres megallo letrehozas.\n");
		}
		else if (code == -1)
		{
			printf("Sikertelen megallo letrehozas. Ez a megallo mar letezik.\n");
		}
		else
		{
			printf("Sikertelen megallo letrehozas.\n");
		}
		break;
	case 2:
		printf("\nA megallok listaja:\n");
		list_stops(stoplist);
		printf("-------------------\n");
		break;
	case 3:
		printf("Adja meg a torlendo megallo nevet: \n");
		scanf_s("%255s", stopname, 256);
		if (find_stop_index_in_linelist(linelist, stopname) > -1)
		{
			printf("A megallo szerepel egy vagy tobb jaratban.\nBiztosan torli? (i/n)\n");
			char confirm;
			scanf_s("%c", &confirm, 1);
			if (confirm == 'i' || confirm == 'I')
			{
				int code = delete_stop(stoplist, stopname);
				if (code == 0)
				{
					printf("Sikeres megallo torles.\n");
				}
				else
				{
					printf("Sikertelen megallo torles.\n");
				}
			}
			else
			{
				printf("Megallo torles megszakitva.\n");
				break;
			}
		}
		else
		{
			int code = delete_stop(stoplist, stopname);
			if (code == 0)
			{
				printf("Sikeres megallo torles.\n");
			}
			else if (code == -1)
			{
				printf("Sikertelen megallo torles. Ilyen megallo nem letezik.\n");
			}
			else
			{
				printf("Sikertelen megallo torles.\n");
			}
		}
		break;
	default:
		break;
	}
}

void submenu_2(StopList *stoplist, LineList *linelist, int num)
{
	int line_num = 0;
	int version = 0;
	switch (num)
	{
	case 1:
		printf("Adja meg a jarat szamat: \n");
		scanf_s("%d", &line_num);
		printf("Adja meg a jarat verzioszamjat: \n");
		scanf_s("%d", &version);
		Line line_to_create = {line_num, version, NULL};
		if (find_line_index(linelist, &line_to_create) > -1)
		{
			printf("Mar letezik ilyen jarat ezzel a verzioval.\n");
			break;
		}
		char stopname[256] = "";
		line_to_create.stoplist = (LineStopList *)malloc(sizeof(LineStopList));
		init_linestoplist(line_to_create.stoplist);
		while (1)
		{
			printf("Adja meg a megallo nevet (befejezeshez 0-at irjon be): \n");
			scanf_s("%s", stopname, 256);
			if (strcmp(stopname, "0") == 0)
				break;
			int stopindex = find_stop_index(stoplist, stopname);
			if (stopindex > -1)
			{
				printf("Adja meg az idot a terminusztol (HH:MM): \n");
				char time_str[5 + 1];
				scanf_s("%5s", time_str, 6);
				char *hour_str = strtok(time_str, ":");
				char *minute_str = strtok(NULL, ":");
				TimeSpan time = {(*hour_str - '0'), (*minute_str - '0'), 0};
				LineStop linestop = {&stoplist->stops[stopindex], time};
				ensure_linestoplist_capacity(line_to_create.stoplist);
				line_to_create.stoplist->stops[line_to_create.stoplist->count] = linestop;
				line_to_create.stoplist->count++;
			}
			else
			{
				printf("Nincs ilyen megallo. Eloszor hozza kell adnia a megallot.\n");
			}
		}
		int creation_code = create_line(linelist, &line_to_create);
		if (creation_code == 0)
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
		printf("Adja meg a torlendo jarat szamat: \n");
		scanf_s("%d", &line_num);
		printf("Adja meg a torlendo jarat verzioszamjat: \n");
		scanf_s("%d", &version);
		Line line_to_delete = {line_num, version, NULL};
		int deletion_code = delete_line(linelist, &line_to_delete);
		if (deletion_code == 0)
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
		printf("Adja meg a jarat szamat: \n");
		scanf_s("%d", &line_num);
		printf("Adja meg a jarat verzioszamjat: \n");
		scanf_s("%d", &version);
		list_line(linelist, line_num, version);
		break;
	default:
		break;
	}
}

void submenu_3(ScheduleList *schedulelist, int num)
{
	switch (num)
	{
	case 1:

		break;
	case 2:
		printf("\nA menetrendek listaja:\n");
		list_schedules(schedulelist);
		printf("----------------------\n");
		break;
	case 3:

		break;
	case 4:

		break;
	default:
		break;
	}
}

void submenu_4(int num)
{
	switch (num)
	{
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	default:
		break;
	}
}

void mainmenu(StopList *stoplist, LineList *linelist, ScheduleList *schedulelist)
{
	int n = -1;
	int nn = -1;
	while (n != 0)
	{
		printf("\n1. Megallok kezelese\n2. Jaratok kezelese\n3. Menetrendek kezelese\n4. Utvonal keresese\n5. Adatok manualis mentese\n0. Kilepes\nValasszon menupontot :");
		scanf_s("%d", &n);
		switch (n)
		{
		case 1:
			printf("\n1. Uj megallo letrehozasa\n2. Megallok listazasa\n3. Megallo torlese\n0. Vissza\nValasszon menupontot :");
			scanf_s("%d", &nn);
			submenu_1(stoplist, linelist, nn);
			nn = -1;
			break;
		case 2:
			printf("\n1. Uj jarat letrehozasa\n2. Jaratok listazasa\n3. Jarat torlese\n4. Jarat adatainak listazasa\n0. Vissza\nValasszon menupontot :");
			scanf_s("%d", &nn);
			submenu_2(stoplist, linelist, nn);
			nn = -1;
			break;
		case 3:
			printf("\n1. Uj menetrend letrehozasa\n2. Menetrendek listazasa\n3. Megallo torlese\n0. Vissza\nValasszon menupontot :");
			scanf_s("%d", &nn);
			submenu_3(schedulelist, nn);
			nn = -1;
			break;
		case 4:
			printf("\n1. Uj menetrend letrehozasa\n2. Menetrendek listazasa\n3. Menetrend torlese\n0. Vissza\nValasszon menupontot :");
			scanf_s("%d", &nn);
			submenu_4(nn);
			nn = -1;
			break;
		case 5:

			break;
		default:
			n = 0;
			break;
		}
	}
}
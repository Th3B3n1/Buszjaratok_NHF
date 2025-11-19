#include "menu.h"

void submenu_1(StopList* stoplist, LineList* linelist, int num)
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
			else if (code == -2)
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
			if (find_stop_index_in_linelist(linelist, stopname) != -1)
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
					else if (code == -2)
					{
						printf("Sikertelen megallo torles. Ilyen megallo nem letezik.\n");
					}
					else
					{
						printf("Sikertelen megallo torles.\n");
					}
				}
				else {
					printf("Megallo torles megszakitva.\n");
					break;
				}
			}
			else {
				int code = delete_stop(stoplist, stopname);
				if (code == 0)
				{
					printf("Sikeres megallo torles.\n");
				}
				else if (code == -2)
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

void submenu_2(StopList* stoplist, LineList* linelist, int num)
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
			Line line = { line_num, version, NULL };
			
			char stopname[256] = "0";
			while (strcmp(stopname, "0") != 0)
			{
				printf("Adja meg a megallo nevet (kilepeshez 0-at irjon be): \n");
				scanf_s("%s", stopname, 256);
				int stopindex = find_stop_index(stoplist, stopname);
				if (stopindex == -1)
				{
					printf("Nincs ilyen megallo. Eloszor hozza kell adnia a megallot.\n");
				}
			}
			break;
		case 2:
			printf("\nA jaratok listaja:\n");
			list_lines(linelist);
			printf("------------------\n");
			break;
		case 3:

			break;
		case 4:

			break;
		default:
			break;
	}
}

void submenu_3(ScheduleList* schedulelist, int num)
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

void mainmenu(StopList* stoplist, LineList* linelist, ScheduleList* schedulelist)
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
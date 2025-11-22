#include "utils.h"

Date init_date()
{
    Date date = {0, 0, 0, {0, 0, 0}};
    return date;
}

int compare_dates(const Date *a, const Date *b)
{
    if (a->year != b->year)
        return a->year < b->year ? -1 : 1;
    if (a->month != b->month)
        return a->month < b->month ? -1 : 1;
    if (a->day != b->day)
        return a->day < b->day ? -1 : 1;
    if (a->hours != b->hours)
        return a->hours < b->hours ? -1 : 1;
    if (a->minutes != b->minutes)
        return a->minutes < b->minutes ? -1 : 1;
    if (a->seconds != b->seconds)
        return a->seconds < b->seconds ? -1 : 1;
    return 0;
}

void print_date(const Date *date)
{
    printf("%4d-%2d-%2d-%2d:%2d:%2d", date->year, date->month, date->day, date->hours, date->minutes, date->seconds);
}

int read_positive_number_from_stdin()
{
    int value_input = 0;
    int ch = getchar();
    if (ch < 0 || ch == '\n')
        return -1;
    do
    {
        if (ch >= '0' && ch <= '9' && value_input <= 99999999)
            value_input = value_input * 10 + (ch - '0');
        else
            value_input = 0;
        ch = getchar();
    } while (ch >= 0 && ch != '\n');
    return value_input;
}

char read_char_from_stdin()
{
    char char_input = '\0';
    char ch = (char)getchar();
    if (ch == '\n' || ch == '\0')
        return '\0';
    char_input = ch;
    return char_input;
}

void trim_line(char *s)
{
    if (!s)
        return;
    s[strcspn(s, "\r\n")] = '\0';
}

char *read_string_from_stdin()
{
    String *first = NULL;
    String *last = NULL;
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        String *next = (String *)malloc(sizeof(String));
        if (!next)
        {
            while (first)
            {
                String *tmp = first;
                first = tmp->next;
                free(tmp);
            }
            return NULL;
        }
        next->c = (char)c;
        next->next = NULL;
        if (!first)
            first = next;
        else
            last->next = next;
        last = next;
    }

    if (!first)
    {
        return NULL;
    }

    int list_len;
    for (String *current = first; current != NULL; current = current->next)
        list_len++;

    char *str = (char *)malloc(list_len * sizeof(char));
    if (!str)
        return NULL;

    int str_counter = 0;
    for (String *current = first; current != NULL; current = current->next)
    {
        str[str_counter++] = current->c;
    };
    str[str_counter] = '\0';

    while (first)
    {
        String *tmp = first;
        first = tmp->next;
        free(tmp);
    }

    return str;
}
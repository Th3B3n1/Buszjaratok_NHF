#include "utils.h"

Date init_date()
{
    Date date = {0, 0, 0, {0, 0, 0}};
    return date;
}

int compare_dates(const Date *a, const Date *b)
{
    if (a->years != b->years)
        return a->years < b->years ? -1 : 1;
    if (a->months != b->months)
        return a->months < b->months ? -1 : 1;
    if (a->days != b->days)
        return a->days < b->days ? -1 : 1;
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
    printf("%4d-%2d-%2d %2d:%2d:%2d", date->years, date->months, date->days, date->hours, date->minutes, date->seconds);
}

void add_time_to_timespan(TimeSpan *time, int hours, int minutes, int seconds)
{
    time->seconds += seconds;
    time->minutes += minutes + time->seconds / 60;
    time->seconds %= 60;

    time->hours += hours + time->minutes / 60;
    time->minutes %= 60;

    time->hours %= 24;
}

void add_time_to_date(Date *date, int years, int months, int days, int hours, int minutes, int seconds)
{
    struct tm t = {0};
    t.tm_year = date->years - 1900;
    t.tm_mon = date->months - 1;
    t.tm_mday = date->days;
    t.tm_hour = date->hours;
    t.tm_min = date->minutes;
    t.tm_sec = date->seconds;

    t.tm_year += years;
    t.tm_mon += months;
    t.tm_mday += days;
    t.tm_hour += hours;
    t.tm_min += minutes;
    t.tm_sec += seconds;

    time_t normalized = mktime(&t);

    if (normalized == (time_t)-1)
        return;

    date->years = t.tm_year + 1900;
    date->months = t.tm_mon + 1;
    date->days = t.tm_mday;
    date->hours = t.tm_hour;
    date->minutes = t.tm_min;
    date->seconds = t.tm_sec;
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

    char *str = (char *)malloc((list_len + 1) * sizeof(char));
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
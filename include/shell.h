#ifndef _SHELL_H
#define _SHELL_H

#define SHELL_BUF_SIZE 100
extern char SHELL_BUF[SHELL_BUF_SIZE];

#define SET_TIME_CMD "setTime"
#define SET_DATE_CMD "setDate"
#define GET_TIME_CMD "getTime"
#define GET_DATE_CMD "getDate"

extern const int MAX_DAYS[12];
enum MONTHS
{
    JANUARY,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};

void shellIrqHandler();
void shellDispatchCommand();
void shellSetTime(char* time);
void shellSetDate(char* date);
void shellGetTime();
void shellGetDate();
int validateDate(int year, int month, int day);

#endif
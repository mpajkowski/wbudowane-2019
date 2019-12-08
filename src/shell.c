#include "shell.h"
#include "rtc.h"
#include "serial.h"
#include "string.h"
#include "trace.h"

char SHELL_BUF[SHELL_BUF_SIZE] = {};
const int MAX_DAYS[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

void shellIrqHandler()
{
    static char ch;
    static char* cursor = SHELL_BUF;
    static int carretPos;

    if (LL_USART_IsActiveFlag_RXNE(SERIAL_UART)) {
        if (carretPos < SHELL_BUF_SIZE - 3) {
            // fetch char from UART
            ch = LL_USART_ReceiveData8(SERIAL_UART);

            // echo back last typed char
            serialPutc(ch);

            // fetched backspace - erase last char, move the cursor back;
            if (ch == '\b') {
                *cursor = '\0';
                cursor--;
                carretPos--;

                // fetched '=' - execute the command, reset cursor state;
            } else if (ch == '=') {
                *cursor = '\0';
                shellDispatchCommand();

                cursor = SHELL_BUF;
                carretPos = 0;

                // update the cursor and carret otherwise
            } else {
                *cursor = ch;
                cursor++;
                carretPos++;
            }
        }
    }
}

void shellDispatchCommand()
{
    char cmd[10];
    char args[10];

    if (sscanf(SHELL_BUF, "%s %s", cmd, args) > 0) {
        TRACE_INFO("Command: cmd=%s, args=%s", &cmd, &args);

        if (strstr(SHELL_BUF, SET_TIME_CMD)) {
            shellSetTime(args);
        } else if (strstr(SHELL_BUF, SET_DATE_CMD)) {
            shellSetDate(args);
        } else if (strstr(SHELL_BUF, GET_TIME_CMD)) {
            shellGetTime();
        } else if (strstr(SHELL_BUF, GET_DATE_CMD)) {
            shellGetDate();
        } else {
            TRACE_WARNING("Command %s not recognized", cmd);
        }
    } else {
        TRACE_WARNING("Wrong command format.");
    }
}

void shellSetTime(char* time)
{
    int hour = 0;
    int min = 0;

    if (sscanf(time, "%2d,%2d", &hour, &min) > 0) {
        if (hour >= 0 && hour < 60 && min >= 0 && min < 60) {
            setTime(hour, min, 0);
            TRACE_INFO("Time set to %d:%d", hour, min);
        } else {
            TRACE_WARNING("Invalid input arguments. Use valid ranges.");
        }
    } else {
        TRACE_WARNING("Failed to set time. Use HOUR,MINUTE format.");
    }
}

void shellSetDate(char* date)
{
    int year = 0;
    int month = 0;
    int day = 0;
    if (sscanf(date, "%4d,%2d,%2d", &year, &month, &day) > 0) {
        if (validateDate(year, month, day)) {
            setDate(0, day, month, year % 2000);
            TRACE_INFO("Date set to %d-%d-%d", year, month, day);
        } else {
            TRACE_WARNING("Invalid input arguments. Use valid ranges.");
        }
    } else {
        TRACE_WARNING("Failed to set date. Use YYYY,MM,DD format.");
    }
}

int validateDate(int year, int month, int day)
{
    int result = 0;
    int isLeapYear = (year % 4 == 0) && (year % 100 != 0);

    if (year >= 2019 && year <= 2099 && month >= 1 && month <= 12 && day >= 1 &&
        day <= MAX_DAYS[month - 1]) {
        result = 1;

        if (month == FEBRUARY) {
            int maxDaysLeap = MAX_DAYS[FEBRUARY];
            int maxDays = isLeapYear ? maxDaysLeap : maxDaysLeap - 1;

            if (day > maxDays) {
                result = 0;
            }
        }
    }

    return result;
}

void shellGetTime()
{
    TRACE_INFO("Time: %s", getTime());
}

void shellGetDate()
{
    TRACE_INFO("Date: %s", getDate());
}
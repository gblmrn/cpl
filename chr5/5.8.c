/*

There is no error checking in day_of_year or month_day.
Remedy this defect.

 */

#include <stdio.h>

static char daytap[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);

int main(int argc, char **argv)
{
  int dayYear = day_of_year(1985, 2, 15); // 31 + 15 = 46
  printf("day_of_year: %d\n", dayYear);
  
  int day, month; // used for month_day
  month_day(1985, 46, &day, &month); // day = 15, month = 2
  printf("day = %d, month = %d\n", day, month);

  return 0;
}

// day_of_year: set day of year from month & day
int day_of_year(int year, int month, int day)
{
  int i, leap;

  if (year < 1752 || month < 1 || month > 12 || day < 1)
    return -1; // error checking

  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
  for (i = 1; i < month; ++i)
    day += daytap[leap][i];
  return day;
}

// month_day: set month, day from day of year
int month_day(int year, int yearday, int *pmonth, int *pday)
{
  int i, leap;

  if (year < 1752 || yearday < 1)
    return -1; //error checking

  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
  for (i = 1; daytap[leap][i] < yearday; ++i)
    yearday -= daytap[leap][i];
  *pmonth = i;
  *pday = yearday;

  return 0;
}

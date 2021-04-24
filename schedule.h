#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "STRUCT.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

int CreateSchedule(int date);
int*** CreateMonthSchedule(Graph* pgraph);

#endif
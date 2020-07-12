

/* 
 * File: scheduler.h
 * Author: Ahmed Hassan
 * Created : July 7, 2020 
 */

#ifndef SCHEDULER_H
#define	SCHEDULER_H

#define SCH_MAX_TASKS 3

typedef struct data {
    /*Pointer to the task (must be a 'void (void)' function)*/
    void (*taskFunction)(void);
    /*Delay (ticks) until the function will (next) be run*/
    u64 delay;
    /*Interval (ticks) between subsequent runs.*/
    u64 period;
    /*Incremented (by scheduler) when task is due to execute*/
    u64 runMe;
} sTask;

void sch_vid_dispatch_tasks(void);

u8 sch_u8_add_task(void ( * pFunction)(),
        const u64 DELAY,
        const u64 PERIOD);
void timerInit(void);
void sch_vid_init(void);
u8 sch_vid_delete_task(u8 index);
void SCH_Report_Status(void);
void SCH_Go_To_Sleep(void);
void sch_update(void);

#endif


#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "utask_struct.h"
#include <stdint.h>
#include <pthread.h>

/*结构体: 定时器线程共享内存
 *[注意] 这个结构体只能在堆或者全局变量中使用, 不能用作临时变量*/
typedef struct {
    uint64_t task_id;           // 到期的任务id
    uint32_t signal;            // 发送的信号, 见下面以SIG开头的宏
    uint32_t occupied_thread;   // 占用这个结构体的线程ID(请自行设置), 不是自己的时会被锁住
}TimerSharedMemory;
/* 线程间的信号 */
#define _SIG_FREE       0
#define _SIG_OCCUPIED   1
#define _SIG_DONE       2

/*结构体: 定时器参数*/
typedef struct {
    TaskList *tasklist;     // 任务指针
    TimerSharedMemory *shm; // 共享内存指针
}TimerArgument;

/*函数: 定时器线程启动函数
 *参数: 任务清单*/

/*函数: 定时器线程执行函数
 *参数: 参数结构体*/
void utask_timer(TimerArgument timer_argument);

#ifdef __cplusplus
}
#endif
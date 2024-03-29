/*  Copyright (c) 2022-2023 by Imagine Studio Group.
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/* FILE: utask_struct.h
 * ENCODING: UTF-8
 * This Header contains the definition of the basic task structure,
 * together with declarations of its operations. 
 * REMEMBER the implemention of the operations are in 
 * `../udata/utask_struct.c`. */
// 注: 我(Medi)用英文主要是防止在某些编辑器乱码.
#pragma once

// 众所周知, C能用的, C++不一定都能用.
// 下面几行是跨两种语言的兼容措施.
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

enum UTask_Type {
    _STATIC = 0,    // 默认类型, 一次性的任务
    _TIME_LIMIT,    // 限时任务, 类似于考试
    _BIG_EVENT,     // 重大事件, 包含了一个小清单
};

enum UTask_DueDate_Type {
    _ONCE     = 0x0,        // 一次
    // _TWICE,              // 1 连续两次
    _CIRCULATE_WEEKLY = 0x80000000, // 最高位取1时表示每周循环, 最低7位表示一周7天
    _EVERYDAY = 0x800000FE,         // 每天
};

enum UTask_Sort_Order {
    _TIME = 0,   // 按时间排序
};

/* 对象: 任务信息 */
typedef struct
{
    int t_id;           // ID
    bool finished;      // 是否完成
    bool isNearArrive;  // 是否临近
    int ttype;          // 类型, 取值见enum UTask_Type
    char name[256];     // 任务名称
    char *desciption;   // 任务描述
    int t_duedate_type; // 指定什么时候到期, 取值见enum UTask_DueDate_Type
    int t_duedate[3];   // 到期日期(格式YY-MM-DD), 到期类型为_CIRCULATE_WEEKLY时为开始日期
    int t_duetime[3];   // 到期时间(格式hh:mm:ss)
    int time_ahead[3];  // 提前多久提醒(格式hh:mm:ss)
    void *priv_data;    // 私有数据, 根据ttype决定类型
} TaskInfo;

/* 任务链表节点 */
typedef struct node
{
    TaskInfo task;
    struct node *next;
} TaskNode;

/* 任务链表特征结构体 */
typedef struct __tasklist_f
{
    uint64_t l_id;          // 清单id
    char name[256];         // 清单名称
    char description[1024]; // 任务描述
    int64_t max_task_id;    // 所有任务id的最大值
    int32_t default_order;  // 默认排序方式, 取值参见enum UTask_Sort_Order

    /*task条目*/
    TaskNode *head;         // 任务头节点
    TaskNode *now;          // 默认状况下的当前节点
    int64_t  length;        // 清单长度
} TaskList;

/* 工具宏 */
#define tmSeconds(array_time) ((array_time)[0] * 3600 + (array_time)[1] * 60 + (array_time)[2])

/* 任务链表 */

/* 函数: 比较两段日期的大小
 * 参数: 指向两个任务节点的指针
 * 返回: n1大于n2则返回1, n1=n2则返回0, n1<n2则返回-1*/
int cmp_node_by_datetime(const TaskNode *n1, const TaskNode *n2);

/* 函数: 按id搜索任务, 返回任务在链表中的位置，同时将任务前一项的指针
 *       传给`prev_item`. 如果找不到，那么`prev_item = NULL`且函数返回`0`.
 * 参数: (传入)链表头, 任务id, (传出)找到的前一项指针
 * 返回: 记头节点为0号, 返回所求tid对应的任务在链表中的位置. 找不到时返回0.
 * 属性: Private */
int get_item_order(TaskNode *L, int tid, TaskNode **prev_item);

/* 函数: 按任务对象在链表中的位置寻找对象, 可以理解为复杂度为O(n)
 *       版的tasknode[index]数组索引.
 * 参数: 链表头, 链表索引号
 * 返回: 记链表头节点为0号, 返回index号节点的指针. */
TaskNode *goto_item(TaskNode *L, int index);

#define _UTASK_INSERT_IN_THE_END -1 // 在末尾插入
/* 函数: 插入一个任务对象
 * 参数: 任务链表头, 任务信息, 插入模式
 *      [choice=0:尾插; 1:头插; n>1:从头节点算起第n个节点后]
 * 返回: 无  */
bool utask_insert(TaskNode *L, TaskInfo tinfo, int choice);

// 答辩后重构的新函数, 与上一个不兼容
/* 函数: 在任务链表里插入一个节点, 插入的位置参见position的取值
 * 参数: 待处理的任务链表, 待插入的任务节点, 任务位置描述
 * 插入位置: -1(_UTASK_INSERT_IN_THE_END)表示附加到末尾, position
 *           为非负整数n时表示以头节点为0号时, 在第n号末尾插入
 * 返回: 是否成功, 成功返回true */
bool utask_insert_f(TaskList *tasklist, TaskInfo taskinfo, int position);

/* 函数: 更新任务特征结构体的任务节点数量
 * 参数: 指向待修改的特征结构体的指针
 * 返回: 返回正数或0表示任务特征结构体的任务节点数量, 返回-1则表示失败*/
int tasklist_length(TaskList *tasklist);

/* 函数: 删除一个节点
 * 参数: 链表头, 任务id
 * 返回: 成功(true) 失败(false) */
bool utask_delet_one_node(TaskNode *L, int id);

/* 函数: 查找一个节点并打印
 * 参数: 头节点, 任务id
 * 返回: 指向所求对象的指针 */
TaskNode *search_node_by_id(TaskNode *L, int id);

/* 函数: 根据id修改一个节点
 * 参数: 链表头, 待修改的信息, 任务id
 * 返回: 无 */
bool change_node_by_id(TaskNode *L, TaskInfo tinfo, int id);

/* 函数: 按照任务是否完成进行排序, 没有完成的排在前面
 * 参数: 任务链表特征结构体
 * 返回: 排序成功则返回0, 否则为其他值(见下面的宏定义) */
int utask_sort_by_finished(TaskList *tasklist);

/* 函数: 按时间对其排序
 * 参数: 任务链表特征结构体
 * 返回: 排序成功则返回0, 否则为其他值(见下面的宏定义) */
int utask_sort_by_time(TaskList *tasklist);

/* 函数: 按默认方式排序, 没做完的在前面, 做完的在后面, 两部分再按照时间排序
 * 参数: 任务链表特征结构体
 * 返回: 排序成功则返回0, 否则为其他值(见下面的宏定义) */
int utask_sort_by_default(TaskList *tasklist);

#define _U_WRONG_TASKLIST -1

/* 函数: 输出任务id为id的任务(没必要, Qt前端会有类似实现)
 * 参数: 头节点，要查找的id
 * 返回: TaskInfo数据结构*/
TaskInfo output_one_item(TaskNode *L, int id);

/* 函数: 输出这个链表(Debug用)
 * 参数:
 * 返回: */
void put_all(TaskNode *L);

/* 函数: 删除这个链表
 * 参数: 链表头节点
 * 返回: 无 */
bool delet_all(TaskNode **L);

// 注释模板
/* 函数:
 * 参数:
 * 返回: */

#ifdef __cplusplus
}
#endif

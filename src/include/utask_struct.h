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
    _EVERYDAY = 0x2,        // 2 每天
    _CIRCULATE_WEEKLY = 0x80000000, // 最高位取1时表示每周循环, 最低7位表示一周7天
};

enum UTask_Sort_Order {
    _TIME = 0,   // 按时间排序
};

/* 对象: 任务信息 */
typedef struct
{
    int t_id;           // ID
    bool finished;      // 是否完成
    int ttype;          // 类型, 取值见enum UTask_Type
    char name[256];     // 任务名称
    char *desciption;   // 任务描述
    int t_duedate_type; // 指定什么时候到期, 取值见enum UTask_DueDate_Type
    int t_duedate[3];   // 到期日期(格式YY-MM-DD), 到期类型为_CIRCULATE_WEEKLY时为开始日期
    int t_duetime[3];   // 到期时间(格式ss:mm:hh)seconds;minutes;hours;
    int time_ahead[3];  // 提前多久提醒(格式ss:mm:hh)
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
    int64_t  max_task_id;   // 所有任务id的最大值
    uint32_t default_order; // 默认排序方式, 取值参见enum UTask_Sort_Order

    /*task条目*/
    TaskNode *head;         // 任务头节点
    TaskNode *now;          // 默认状况下的当前节点
    uint64_t length;        // 清单长度
} TaskList;

/* 任务链表 */

/* 函数: 按任务对象在链表中的位置寻找对象, 可以理解为复杂度为O(n)
 * 版的tasknode[index]数组索引.
 * 参数: 链表头, 链表索引号
 * 返回: 记链表头节点为0号, 返回index号节点的指针. */
TaskNode *goto_item(TaskNode *L, int index);

/* 函数: 插入一个任务对象
 * 参数: 任务链表头, 任务信息, 插入模式
 *      [choice=0:尾插; 1:头插; n>1:从头节点算起第n个节点后]
 * 返回: 无  */
bool utask_insert(TaskNode *L, TaskInfo tinfo, int choice);

/* 函数: 删除一个节点
 * 参数: 链表头, 任务id
 * 返回: 成功(true) 失败(false) */
bool utask_delet_one_node(TaskNode *L, char id);

/* 函数: 查找一个节点并打印
 * 参数: 头节点, 任务id
 * 返回: 指向所求对象的指针 */
TaskNode *search_node_by_id(TaskNode *L, int id);

/* 函数: 根据id修改一个节点
 * 参数: 链表头, 待修改的信息, 任务id
 * 返回: 无 */
bool change_node_by_id(TaskNode *L, TaskInfo tinfo, int id);

/* 函数(未实现): 按时间对其排序
 * 参数: 头节点
 * 返回: void(需要修改) */
void time_sort(TaskNode *L);

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

/* 函数: 按照任务是否完成进行排序, 没有完成的排在前面(是吗?@楚楚)
 * 参数: 任务链表头节点
 * 返回: 排序成功则返回true, 否则为false */
bool finished_sort(TaskNode *head);

// 注释模板
/* 函数:
 * 参数:
 * 返回:
 */


#ifdef __cplusplus
}
#endif

/* utask_struct.c -- U.toGo任务结构体操作的实现 */
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
#include "../include/utask_struct.h"

/* 函数: 按id搜索任务, 返回任务在链表中的位置，同时将任务前一项的指针
 *       传给`prev_item`. 如果找不到，那么`prev_item = NULL`且函数返回`0`.
 * 参数: (传入)链表头, 任务id, (传出)找到的前一项指针
 * 返回: 记头节点为0号, 返回所求tid对应的任务在链表中的位置. 找不到时返回0.
 * 属性: Private */
int get_item_order(TaskNode *L, int tid, TaskNode **prev_item)
{
    TaskNode *ptr = NULL;
    int ret = 0;

    while ((L != NULL) && L->task.t_id != tid)
    {
        ptr = L;
        L = L->next;
        ret++;
    }
    if (L == NULL)
    {
        *prev_item = NULL;
        return 0;
    }

    *prev_item = ptr;
    return ret;
}

/* 函数: 按任务对象在链表中的位置寻找对象, 可以理解为复杂度为O(n)
 * 版的tasknode[index]数组索引.
 * 参数: 链表头, 链表索引号
 * 返回: 记链表头节点为0号, 返回index号节点的指针.
 * 属性: Public*/
TaskNode *goto_item(TaskNode *L, int index)
{
    TaskNode *ret = L;
    for (int i = 0; (ret != NULL) && (i < index); i++)
        ret = ret->next;

    return ret;
}

/*函数: 交换两个链表节点. 算法请按照源代码自行画图理解.
 *参数: 两个节点的指针的前一节点(the pointers point at
 *                      previous items of node a and b)
 *返回: 无*/
bool swap_two_nodes(TaskNode *a_prev, TaskNode *b_prev)
{
    // exception
    if (a_prev == NULL || b_prev == NULL)
        return false;
    else if (a_prev->next == NULL || b_prev->next == NULL)
        return false;
    else if (a_prev == b_prev)
        return true;
    else if (a_prev->next == b_prev)
    {
        TaskNode *a = a_prev->next, *b = b_prev->next;
        a_prev->next = b;
        a->next = b->next;
        b->next = a;
    }
    else if (b_prev->next == a_prev)
    {
        TaskNode *a = a_prev->next, *b = b_prev->next;
        b_prev->next = a;
        b->next = a->next;
        a->next = b;
    }
    else
    {
        TaskNode *a = a_prev->next, *a_next = a->next;
        TaskNode *b = b_prev->next, *b_next = b->next;
        // swap two nodes' "next" pointer
        a->next = b_next, b->next = a_next;
        // swap two nodes' "previous item"
        a_prev->next = b, b_prev->next = a;
    }
    return true;
}

bool utask_insert(TaskNode *L, TaskInfo tinfo, int choice) // 插入//1头插，0尾插，choice为newnode为第i个节点
{
    TaskNode *next, *newnode;
    int i = 2, u = 1;
    newnode = (TaskNode *)malloc(sizeof(TaskNode));
    if (newnode == NULL)
        return false;
    newnode->task = tinfo;
    newnode->next = NULL;
    next = L->next;
    // 头插法
    if (choice == 1)
    {
        L->next = newnode;
        newnode->next = next;
        // newnode->task.t_id = u;
        while (next != NULL)
        {
            // next->task.t_id = u+1;
            next = next->next;
            u++;
        }
    }
    else
        // 尾插法
        if (choice == 0)
        {
            if (next == NULL)
            {
                L->next = newnode;
                // newnode->task.t_id = 1;
            }
            else
            {
                while (next->next != NULL)
                    next = next->next;

                next->next = newnode;
                // newnode->task.t_id = next ->task.t_id + 1;
            }
        }
        else
        // 任意插
        {
            if (next == NULL)
            {
                return false;
            }
            while (next != NULL)
            {
                if (choice == i)
                {
                    newnode->next = next->next;
                    next->next = newnode;
                    // newnode->task.t_id = next ->task.t_id+1;
                    // u = newnode->task.t_id+1;
                    next = newnode->next;
                    while (next != NULL)
                    {
                        // next->task.t_id = u;
                        // u++;
                        next = next->next;
                    }
                    break;
                }
                else
                {
                    i++;
                    next = next->next;
                    if (next == NULL)
                    {
                        return false;
                    }
                }
            }
        }
    return true;
}

int tasklist_length(TaskList *tasklist) // 更新tasklist的长度，算法时间复杂度为O(n)
{
    if (tasklist == NULL || tasklist->head == NULL)
        return -1;

    TaskNode *ptr = tasklist->head;
    int tasklen = 0;

    while (ptr != NULL)
    {
        ptr = ptr->next;
        tasklen++;
    }
    tasklist->length = tasklen;
    return tasklen;
}

bool utask_delet_one_node(TaskNode *L, char id) // 删除一个节点
{
    TaskNode *cur = L->next, *front = L;
    L->task.t_id = 0;
    if (id <= 0)
    {
        return false;
    }
    while (cur->task.t_id != id)
    {
        front = front->next;
        cur = cur->next;
        if (cur == NULL)
        {
            return false;
        }
    }
    if (cur->next == NULL)
    {
        front->next = NULL;
        free(cur);
    }
    else
    {
        front->next = cur->next;
        free(cur);
        while (front->next != NULL)
        {
            front = front->next;
        }
    }
    return true;
}

TaskNode *search_node_by_id(TaskNode *L, int id) // 查找
{
    TaskNode *cur;
    cur = L->next;
    while (cur->task.t_id != id)
    {
        cur = cur->next;
        if (cur == NULL)
            return NULL;
    }
    return cur;
}

bool change_node_by_id(TaskNode *L, TaskInfo tinfo, int id) // 改
{
    TaskNode *cur;
    tinfo.t_id = id;
    cur = L->next;
    while (cur->task.t_id != id)
    {
        cur = cur->next;
        if (cur == NULL)
            return false;
    }
    cur->task = tinfo;
    return true;
}

int utask_sort_by_time(TaskList *tasklist)
{
    if (tasklist == NULL || tasklist->head == NULL || tasklist->head->next == NULL)
        return _U_WRONG_TASKLIST;
    // 更新任务清单的长度 -- 所有操作函数从节点转向链表特征结构体后这行会被清理掉
    int ordered_len = tasklist_length(tasklist);
    while (ordered_len > 0)
    {
        TaskNode *ptr = tasklist->head;
        for (int i = 0; i < ordered_len - 1; i++)
            if (tmSeconds(ptr->next->task.t_duetime) > tmSeconds(ptr->next->next->task.t_duetime))
                swap_two_nodes(ptr, ptr->next);
        ordered_len--;
    }
    return 0;
}

int utask_sort_by_finished(TaskList *tasklist)
{
    if (tasklist == NULL || tasklist->head == NULL || tasklist->head->next == NULL)
        return _U_WRONG_TASKLIST;
    // 更新任务清单的长度 -- 所有操作函数从节点转向链表特征结构体后这行会被清理掉
    int ordered_len = tasklist_length(tasklist);
    while (ordered_len > 0)
    {
        TaskNode *ptr = tasklist->head;
        for (int i = 0; i < ordered_len - 1; i++)
            if (ptr->next->task.finished == true && ptr->next->next->task.finished == false)
                swap_two_nodes(ptr, ptr->next);
        ordered_len--;
    }
    return 0;
}

int utask_sort_by_default(TaskList *tasklist)
{
    if (utask_sort_by_finished(tasklist) == _U_WRONG_TASKLIST)
    {
        fprintf(stderr, "ERROR message from %s(): Wrong task list, or there is a bug.\n", __func__);
        return _U_WRONG_TASKLIST;
    }

    // 获取tasklist未完成部分的长度
    TaskNode *ptr = tasklist->head->next;
    int unfinished_len = 0;
    while (ptr != NULL && ptr->task.finished == false)
    {
        unfinished_len++;
        ptr = ptr->next;
    }

    // 对已完成部分按时间排序
    while (unfinished_len > 0)
    {
        TaskNode *ptr = tasklist->head;
        for (int i = 0; i < unfinished_len - 1; i++)
            if (tmSeconds(ptr->next->task.t_duetime) > tmSeconds(ptr->next->next->task.t_duetime))
                swap_two_nodes(ptr, ptr->next);
        unfinished_len--;
    }
    return 0;
}

TaskInfo output_one_item(TaskNode *L, int id)
{
    TaskNode *info = search_node_by_id(L, id);
    if (info == NULL)
        return (TaskInfo){
            .t_id = 0,
            .finished = false,
            .ttype = _ONCE,
            .desciption = NULL,
            .priv_data = NULL,
        };
    else
        return info->task;
}

void put_all(TaskNode *L)
{
    TaskNode *p;
    p = L->next;
    while (p != NULL)
    {
        printf("%d %s %d/%d/%d %s\n", p->task.t_id, p->task.name,
               p->task.t_duetime[0], p->task.t_duetime[1], p->task.t_duetime[2],
               p->task.desciption);
        p = p->next;
    }
}

bool delet_all(TaskNode **L)
{
    TaskNode *p;
    while (*L)
    {
        if ((*L)->task.desciption != NULL)
            free((*L)->task.desciption);
        p = *L;
        *L = (*L)->next;
        free(p);
    }
    *L = NULL;
    return true;
}

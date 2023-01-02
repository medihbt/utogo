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
#include "../include/utask_io.h"

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

TaskNode *goto_node_by_id(TaskNode *head, int id, TaskNode **prev)
{
    if (head == NULL || head->next == NULL)
        return NULL;

    TaskNode *ptr = head;
    while(ptr->next->task.t_id != id && ptr->next != NULL)
        ptr = ptr->next;

    if (prev != NULL) *prev = ptr;
    return ptr->next;
}

/* 函数: 
 * 参数: 
 * 返回: n1大于n2则返回1, n1=n2则返回0, n1<n2则返回-1*/
int cmp_node_by_datetime(const TaskNode *n1, const TaskNode *n2)
{
    if (n1 == NULL || n2 == NULL)
        return 0;
    /*date*/
    for (int i = 0; i < 3; i++)
    {
        if (n1->task.t_duedate[i] > n2->task.t_duedate[i])
            return 1;
        else if (n1->task.t_duedate[i] < n2->task.t_duedate[i])
            return -1;
    }
    /*time*/
    for (int i = 0; i < 3; i++)
    {
        if (n1->task.t_duetime[i] > n2->task.t_duetime[i])
            return 1;
        else if (n1->task.t_duetime[i] < n2->task.t_duetime[i])
            return -1;
    }
    return 0;
}

int tasklist_length(TaskList *tasklist)
{
    if (tasklist == NULL || tasklist->head == NULL)
        return -1;

    int i = 0;
    for (TaskNode *ptr = tasklist->head; ptr->next != NULL; ptr = ptr->next)
        i++;
    tasklist->length = i;
    return i;
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

/* 函数: 在任务链表里插入一个节点, 插入的位置参见position的取值
 * 参数: 待处理的任务链表, 待插入的任务节点, 任务位置描述
 * 插入位置: -1(_UTASK_INSERT_IN_THE_END)表示附加到末尾, position
 *           为非负整数n时表示以头节点为0号时, 在第n号末尾插入
 * 返回: 是否成功, 成功返回true */
bool utask_insert_f(TaskList *tasklist, TaskInfo taskinfo, int position)
{
    if (tasklist == NULL || tasklist->head == NULL)
        return false;
    else if (position < -1 || position > tasklist->length)
        return false;

    TaskNode *p_ins = (TaskNode *)malloc(sizeof(TaskNode));
    (*p_ins) = (TaskNode){
        .task = taskinfo,
        .next = NULL,
    };
    // allocate new id
    p_ins->task.t_id = ++(tasklist->max_task_id);

    /* 尾部插入 */
    if (position == _UTASK_INSERT_IN_THE_END)
    {
        TaskNode *ptr = tasklist->head;
        while (ptr->next != NULL)
            ptr = ptr->next;
        ptr->next = p_ins;
    }
    else /* 按序插入 */
    {
        TaskNode *ptr = goto_item(tasklist->head, position);
        p_ins->next = ptr->next;
        ptr->next = p_ins;
    }

    tasklist->length++;
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

bool utask_delet_one_node_f(TaskList *tasklist, int id)
{
    if (tasklist == NULL)
        return false;

    TaskNode *cur, *prev;
    cur = goto_node_by_id(tasklist->head, id, &prev);
    if (cur == NULL)
        return false;
    
    prev->next = cur->next;
    free(cur);
    tasklist->length--;
    return true;
}

inline TaskNode *search_node_by_id_f(const TaskList *tasklist, int id)
{
    if (tasklist == NULL)
        return NULL;
    else
        return goto_node_by_id(tasklist->head, id, NULL);
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

int utask_sort_by_finished(TaskList *tasklist)
{
    if (tasklist == NULL || tasklist->head == NULL || tasklist->head->next == NULL)
        return _U_WRONG_TASKLIST;
    // 更新任务清单的长度 -- 所有操作函数从节点转向链表特征结构体后这行会被清理掉
    int ordered_len = tasklist_length(tasklist);
    while (ordered_len > 0)
    {
        TaskNode *ptr = tasklist->head;
        for (int i = 0; i < ordered_len - 2; i++)
        {
            if (ptr->next->task.finished == true && ptr->next->next->task.finished == false)
                swap_two_nodes(ptr, ptr->next);

            ptr = ptr->next;
        }
        ordered_len--;
    }
    return 0;
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
        {
            if (cmp_node_by_datetime(ptr->next, ptr->next->next) > 0)
                swap_two_nodes(ptr, ptr->next);
            ptr = ptr->next;
        }
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

bool utask_delet_one_node(TaskNode *L, int id) // 删除一个节点
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

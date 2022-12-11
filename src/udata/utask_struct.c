#include "../include/utask_struct.h"

/*Medi注: 本次新增的两个函数时间复杂度都为O(n), 省着点用!!!*/

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
        newnode->task.t_id = u;
        while (next != NULL)
        {
            next->task.t_id = u + 1;
            next = next->next;
            u++;
        }
    }
    else if (choice == 0) // 尾插法
    {
        if (next == NULL)
        {
            L->next = newnode;
            newnode->task.t_id = 1;
        }
        else
        {
            while (next->next != NULL)
            {
                next = next->next;
            }
            next->next = newnode;
            newnode->task.t_id = next->task.t_id + 1;
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
                newnode->task.t_id = next->task.t_id + 1;
                u = newnode->task.t_id + 1;
                next = newnode->next;
                while (next != NULL)
                {
                    next->task.t_id = u;
                    u++;
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

bool utask_delet_one_node(TaskNode *L, char id) // 删除一个节点
{
    TaskNode *cur, *front;
    int u;
    front = L;
    cur = L->next;
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
        u = front->task.t_id + 1;
        while (front->next != NULL)
        {
            front = front->next;
            front->task.t_id = u;
            u++;
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
        {

            return false;
        }
    }
    cur->task = tinfo;
    return true;
}

void time_sort(TaskNode *L); // 按时间对其排序

TaskInfo output_one_item(TaskNode *L, int id) // 显示第t_id为id的数
{
    TaskNode *cur;
    TaskInfo inf;
    int i = 0;
    cur = L->next;
    while (cur->task.t_id != id)
    {
        cur = cur->next;
        if (!cur)
            return (TaskInfo){
                .t_id = 0,
                .finished = false,
                .ttype = _ONCE,
                .desciption = NULL,
                .priv_data = NULL,
            };
    }
    inf = cur->task;
    return inf;
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
        p = *L;
        *L = (*L)->next;
        free(p);
    }
    *L = NULL;
    return true;
}

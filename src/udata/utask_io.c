/*  Copyright (c) 2022-2023 Imagine Studio PBLF Group.
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
/*utask_io.c -- Main Part of U.toGo Configuration Analyzing Module*/
#include "../include/utask_io.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UTASK_IO_DEBUG_MAIN 0

const char *TASKLIST_DEFAULT_ORDER[1] = {
    "time",
};

const char *TASKLIST_TYPES[3] = {
    "static",
    "timelimit",
    "bigevent",
};


TaskList data_tree_to_tasklist(UniListObject *data_tree)
{
    /*初始化返回节点*/
    TaskList tasklist = {
        .head = (TaskNode *)malloc(sizeof(TaskNode)),
        .now = tasklist.head,
        .length = 0,
        .max_task_id = 0,
        .default_order = 0,
    };
    UListNode *node_guide = ulist_change_current_node(data_tree, "#/", 0);
    if (node_guide == NULL)
        return tasklist;

    /* 初始化元数据 */
    *(tasklist.head) = (TaskNode){
        .task = (TaskInfo){
            .name = {0},
            .desciption = NULL,
            .priv_data = NULL,
        },
    };

    /* 通过遍历树节点给tasklist的属性赋值 */
    // tasklist
    if ((node_guide = ulist_change_current_node(data_tree, "list", 0)) == NULL)
    {
        tasklist.l_id = 0;
        tasklist.length = 0;
        tasklist.max_task_id = 0;
        memcpy(tasklist.name, "Untitled List", 14);
        return tasklist;
    }

    // [tasklist.l_id]  int(文件) -> int(结构体)
    if ((node_guide = ulist_change_current_node(data_tree, "l_id", 0)) == NULL) // 失败时data_tree的now节点不会自动跳转
        tasklist.l_id = 0;
    else
    {
        if (node_guide->line.value == NULL || sscanf(node_guide->line.value, "%ld", &tasklist.l_id) < 1)
            tasklist.l_id = 0;
        ulist_change_current_node(data_tree, "#..", 0); // 返回上一级节点
    }
    // [tasklist.name]  string -> char[256]
    if ((node_guide = ulist_change_current_node(data_tree, "name", 0)) == NULL)
        memcpy(tasklist.name, "Untitled", 9);
    else
    {
        if (node_guide->line.value == NULL)
            memcpy(tasklist.name, "Untitled", 9);
        else
            strncpy(tasklist.name, node_guide->line.value, 256);
        ulist_change_current_node(data_tree, "#..", 0);
    }
    // [tasklist.description]   string -> char[1024]
    if ((node_guide = ulist_change_current_node(data_tree, "description", 0)) == NULL)
        memcpy(tasklist.description, "\0\0\0", 4);
    else
    {
        if (node_guide->line.value == NULL)
            memcpy(tasklist.description, "\0\0\0", 4);
        else
            strncpy(tasklist.description, node_guide->line.value, 1024);
        ulist_change_current_node(data_tree, "#..", 0);
    }
    // [tasklist.default_order] string -> int
    if ((node_guide = ulist_change_current_node(data_tree, "default_order", 0)) == NULL)
        tasklist.default_order = _TIME;
    else
    {
        if (node_guide->line.value == NULL)
            tasklist.default_order = _TIME;
        else if (!strcmp(node_guide->line.value, "time"))
            tasklist.default_order = _TIME;
        else
            tasklist.default_order = 0x0;
        ulist_change_current_node(data_tree, "#..", 0);
    }
    // [tasklist.task]  (子链表) array -> TaskNode *heads
    int task_count = 0;
    do
    {
        // /*查看是否有task节点*/
        // [tasklist.task[tasks_count]]
        if (ulist_change_current_node(data_tree, "task", task_count) == NULL)
            break;
        // else if success
        // 新建一个任务接收读取的内容
        tasklist.now->next = (TaskNode *)malloc(sizeof(TaskNode));
        *(tasklist.now->next) = (TaskNode){
            .task = (TaskInfo){
                .priv_data = NULL,
                .desciption = (char *)malloc(MAX_DESCRIPTION_SIZE),
            },
            .next = NULL,
        };

        // tasklist.task[tasks_count].t_id      int -> int
        if ((node_guide = ulist_change_current_node(data_tree, "t_id", 0)) == NULL)
            tasklist.now->next->task.t_id = -1;
        else
        {
            if (node_guide->line.value == NULL)
                tasklist.now->next->task.t_id = -1;
            else if (sscanf(node_guide->line.value, "%d", &tasklist.now->next->task.t_id) < 1)
                tasklist.now->next->task.t_id = -1;
            ulist_change_current_node(data_tree, "#..", 0);
        }
        tasklist.max_task_id = tasklist.max_task_id > tasklist.now->next->task.t_id ? tasklist.max_task_id : tasklist.now->next->task.t_id;

        // tasklist.task[tasks_count].finished  string -> int
        if ((node_guide = ulist_change_current_node(data_tree, "finished", 0)) == NULL)
            tasklist.now->next->task.finished = false;
        else
        {
            if (node_guide->line.value == NULL)
                tasklist.now->next->task.finished = false;
            else if ((!strncmp(node_guide->line.value, "yes", 3)) || (!strncmp(node_guide->line.value, "YES", 3)))
                tasklist.now->next->task.finished = true;
            else
                tasklist.now->next->task.finished = false;
            ulist_change_current_node(data_tree, "#..", 0);
        }

        // tasklist.task[tasks_count].type      string -> int
        if ((node_guide = ulist_change_current_node(data_tree, "type", 0)) == NULL)
            tasklist.now->next->task.ttype = _STATIC;
        else
        {
            if (node_guide->line.value == NULL)
                tasklist.now->next->task.ttype = _STATIC;
            if (!strncmp(node_guide->line.value, "static", 4))          // 普通任务
                tasklist.now->next->task.ttype = _STATIC;
            else if (!strncmp(node_guide->line.value, "timelimit", 4))  // 限时任务
                tasklist.now->next->task.ttype = _TIME_LIMIT;
            else if (!strncmp(node_guide->line.value, "bigevent", 4))   // 重大事件
                tasklist.now->next->task.ttype = _BIG_EVENT;
            ulist_change_current_node(data_tree, "#..", 0);
        }
        // tasklist.task[tasks_count].name      string -> char[256]
        if ((node_guide = ulist_change_current_node(data_tree, "name", 0)) == NULL)
            memcpy(tasklist.now->next->task.name, "Untitled", 9);
        else
        {
            if (node_guide->line.value == NULL)
                memcpy(tasklist.now->next->task.name, "Untitled", 9);
            else
                strncpy(tasklist.now->next->task.name, node_guide->line.value, 256);
            ulist_change_current_node(data_tree, "#..", 0);
        }
        // tasklist.task[tasks_count].description       string -> char *
        if ((node_guide = ulist_change_current_node(data_tree, "description", 0)) == NULL)
            tasklist.now->next->task.desciption[0] = 0x0;
        else
        {
            if (node_guide->line.value == NULL)
                tasklist.now->next->task.desciption[0] = 0x0;
            else
                strncpy(tasklist.now->next->task.desciption, node_guide->line.value, MAX_DESCRIPTION_SIZE);
            ulist_change_current_node(data_tree, "#..", 0);
        }
        // tasklist.task[tasks_count].t_duedate_type
        if ((node_guide = ulist_change_current_node(data_tree, "t_duedate_type", 0)) == NULL)
            tasklist.now->next->task.t_duedate_type = _ONCE;
        else
        {
            if (node_guide->line.value == NULL)
                tasklist.now->next->task.t_duedate_type = _ONCE;
            else if (!strncmp(node_guide->line.value, "once", 4))    // 一次
                tasklist.now->next->task.t_duedate_type = _ONCE;
            else if (!strncmp(node_guide->line.value, "everyday", 5))
                tasklist.now->next->task.t_duedate_type = _EVERYDAY; // 每天
            else if (node_guide->line.value[0] == 'w')               // 每周循环, 以w开头
            {
                tasklist.now->next->task.t_duedate_type = _CIRCULATE_WEEKLY;
                for (int i = 1; node_guide->line.value[i] != 0x0; i++) // w后面接1234567或其一部分
                    if (node_guide->line.value[i] >= '1' && node_guide->line.value[i] <= '7')
                        tasklist.now->next->task.t_duedate_type |= (0x01 << (node_guide->line.value[i] - '0'));
            }
            ulist_change_current_node(data_tree, "#..", 0);
        }
        // tasklist.task[tasks_count].t_duedate
        if ((node_guide = ulist_change_current_node(data_tree, "t_duedate", 0)) == NULL)
        {
            tasklist.now->next->task.t_duedate[0] = 2000;
            tasklist.now->next->task.t_duedate[1] = 1;
            tasklist.now->next->task.t_duedate[2] = 1;
        }
        else
        {
            if (node_guide->line.value == NULL || sscanf(node_guide->line.value, "%d-%d-%d",
                                                         tasklist.now->next->task.t_duedate,
                                                         tasklist.now->next->task.t_duedate + 1,
                                                         tasklist.now->next->task.t_duedate + 2) < 3)
            {
                tasklist.now->next->task.t_duedate[0] = 2000;
                tasklist.now->next->task.t_duedate[1] = 1;
                tasklist.now->next->task.t_duedate[2] = 1;
            }
            ulist_change_current_node(data_tree, "#..", 0);
        }
        // tasklist.task[tasks_count].t_duetime
        if ((node_guide = ulist_change_current_node(data_tree, "t_duetime", 0)) == NULL)
        {
            tasklist.now->next->task.t_duetime[0] = 0;
            tasklist.now->next->task.t_duetime[1] = 0;
            tasklist.now->next->task.t_duetime[2] = 0;
        }
        else
        {
            if (node_guide->line.value == NULL)
            {
                tasklist.now->next->task.t_duetime[0] = 0;
                tasklist.now->next->task.t_duetime[1] = 0;
                tasklist.now->next->task.t_duetime[2] = 0;
            }
            else
                sscanf(node_guide->line.value, "%d:%d:%d",
                       tasklist.now->next->task.t_duetime,
                       tasklist.now->next->task.t_duetime + 1,
                       tasklist.now->next->task.t_duetime + 2);
            ulist_change_current_node(data_tree, "#..", 0);
        }
        // tasklist.task[tasks_count].time_ahead
        if ((node_guide = ulist_change_current_node(data_tree, "time_ahead", 0)) == NULL)
        {
            tasklist.now->next->task.time_ahead[0] = 0;
            tasklist.now->next->task.time_ahead[1] = 0;
            tasklist.now->next->task.time_ahead[2] = 0;
        }
        else
        {
            if (node_guide->line.value == NULL)
            {
                tasklist.now->next->task.time_ahead[0] = 0;
                tasklist.now->next->task.time_ahead[1] = 0;
                tasklist.now->next->task.time_ahead[2] = 0;
            }
            else
                sscanf(node_guide->line.value, "%d:%d:%d",
                       tasklist.now->next->task.time_ahead,
                       tasklist.now->next->task.time_ahead + 1,
                       tasklist.now->next->task.time_ahead + 2);
            ulist_change_current_node(data_tree, "#..", 0);
        }
        // tasklist.task[tasks_count].private
        // Medi注: 这种类似于多态的做法貌似不适于C++... C++会有更强大的解决方案吧。
        if ((node_guide = ulist_change_current_node(data_tree, "private", 0)) == NULL)
            tasklist.now->next->task.priv_data = NULL;
        else
        {
            switch (tasklist.now->next->task.ttype)
            {
            case _TIME_LIMIT: // 限时任务: private指向一个时间数组
                tasklist.now->next->task.priv_data = (int *)malloc(sizeof(int) * 3);
                if ((node_guide = ulist_change_current_node(data_tree, "timespan", 0)) == NULL)
                {
                    ((int *)tasklist.now->next->task.priv_data)[0] = 0;
                    ((int *)tasklist.now->next->task.priv_data)[1] = 0;
                    ((int *)tasklist.now->next->task.priv_data)[2] = 0;
                }
                else
                {
                    if (node_guide->line.value == NULL || sscanf(node_guide->line.value, "%d:%d:%d",
                                                                 (int *)tasklist.now->next->task.priv_data,
                                                                 (int *)tasklist.now->next->task.priv_data + 1,
                                                                 (int *)tasklist.now->next->task.priv_data + 2) < 3)
                    {
                        /*注意写法. 先写出private的完整路径, 然后强制类型转换为(int *), 然后当数组用*/
                        ((int *)tasklist.now->next->task.priv_data)[0] = 0;
                        ((int *)tasklist.now->next->task.priv_data)[1] = 0;
                        ((int *)tasklist.now->next->task.priv_data)[2] = 0;
                    }
                    ulist_change_current_node(data_tree, "#..", 0); // tasklist.task.private.data => tasklist.task.private
                }
                break;
                // case _BIG_EVENT: // 重大事件: private指向一个任务链表 //敬请期待...
                //     tasklist.now->next->task.priv_data = (TaskNode *)malloc(sizeof(TaskNode)); // 启动子列表
                //     break;

            default:
                break;
            }
            /*成功则返回tasklist.task*/
            ulist_change_current_node(data_tree, "#..", 0); // tasklist.task.private => tasklist.task
        }
        /* tasklist.now往后指，然后cd到上一级节点
         * 失败则datatree.now停留在tasklist.task, 直接返回tasklist*/
        tasklist.now = tasklist.now->next;
        ulist_change_current_node(data_tree, "#..", 0); // tasklist.task => tasklist
        task_count++;
    } while (1);

    tasklist.length = task_count;
    return tasklist;
}

TaskList new_tasklist(char *list_file_name)
{
    // 为返回链表初始化备用值, 防止文件不存在或者出错时返回一个无效链表导致段错误
    TaskList tasklist = {
        .l_id = 0,
        .max_task_id = 0,
        .default_order = 0,
        .head = (TaskNode *)malloc(sizeof(TaskNode)),
        .now = tasklist.head,
    };
    if (tasklist.head == NULL)
    {
        fprintf(stderr, "ERROR message reported by function %s(): CANNOT allocate memory", __func__);
        return tasklist;
    }
    *(tasklist.head) = (TaskNode){
        .task = (TaskInfo){
            .t_id = -1,
            .ttype = _STATIC,
            .name = "#HEAD",
            .desciption = NULL,
            .priv_data = NULL,
        },
        .next = NULL,
    };

    // 第一/二阶段
    FILE *list_file = fopen(list_file_name, "r");
    UniListObject *parsed_text = ulist_object_from_file(list_file);
    if (parsed_text == NULL)
        return tasklist;

    // 第三阶段
    free(tasklist.head);
    tasklist = data_tree_to_tasklist(&parsed_text);
    if (ulist_destory_object(parsed_text) == false)
        fprintf(stderr, "ERROR message reported by function %s(): data tree cannot be released, which causes a memory leak.\n", __func__);

    fclose(list_file);
    return tasklist;
}

int write_tasklist(TaskList *tasklist, const char *filename)
{
    if (tasklist == NULL)
    {
        fprintf(stderr, "ERROR message reported by function %s(): tasklist pointer is NULL. Please check the function who called %s.\n",
                __func__, __func__);
        return -1;
    }
    char conv_buffer[MAX_DESCRIPTION_SIZE];
    FILE *fp_out = fopen(filename, "w");
    if (fp_out == NULL)
    {
        fprintf(stderr, "ERROR message reported by function %s(): CANNOT open file %s, please "
                        "check the permission of the output directory you've configured.\n",
                __func__, filename);
        return -1;
    }

    // # 配置文件的初始信息, 为手动修改文件的人做准备
    fputs("# encoding: utf-8\n", fp_out);
    fputs("# 此配置文件是U.toGo自动生成的, 用于存放U.toGo场景数据. 场景名称见list.name字段.\n", fp_out);
    fputs("# 如果你要手动修改文件数据, 请参见\n"
          "# <https://gitee.com/medihbt/utogo/blob/main/docs/format_unilist.md>.\n"
          "# 注意检查你的编辑器是否开启了tab转空格, 如果有, 请关闭.\n\n", fp_out);
    // 0 list:
    fputs("list: # the start of the list\n", fp_out);
    // 1    l_id:
    fprintf(fp_out, "\tl_id: \"%ld\"\n", tasklist->l_id);
    // 1    name:
    if (unconvert_string_from_ulist(conv_buffer, tasklist->name, MAX_DESCRIPTION_SIZE) == -1)
        return -1;
    else
        fprintf(fp_out, "\tname: \"%s\"\n", conv_buffer);
    // 1    description:
    if (unconvert_string_from_ulist(conv_buffer, tasklist->description, MAX_DESCRIPTION_SIZE) == -1)
        return -1;
    else
        fprintf(fp_out, "\tdescription: \"%s\"\n", conv_buffer);
    // 1    default_order:
    fprintf(fp_out, "\tdefault_order: \"%s\"\n", TASKLIST_DEFAULT_ORDER[tasklist->default_order]);
    for (TaskNode *ptr = tasklist->head->next; ptr != NULL; ptr = ptr->next)
    {
        // 1 task:
        fprintf(fp_out, "\ttask:\n");
        // 2    t_id:
        fprintf(fp_out, "\t\tt_id: \"%d\"\n", ptr->task.t_id);
        // 2    finished:
        fprintf(fp_out, "\t\tfinished: \"%s\"\n",
                (ptr->task.finished == true ? "yes" : "no"));
        // 2    type:
        fprintf(fp_out, "\t\ttype: \"%s\"\n",
                TASKLIST_TYPES[ptr->task.ttype]);
        // 2    name:
        if (unconvert_string_from_ulist(conv_buffer, ptr->task.name, MAX_DESCRIPTION_SIZE) == -1)
        {
            remove(filename);
            fputs("ERROR message: there is a bug in converting \"name\"", stderr);
            return -1;
        }
        else
            fprintf(fp_out, "\t\tname: \"%s\"\n", conv_buffer);
        // 2    description:
        if (unconvert_string_from_ulist(conv_buffer, ptr->task.desciption, MAX_DESCRIPTION_SIZE) == -1)
        {
            remove(filename);
            fputs("ERROR message: there is a bug in converting \"name\"", stderr);
            return -1;
        }
        else
            fprintf(fp_out, "\t\tdescription: \"%s\"\n", conv_buffer);
        // 2    t_duedate_type:
        switch (ptr->task.t_duedate_type)
        {
        case _ONCE:
            fprintf(fp_out, "\t\tt_duedate_type: \"once\"\n");
            break;
        case _EVERYDAY:
            fprintf(fp_out, "\t\tt_duedate_type: \"everyday\"\n");
            break;
        default: // _CIRCULATE_WEEKLY
            fprintf(fp_out, "\t\tt_duedate_type: \"w");
            if ((ptr->task.t_duedate_type & _CIRCULATE_WEEKLY) != 0x0)
            {
                for (int i = 1; i <= 7; i++)
                    if ((ptr->task.t_duedate_type & (0x01 << i)) != 0x0)
                        fprintf(fp_out, "%d", i);
                fprintf(fp_out, "\"\n");
            }
            else
                fprintf(fp_out, "\"\n");
            break;
        }
        // 2    t_duedate
        fprintf(fp_out, "\t\tt_duedate: \"%d-%02d-%02d\"\n",
                ptr->task.t_duedate[0],
                ptr->task.t_duedate[1],
                ptr->task.t_duedate[2]);
        // 2    t_duetime
        fprintf(fp_out, "\t\tt_duetime: \"%02d:%02d:%02d\"\n",
                ptr->task.t_duetime[0],
                ptr->task.t_duetime[1],
                ptr->task.t_duetime[2]);
        // 2    time_ahead
        fprintf(fp_out, "\t\ttime_ahead: \"%02d:%02d:%02d\"\n",
                ptr->task.time_ahead[0],
                ptr->task.time_ahead[1],
                ptr->task.time_ahead[2]);
        // 2    private
        fprintf(fp_out, "\t\tprivate:\n");
        switch (ptr->task.ttype)
        {
        case _STATIC:
            fprintf(fp_out, "\t\t\tNULL:\n");
            break;
        case _TIME_LIMIT:
            if (ptr->task.priv_data == NULL)
                fprintf(fp_out, "\t\t\ttimespan:\"00:00:00\"\n");
            else
                fprintf(fp_out, "\t\t\ttimespan:\"%02d:%02d:%02d\"\n",
                        ((int *)ptr->task.priv_data)[0],
                        ((int *)ptr->task.priv_data)[1],
                        ((int *)ptr->task.priv_data)[2]);
            break;
        default:
            fprintf(fp_out, "\t\t\tNULL:\n");
        }
    }
    fclose(fp_out);
    return 0;
}

#if UTASK_IO_DEBUG_MAIN == 1
int main(int argc, char *argv[]) //../../bootstrap/debug_examples/main.scene.txt
{
    TaskList tasklist = new_tasklist("../../bootstrap/debug_examples/main.scene.txt");
    // TaskNode *test = search_node_by_id(tasklist.head, 4);
    printf("所有任务的最大id是 = %ld\n", tasklist.max_task_id);
    // printf("tasklist.task[4].duedate_type = %b\n", test->task.t_duedate_type);
    /* 我没有Linux根目录下的写权限, 此处测试创建文件报错是否正常 */
    write_tasklist(&tasklist, "/test.out");
    /* 测试NULL报错是否正常 */
    write_tasklist(NULL, NULL);
#ifdef __linux__
    write_tasklist(&tasklist, "/dev/stdout");
#elif
    write_tasklist(&tasklist, "test.out");
#endif
    delet_all(&(tasklist.head));
}
#endif

#ifdef __cplusplus
}
#endif

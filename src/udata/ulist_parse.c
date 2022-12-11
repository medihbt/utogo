/*Copyright (c) 2022-2023 Imagine Studio PBLF Group.*/

#include "../include/utask_io.h"

/*DEBUG用的宏*/
#define UTASK_IO_DEBUG_C 1
#define UTASK_IO_DEBUG_OUTPUT 1
#define UTASK_CONVERT 1

#define UTASK_MEM_BLOCK_SIZE 1024

char *get_name_from_buffer(char *dest, /*const*/ char *buff)
{
    char *cur = dest;
    while (*buff != ':')
    {
        if (*buff == '#' || *buff == '\n')
            return NULL;
        *cur = *buff;
        buff++, cur++;
    }
    *cur = 0;
    return buff;
}

int get_value_from_buffer(char **p_begin_out, /*const */ char *buff)
{
    if (p_begin_out == NULL || buff == NULL)
        return 0;

    while (*buff != '\"')
    {
        if (*buff == '\n' || *buff == '#')
            return 0;
        buff++;
    }
    *p_begin_out = (++buff);

    while (*buff != '\"')
    {
        if (*buff == '\n')
        {
            *p_begin_out = NULL;
            return 0;
        }
        buff++;
    }

    return buff - *p_begin_out;
}

ParsedText parse_config_to_lines(char *fileName)
{
    ParsedText parsed_text = {
        .head = (ParsedNode *)malloc(sizeof(ParsedNode)),
        .now = parsed_text.head,
        .length = 0,
    };
    *(parsed_text.head) = (ParsedNode){
        .line = (TextLine){
            .level = -1,
            .name = "HEAD",
            .value = NULL,
        },
        .parent = NULL,
        .child = NULL,
        .next = NULL,
    };
    ParsedNode *current = parsed_text.head;
    FILE *cfg_file = fopen(fileName, "r");
    char *buffer = (char *)calloc(4 * UTASK_MEM_BLOCK_SIZE, sizeof(char));
    int lines = 0;

    if (parsed_text.head == NULL || cfg_file == NULL)
        return (ParsedText){NULL, NULL, 0};

    char *ptmp = NULL, *desc_text = NULL;
    while (fgets(buffer, 3 * UTASK_MEM_BLOCK_SIZE * sizeof(char), cfg_file) != NULL)
    {
        ParsedNode tmp_node = {
            .line = {
                .level = get_str_level(buffer),
                .name = {0},
                .value = NULL,
            },
            .parent = NULL,
            .child = NULL,
            .next = NULL,
        };

        ptmp = buffer + tmp_node.line.level;
        if ((ptmp = get_name_from_buffer(tmp_node.line.name, ptmp)) == NULL)
        {
            tmp_node.line.name[0] = 0;
            continue;
        }

        current->next = (ParsedNode *)malloc(sizeof(ParsedNode));
        *(current->next) = tmp_node;

        int value_length = get_value_from_buffer(&ptmp, ptmp);
        if (value_length != 0)
        {
            current->next->line.value = (char *)malloc(sizeof(char) * UTASK_MEM_BLOCK_SIZE);
            memcpy(current->next->line.value, ptmp, value_length);
            current->next->line.value[value_length + 1] = 0x0;
        }
        current = current->next;
    }
    fclose(cfg_file);
    free(buffer);
    return parsed_text;
}

ParsedText *generate_data_tree(ParsedText *parsed_text)
{
    if (parsed_text == NULL)
        return NULL;

    /*令所有节点成为头节点的子节点*/
    ParsedNode *parsed_head = parsed_text->head;
    parsed_head->child = parsed_head->next;
    parsed_head->next = NULL;
    parsed_head->child->parent = parsed_head;

    /*创建指针栈*/
    ParsedNode *content[16] = {parsed_head, NULL};
    ParsedNode **base = content + 1, **top = content + 1;

    ParsedNode *ptr_op = parsed_head->child, *ptr_prev = parsed_head;
    *top = ptr_op;
    while (ptr_op != NULL)
    {
        top = base + ptr_op->line.level;
        ParsedNode *ptmp = NULL;
        int delta_level = ptr_op->line.level - ptr_prev->line.level;
        if (delta_level >= 2)
        {
            fprintf(stderr, "ERROR message from %s() in %s: syntax error in tasklist file\n", __func__, __FILE__);
            return NULL;
        }

        switch (delta_level)
        {
        case 1: // 当前节点是上一个的子节点, ptr_prev与ptr_op建立父子关系
            ptr_op->parent = ptr_prev;
            ptr_prev->child = ptr_op;
            ptmp = ptr_prev;
            break;
        case 0: // 当前节点与上一个节点同级, ptr_prev与ptr_op的父节点建立父子关系
            ptr_op->parent = ptr_prev->parent;
            ptmp = ptr_op->parent;
        default: // 下一节点比上一节点少缩进了, ptr_prev与它同级前一节点的父节点建立父子关系
            ptr_op->parent = (*top)->parent;
            ptmp = ptr_op->parent;
            break;
        }
        // 当前节点的所有父节点往后推一格
        while (ptmp != parsed_head)
        {
            ptmp->next = ptr_op->next;
            ptmp = ptmp->parent;
        }
        *top = ptr_op;
        ptr_prev = ptr_op;
        ptr_op = ptr_op->next;
    }
    parsed_text->head->next = NULL;
    return parsed_text;
}

ParsedNode *change_current_node(ParsedText *parsed_text, const char *node_name, int node_order)
{
    if (parsed_text == NULL || node_name == NULL || node_order < 0)
        return NULL;
    else if (parsed_text->head == NULL || parsed_text->head->child == NULL)
        return NULL;
    else if (parsed_text->now == NULL)
        return NULL;

    ParsedNode *ptext_now_dump = parsed_text->now;

    if (!strcmp(node_name, "#..")) // "#.."返回父节点，灵感来源于上一级文件夹(名称为"..")
    {
        if (parsed_text->now->parent == NULL)
            return NULL;
        else
            parsed_text->now = parsed_text->now->parent;
    }
    else if (!strcmp(node_name, "#/") || !strcmp(node_name, "#HEAD")) // "#/"或"#HEAD"返回头节点
    {
        parsed_text->now = parsed_text->head;
    }
    else // 找寻名称为node_name的子节点
    {
        if (parsed_text->now->child == NULL)
            return NULL;

        ParsedNode *ptr = parsed_text->now->child;
        int ptr_level = ptr->line.level;

        int order_count = 0;
        while ((ptr != NULL) && (ptr->line.level == ptr_level) && (order_count <= node_order))
        {
            if (!strcmp(ptr->line.name, node_name))
            {
                order_count++;
                parsed_text->now = ptr;
            }
            ptr = ptr->next;
        }
        if ((parsed_text->now == ptext_now_dump) || (order_count <= node_order))
            return NULL;
    }
    return parsed_text->now;
}

TaskList data_tree_to_tasklist(ParsedText *data_tree)
{
    /*初始化返回节点*/
    TaskList tasklist = {
        .head = (TaskNode *)malloc(sizeof(TaskNode)),
        .now = tasklist.head,
        .length = 0,
        .max_task_id = 0,
        .default_order = 0,
    };
    ParsedNode *node_guide = change_current_node(data_tree, "#/", 0);
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
    if ((node_guide = change_current_node(data_tree, "list", 0)) == NULL)
    {
        tasklist = (TaskList){
            .l_id = 0,
            .max_task_id = 0,
            .length = 0,
        };
        memcpy(tasklist.name, "Untitled List", 14);
        return tasklist;
    }

    // [tasklist.l_id]  int(文件) -> int(结构体)
    if ((node_guide = change_current_node(data_tree, "l_id", 0)) == NULL) // 失败时data_tree的now节点不会自动跳转
        tasklist.l_id = 0;
    else
    {
        if (node_guide->line.value == NULL || sscanf(node_guide->line.value, "%ld", &tasklist.l_id) < 1)
            tasklist.l_id = 0;
        change_current_node(data_tree, "#..", 0); // 返回上一级节点
    }
    // [tasklist.name]  string -> char[256]
    if ((node_guide = change_current_node(data_tree, "name", 0)) == NULL)
        memcpy(tasklist.name, "Untitled", 9);
    else
    {
        if (node_guide->line.value == NULL)
            memcpy(tasklist.name, "Untitled", 9);
        else
            strncpy(tasklist.name, node_guide->line.value, 256);
        change_current_node(data_tree, "#..", 0);
    }
    // [tasklist.description]   string -> char[1024]
    if ((node_guide = change_current_node(data_tree, "description", 0)) == NULL)
        memcpy(tasklist.description, "\0\0\0", 4);
    else
    {
        if (node_guide->line.value == NULL)
            memcpy(tasklist.description, "\0\0\0", 4);
        else
            strncpy(tasklist.description, node_guide->line.value, 1024);
        change_current_node(data_tree, "#..", 0);
    }
    // [tasklist.default_order] string -> int
    if ((node_guide = change_current_node(data_tree, "default_order", 0)) == NULL)
        tasklist.default_order = _TIME;
    else
    {
        if (node_guide->line.value == NULL)
            tasklist.default_order = _TIME;
        else if (!strcmp(node_guide->line.value, "time"))
            tasklist.default_order = _TIME;
        else
            tasklist.default_order = 0x0;
        change_current_node(data_tree, "#..", 0);
    }
    // [tasklist.task]  (子链表) array -> TaskNode *heads
    int task_count = 0;
    do
    {
        // /*查看是否有task节点*/
        // [tasklist.task[tasks_count]]
        if (change_current_node(data_tree, "task", task_count) == NULL)
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
        int debug_var;
        if ((node_guide = change_current_node(data_tree, "t_id", 0)) == NULL)
            tasklist.now->next->task.t_id = -1;
        else
        {
            if (node_guide->line.value == NULL)
                tasklist.now->next->task.t_id = -1;
            else if (sscanf(node_guide->line.value, "%d", &tasklist.now->next->task.t_id) < 1)
                tasklist.now->next->task.t_id = -1;
            change_current_node(data_tree, "#..", 0);
        }
        tasklist.max_task_id = tasklist.max_task_id > tasklist.now->next->task.t_id ? tasklist.max_task_id : tasklist.now->next->task.t_id;

        // tasklist.task[tasks_count].finished  string -> int
        if ((node_guide = change_current_node(data_tree, "finished", 0)) == NULL)
            tasklist.now->next->task.finished = false;
        else
        {
            if (node_guide->line.value == NULL)
                tasklist.now->next->task.finished = false;
            else if ((!strncmp(node_guide->line.value, "yes", 3)) || (!strncmp(node_guide->line.value, "YES", 3)))
                tasklist.now->next->task.finished = true;
            else
                tasklist.now->next->task.finished = false;
            change_current_node(data_tree, "#..", 0);
        }

        // tasklist.task[tasks_count].type      string -> int
        if ((node_guide = change_current_node(data_tree, "type", 0)) == NULL)
            tasklist.now->next->task.ttype = _STATIC;
        else
        {
            if (node_guide->line.value == NULL)
                tasklist.now->next->task.ttype = _STATIC;
            if (!strncmp(node_guide->line.value, "static", 6)) // 普通任务
                tasklist.now->next->task.ttype = _STATIC;
            else if (!strncmp(node_guide->line.value, "timelimit", 5)) // 限时任务
                tasklist.now->next->task.ttype = _TIME_LIMIT;
            else if (!strncmp(node_guide->line.value, "bigevent", 4)) // 重大事件
                tasklist.now->next->task.ttype = _BIG_EVENT;
            change_current_node(data_tree, "#..", 0);
        }
        // tasklist.task[tasks_count].name      string -> char[256]
        if ((node_guide = change_current_node(data_tree, "name", 0)) == NULL)
            memcpy(tasklist.now->next->task.name, "Untitled", 9);
        else
        {
            if (node_guide->line.value == NULL)
                memcpy(tasklist.now->next->task.name, "Untitled", 9);
            else
                strncpy(tasklist.now->next->task.name, node_guide->line.value, 256);
            change_current_node(data_tree, "#..", 0);
        }
        // tasklist.task[tasks_count].description       string -> char *
        if ((node_guide = change_current_node(data_tree, "description", 0)) == NULL)
            tasklist.now->next->task.desciption[0] = 0x0;
        else
        {
            if (node_guide->line.value == NULL)
                tasklist.now->next->task.desciption[0] = 0x0;
            else
                strncpy(tasklist.now->next->task.desciption, node_guide->line.value, MAX_DESCRIPTION_SIZE);
            change_current_node(data_tree, "#..", 0);
        }
        // tasklist.task[tasks_count].t_duedate_type
        if ((node_guide = change_current_node(data_tree, "t_duedate_type", 0)) == NULL)
            tasklist.now->next->task.t_duedate_type = _ONCE;
        else
        {
            if (node_guide->line.value == NULL)
                tasklist.now->next->task.t_duedate_type = _ONCE;
            else if (!strncmp(node_guide->line.value, "once", 4)) // 一次
                tasklist.now->next->task.t_duedate_type = _ONCE;
            else if (!strncmp(node_guide->line.value, "everyday", 5))
                tasklist.now->next->task.t_duedate_type = _EVERYDAY; // 每天
            else if (node_guide->line.value[0] == 'w')               // 每周循环, 以w开头
            {
                tasklist.now->next->task.t_duedate_type = _CIRCULATE_WEEKLY;
                for (int i = 1; node_guide->line.value[i] != 0x0; i++) // w后面接1234567或其一部分
                    if (node_guide->line.value[i] >= '0' && node_guide->line.value[i] <= '9')
                        tasklist.now->next->task.t_duedate_type |= (0x01 << (node_guide->line.value[i] - '0'));
            }
            change_current_node(data_tree, "#..", 0);
        }
        // tasklist.task[tasks_count].t_duedate
        if ((node_guide = change_current_node(data_tree, "t_duedate", 0)) == NULL)
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
            change_current_node(data_tree, "#..", 0);
        }
        // tasklist.task[tasks_count].t_duetime
        if ((node_guide = change_current_node(data_tree, "t_duetime", 0)) == NULL)
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
                       tasklist.now->next->task.t_duetime + 2,
                       tasklist.now->next->task.t_duetime + 1,
                       tasklist.now->next->task.t_duetime);
            change_current_node(data_tree, "#..", 0);
        }
        // tasklist.task[tasks_count].time_ahead
        if ((node_guide = change_current_node(data_tree, "time_ahead", 0)) == NULL)
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
                       tasklist.now->next->task.time_ahead + 2,
                       tasklist.now->next->task.time_ahead + 1,
                       tasklist.now->next->task.time_ahead);
            change_current_node(data_tree, "#..", 0);
        }
        // tasklist.task[tasks_count].private
        if ((node_guide = change_current_node(data_tree, "private", 0)) == NULL)
            tasklist.now->next->task.priv_data = NULL;
        else
        {
            switch (tasklist.now->next->task.ttype)
            {
            case _TIME_LIMIT: // 限时任务: private指向一个时间数组
                tasklist.now->next->task.priv_data = (int *)malloc(sizeof(int) * 3);
                if ((node_guide = change_current_node(data_tree, "timespan", 0)) == NULL)
                {
                    ((int *)tasklist.now->next->task.priv_data)[0] = 0;
                    ((int *)tasklist.now->next->task.priv_data)[1] = 0;
                    ((int *)tasklist.now->next->task.priv_data)[2] = 0;
                }
                else
                {
                    if (node_guide->line.value == NULL || sscanf(node_guide->line.value, "%d:%d:%d",
                                                                 (int *)tasklist.now->next->task.priv_data + 2,
                                                                 (int *)tasklist.now->next->task.priv_data + 1,
                                                                 (int *)tasklist.now->next->task.priv_data) < 3)
                    {
                        /*注意写法. 先写出private的完整路径, 然后强制类型转换为(int *), 然后当数组用*/
                        ((int *)tasklist.now->next->task.priv_data)[0] = 0;
                        ((int *)tasklist.now->next->task.priv_data)[1] = 0;
                        ((int *)tasklist.now->next->task.priv_data)[2] = 0;
                    }
                    change_current_node(data_tree, "#..", 0); // tasklist.task.private.data => tasklist.task.private
                }
                break;
                // case _BIG_EVENT:
                //     tasklist.now->next->task.priv_data = (TaskNode *)malloc(sizeof(TaskNode)); // 启动子列表
                //     break;

            default:
                break;
            }
            /*成功则返回tasklist.task*/
            change_current_node(data_tree, "#..", 0); // tasklist.task.private => tasklist.task
        }
        /* tasklist.now往后指，然后cd到上一级节点
         * 失败则datatree.now停留在tasklist.task, 直接返回tasklist*/
        tasklist.now = tasklist.now->next;
        change_current_node(data_tree, "#..", 0); // tasklist.task => tasklist
        task_count++;
    } while (1);

    return tasklist;
}

bool destory_data_tree(ParsedText *data_tree)
{
    ParsedNode *ptr_prev = data_tree->head;
    for(ParsedNode *ptr = data_tree->head->child; ptr != NULL;)
    {
        free(ptr->line.value);
        free(ptr_prev);
        ptr_prev = ptr;
        ptr = ptr->child != NULL ? ptr->child : ptr->next;
    }
    free(ptr_prev);
    return true;
}

#if UTASK_IO_DEBUG_C == 1
/* 函数: 测试使用的主程序 */
#define STAGE_2_PART 1
#define STAGE_3 1
int main(int argc, char *argv[])
{
    // if (argc < 2)
    // {
    //     puts("测试主函数 用法: ");
    //     printf("%s [文件名]\n\n", argv[0]);
    //     return 0;
    // }
    ParsedText parsed_text = parse_config_to_lines("../../bootstrap/debug_examples/main.scene.txt");
    puts("\033[01mParsing成功! 以下是行数据: \033[0m");
    for (ParsedNode *ptr = parsed_text.head; ptr->next != NULL; ptr = ptr->next)
        printf("\033[01m%4d\033[0m \033[01;32m%s\033[0m = %s\n",
               ptr->line.level,
               ptr->line.name,
               ptr->line.value);

    generate_data_tree(&parsed_text);

    /*全图测试*/
    int level = 0;
    for (ParsedNode *ptr = parsed_text.head->child; ptr != NULL;)
    {
        if (level == 1)
            printf(".");
        print_n_tab(stdout, ptr->line.level);
        printf("\033[01;32m%s\033[0m = \033[01m%s\033[0m\n", ptr->line.name, ptr->line.value);
        if (ptr->child != NULL)
        {
            ptr = ptr->child;
            level = 1;
        }
        else
        {
            ptr = ptr->next;
            level = 0;
        }
    }
#if STAGE_2_PART == 1
    /*同级元素测试*/
    puts("同级元素测试:\n");
    // l0: #HEAD.child
    puts("L0: ");
    for (ParsedNode *ptr = parsed_text.head->child; ptr != NULL; ptr = ptr->next)
    {
        print_n_tab(stdout, ptr->line.level);
        printf("\033[01;32m%s\033[0m = \033[01m%s\033[0m\n", ptr->line.name, ptr->line.value);
    }
    printf("\n");
    // l1: list.child
    puts("L1: ");
    for (ParsedNode *ptr = parsed_text.head->child->child; ptr != NULL; ptr = ptr->next)
    {
        print_n_tab(stdout, ptr->line.level);
        printf("\033[01;32m%s\033[0m = \033[01m%s\033[0m\n", ptr->line.name, ptr->line.value);
    }
    printf("\n");
    // l2: task[0].child
    puts("L2[0]: ");
    for (ParsedNode *ptr = parsed_text.head->child->child->next->next->next->next->child; (ptr != NULL) && (ptr->line.level == 2); ptr = ptr->next)
    {
        print_n_tab(stdout, ptr->line.level);
        printf("\033[01;32m%s\033[0m = \033[01m%s\033[0m\n", ptr->line.name, ptr->line.value);
    }
    printf("\n");
    // l2: task[1].child
    puts("L2[1]: ");
    for (ParsedNode *ptr = parsed_text.head->child->child->next->next->next->next->child->next; (ptr != NULL) && (ptr->line.level == 2); ptr = ptr->next)
    {
        print_n_tab(stdout, ptr->line.level);
        printf("\033[01;32m%s\033[0m = \033[01m%s\033[0m\n", ptr->line.name, ptr->line.value);
    }
    printf("\n");
#endif

    TaskList tasklist = data_tree_to_tasklist(&parsed_text);

#if STAGE_3 == 1
    for (int search_tag = 1; search_tag <= 3; search_tag++)
    {
        // printf("%d name: %s\n", search_tag, search_node_by_id(tasklist.head, search_tag)->task.name);
        printf("task%d duedate: %d-%d-%d\n", search_tag,
               search_node_by_id(tasklist.head, search_tag)->task.t_duedate[0],
               search_node_by_id(tasklist.head, search_tag)->task.t_duedate[1],
               search_node_by_id(tasklist.head, search_tag)->task.t_duedate[2]);
        printf("task%d duetime: %02d:%02d:%02d\n", search_tag,
               search_node_by_id(tasklist.head, search_tag)->task.t_duetime[2],
               search_node_by_id(tasklist.head, search_tag)->task.t_duetime[1],
               search_node_by_id(tasklist.head, search_tag)->task.t_duetime[0]);
    }
#endif

    destory_data_tree(&parsed_text);

    return 0;
}
#endif
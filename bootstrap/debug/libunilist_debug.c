#include "../../src/libunilist/unilist.h"
#include "../../src/include/utask_io.h"
#include <unistd.h>

/*DEBUG用的宏*/
#define UTASK_IO_DEBUG_OUTPUT 0
#define UTASK_CONVERT 0
#define UTASK_BLACKBOX 1

/* 函数: 测试使用的主程序 */
#define STAGE_2_PART 1
#define STAGE_3 1
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        puts("测试主函数 用法: ");
        printf("%s [文件名]\n\n", argv[0]);
        return 0;
    }
    /*convert*/
    char *src = "aa\tbbcc";
    char dest[100];
    convert_string_from_file(dest, src, 100);
    printf("%s\n", dest);

    ParsedText parsed_text = parse_config_to_lines(argv[1]);
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

#if STAGE_3 == 1
    TaskList tasklist = data_tree_to_tasklist(&parsed_text);

    for (int search_tag = 1; search_tag <= 3; search_tag++)
    {
        printf("task%d name: %s\n", search_tag, search_node_by_id(tasklist.head, search_tag)->task.name);
        printf("task%d type: %d\n", search_tag, search_node_by_id(tasklist.head, search_tag)->task.ttype);
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
    fflush(stdout);
#ifdef __linux__
#if UTASK_BLACKBOX == 1
    write_tasklist(&tasklist, "/dev/stdout");
#endif
#endif
    destory_data_tree(&parsed_text);
    return 0;
}
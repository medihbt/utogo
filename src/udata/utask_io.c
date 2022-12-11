/*Copyright (c) 2022-2023 Imagine Studio PBLF Group.*/
/*utask_io.c -- Main Part of U.toGo Configuration Analyzing Module*/
#include "../include/utask_io.h"
#include "../include/err.h"

#define UTASK_IO_DEBUG_MAIN 1

const char *TASKLIST_DEFAULT_ORDER[1] = {
    "time",
};

TaskList new_tasklist(char *list_file_name)
{
    ParsedText parsed_text = parse_config_to_lines(list_file_name);
    ParsedText *status = generate_data_tree(&parsed_text);
    if (status == NULL)
    {
        fprintf(stderr, "ERROR message reported by function %s(): wrong configuration file, or there is a bug in this program.\n", __func__);
        return (TaskList){
            .head = NULL,
            .now = NULL,
        };
    }
    TaskList tasklist = data_tree_to_tasklist(&parsed_text);
    if (destory_data_tree(&parsed_text) == false)
        fprintf(stderr, "ERROR message reported by function %s(): data tree cannot be released, which causes a memory leak.\n", __func__);

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
    char description[MAX_DESCRIPTION_SIZE * 2];
    FILE *fp_out = fopen(filename, "w");
    if (fp_out == NULL)
    {
        fprintf(stderr, "ERROR message reported by function %s(): CANNOT open file %s, please "
                        "check the permission of the output directory you've configured.\n",
                __func__, filename);
        return -1;
    }
    fputs("list: # the start of the list", fp_out);
    fprintf(fp_out, "\tl_id: \"%d\"\n", tasklist->l_id);
    fprintf(fp_out, "\tname: \"%s\"\n", tasklist->name);
    fprintf(fp_out, "\tdescription: \"%s\"\n", tasklist->description);
    fprintf(fp_out, "\tdefault_order: \"%s\"\n", TASKLIST_DEFAULT_ORDER[tasklist->default_order]);
    for (TaskNode *ptr = tasklist->head->next; ptr != NULL; ptr = ptr->next)
    {
        fprintf(fp_out, "\ttask:\n");
        fprintf(fp_out, "\t\tt_id: \"%d\"", ptr->task.t_id);
        
    }
    
    return 0;
}

#if UTASK_IO_DEBUG_MAIN == 1
int main(void)
{
    TaskList tasklist = new_tasklist("../../bootstrap/debug_examples/main.scene.txt");
    /* 我没有Linux根目录下的写权限, 此处测试创建文件报错是否正常 */
    write_tasklist(&tasklist, "/test.out");
    /* 测试NULL报错是否正常 */
    write_tasklist(NULL, NULL);
}
#endif
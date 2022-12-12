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
#include "../include/err.h"

#define UTASK_IO_DEBUG_MAIN 0

const char *TASKLIST_DEFAULT_ORDER[1] = {
    "time",
};

const char *TASKLIST_TYPES[3] = {
    "static",
    "timelimit",
    "bigevent",
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
    char conv_buffer[MAX_DESCRIPTION_SIZE];
    FILE *fp_out = fopen(filename, "w");
    if (fp_out == NULL)
    {
        fprintf(stderr, "ERROR message reported by function %s(): CANNOT open file %s, please "
                        "check the permission of the output directory you've configured.\n",
                __func__, filename);
        return -1;
    }

    // 0 list:
    fputs("list: # the start of the list\n", fp_out);
    // 1    l_id:
    fprintf(fp_out, "\tl_id: \"%ld\"\n", tasklist->l_id);
    // 1    name:
    if (unconvert_string_from_tasklist(conv_buffer, tasklist->name, MAX_DESCRIPTION_SIZE) == -1)
        return -1;
    else
        fprintf(fp_out, "\tname: \"%s\"\n", conv_buffer);
    // 1    description:
    if (unconvert_string_from_tasklist(conv_buffer, tasklist->description, MAX_DESCRIPTION_SIZE) == -1)
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
        if (unconvert_string_from_tasklist(conv_buffer, ptr->task.name, MAX_DESCRIPTION_SIZE) == -1)
        {
            remove(filename);
            fputs("ERROR message: there is a bug in converting \"name\"", stderr);
            return -1;
        }
        else
            fprintf(fp_out, "\t\tname: \"%s\"\n", conv_buffer);
        // 2    description:
        if (unconvert_string_from_tasklist(conv_buffer, ptr->task.desciption, MAX_DESCRIPTION_SIZE) == -1)
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
                for (int i = 0; i < 7; i++)
                    if ((ptr->task.t_duedate_type & (0x01 << i)) != 0x0)
                        fprintf(fp_out, "%d", i + 1);
                fprintf(fp_out, "\"\n");
            }
            else
                fprintf(fp_out, "\t\tt_duedate_type: \"once\"\n");
            break;
        }
        // 2    t_duedate
        fprintf(fp_out, "\t\tt_duedate: \"%d-%02d-%02d\"\n",
                ptr->task.t_duedate[0], 
                ptr->task.t_duedate[1], 
                ptr->task.t_duedate[2]);
        // 2    t_duetime
        fprintf(fp_out, "\t\tt_duetime: \"%02d:%02d:%02d\"\n",
                ptr->task.t_duetime[2], 
                ptr->task.t_duetime[1], 
                ptr->task.t_duetime[0]);
        // 2    time_ahead
        fprintf(fp_out, "\t\ttime_ahead: \"%02d:%02d:%02d\"\n",
                ptr->task.time_ahead[2], 
                ptr->task.time_ahead[1], 
                ptr->task.time_ahead[0]);
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
                        ((int *)ptr->task.priv_data)[2],
                        ((int *)ptr->task.priv_data)[1],
                        ((int *)ptr->task.priv_data)[0]);
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
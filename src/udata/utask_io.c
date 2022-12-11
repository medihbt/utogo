/*Copyright (c) 2022-2023 Imagine Studio PBLF Group.*/
/*utask_io.c -- Main Part of U.toGo Configuration Analyzing Module*/
#include "../include/utask_io.h"

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
        fprintf(stderr, "ERROR message reported by function %s(): data tree cannot be released, which causes memory leak.\n", __func__);

    return tasklist;
}
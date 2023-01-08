/*  unilist.c -- main part of libunilist
    Copyright (c) 2022-2023 Imagine Studio PBLF Group.
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

#include "unilist.h"

#define __LIBUNILIST_DEBUG_MAIN 0

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

bool append_child_node(ParsedText *data_tree, const char *name, const char *value)
{
    if (name == NULL || value == NULL)
        return false;
    else if (data_tree == NULL || data_tree->now == NULL)
        return false;

    ParsedNode *node = (ParsedNode *)malloc(sizeof(ParsedNode));
    ParsedNode *prev = data_tree->now->next;
    *node = (ParsedNode){
        .child = NULL,
        .parent = data_tree->now,
        .next = data_tree->now->next,
        .line = (TextLine){
            .level = data_tree->now->line.level + 1,
            .value = (char *)malloc(sizeof(char) * MAX_DESCRIPTION_SIZE),
        },
    };
    strncpy(node->line.name, name, 256);
    strncpy(node->line.value, value, MAX_DESCRIPTION_SIZE);
    
    if (data_tree->now->child == NULL)
    {
        data_tree->now->child = node;
    }
    else
    {
        while (prev->next != NULL)
            prev = prev->next;
        prev->next = node;
    }
    return true;
}

bool destory_data_tree(ParsedText *data_tree)
{
    ParsedNode *ptr_prev = data_tree->head;
    for (ParsedNode *ptr = data_tree->head->child; ptr != NULL;)
    {
        free(ptr->line.value);
        free(ptr_prev);
        ptr_prev = ptr;
        ptr = ptr->child != NULL ? ptr->child : ptr->next;
    }
    free(ptr_prev);
    return true;
}

#if __LIBUNILIST_DEBUG_MAIN == 1
int main(void)
{
    ParsedText data = parse_config_to_lines("../../bootstrap/dbg_samples/main.scene");
    generate_data_tree(&data);
    change_current_node(&data, "#/", 0);
    change_current_node(&data, "list", 0);
    change_current_node(&data, "task", 0);
    u_print_data_tree(&data, stdout);
    puts("================================");
    u_print_current_subtree(&data, stdout);
    return 0;
}
#endif

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

int u_print_current_subtree(const ParsedText *parsed_text, FILE *__stream)
{
    int level = 0, nodes = 0;
    char buff[MAX_DESCRIPTION_SIZE];
    ParsedNode *ptr = parsed_text->now;
    do {
        print_n_tab(__stream, level);
        if (unconvert_string_from_tasklist(buff, ptr->line.value, MAX_DESCRIPTION_SIZE) == -1)
        {
            buff[0]= 0;
            fprintf(__stream, "%s:\n", ptr->line.name);
        }
        else 
            fprintf(__stream, "%s: \"%s\"\n", ptr->line.name, buff);
        nodes++;

        if (ptr->child != NULL)     // 有子节点, 切换到子节点
            level++, ptr = ptr->child;
        else if (ptr->next != NULL) // 否则切换到下一级或者下一个父节点
        {
            level -= (ptr->line.level - ptr->next->line.level);
            ptr = ptr->next;
        }
        else break;
    } while (level > 0);
    return nodes;
}

int u_print_data_tree(const ParsedText *parsed_text, FILE *__stream)
{
    if (parsed_text == NULL || parsed_text->head == NULL)
        return -1;
    ParsedText dump_text = (ParsedText){
        .now = parsed_text->head->child,
        .length = parsed_text->length,
    };
    return u_print_current_subtree(&dump_text, __stream);
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

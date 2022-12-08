#include "../include/utask_io.h"

#define UTASK_IO_DEBUG_C 1
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
            *p_begin_out == NULL;
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

#define GetFirstInChilds(parsed_node) ((parsed_node)->parent->child)

ParsedNode *change_current_node(ParsedText *parsed_text, const char *node_name, int node_order)
{
    if (parsed_text == NULL || node_name == NULL || node_order < 0)
        return NULL;
    else if (parsed_text->head == NULL || parsed_text->head->child == NULL)
        return NULL;
    else if (parsed_text->now == NULL)
        return NULL;

    char *current_name = parsed_text->now->line.name;
    int order_count = 0;
    if (!strcmp(node_name, "#.."))
    {
        if (parsed_text->now->parent == NULL)
            return NULL;
        else
            parsed_text->now = parsed_text->now->parent;
    }
    else if (!strcmp(node_name, "#/") || !strcmp(node_name, "#HEAD"))
    {
        parsed_text->now = parsed_text->head;
    }
    else
    {
        ParsedNode *ptr = GetFirstInChilds(parsed_text->now);
        int ptr_level = ptr->line.level;
        while ((ptr->line.level == ptr_level) && (order_count <= node_order))
        {
            if (!strcmp(ptr->line.name, node_name))
                order_count++;
            ptr = ptr->next;
        }
        if (ptr->line.level != ptr_level)
            return NULL;
    }
    return parsed_text->now;
}

#if UTASK_IO_DEBUG_C == 1
/* 函数: 测试使用的主程序 */
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        puts("测试主函数 用法: ");
        printf("%s [文件名]\n\n", argv[0]);
        return 0;
    }
    ParsedText parsed_text = parse_config_to_lines("../../bootstrap/debug_examples/main.scene.txt");
    puts("\033[01mParsing成功! 以下是行数据: \033[0m");
    for (ParsedNode *ptr = parsed_text.head; ptr->next != NULL; ptr = ptr->next)
        printf("\033[01m%4d\033[0m \033[01;32m%s\033[0m = %s\n",
               ptr->line.level,
               ptr->line.name,
               ptr->line.value);
    
    generate_data_tree(&parsed_text);

    ParsedNode *node = change_current_node(&parsed_text, "#/", 0);
    if (node == NULL)
        puts("ERROR: Node not found");
    else
    {
        puts("\033[01mFinding成功! 以下是节点数据: \033[0m");
        printf("\033[01m%4d\033[0m \033[01;32m%s\033[0m = %s\n",
               node->line.level,
               node->line.name,
               node->line.value);
    }

    return 0;
}
#endif
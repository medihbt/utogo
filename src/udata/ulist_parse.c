#include "../../include/utask_io.h"

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

        // int value_length = get_value_from_buffer(&ptmp, ptmp);
        char *value_begin = NULL;
        int value_length = get_value_from_buffer(&value_begin, ptmp);
        if (value_length != 0)
        {
            current->next->line.value = (char *)malloc(sizeof(char) * UTASK_MEM_BLOCK_SIZE);
            memcpy(current->next->line.value, value_begin, value_length);
            current->next->line.value[value_length + 1] = 0x0;
        }
        current = current->next;
    }
    fclose(cfg_file);
    free(buffer);
    return parsed_text;
}

#if UTASK_IO_DEBUG_C == 1
/* 函数: 测试使用的主程序 */
int main()
{
    ParsedText parsed_text = parse_config_to_lines("../ttext");
    for (ParsedNode *ptr = parsed_text.head; ptr->next != NULL; ptr = ptr->next)
        printf("%d|%s=%s\n",
               ptr->line.level,
               ptr->line.name,
               ptr->line.value);

    return 0;
}
#endif
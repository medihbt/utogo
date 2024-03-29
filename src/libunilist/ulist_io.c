/*  ulist_io.c -- unilist input and output
 *  Copyright (c) 2022-2023 Imagine Studio PBLF Group.
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

/*内部宏包*/
#define ULIST_MEM_BLOCK_SIZE 1024


/*字符串转义与反转义*/

int64_t convert_string_from_file(char *dest, const char *src, int64_t dest_len)
{
    if (dest == NULL || src == NULL)
        return -1;

    int64_t conv_len = 0;
    while (*src != '\0' && (conv_len < dest_len - 1))
    {
        if (*src == '\\')
        {
            src++;
            switch (*src)
            {
                case 'n':  *dest = '\n'; break;
                case 't':  *dest = '\t'; break;
                case '\"': *dest = '\"'; break;
                case '\\': default:
                    *dest = '\\';
            }
        }
        else
        {
            *dest = *src;
        }
        src++, dest++, conv_len++;
    }
    *dest = '\0';
    return conv_len;
}

int64_t unconvert_string_from_ulist(char *dest, const char *src, int64_t dest_len)
{
    if (dest == NULL || src == NULL)
        return -1;

    int64_t unconv_len = 0;
    while (*src != '\0' && unconv_len < dest_len - 1)
    {
        switch (*src)
        {
        case '\\':
            *(dest++) = '\\'; *dest = '\\';
            unconv_len++;
            break;
        case '\t':
            *(dest++) = '\\'; *dest = 't';
            unconv_len++;
            break;
        case '\n':
            *(dest++) = '\\'; *dest = 'n';
            unconv_len++;
            break;
        case '\"':
            *(dest++) = '\\'; *dest = '\"';
            unconv_len++;
        default:
            *dest = *src;
            break;
        }
        dest++, src++, unconv_len++;
    }
    *dest = '\0';
    return unconv_len;
}

/* 配置文件读取 */
// 第一阶段 - 工具函数

char *get_name_from_buffer(char *dest, char *buff)
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

int get_value_from_buffer(char **p_begin_out, char *buff)
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
        if (*buff == '\n') // 某一行结束但没有引号, 配置文件语法错误
        {
            *p_begin_out = NULL;
            return 0;
        }
        else if (*buff == '\\') // 避开转义字符的影响
            buff++;
        buff++;
    }

    return buff - *p_begin_out;
}

UniListObject ulist_config_to_lines(FILE *cfg_fp)
{
    /* 初始化行链表的特征结构体 */
    UniListObject parsed_text = {
        .head = (UListNode *)malloc(sizeof(UListNode)),
        .now = parsed_text.head,
        .length = 0,
    };
    *(parsed_text.head) = (UListNode){
        .line = (TextLine){
            .level = -1,
            .name = "HEAD",
            .value = NULL,
        },
        .parent = NULL,
        .child = NULL,
        .next = NULL,
    };
    UListNode *current = parsed_text.head;

    /* 初始化读取行缓冲区与转义行缓冲区 */
    char *buffer = (char *)calloc(4 * ULIST_MEM_BLOCK_SIZE, sizeof(char));
    char *conv_buffer = (char *)calloc(4 * ULIST_MEM_BLOCK_SIZE, sizeof(char));

    if (((size_t)(parsed_text.head) | (size_t)buffer | (size_t)conv_buffer | (size_t)cfg_fp) == NULL)
    {
        free(parsed_text.head), free(buffer), free(conv_buffer);
        return (UniListObject){NULL, NULL, 0};
    }

    // 行读取与解析
    char *ptmp = NULL;
    while (fgets(buffer, 4 * ULIST_MEM_BLOCK_SIZE * sizeof(char), cfg_fp) != NULL)
    {
        /* 初始化接受结构体. 不直接malloc是为了防止
         * 遇到无效行或注释行时内存泄漏或浪费资源. */
        UListNode tmp_node = {
            .line = {
                .level = get_str_level(buffer),
                .name = {0},
                .value = NULL,
            },
            .parent = NULL,
            .child = NULL,
            .next = NULL,
        };

        // ptmp前面的数据永远是用过的
        ptmp = buffer + tmp_node.line.level;
        /* 获取属性名 */
        if ((ptmp = get_name_from_buffer(tmp_node.line.name, ptmp)) == NULL)
        {
            tmp_node.line.name[0] = 0;
            continue;
        }

        current->next = (UListNode *)malloc(sizeof(UListNode));
        *(current->next) = tmp_node;

        /* 获取属性值 */
        int value_length = get_value_from_buffer(&ptmp, ptmp);
        if (value_length != 0)
        {
            current->next->line.value = (char *)malloc(sizeof(char) * MAX_DESCRIPTION_SIZE);
            memcpy(conv_buffer, ptmp, value_length);
            conv_buffer[value_length] = 0x0;
            if (convert_string_from_file(current->next->line.value, conv_buffer, MAX_DESCRIPTION_SIZE) == -1)
                return parsed_text;
        }
        current = current->next;
    }
    free(buffer), free(conv_buffer);
    return parsed_text;
}

/*配置文件解析: 第二阶段*/
UniListObject *ulist_generate_data_tree(UniListObject *line_list)
{
    if (line_list == NULL)
        return NULL;

    /*令所有节点成为头节点的子节点*/
    UListNode *line_list_head = line_list->head;
    line_list_head->child = line_list_head->next;
    line_list_head->child->parent = line_list_head;

    /*创建指针栈*/
    UListNode *content[16] = {line_list_head, NULL};
    UListNode **base = content + 1, **top = content + 1;

    UListNode *ptr_op = line_list_head->child, *ptr_prev = line_list_head;
    *top = ptr_op;
    while (ptr_op != NULL)
    {
        top = base + ptr_op->line.level;
        UListNode *ptmp = NULL;
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
        while (ptmp != NULL)
        {
            ptmp->next = ptr_op->next;
            ptmp = ptmp->parent;
        }
        *top = ptr_op;
        ptr_prev = ptr_op;
        ptr_op = ptr_op->next;
    }
    line_list->head->next = NULL;
    return line_list;
}

/* UniList的输出 */
int ulist_print_current_subtree(const UniListObject *parsed_text, FILE *__stream)
{
    int level = 0, nodes = 0;
    char buff[MAX_DESCRIPTION_SIZE];
    UListNode *ptr = parsed_text->now;
    do {
        print_n_tab(__stream, level);
        if (unconvert_string_from_ulist(buff, ptr->line.value, MAX_DESCRIPTION_SIZE) == -1)
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

int ulist_print(const UniListObject *parsed_text, FILE *__stream)
{
    if (parsed_text == NULL || parsed_text->head == NULL)
        return -1;

    UniListObject dump_text = (UniListObject){
        .now = parsed_text->head->child,
        .length = parsed_text->length,
    };
    int ret = 0;
    do {
        ret += ulist_print_current_subtree(&dump_text, __stream);
        dump_text.now = dump_text.now->next;
    } while (dump_text.now != NULL);
    return ret;
}

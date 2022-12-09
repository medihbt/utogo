#include <stdio.h>
#include "utask_io.h"

ParsedText *generate_data_tree(ParsedText *parsed_text)
{
    if (parsed_text == NULL)
    {
        return NULL;
    }
    /*令头节点的子节点指针指向下一节点，next指针指空，令下一级的父节点为HEAD*/
    ParsedNode *parsed_head = parsed_text->head;
    parsed_head->child = parsed_head->next;
    parsed_head->next = NULL;
    parsed_head->child->parent = parsed_head;

    /*创建指针栈*/
    ParsedNode *content[16] = {NULL};
    ParsedNode **base, **top;
    base = content + 1;
    top = content + 1;
    content[0] = parsed_head;

    /*对数据块进行操作*/
    ParsedNode *ptr_op = parsed_head->next, *ptr_prev = parsed_head->next;
    *top = ptr_op;
    while (ptr_op != NULL)
    {
        top = base + ptr_op->line.level;
        if (ptr_op->line.level > (ptr_prev->line.level + 1))
        {
            fprintf(stderr, "ERROR reported by function %s: Syntax error caused by too many indents of the file\n", __func__);
            return NULL;
        }

        ParsedNode *ptmp;
        switch ((ptr_op->line.level) - (ptr_prev->line.level))
        {
        case 1:
            ptr_op->parent = ptr_prev;
            ptr_prev->child = ptr_op;
            ptr_prev->next = ptr_op->next;
            /*以上建立父子关系*/
            ptmp = ptr_prev;
            break;
        case 0:
            ptr_op->parent = ptr_prev->parent;
            ptr_prev->parent->next = ptr_op->next;
            /*以上建立父子关系*/
            ptmp = ptr_prev->parent;
            break;
        default:
            ptmp = ptr_prev;
            int n = (ptr_op->line.level) - (ptr_prev->line.level);
            for (int i = 0; i < n; i++)
            {
                ptmp = ptmp->parent;
            }
            while (ptmp != parsed_head)
            {
                ptmp->next = ptr_op->next;
                ptmp = ptmp->parent;
            }
            top = ptr_op;
            ptr_prev = ptr_op;
            ptr_op = ptr_op->next;
            break;
        }
    }
    return parsed_text;
}
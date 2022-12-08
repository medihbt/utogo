#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// #include "cross_platform.h"
#include "utask_struct.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*对象: 文本每一行的抽象形式，既可以组成链表，又可以组成树结构*/
/*每一行的单元*/
typedef struct
{
    int level;      //缩进级别
    char name[256]; //属性名
    char *value;    //属性值
} TextLine;

/* 结构体: 行链表节点 */
typedef struct __parsed
{
    TextLine line;
    struct __parsed *parent; // 指向父节点, 类似于最接近的"主干"
    struct __parsed *child;  // 指向子节点
    struct __parsed *next;   // 指向同一级的下一个节点
} ParsedNode;

/* 结构体: 拆分链表的特征结构体
 * 
 */
typedef struct
{
    ParsedNode *head;   // 头节点指针
    ParsedNode *now;    // 参考用的当前节点
    int length;         // 链表长度
} ParsedText;


/* 一些杂项内联函数与宏定义函数 */

/*内联函数: 打印n个tab字符
 *          (编译时插入调用者，写在头文件里)
 *参数: 配置文件结构体指针, Tab数量*/
static inline void print_n_tab(FILE *outfile, int n)
{
    for (int i = 0; i < n; i++)
        fputc('\t', outfile);
}

/*内联函数: 统计每一行的缩进级别
 *参数: 字符串
 *返回: 缩进级别*/
static inline int get_str_level(char *str)
{
    char *tmp = str;
    while (*tmp == '\t')
        tmp++;
    return tmp - str;
}

/* 清单文件的操作函数 */

/* 函数: 读入清单文件并拆成小行
 * 参数: 清单文件名
 * 返回: 拆分好的链表*/
ParsedText parse_config_to_lines(char *fileName);

#ifdef __cplusplus
}
#endif
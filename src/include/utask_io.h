#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// #include "cross_platform.h"
#include "utask_struct.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_DESCRIPTION_SIZE 3072

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

/* 宏: 找到节点树的同级第一个节点 */
#define GetFirstInChilds(parsed_node) ((parsed_node)->parent->child)

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

/* 函数: 把拆出来的行链表组织成语义树
 * 参数: 行链表
 * 返回: 重组得到的语义树指针，NULL或最高4位十六进制为F则表示出错*/
ParsedText *generate_data_tree(ParsedText *parsed_text);

/* 函数: 改变当前的节点名称为第node_order + 1个node_name.用法类似于cd命令.
 * 参数: 重组得到的语义树指针, 要切换的节点的名称, 同名节点的顺序
 *       [注] 1. 返回上一级节点请使用"#.."而非"..",因为可能会有叫作".."的节点.
 *            2. 类似的, 返回头节点请使用"#/"或者"#HEAD".
 *            3. 第一个节点的node_order为0, 以此类推.
 *            4. 调用一次该函数不能连续切换多次节点, 即没有与命令"cd ../a/b/c"等价的操作
 * 返回: 成功则返回找到的节点指针, 失败则返回NULL. */
ParsedNode *change_current_node(ParsedText *parsed_text, const char *node_name, int node_order);

/* 函数: 读取整理好的文本树, 转化为Tasklist链表
 * 参数: 构造好的语义树指针
 * 返回: 构造好的TaskList */
TaskList data_tree_to_tasklist(ParsedText *data_tree);

/*以下函数未完成*/
/* 函数: 销毁语义树
 * 参数: 指向语义树的指针
 * 返回: bool成功或失败 */
bool destory_data_tree(ParsedText *data_tree);

/* 函数: 根据结构体内容写回文本文件
 * 参数: 任务清单结构体
 * 返回: int 0表示成功, -1表示失败*/
int write_tasklist(TaskList tasklist);

#ifdef __cplusplus
}
#endif
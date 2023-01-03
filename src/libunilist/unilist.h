/*unilist.h -- UniList文件的解析接口*/
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

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
    ParsedNode *now;    // 当前节点, pivate
    int length;         // 链表/语义树的节点个数
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

/*字符串操作函数*/

/*函数: 将配置文件里的字符串转义成正常字符串. 转义标准见文档.
 *参数: 目标字符串, 源字符串, 最大长度
 *返回: 转义后字符串的大小, 返回-1则表示失败*/
int64_t convert_string_from_file(char *dest, const char *src, int64_t dest_len);

/*函数: 将任务清单的字符串反转义成配置文件里的字符串.
 *参数: 目标字符串, 源字符串, 最大长度
 *返回: 转义后字符串的大小, 返回-1则表示失败*/
int64_t unconvert_string_from_tasklist(char *dest, const char *src, int64_t dest_len);


/* 清单文件读取接口 */

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

/* 函数: 在当前节点下附加子节点, 子节点始终附加到最后一个
 * 参数: 语义树指针, 子节点名称, 子节点值
 * 返回: 成功/失败 */
bool append_child_node(ParsedText *data_tree, const char *name, const char *value);

/* 函数: 打印当前节点及其所有子节点构成的子树到目标文件
 * 参数: 重组完成的语义树, 目标文件结构体指针
 * 返回: 打印节点的数量 */
int u_print_current_subtree(const ParsedText *parsed_text, FILE *__stream);

/* 函数: 打印语义树到目标文件
 * 参数: 重组完成的语义树, 目标文件结构体指针
 * 返回: 打印节点的数量 */
int u_print_data_tree(const ParsedText *parsed_text, FILE *__stream);

/* 函数: 把当前节点的所有下一级子节点串成数组, 类似于ls
 * 参数: 重组完成的链表
 * 返回: 节点数组的首元素指针 */
TextLine *u_list_current_subnode(const ParsedText *parsed_text);

/* 函数: 销毁语义树
 * 参数: 指向语义树的指针
 * 返回: bool成功或失败 */
bool destory_data_tree(ParsedText *data_tree);

#ifdef __cplusplus
}
#endif

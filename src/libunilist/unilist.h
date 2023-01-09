/** @file unilist.h -- UniList文件的解析接口
  * @author Medi H.B.T.
  * @class UniListObject
  * @copyright Copyright (c) 2022 - 2023 Imagine Studio PBLF Team.
  * This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
  * @version 0.0.1
  */
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


/** @name UniListObject 对象
  * @brief UniList的数据表现形式, 包括3个结构体与一些方法. */

/** @struct TextLine
 * @brief 每一行的单元 */
typedef struct TextLine
{
    int level;      ///< 缩进级别
    char name[256]; ///< 属性名
    char *value;    ///< 属性值
} TextLine;

/** @struct UListNode
 * @brief 行链表节点 */
typedef struct UListNode
{
    TextLine line;
    struct UListNode *parent; ///< 指向父节点, 类似于最接近的"主干"
    struct UListNode *child;  ///< 指向子节点
    struct UListNode *next;   ///< 指向同一级的下一个节点
} UListNode;

/** @struct UniListObject
 * @brief 拆分链表的特征结构体 */
typedef struct UniListObject
{
    /* public */
    UListNode *head;   ///< 头节点指针
    /* private */
    UListNode *now;    ///< 当前节点
    int length;        ///< 链表/语义树的节点个数
} UniListObject;


/* 一些杂项内联函数与宏定义函数 */

/* 宏: 找到节点树的同级第一个节点 */
#define GetFirstInChilds(parsed_node) ((parsed_node)->parent->child)

/** @brief 打印n个tab字符
  *          (编译时插入调用者，写在头文件里)
  * @param outfile 配置文件结构体指针
  * @param n Tab数量
  * @return 无 */
static inline void print_n_tab(FILE *outfile, int n)
{
    for (int i = 0; i < n; i++)
        fputc('\t', outfile);
}

/** 内联函数: 统计每一行的缩进级别
  * @param str 字符串
  * @return int 缩进级别*/
static inline int get_str_level(char *str)
{
    char *tmp = str;
    int str_level = 0;
    char isspace_flag = 0;
    do {
        if (*tmp == '\t')
            isspace_flag = 1, tmp++, str_level += 4;
        else if (*tmp == ' ')
            isspace_flag = 1, tmp++, str_level++;
        else
            isspace_flag = 0;
    } while (isspace_flag);
    
    return (str_level / 4);
}


/* UniList转义 */

/**
 * @brief  将配置文件里的字符串转义成正常字符串. 转义标准见文档.
 * @param  dest     目标字符串
 * @param  src      源字符串
 * @param  dest_len 转义的最大长度
 * @return 转义后字符串的大小, 返回-1则表示失败*/
int64_t convert_string_from_file(char *dest, const char *src, int64_t dest_len);

/**
 * @brief  将任务清单的字符串反转义成配置文件里的字符串.
 * @param  dest 目标字符串
 * @param  src 源字符串
 * @param  dest_len 最大长度
 * @return 转义后字符串的大小, 返回-1则表示失败*/
int64_t unconvert_string_from_ulist(char *dest, const char *src, int64_t dest_len);


/*! @htmlonly <h3>清单文件的构造函数</h3> */

/** @fn ulist_new_object
 * @brief  创建一个空清单结构体
 * @param  void
 * @return 指向空结构体的指针
 * @sa     ulist_object_from_file
 * @sa     ulist_object_from_string */
UniListObject *ulist_new_object(void);

/** @fn
 * @brief  从ulist文件读取一个清单结构体
 * @param  list_fp 指向配置文件的FILE指针
 * @return 指向UniList结构体的指针
 * @sa     ulist_object_from_string */
UniListObject *ulist_object_from_file(FILE *list_fp);

/** @fn
 * @brief  从ulist文件读取一个清单结构体
 * @param  ulist_str 包含UniList对象的字符串
 * @return 指向UniList结构体的指针
 * @sa     ulist_object_from_file */
UniListObject *ulist_object_from_string(const char *ulist_str);

// ulist_object_from_file的几个阶段

/** @fn
 * @brief  读入清单文件并拆成行链表(1)
 * @param  cfg_fp 指向清单文件结构体的指针
 * @return 拆分好的链表
 * @sa     ulist_string_to_lines */
UniListObject ulist_config_to_lines(FILE *cfg_fp);

/** @fn
 * @brief 读入字符串并拆成行链表(1)
 * @remark 未实现
 * @param src 源字符串
 * @return 拆分好的行链表 */
UniListObject ulist_string_to_lines(const char *src);

/** @fn
 * @brief 把行链表组织成语义树(2)
 * @param line_list 从文件读出的行链表
 * @return 重组得到的语义树指针，NULL或最高4位十六进制为F则表示出错*/
UniListObject *ulist_generate_data_tree(UniListObject *line_list);


/* UniList的操作函数 */

/**
 * 函数: 把当前节点的所有下一级子节点串成数组, 类似于ls
 * @remark 未实现
 * 参数: 重组完成的链表
 * 返回: 节点数组的首元素指针 */

/** @fn
 * @brief 打印语义树到目标文件
 * @param parsed_text 重组完成的语义树
 * @param __stream 目标文件结构体指针
 * 返回: 打印节点的数量 */
int ulist_print(const UniListObject *parsed_text, FILE *__stream);

/**
 * @brief  打印当前节点及其所有子节点构成的子树到目标文件
 * @param  parsed_text 重组完成的语义树
 * @param  __stream 目标文件结构体指针
 * @return 打印节点的数量 */
int ulist_print_current_subtree(const UniListObject *parsed_text, FILE *__stream);

/**
 * @brief 改变当前的节点名称为第node_order + 1个node_name.用法类似于cd命令.
 * @param parsed_text 指向UniList结构体的指针
 * @param node_name   要切换的节点名称
 * @param node_order  同名节点的顺序
 * @warning   1. 返回上一级节点请使用"#.."而非"..",因为可能会有叫作".."的节点.
 * @warning   2. 类似的, 返回头节点请使用"#/"或者"#HEAD".
 * @warning   3. 第一个节点的node_order为0, 以此类推.
 * @warning   4. 调用一次该函数不能连续切换多次节点, 即没有与命令"cd ../a/b/c"等价的操作
 * @return 成功则返回找到的节点指针, 失败则返回NULL. */
UListNode *ulist_change_current_node(UniListObject *parsed_text, const char *node_name, int node_order);

/**
 * @brief  在当前节点下附加子节点, 子节点始终附加到最后一个
 * @param  data_tree 语义树指针
 * @param  name 子节点名称
 * @param  value 子节点值
 * @return 成功为true, 失败为false */
bool ulist_append_child_node(UniListObject *data_tree, const char *name, const char *value);

/**
 * @brief 在data_tree的当前节点后附加同级节点
 * @param data_tree UniList对象
 * @param name      插入节点的名称
 * @param value     插入节点的值
 * @return 指向插入的节点的指针, 插入失败时返回NULL*/
UListNode *ulist_insert_friend_node(UniListObject *data_tree, const char *name, const char *value);

/* 析构函数: */
/**
 * @brief 销毁语义树
 * @param data_tree 指向语义树的指针
 * @return 成功或失败 */
bool ulist_destory_object(UniListObject *data_tree);

#ifdef __cplusplus
}
#endif

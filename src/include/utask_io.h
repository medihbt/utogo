#pragma once

#ifdef __cplusplus
extern "C" {
#endif

//#include "utask_timer.h"
#include "utask_struct.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../libunilist/unilist.h"

/* 函数: 读取整理好的文本树, 转化为Tasklist链表
 * 参数: 构造好的语义树指针
 * 返回: 构造好的TaskList */
TaskList data_tree_to_tasklist(UniListObject *data_tree);

/*函数: 读取清单文件, 生成任务链表
 *参数: 文件名
 *返回: 任务链表的特征结构体 */
TaskList new_tasklist(char *list_file_name);

/* 函数: 根据结构体内容写回文本文件. 如果原本的文件存在，则清空重写.
 * 参数: 任务清单结构体, 要写入的文件
 * 返回: int 0表示成功, -1表示失败*/
int write_tasklist(TaskList *tasklist, const char *filename);

#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include "../../src/include/utask_io.h"
#include "../../src/include/utask_struct.h"

#define _UTASK_DEBUG_INCDEC 0
#define _UTASK_DEBUG_SEARCH 0
#define _UTASK_DEBUG_SORT 0

bool inputTaskInfo(TaskInfo *pinfo)
{
    if (pinfo == NULL)
        return false;
    puts("测试输入: \n"
         "typedef struct\n"
         "{\n"
         "    int t_id;           // ID\n"
         "    bool finished;      // 是否完成\n"
         "    bool isNearArrive;  // 是否临近\n"
         "    int ttype;          // 类型, 取值见enum UTask_Type\n"
         "    char name[256];     // 任务名称\n"
         "    char *desciption;   // 任务描述\n"
         "    int t_duedate_type; // 指定什么时候到期, 取值见enum UTask_DueDate_Type\n"
         "    int t_duedate[3];   // 到期日期(格式YY-MM-DD), 到期类型为_CIRCULATE_WEEKLY时为开始日期\n"
         "    int t_duetime[3];   // 到期时间(格式hh:mm:ss)\n"
         "    int time_ahead[3];  // 提前多久提醒(格式hh:mm:ss)\n"
         "    void *priv_data;    // 私有数据, 根据ttype决定类型\n"
         "} TaskInfo;\n");
    if (scanf("%d%d%d%d%s%s%d%d%d%d%d%d%d%d%d%d",
              &(pinfo->t_id), &(pinfo->finished), &(pinfo->isNearArrive),
              &(pinfo->ttype), pinfo->name, pinfo->desciption,
              &(pinfo->t_duedate_type),
              &(pinfo->t_duedate[0]), &(pinfo->t_duedate[1]), &(pinfo->t_duedate[2]),
              &(pinfo->t_duetime[0]), &(pinfo->t_duetime[1]), &(pinfo->t_duetime[2]),
              &(pinfo->time_ahead[0]), &(pinfo->time_ahead[1]), &(pinfo->time_ahead[2])) == 16)
        return true;
    return false;
}

int main(int argc, char *argv[])
{
#ifndef __linux__
    puts("This program can only be run on Linux.");
    return 0;
#else
    if (argc < 2)
    {
        puts("测试主函数 用法: ");
        printf("%s [配置文件名]\n\n", argv[0]);
        return 0;
    }

    /*load tasklist from file*/
    TaskList tasklist = new_tasklist(argv[1]);
    if (tasklist.head == NULL)
        return 0;
    write_tasklist(&tasklist, "/dev/stdout");

    /* 检查Tasklist是否完整 */
    printf("tasklist.length is %ld before recounting.\n", tasklist.length);
    int64_t tasklen = tasklist_length(&tasklist);
    printf("The real length is %ld.\n", tasklen);

    /* 增删查改相关 */
#if _UTASK_DEBUG_INCDEC == 1   // 增加 & 删除
    TaskInfo taskinfo = (TaskInfo){
        .desciption = (char *)malloc(MAX_DESCRIPTION_SIZE),
        .priv_data = NULL,
    };
    inputTaskInfo(&taskinfo);
    /*Legacy, tasklist.length不变*/
    utask_insert(tasklist.head, taskinfo, 1);
    puts("\033[01mLegacy, tasklist.length不变\033[0m");
    write_tasklist(&tasklist, "/dev/stdout");
    utask_delet_one_node(tasklist.head, taskinfo.t_id);
    /*New, 还未使用*/
    printf("%d\n", utask_insert_f(&tasklist, taskinfo, -1));
    puts("\033[01mNew, 还未使用\033[0m");
    write_tasklist(&tasklist, "/dev/stdout");
    printf("\033[01m测试tasklist\033[0m: "
           "length=%ld AND Max ID=%ld\n",
           tasklist.length, tasklist.max_task_id);
#endif
#if _UTASK_DEBUG_SEARCH == 1
    // 搜索 & 排序
    TaskNode *node = search_node_by_id(tasklist.head, taskinfo.t_id);
    printf("task:\n"
           "	t_id: \"%d\"\n"
           "	finished: \"%d\"\n"
           "	type: \"%d\"\n"
           "	name: \"%s\"\n"
           "	description: \"%s\"\n"
           "	t_duedate_type: \"%d\"\n"
           "	t_duedate: \"%d-%02d-%02d\"\n"
           "	t_duetime: \"%02d-%02d-%02d\"\n"
           "	time_ahead: \"%02d-%02d-%02d\"\n"
           "	private:\n"
           "		NULL:\n",
           node->task.t_id, node->task.finished, node->task.ttype,
           node->task.name, node->task.desciption, node->task.t_duedate_type,
           node->task.t_duedate[0], node->task.t_duedate[1], node->task.t_duedate[2],
           node->task.t_duetime[0], node->task.t_duetime[1], node->task.t_duetime[2],
           node->task.time_ahead[0], node->task.time_ahead[1], node->task.time_ahead[2]);
#endif
#if _UTASK_DEBUG_SORT == 1
    utask_sort_by_time(&tasklist);
    puts("排序完后: ");
    write_tasklist(&tasklist, "/dev/stdout");
    printf("%d %d\n",
           cmp_node_by_datetime(search_node_by_id(tasklist.head, 1), search_node_by_id(tasklist.head, 2)),
           cmp_node_by_datetime(search_node_by_id(tasklist.head, 3), search_node_by_id(tasklist.head, 4)));
#endif

    delet_all(&tasklist.head);
    return 0;
#endif
}
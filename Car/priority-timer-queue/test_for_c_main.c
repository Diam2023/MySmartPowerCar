/**
 * @file main.c
 * @brief 
 * @author monoliths (monoliths-uni@outlook.com)
 * @version 1.0
 * @date 2022-01-02
 * 
 * *********************************************************************************
 * 
 * @note version:1.0
 * @description: identify 
 * 
 * *********************************************************************************
 */
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdint.h>

#include "priority_timer_queue_func.h"

extern queue_node_type *queue_timer_nodes;

typedef struct test_structure
{
    int a;
    uint32_t d;
} test_structure;

void *func_say_1(void *td)
{
    if (td == NULL)
    {

        printf("return: 1\n");
    }
    else
    {
        test_structure *ts = (test_structure *)td;
        printf("%d, %d\n", ts->a, (int)ts->d);
    }

    return td;
}

void func_say_2()
{
    printf("return: 2\n");
}

void func_say_3()
{
    printf("return: 3\n");
}

void func_say_4()
{
    printf("return: 4\n");
}

void showTimers()
{
    for (size_t i = 0; i < size(); i++)
    {
        printf("index: %d size: %d\n", (int)i, (int)size());
        printf("index: %d timer: %d\n", (int)i, (int)queue_timer_nodes[i]._timer);
        printf("--------------------------------------- show timers end \n");
    }
}

void timerRunningCount(int i_)
{
    for (size_t i = 0; i < i_; i++)
    {
        timer_running();
    }

    printf("running ed: %d\n", i_);
}

int main()
{
    init_priority_queue();

    test_structure *ts;

    ts = (test_structure *)calloc(1, sizeof(test_structure));

    ts->a = 1;
    ts->d = 0x92;

    push_node_release(
        create_timer_node((node_func_type)&func_say_2, 0, 200, NULL));

    // queue_node_type *tp;
    push_node_release(
        create_timer_node((node_func_type)&func_say_2, 0, 200, NULL));
    push_node_release(
        create_timer_node((node_func_type)&func_say_1, 0, 300, NULL));
    push_node_release(
        create_timer_node((node_func_type)&func_say_4, 0, 600, NULL));
    push_node_release(
        create_timer_node((node_func_type)&func_say_2, 0, 200, NULL));
    push_node_release(
        create_timer_node((node_func_type)&func_say_1, 0, 300, NULL));
    push_node_release(
        create_timer_node((node_func_type)&func_say_4, 0, 600, NULL));
    push_node_release(
        create_timer_node((node_func_type)&func_say_2, 0, 200, NULL));
    push_node_release(
        create_timer_node((node_func_type)&func_say_1, 0, 300, NULL));
    push_node_release(
        create_timer_node((node_func_type)&func_say_4, 0, 600, NULL));
    push_node_release(
        create_timer_node((node_func_type)&func_say_2, 0, 200, NULL));
    push_node_release(
        create_timer_node((node_func_type)&func_say_1, 0, 300, NULL));
    push_node_release(
        create_timer_node((node_func_type)&func_say_4, 0, 600, NULL));
    push_node_release(
        create_timer_node((node_func_type)&func_say_2, 0, 200, NULL));
    push_node_release(
        create_timer_node((node_func_type)&func_say_1, 0, 300, NULL));
    push_node_release(
        create_timer_node((node_func_type)&func_say_4, 0, 600, NULL));

    // tp = find_node_by_function((node_func_type)&func_say_1);

    // if (tp != NULL)
    // {
    //     printf("%d\n", (int) tp->_timer);
    //     // tp->_timer = 100;
    //     tp->_enabled = 0;

    //     erase_node(tp);
    // }

    run_timer_node();

    showTimers();

    timerRunningCount(101);

    showTimers();

    run_timer_node();

    showTimers();

    timerRunningCount(120);

    run_timer_node();

    push_node_release(
        create_timer_node((node_func_type)&func_say_2, 0, 200, NULL));
    push_node_release(
        create_timer_node((node_func_type)&func_say_1, 0, 100, NULL));
    push_node_release(
        create_timer_node((node_func_type)&func_say_4, 0, 50, NULL));

    timerRunningCount(120);
    showTimers();
    run_timer_node();

    run_inner_timer_node();

    timerRunningCount(120);
    showTimers();
    run_inner_timer_node();
    showTimers();
    run_timer_node();
    timerRunningCount(120);
    showTimers();
    run_timer_node();
    run_inner_timer_node();
    timerRunningCount(120);
    showTimers();
    run_inner_timer_node();
    run_timer_node();

    free(ts);

    // queue_node_type *tp;

    // tp = find_node_by_function((node_func_type)&func_say_1);

    // if (tp != NULL)
    // {
    //     printf("%d\n", (int) tp->_timer);
    //     // tp->_timer = 100;
    //     tp->_enabled = 0;

    //     erase_node(tp);
    // }

    deallocate_queue_memory();

    // showTimers();
    // printf("%d\n", (int)queue_timer_node_element_size);
    // printf("%d\n", (int)size());

    // showTimers();
    // showTimers();
    // showTimers();

    // free(ts);
    // thread th2(thread_timer);//第一个参数为函数名，第二个参数为该函数的第一个参数，如果该函数接收多个参数就依次写在后面。此时线程开始执行。

    // th2.join(); //此时主线程被阻塞直至子线程执行结束。

    // while (true)
    // {
    //     // 运行定时程序
    //     execute_timer_node();
    // }
}

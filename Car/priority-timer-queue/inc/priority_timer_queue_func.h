/**
 * @file priority_timer_queue_func.h
 * 
 * @brief priority timer queue function header
 * @author monoliths (monoliths-uni@outlook.com)
 * @version 1.0
 * @date 2022-01-03
 * 
 * *********************************************************************************
 * 
 * @note version:1.0
 * @description: 基础QUEUE方法.
 * 
 * @note version:1.1
 * @description: 功能性扩展
 * 
 * * @details 添加了处理返回值的回调函数.
 * 
 * @note version: 1.2
 * @description: bug
 * 
 * * @details 解决不能实时更改timer问题
 * 
 * 
 * *********************************************************************************
 */
#ifndef PRIORITY_TIMER_QUEUE_FUNC_H
#define PRIORITY_TIMER_QUEUE_FUNC_H

#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @brief 数据初始长度
 */
#define DEFAULT_LENGTH 10

/**
 * @brief 设置数据增长步长
 */
#define DEFAULT_INCREASED_LENGTH 10

#define TOP_NODE_INDEX 0
#define DEFAULT_SIZE_ZERO 0

#define NODE_SIZE sizeof(queue_node_type)
#define ARGS_SIZE(args__) sizeof(*args__)

#define ALLOC_NODE() (queue_node_type *)calloc(1, NODE_SIZE)
#define ALLOC_NODES(size__) (queue_node_type *) \
    calloc(size__, NODE_SIZE)

#ifndef UINT32_MAX
#define UINT32_MAX (4294967295U)
#endif

#ifndef UINT8_MAX
#define UINT8_MAX (255)
#endif

#define QUEUE_TIMER_TYPE_MAX UINT32_MAX

/**
 * @brief 节点标志的基本类型
 */
typedef unsigned char uint8_t;

/**
 * @brief 队列中储存节点数量的类型
 */
// typedef unsigned long size_t;

/**
 * @brief 储存定时器周期数的数据类型
 */
typedef unsigned int queue_timer_t;

/**
 * @brief 节点函数类型的指针
 */
typedef void *(*node_func_type)(void *);

/**
 * @brief 队列节点的类型
 */
typedef struct queue_node_type
{
    /**
     * @brief 等待timer个时钟周期后执行_function
     */
    queue_timer_t _timer; // sizeof 8

    /**
     * @brief 定时执行的函数指针
     */
    node_func_type _function; // sizeof 4

    /**
     * @brief 如果不为零则为使能
     */
    uint8_t _enabled;

    /**
     * @brief 该值为循环次数，如果为0则不循环 
     * 循环计数是否启用取决于_count_loop的值时候不为0
     * 当_loop为uint8最大值时无限循环
     */
    uint8_t _loop;

    /**
     * @brief 如果_loop为不为0且_count_loop不为零，则_loop_timer为下一次循环的初始等待周期数
     */
    queue_timer_t _loop_timer;

    /**
     * @brief 定实执行函数的参数
     */
    void *_args;

    /**
     * @brief 优先级，优先级越靠近0则在_timer相等的情况下节点约靠近队首 默认为0xFF
     */
    uint8_t _priority;

    /**
     * @brief 如果为1则在中断内部执行
     */
    uint8_t _inner;

    // // /**
    // // @brief 该指针指向运行后的结果. 如果没有注册结果处理指针，该节点会保留在该节点中且不使能，请即时处理
    // // @sense: 1.1
    // // */
    // // void *_result;

    /**
     * @brief 注册的结果指针处理函数
     * @sense: 1.1
     * @details 使用#register_result_performance函数将该属性添加到节点。
     */
    node_func_type _performance_func;
} queue_node_type;

/**
 * @brief 初始化10个可容纳节点的数组 
 */
void init_priority_queue();

/**
 * @brief 增加可容纳的节点数量
 */
void increase_nodes();

/**
 * @brief 销毁队列并释放内存
 */
void deallocate_queue_memory();

/**
 * @brief 清理node
 * @param  node_            待执行node
 */
void deallocate_node(queue_node_type *node_);

/**
 * @brief 按照每个节点的定时器周期数进行排序
 */
void rank_timer();

/**
 * @brief 使用函数指针找到队列中的节点
 * @param  func_            函数指针
 * @return queue_node_type* 节点指针
 */
queue_node_type *find_node_by_function(node_func_type func_);

/**
 * @brief 复制节点node_到队列中
 * @param  node_            queue_node_type类型节点的指针
 * @return queue_node_type* queue_node_type类型节点的指针
 */
queue_node_type *__push_node(queue_node_type *node_);

/**
 * @brief 复制节点node_到队列中，并释放node_的内存
 * @param  node_            queue_node_type类型节点的指针
 */
void push_node_release(queue_node_type *node_);

/**
 * @brief 当其定时器周期数不为零时使队列中所有的节点周期数+1
 */
void timer_running();

/**
 * @brief 弹出队列中优先级最高的（第一个）节点
 * @return queue_node_type* 节点的指针
 */
queue_node_type *pop_node();

/**
 * @brief 
 * @param  index_           desc
 * @return queue_node_type* @c 
 */
queue_node_type *pop_index_node(size_t index_);

/**
 * @brief 如果队列中存在node_，则从队列中删除它
 * @param  node_            指向node_的指针
 */
void erase_node(queue_node_type *node_);

/**
 * @brief 执行并清理node
 * @param  node_            node
 */
void execute_node(queue_node_type *node_);

/**
 * @brief 运行当前定时器周期数为零的所有节点中的函数
 */
void run_timer_node();

/**
 * @brief 运行当前定时周期数为零且为中断内部执行的所有节点中的函数
 */
void run_inner_timer_node();

/**
 * @brief 返回队列中的元素数量
 * 
 * @return 队列中的元素数量
 */
size_t size();

/**
 * @brief 判断当前队列时候为空
 * 
 * @return 如果当前队列为空则返回0
 */
uint8_t empty();

/**
 * @brief 设置node_是否启用
 * @param  enabled_         若为0则不启用，1为启用
 * @param  node_            节点的指针
 * @return queue_node_type* 返回操作节点的指针
 */
queue_node_type *set_enabled(uint8_t enabled_, queue_node_type *node_);

/**
 * @brief 设置定时时间
 * @param  timer_           timer_ queue_timer_t类型的值
 * @param  node_            节点的指针
 * @return queue_node_type* 返回操作节点的指针
 */
queue_node_type *set_timer(queue_timer_t timer_, queue_node_type *node_);

/**
 * @brief 设置定时时间
 * @param  loop_            设置循环次数，0为关闭循环 UINT8_MAX为无限循环 若节点_loop_timer为0且_time不为0则设置_loop_timer的值为_timer的值
 * @param  node_            节点的指针
 * @return queue_node_type* 返回操作节点的指针
 */
queue_node_type *set_loop(uint8_t loop_, queue_node_type *node_);

/**
 * @brief 设置定时时间
 * @param  loop_timer_      timer_ queue_timer_t类型的值
 * @param  node_            节点的指针
 * @return queue_node_type* 返回操作节点的指针
 */
queue_node_type *set_loop_timer(queue_timer_t loop_timer_, queue_node_type *node_);

/**
 * @brief 设置优先级
 * @param  priority_        0的优先最高
 * @param  node_            节点的指针
 * @return queue_node_type* 返回操作的节点的指针
 */
queue_node_type *set_priority(uint8_t priority_, queue_node_type *node_);

/**
 * @brief 设置优先级
 * @param  args_             节点函数的参数
 * @param  node_            节点的指针
 * @return queue_node_type* 返回操作的节点的指针
 */
queue_node_type *set_args(void *args_, queue_node_type *node_);

/**
 * @brief 注册一个处理节点运行后返回值的函数.
 * @param  func_            节点结果处理函数指针
 * @param  node_            节点的指针
 * @sense: 1.1
 */
void register_result_performance(node_func_type func_, queue_node_type *node_);

/**
 * @brief 创建node以便加入到队列
 * @param  node_func_       节点函数指针
 * @param  inner_           0为异步执行，即在调用run_timer_node()函数时执行
 * @param  enabled_         0为关闭节点执行会跳过排序
 * @param  timer_           经过timer_个时钟周期后执行
 * @param  loop_            如果启用计数循环，则该参数为第一次运行后循环运行的次数，0为不循环，最大值为无限循环
 * @param  loop_timer_      计数循环的时钟中断周期数
 * @param  priority_        该节点的函数在相同timer时执行的有限级，0为优先级最高。
 * @param  args_            等待执行函数的参数。
 * @param  performance_func_            结果处理函数
 * @return queue_node_type* 返回创建好的queue_node_type类型的指针。
 */
queue_node_type *__create_queue_node(node_func_type node_func_, uint8_t inner_, uint8_t enabled_, queue_timer_t timer_, uint8_t loop_, queue_timer_t loop_timer_, uint8_t priority_, void *args_, node_func_type performance_func_);

/**
 * @brief 创建一个默认优先级的定时node
 * @param  node_func_       节点函数指针
 * @param  inner_           若为0则在中断函数外部执行
 * @param  timer_           定时器周期数
 * @param  args_            等待执行函数的参数
 * @return queue_node_type* 返回创建的 {@link create_asynchronous_node} 指针，返回创建的queue_node_type指针 
 */
queue_node_type *create_timer_node(node_func_type node_func_, uint8_t inner_, queue_timer_t timer_, void *args_);

#ifdef __cplusplus
}
#endif

#endif // PRIORITY_TIMER_QUEUE_FUNC_H

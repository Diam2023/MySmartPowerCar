#include "priority_timer_queue_func.h"

/**
 * @brief 节点储存的数组
 */
queue_node_type *queue_timer_nodes;

/**
 * @brief 目前储存的节点个数
 */
volatile static size_t queue_timer_node_size;

/**
 * @brief 目前数组能储存的节点数
 */
volatile static size_t queue_timer_node_length;

void init_priority_queue()
{
    // 初始化为空指针
    queue_timer_nodes = NULL;

    // 分配默认内存
    queue_timer_nodes = ALLOC_NODES(DEFAULT_INCREASED_LENGTH);

    // 判断是否为空指针
    if (queue_timer_nodes == NULL)
    {
        // 可用堆大小不足
    }
    else
    {
        // 初始化队列节点个数以及分配的大小
        queue_timer_node_size = DEFAULT_SIZE_ZERO;
        queue_timer_node_length = DEFAULT_LENGTH;
    }
}
void increase_nodes()
{
    // 增加最大容纳大小
    queue_timer_node_length += DEFAULT_INCREASED_LENGTH;

    // 重新分配队列的大小，使其增加原来的加上步长个空间
    queue_node_type *queue_timer_nodes_ = (queue_node_type *)
        reallocarray(queue_timer_nodes, NODE_SIZE, queue_timer_node_length);
    if (queue_timer_nodes_ == NULL)
    {
        // 需要的空间大于所剩余的空间
        // 错误处理
    }
    else
    {
        // 使queue_timer_nodes指向queue_timer_nodes_
        queue_timer_nodes = queue_timer_nodes_;
    }
    // 解除指针引用
    queue_timer_nodes_ = NULL;
}

void deallocate_node(queue_node_type *node_)
{
    // 回收缓存数据的内存
    memset(node_, 0, NODE_SIZE);
    free(node_);
    node_ = NULL;
}

void deallocate_queue_memory()
{
    // 回收elements的内存
    memset(queue_timer_nodes, 0, queue_timer_node_length * NODE_SIZE);
    free(queue_timer_nodes);
    queue_timer_nodes = NULL;

    // 记零
    queue_timer_node_size = 0;
    queue_timer_node_length = 0;
}

void rank_timer()
{
    if (size() > 1)
    {
        queue_node_type *temp;
        // 分配临时内存用于交换内存数据
        temp = ALLOC_NODE();

        // queue_timer_t temp_timer = QUEUE_TIMER_TYPE_MAX;

        for (size_t i = (queue_timer_node_size - 1); i > 0; i--)
        {
            // 排序指标为节点的剩余时钟周期数_timer
            if (queue_timer_nodes[i]._timer < queue_timer_nodes[i - 1]._timer)
            {
                memmove(temp, (queue_timer_nodes + (i - 1)), NODE_SIZE);
                memmove((queue_timer_nodes + (i - 1)), (queue_timer_nodes + i), NODE_SIZE);
                memmove((queue_timer_nodes + i), temp, NODE_SIZE);
                memset(temp, 0, NODE_SIZE);
            }

            if ((queue_timer_nodes[i]._timer == queue_timer_nodes[i - 1]._timer) && (queue_timer_nodes[i]._priority != queue_timer_nodes[i - 1]._priority))
            {
                if (queue_timer_nodes[i]._priority > queue_timer_nodes[i - 1]._priority) // 优先级大于
                {
                    memmove(temp, (queue_timer_nodes + (i - 1)), NODE_SIZE);
                    memmove((queue_timer_nodes + (i - 1)), (queue_timer_nodes + i), NODE_SIZE);
                    memmove((queue_timer_nodes + i), temp, NODE_SIZE);
                    memset(temp, 0, NODE_SIZE);
                }
            }
        }

        // 释放临时内存
        deallocate_node(temp);
    }
}

queue_node_type *find_node_by_function(node_func_type func_)
{
    queue_node_type *temp_node_;
    temp_node_ = NULL;
    if (!empty())
    {
        for (size_t i = 0; i < size(); i++)
        {
            if (queue_timer_nodes[i]._function == func_)
            {
                temp_node_ = &queue_timer_nodes[i];
            }
        }
    }

    return temp_node_;
}

void push_node_release(queue_node_type *node_)
{
    free(__push_node(node_));
}

queue_node_type *__push_node(queue_node_type *node_)
{
    // 增加一个节点到队列中
    if ((queue_timer_node_size + 1) >= queue_timer_node_length)
    {
        // 但队列容纳不下的时候就扩容
        increase_nodes();
    }

    // 将节点数据复制到队列中
    memmove((queue_timer_nodes + queue_timer_node_size), node_, NODE_SIZE);
    (queue_timer_nodes + queue_timer_node_size)->_args = node_->_args;

    queue_timer_node_size++;

    // 排序
    rank_timer();

    return node_;
}

queue_node_type *pop_node()
{
    return pop_index_node(TOP_NODE_INDEX);
}

queue_node_type *pop_index_node(size_t index_)
{
    queue_node_type *temp_node_;

    temp_node_ = NULL;

    if (!empty() && index_ < size())
    {
        temp_node_ = ALLOC_NODE();

        memmove(temp_node_, (queue_timer_nodes + index_), NODE_SIZE);

        memset((queue_timer_nodes + index_), 0, NODE_SIZE);

        memmove((queue_timer_nodes + index_), (queue_timer_nodes + (index_ + 1)), ((queue_timer_node_size - index_) * NODE_SIZE));

        memset((queue_timer_nodes + (queue_timer_node_size - 1)), 0, NODE_SIZE);

        queue_timer_node_size--;

        rank_timer();
    }

    return temp_node_;
}

void erase_node(queue_node_type *node_)
{
    if (!empty())
    {
        // index 用于标记是队列中的哪一个需要移除
        int index = -1;
        // 遍历队列
        for (size_t i = 0; i < size(); i++)
        {
            if (&queue_timer_nodes[i] == node_)
            {
                // 符合条件则返回下标
                index = i;
                break;
            }
        }

        if (index != -1)
        {
            queue_node_type *temp = pop_index_node(index);

            deallocate_node(temp);
        }
    }
}

void execute_node(queue_node_type *node_)
{
    // 通过节点储存的参数数据来执行节点函数
    void *result = NULL;
    result = node_->_function(node_->_args);

    if (node_->_performance_func != NULL)
    {
        node_->_performance_func(result);
    }
    result = NULL;

    if (node_->_loop != 0)
    {
        if (node_->_loop != UINT8_MAX) // 循环定时执行loop次
        {
            node_->_loop--; // 计数器减一
        }
        // 循环和执行时重置计数周期并加入到队列
        if (node_->_timer == 0)
        {
            node_->_timer = node_->_loop_timer;
        }
        __push_node(node_);
    }

    // 满足清理条件

    deallocate_node(node_);
}

void run_timer_node()
{
    if (!empty())
    {
        size_t position_index = 0;
        size_t now_size = queue_timer_node_size;
        for (size_t i = 0; i < now_size; i++)
        {
            // 如果未使能则跳过
            if (queue_timer_nodes[position_index]._enabled == 0 || queue_timer_nodes[position_index]._inner != 0)
            {
                position_index++;
                continue;
            }
            if (queue_timer_nodes[position_index]._timer <= 0)
            {
                queue_node_type *temp_node_;
                // 取队列中top0的节点
                temp_node_ = pop_index_node(position_index);

                execute_node(temp_node_);
            }
            else
            {
                // 当定时器不为0时跳出循环
                break;
            }
        }
    }
}

void run_inner_timer_node()
{
    if (!empty())
    {
        size_t position_index = 0;
        size_t now_size = queue_timer_node_size;
        for (size_t i = 0; i < now_size; i++)
        {
            // 如果未使能或者没开启内部执行则跳过
            if (queue_timer_nodes[position_index]._inner == 0 || queue_timer_nodes[position_index]._enabled == 0)
            {
                position_index++;
                continue;
            }

            if (queue_timer_nodes[position_index]._timer <= 0)
            {
                // 取队列中top0的节点
                queue_node_type *temp = pop_index_node(position_index);

                execute_node(temp);
            }
            else
            {
                // 当定时器不为0时跳出循环
                break;
            }
        }
    }
}

inline void timer_running()
{
    if (!empty())
    {
        for (size_t i = 0; i < size(); i++)
        {
            // 在使能与定时周期未结束时运行
            if (queue_timer_nodes[i]._enabled != 0 && queue_timer_nodes[i]._timer > 0)
            {
                queue_timer_nodes[i]._timer--;
            }
        }
    }

    rank_timer();
}

size_t size()
{
    return queue_timer_node_size;
}

uint8_t empty()
{
    return (uint8_t)(queue_timer_node_size == 0);
}

queue_node_type *set_enabled(uint8_t enabled_, queue_node_type *node_)
{
    node_->_enabled = enabled_;
    return node_;
}

queue_node_type *set_timer(queue_timer_t timer_, queue_node_type *node_)
{
    node_->_timer = timer_;
    return node_;
}

queue_node_type *set_loop(uint8_t loop_, queue_node_type *node_)
{
    node_->_loop = loop_;
    // 若节点_loop_timer为0且_time不为0则设置_loop_timer的值为_timer的值
    if (node_->_loop_timer == 0 && node_->_timer != 0)
    {
        node_->_loop_timer = node_->_timer;
    }
    return node_;
}

queue_node_type *set_loop_timer(queue_timer_t loop_timer_, queue_node_type *node_)
{
    node_->_loop_timer = loop_timer_;
    return node_;
}

queue_node_type *set_priority(uint8_t priority_, queue_node_type *node_)
{
    node_->_priority = priority_;
    return node_;
}

queue_node_type *set_args(void *args_, queue_node_type *node_)
{
    node_->_args = args_;
    return node_;
}

void register_result_performance(node_func_type func_, queue_node_type *node_)
{
    node_->_performance_func = func_;
}

queue_node_type *__create_queue_node(node_func_type node_func_, uint8_t inner_, uint8_t enabled_, queue_timer_t timer_, uint8_t loop_, queue_timer_t loop_timer_, uint8_t priority_, void *args_, node_func_type performance_func_)
{
    queue_node_type *temp_node_;

    temp_node_ = ALLOC_NODE();

    temp_node_->_function = node_func_;

    temp_node_->_inner = inner_;

    temp_node_->_enabled = enabled_;

    temp_node_->_timer = timer_;

    temp_node_->_loop = loop_;

    temp_node_->_loop_timer = loop_timer_;

    temp_node_->_priority = priority_;

    temp_node_->_args = args_;

    temp_node_->_performance_func = performance_func_;

    return temp_node_;
}

queue_node_type *create_timer_node(node_func_type node_func_, uint8_t inner_, queue_timer_t timer_, void *args_)
{
    return __create_queue_node(
        node_func_,
        inner_,
        1,
        timer_,
        0,
        timer_,
        UINT8_MAX,
        args_,
        NULL);
}

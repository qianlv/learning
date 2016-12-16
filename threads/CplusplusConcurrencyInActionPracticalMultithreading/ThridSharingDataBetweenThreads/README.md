## Protecting a list with a mutex
[STM](https://zh.wikipedia.org/wiki/%E8%BD%AF%E4%BB%B6%E4%BA%8B%E5%8A%A1%E5%86%85%E5%AD%98)
##  Accidentally passing out a reference to prctected data
__Don’t pass pointers and references to protected data outside the scope of the lock, whether by
returning them from a function, storing them in externally visible memory, or passing them as
arguments to user-supplied functions.__

## Spotting race conditions inherent in interfaces
    ```
        stack<int> s;
        if (!s.empty())         // 1
        {
            int const value = s.top(); // 2
            s.pop();            // 3
            do_something(value);
        }
    ```
    即使数据结构的每个接口的是thread safe 也不能保证程序是 thread safe.
    例如: 上述代码中有 2 处 race conditions
    代码标记1处和2处, 1和2之间可能有另一个线程已经 pop, 导致 top 行为未定义. 解决方式: top 抛出异常, 不过这样　empty 显得多余.
    代码标记2处和3处, 有可能两个线程同时先后运行2处 top 获取的value 相同, 然后在同时运行3处的 pop, 导致一个值被获取2次, 另一个值被忽略.
    ```
        if (!s.empty())                     |       
                                            |   if (!s.empty())
        {                                   |   {
                                            |       int const value = s.top();
            int const value = s.top();      |
                                            |       s.pop();
            s.pop();                        |       
                                            |       do_something(value);
            do_something(value);            |   }
        }                                   |

    ```
    解决方式: 合并 top 和 pop, 这样也会其他问题, 如果合并后的 pop 返回时拷贝发生异常(如bad_alloc) 那么数据就丢失了, 这也是不可以接受的.
    1. 传递引用给 pop, 局限返回值可能不支持赋值构造函数
    ```
        std::stack<std::vector<int>> some_stack;
        std::vector<int> result;
        some_stack.pop(result);
    ```
    2. 保证 copy constructor 和 move constructor 不抛异常.
    3. 返回指针(shared_ptr), 但是相比 no-thread-safe 的原来在栈上分配内存变为在堆上(new).
## Deadlock
    1. 按顺序加锁 std::lock
    2. [lock hierachies to avoid deadlock](http://www.drdobbs.com/parallel/use-lock-hierarchies-to-avoid-deadlock/204801163), 就是给加等级, 加锁顺序必须又高等级到低等级

## 锁的粒度
    1. A lock should be held for only the minimum possible time needed to perform the required operations

## Protecting shared data during initialization
    1. Double-Checked Locking
    ```
        void undefined_behaviour_with_double_checked_locking()
        {
            if (!resource_ptr)
            {
                std::lock_guard<std::mutex> lk(resource_ptr);
                if (!resource_ptr)
                {
                    resource_ptr.reset(new some_resource);
                }
            }
            resource_ptr->do_something();
        }
    ```
    这种方式问题在于: `resource_ptr.reset(new some_resource)` 包含 3 步: 1. 分配内存 2. 调用构造函数 3. 赋值给 resource_ptr  
    cpu 乱序执行的时可能导致步骤 3 在步骤 2 之前, 那么可能别的线程拿到一个没有调用构造函数的 resource_ptr.
    2. std::call_once
    ```
        std::shared_prt<some_resource> resource_ptr;
        std::once_flag resource_flag;
        void init_resource()
        {
            resource_ptr.reset(new some_resource);
        }

        void foo()
        {
            std::call_once(resource_flag, init_resource);
            resource_ptr->do_something();
        }
    ```
    3. static, C++11 之后保证只有一个线程初始化
    ```
        class my_class;
        my_class& get_my_class_instance()
        {
            static my_class instance;
            return instance
        }
    ```
    

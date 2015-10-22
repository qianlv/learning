1. Introduction to Iterators and Generators
    略

2. Processing Data File
    1). Generators as a Pipeline
    2). 按管道的方式处理数据, 把一个大的问题分解, 迭代器(iteration)把管道连接起来.

        wwwlog = open('access-log')
        bytecolumn = (line.rsplit(None, 1)[1] for line in wwwlog)
        bytes = (int(x) for x in bytecolumn if x != '-')
        print "Total", sum(bytes)

   ``` 
    flow
    st=>start: access-log
    e=>end: sum()
    op1=>operation: bytecolumn
    op2=>operation: bytes

    st(right)->op1(right)->op2(right)->e
   ```

   3). Generator 优点: 没有使用大的临时list, 因此可以应用在大文件处理上

3. Fun with files and directories
    1). 使用Generator处理文件和目录的例子
    2), [fun with files and directories](https://github.com/qianlv/learning/blob/master/python/generator/fun_with_files_and_directories.py)

4. Parsing and Processing Data
    1). 数据处理
    2). [parsing and prcessing data](https://github.com/qianlv/learning/blob/master/python/generator/parsing_and_prcessing_data.py)

5. Processing Infinite Data
    1). 处理无限数据流, 类似"tail -f"
    2). [processing infinite data](https://github.com/qianlv/learning/blob/master/python/generator/processing_infinite_data.py)

6. Feeding the Pipeline
    1). 生成器(generator)管道(Pipeline) 需要数据流入的源头
    2). 上面提到都是基于文件, 此节包括了socket和Queue两个源.
    3). [feeding the pipeline](https://github.com/qianlv/learning/blob/master/python/generator/feeding_the_pipeline.py)

7. Extending the Pipeline
    1). 进程, 线程和机器间的Pipeline.
    2). [extending the pipeline](https://github.com/qianlv/learning/blob/master/python/generator/extending_the_pipeline.py)
        [netcons](https://github.com/qianlv/learning/blob/master/python/generator/netcons.py)
        [netprod](https://github.com/qianlv/learning/blob/master/python/generator/netprod.py)d

8. Fanning Out
    1). Pipeline内容流入多个Consumers
    2). 在Consumer内无法继续使用管道方式处理数据
    3). 多个数据源(Sources)处理: 串行, 并行
    4). 多路生成器(Multiplexing Generators)
    5). [fannng out](https://github.com/qianlv/learning/blob/master/python/generator/fanning_out.py)

9. Various Programming Tricks
    1). Creating Generators.
    2). Debug.
    3). Recording the last Item.
    4). Generators can be shut down using .close().
        In the generator, GeneratorExit is raised and can't be ignored.
        if you ignore GeneratorExit, you'll get RunTimeError.
    5). Can't a thread shutdown a generator running in a different thread?
        Answer: No
    6). You can't shutdown a generator with a signal.
    7). The only way to externally shutdown a generator would be to 
        instrument with a flag or some kind of check.
    8). [various programming tricks](https://github.com/qianlv/learning/blob/master/python/generator/various_programming_tricks.py)

10. Co-routines(协程)
    1). generators can receive value using .send().
    2). This form of generators is a "co-routines" or "reverse-generator".
    3). Coroutine Pipeling, Instead of being defining by iteration, it's
        defining by pushing values into the pipeling using .send()
        You can see this example to understand.
    4). [co-routines](https://github.com/qianlv/learning/blob/master/python/generator/co_routines.py)

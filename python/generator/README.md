### 1. Introduction to Iterators and Generators
    略

### 2. Processing Data File
    1. Generators as a Pipeline
    2. 按管道的方式处理数据, 把一个大的问题分解, 迭代器(iteration)把管道连接起来.
    3. Generator 优点: 没有使用大的临时list, 因此可以应用在大文件处理上

        wwwlog = open('access-log')
        bytecolumn = (line.rsplit(None, 1)[1] for line in wwwlog)
        bytes = (int(x) for x in bytecolumn if x != '-')
        print "Total", sum(bytes)

flow
st=>start: access-log
e=>end: sum()
op1=>operation: bytecolumn
op2=>operation: bytes

st(right)->op1(right)->op2(right)->e


### 3. Fun with files and directories
    * 使用Generator处理文件和目录的例子
    * [fun with files and directories](https://github.com/qianlv/learning/blob/master/python/generator/fun_with_files_and_directories.py)

### 4. Parsing and Processing Data
    * 数据处理
    * [parsing and prcessing data](https://github.com/qianlv/learning/blob/master/python/generator/parsing_and_prcessing_data.py)

### 5. Processing Infinite Data
    * 处理无限数据流, 类似"tail -f"
    * [processing infinite data](https://github.com/qianlv/learning/blob/master/python/generator/processing_infinite_data.py)

### 6. Feeding the Pipeline
    * 生成器(generator)管道(Pipeline) 需要数据流入的源头
    * 上面提到都是基于文件, 此节包括了socket和Queue两个源.
    * [feeding the pipeline](https://github.com/qianlv/learning/blob/master/python/generator/feeding_the_pipeline.py)

### 7. Extending the Pipeline
    * 进程, 线程和机器间的Pipeline.
    * [extending the pipeline](https://github.com/qianlv/learning/blob/master/python/generator/extending_the_pipeline.py)  
      [netcons](https://github.com/qianlv/learning/blob/master/python/generator/netcons.py)  
      [netprod](https://github.com/qianlv/learning/blob/master/python/generator/netprod.py)

### 8. Fanning Out
    * Pipeline内容流入多个Consumers
    * 在Consumer内无法继续使用管道方式处理数据
    * 多个数据源(Sources)处理: 串行, 并行
    * 多路生成器(Multiplexing Generators)
    * [fannng out](https://github.com/qianlv/learning/blob/master/python/generator/fanning_out.py)

### 9. Various Programming Tricks
    * Creating Generators.
    * Debug.
    * Recording the last Item.
    * Generators can be shut down using .close(). In the generator, GeneratorExit is raised and can't be ignored.  
      if you ignore GeneratorExit, you'll get RunTimeError.  
    * Can't a thread shutdown a generator running in a different thread?  Answer: No
    * You can't shutdown a generator with a signal.
    * The only way to externally shutdown a generator would be to instrument with a flag or some kind of check.
    * [various programming tricks](https://github.com/qianlv/learning/blob/master/python/generator/various_programming_tricks.py)

### 10. Co-routines(协程)
    * generators can receive value using .send().
    * This form of generators is a "co-routines" or "reverse-generator".
    * Coroutine Pipeling, Instead of being defining by iteration, it's defining by pushing values into the pipeling using .send(). You can see this example to understand.
    * [co-routines](https://github.com/qianlv/learning/blob/master/python/generator/co_routines.py)

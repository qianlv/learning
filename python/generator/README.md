6. Feeding the Pipeline
    生成器(generator)管道(Pipeline) 需要数据流入的源头
    上面提到都是基于文件, 此节包括了socket和Queue两个源.

7. Extending the Pipeline
    进程和机器间的Pipeline.

8. Fanning Out
    Pipeline内容流入多个Consumers
    在Consumer内无法继续使用管道方式处理数据
    多个数据源(Sources)处理: 串行, 并行
    多路生成器(Multiplexing Generators)

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

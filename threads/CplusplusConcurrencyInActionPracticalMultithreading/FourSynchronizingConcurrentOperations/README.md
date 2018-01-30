# 线程同步

## 同步方式
+ 设置Flag, 不断检查.
+ 设置Flag, 不断检查, 如果不满足sleep a periods.
+ Condition variable, 适用于多个线程等待相同Event.
> [Spurious wake](https://en.wikipedia.org/wiki/Spurious_wakeup),
> [SO上的一些解释](http://stackoverflow.com/questions/8594591/why-does-pthread-cond-wait-have-spurious-wakeups).
+ Future, 等待一次性的事件

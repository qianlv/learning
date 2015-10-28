# encoding=utf-8

from coroutines_pipeline_dataflow import broadcast
from coroutines_pipeline_dataflow import printer
from coroutines_pipeline_dataflow import grep
from from_data_processing_to_concurrent_programming import threaded

p = printer()
target = broadcast([threaded(grep('foo', p)),
                    threaded(grep('bar', p))])

for i in xrange(10):
    target.send("foo is nice\n")
    target.send("bar is bad\n")
target.close()

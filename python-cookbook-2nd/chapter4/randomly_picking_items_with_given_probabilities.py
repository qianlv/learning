#!/usr/bin/python
#encoding=utf-8

import random
# 从列表中获取元素根据另一列表的给出的概率
def random_pick(some_lists, probabilities):
    x = random(0,1)
    cumulative_probability = 0.0
    for item, item_probability in zip(some_lists, probabilities):
        cumulative_probability += item_probability
        if x < cumulative_probability: break
    return item
# 根据一个列表的权重选取元素
def random_pick_weight(some_lists, relative_odds):
    table = [ z for x, y in zip(some_lists, relative_odds) for z in [x] * y ] 
    while True:
        yield random.choice(table)

if __name__ == '__main__':
    x = random_pick_weight('ciao', [1, 2, 3, 4])
    for two_chars in zip('123', x):
        print ''.join(two_chars)
    import itertools
    print  ''.join(itertools.islice(x, 8))

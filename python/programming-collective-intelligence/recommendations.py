# encoding=utf-8
from math import sqrt

# A dictionary of movie critics and their ratings of a small
# set of movie
critics = {
    'Lisa Rose' : {
        'Lady in the Water' : 2.5, 'Snakes on a Plane' : 3.5,
        'Just My Luck': 3.0, 'Superman Returns': 3.5,
        'You, Me and Dupree': 2.5, 'The Night Listener': 3.0},
    'Gene Seymour': {
        'Lady in the Water': 3.0, 'Snakes on a Plane': 3.5,
        'Just My Luck': 1.5, 'Superman Returns': 5.0,
        'The Night Listener': 3.0, 'You, Me and Dupree': 3.5},
    'Michael Phillips': {
        'Lady in the Water': 2.5, 'Snakes on a Plane': 3.0,
        'Superman Returns': 3.5, 'The Night Listener': 4.0},
    'Claudia Puig': {'Snakes on a Plane': 3.5, 'Just My Luck': 3.0,
        'The Night Listener': 4.5, 'Superman Returns': 4.0,
        'You, Me and Dupree': 2.5},
    'Mick LaSalle': {'Lady in the Water': 3.0, 'Snakes on a Plane': 4.0,
        'Just My Luck': 2.0, 'Superman Returns': 3.0, 'The Night Listener': 3.0,
        'You, Me and Dupree': 2.0},
    'Jack Matthews': {'Lady in the Water': 3.0, 'Snakes on a Plane': 4.0,
        'The Night Listener': 3.0, 'Superman Returns': 5.0, 'You, Me and Dupree': 3.5},
    'Toby': {'Snakes on a Plane':4.5,'You, Me and Dupree':1.0,'Superman Returns':4.0}}

def sim_distance_base_euclidean(prefs, person1, person2):
    ''' Returns a distance-based similarity score for persons1 and person2
        Get higher values for people who are similar.
        so values = 1 / (1 + euclidean_distance) 
    '''
    # Get the list of shared_items
    si = {}
    for item in prefs[person1]:
        if item in prefs[person2]:
            si[item] = 1

    # if they have no ratings in common, return 0
    if len(si) == 0: return 0

    # Add up the squares of all the differences
    sum_of_squres = sum([pow(prefs[person1][item] - prefs[person2][item], 2)
                         for item in prefs[person1] if item in prefs[person2]])
    
    return 1 / (1 + sum_of_squres)

def sim_distance_base_pearson(prefs, person1, person2):
    
    # Get the list of shared_items
    si = {}
    for item in prefs[person1]:
        if item in prefs[person2]:
            si[item] = 1

    n = len(si)
    if n == 0:
        return 0

    sum1 = sum([prefs[person1][it] for it in si])
    sum2 = sum([prefs[person2][it] for it in si])

    sum1Sq = sum([pow(prefs[person1][it], 2) for it in si])
    sum2Sq = sum([pow(prefs[person2][it], 2) for it in si])

    pSum = sum([prefs[person1][it] * prefs[person2][it] for it in si])

    num = pSum - (sum1 * sum2 * 1.0 / n)
    den = sqrt((sum1Sq - pow(sum1, 2) / n) * (sum2Sq - pow(sum2, 2) / n))
    if den == 0:
        return den

    return num / den

'''
    metric(度量): 一个function在集合X, d: X x X -> R, R是real number.
    且x,y,z在集合X中的，满足: 1. d(x,y) >= 0, 2. d(x,y) if and only if x = y
    3. d(x,y) = d(y,x) 4. d(x,z) <= d(x,y) + d(y,z)
    一些度量函数(任意度量函数都有平移不变性)
    1. discrete metric: if x = y then d(x,y) = 0, 其他则d(x,y) = 1
    2. Euclidean metric(欧几里得距离): d(x, y) = sqrt((x1 - x2)^2 + (y1 - y2)^2)
    3. Manhattan metric(曼哈顿距离): d(x, y) = |x1 - x2| + |y1 - y2|
    4. Graph metric: d(x,y) 表示图上两点的最小路径变的个数(图的任意点之间可达)
    5. Hamming metric: d(x,y) 表示两个相同长度的字符串(string)在相同位置字符不同的个数.
    6. Jaccard metric(Tanimoto): d(x,y) 表示两个集合中不同元素占所有元素的比例
'''

def topMatches(prefs, person, n=5, similarity=sim_distance_base_euclidean):
    ''' Returns the best matches of person from the prefs dictionary.
        Number of results and similarity function are optional params.
    '''
    scores = [(similarity(prefs, person, other),other)
              for other in prefs if other != person]
    scores.sort()
    scores.reverse()
    return scores[0:n]

# 对于每个电影的评分求加权平均数
def getRecommendations(prefs, person, similarity = sim_distance_base_pearson):
    ''' Return recommendations for a person by use a weighted average
        of every other user's rankings
    '''
    totals = {}
    simSums = {}
    for other in prefs:
        if other == person:
            continue
        sim = similarity(prefs, person, other)
        if sim <= 0:
            continue
        for item in prefs[other]:
            # only score movies I haven't seen yet
            if item not in prefs[person] or prefs[person][item] == 0:
                # similarity * score
                totals.setdefault(item, 0)
                totals[item] += sim * prefs[other][item]
                # Sum of similarity
                simSums.setdefault(item, 0)
                simSums[item] += sim

    # Create the normalized list
    rankings = [(total/simSums[item], item) for item, total in totals.items()]

    rankings.sort()
    rankings.reverse()
    return rankings

def transformPrefs(prefs):
    ''' 翻转Prefs
    '''
    result = {}
    for person in prefs:
        for item in prefs[person]:
            result.setdefault(item, {})
            result[item][person] = prefs[person][item]
    return result

def calculateSimilarItem(prefs, n = 10):
    ''' Return a dictionay of items showing which othe items they
        are similar to
    '''
    result = {}
    itemPrefs = transformPrefs(prefs)
    c = 0
    for item in itemPrefs:
        c += 1
        if c % 100 == 0: 
            print "%d / %d" % (c, len(itemPrefs))
        scores = topMatches(itemPrefs, item, n = n, similarity = sim_distance_base_euclidean)
        result[item] = scores
    return result



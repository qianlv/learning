# encoding=utf-8
# Definition for a point.
# class Point(object):
#     def __init__(self, a=0, b=0):
#         self.x = a
#         self.y = b

# P1(X1, Y1), P2(X2, Y2), Ax + By + C = 0
# A = Y2 - Y1, B = X1 - X2, C = X2*Y1 - X1*Y2


class Point(object):
    def __init__(self, a=0, b=0):
        self.x = a
        self.y = b


class Solution(object):
    def maxPoints(self, points):
        """
        :type points: List[Point]
        :rtype: int
        """
        def get_slope(p1, p2):
            return (p2.y - p1.y + 0.0) / (p2.x - p1.x)

        m = 0
        # 每次只考虑以点i共线的点有多少
        for i, p1 in enumerate(points):
            dic = {'self': 1}
            same = 0
            for p2 in points[i+1:]:
                if p1.x == p2.x and p1.y == p2.y:
                    same += 1
                    continue
                if p1.x == p2.x:
                    dic['self'] += 1
                else:
                    slope = get_slope(p1, p2)
                    dic.setdefault(slope, 1)
                    dic[slope] += 1
            m = max(m, max(dic.values()) + same)
        return m


if __name__ == '__main__':
    sol = Solution()
    # points = [Point(3, 1), Point(12, 3), Point(3, 1), Point(-6, -1)]
    points = [Point(0, 0), Point(1, 0)]
    print sol.maxPoints(points)

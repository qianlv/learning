# encoding=utf-8
'''
关于时区tzinfo
tzinfo 是python时区的抽象类, 如果要给一个datetime赋值时区,
需创建一个tzinfo的子类,然后绑定到datetime.tzinfo属性上
'''
import datetime
import re

'''
datetime object 有2中类型:
1. offset-native, 不带有时区信息, python默认都是这种类型, tzinfo属性为None.
2. offset-aware, 带有时区信息, 需要自己实现tzinfo类(标准库中的tzinfo为抽象类).
offset-native的datetime object可以通过replace方式替换tzinfo, 替换属性不会根据时间差改变
offset-aware的datetime object 通过astimezone修改时区
'''


class UTC(datetime.tzinfo):
    def __init__(self, utc):
        utc = str(utc.strip().upper())
        re_utc = re.compile(r'^([\+\-])([0-9]{1,2})\:([0-9]{1,2})$')
        mt = re_utc.match(utc)
        if mt:
            minus = mt.group(1) == '-'
            hours = int(mt.group(2))
            minutes = int(mt.group(3))
            if minus:
                hours, minutes = -hours, -minutes
            self._utcoffset = datetime.timedelta(hours=hours, minutes=minutes)
            self._tzname = 'UTC{}'.format(utc)
        else:
            raise ValueError('bad utc time zone')

    def utcoffset(self, dt):
        return self._utcoffset

    def tzname(self, dt):
        return self._tzname

    # 夏令时
    def dst(self, dt):
        return datetime.timedelta(0)

    def __str__(self):
        return 'UTC tzinfo object ({})'.format(self._tzname)

    __repr__ = __str__

# 默认的datetime不带时区信息
curdate = datetime.datetime.now()
print curdate.tzinfo
curdate = datetime.datetime.now(tz=UTC('-2:00'))  # 西2区的当前时间
print curdate
print curdate.tzinfo
utc7 = UTC('+07:00')
utc8 = UTC('+08:00')
test_tuple = (2015, 10, 11, 14, 58)
# utc8_time, utc7_time 不同时区的同一时刻
utc8_time = datetime.datetime(*test_tuple, tzinfo=utc8)
utc7_time = utc8_time.astimezone(utc7)
print utc8_time
print utc7_time
timespan = utc8_time - utc7_time
print type(timespan), timespan.total_seconds()

'''
时区模块pytz
'''

import pytz

# 对于国家的时区列表
print pytz.country_timezones('cn')  # [u'Asia/Shanghai', u'Asia/Urumqi']

tz = pytz.timezone('Asia/Shanghai')
dt = datetime.datetime(*test_tuple, tzinfo=tz)
print repr(dt)
# datetime.datetime(2015, 10, 11, 14, 58,
# tzinfo=<DstTzInfo 'Asia/Shanghai' LMT+8:06:00 STD>)
# dt有一个LMT(local Mean Time)为本地平均时间, 时间是+8:06, 比北京时间快6分钟
dt_cst = datetime.datetime(*test_tuple, tzinfo=utc8)
print dt_cst == dt  # False

# 正确获取构造offset-aware类型datetime object的方法是:
# 使用timezone.localize()方法生成带时区的datetime, 不要通过构造函数中传入tzinfo的方式实现
dt2 = datetime.datetime(*test_tuple)
dt2 = tz.localize(dt2)
print repr(dt2)
# datetime.datetime(2015, 10, 11, 14, 58,
# tzinfo=<DstTzInfo 'Asia/Shanghai' CST+8:00:00 STD>)
# dt2 变为CST(Central Standard Time), 时间+8:00:00也是对的
print dt2 == dt_cst  # True

# 夏令时
# 通过timezone.normalize函数处理夏令时
# 特别在时区之间转换的时候调用normalize函数
eastern = pytz.timezone('US/Eastern')
dt3 = datetime.datetime(2002, 10, 27, 1, 0)
dt3 = eastern.localize(dt3)
print dt3   # 2002-10-27 01:00:00-05:00
dt4 = dt3 - datetime.timedelta(minutes=10)
print dt4   # 2002-10-27 00:50:00-05:00
dt5 = eastern.normalize(dt4)
print dt5   # 2002-10-27 01:50:00-04:00
print repr(dt4.tzinfo)
print repr(dt5.tzinfo)

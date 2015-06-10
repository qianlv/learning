#/usr/bin/python
#encoding=utf-8

#每次处理一个字符
thestring = "the string is string"
thelist = list(thestring)
print thelist

for c in thestring:
    print c,
print ' '

results = [ c for c in thestring]
print results

def do_some_thing(c):
    print c,
results = map(do_some_thing, thestring)
print ' '

magic_chars = set("aaaabbbce") #集合
poppins_chars = set("abgh")
print magic_chars & poppins_chars
print '-'.join(magic_chars & poppins_chars)
print magic_chars | poppins_chars
print magic_chars ^ poppins_chars

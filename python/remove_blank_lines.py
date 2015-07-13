import re

def method1(txt):
    ret=""
    for line in txt.split("\n"):
        if line.strip()!='':
            ret += line + "\n"
    return ret

def method2(txt):
    return '\n'.join([line for line in txt.split("\n") if line.strip()!=''])

def method3(txt):
    while '\n\n' in txt:
        txt = txt.replace('\n\n','\n')
    return txt

#\s:空白字符从[ \t\n\r\f\v]
def method4(txt):
    return re.sub("\n\s*\n*", "\n", txt)

text = """`Twas brillig, and the slithy toves
Did gyre and gimble in the wabe:
All mimsy were the borogoves,
And the mome raths outgrabe.


"Beware the Jabberwock, my son!
The jaws that bite, the claws that catch!
Beware the Jubjub bird, and shun
The frumious Bandersnatch!"

He took his vorpal sword in hand:
Long time the manxome foe he sought --
So rested he by the Tumtum tree,
And stood awhile in thought.

And, as in uffish thought he stood,
The Jabberwock, with eyes of flame,
Came whiffling through the tulgey wood,
And burbled as it came!

One, two! One, two! And through and through
The vorpal blade went snicker-snack!
He left it dead, and with its head
He went galumphing back.

"And, has thou slain the Jabberwock?
Come to my arms, my beamish boy!
O frabjous day! Callooh! Callay!'
He chortled in his joy.


`Twas brillig, and the slithy toves
Did gyre and gimble in the wabe;
All mimsy were the borogoves,
And the mome raths outgrabe."""

if __name__ == '__main__':
    print method1(text)
    print method2(text)
    print method3(text)
    print method4(text)

# Python性能优化

## 命名规范

推荐PEP8规范：https://www.python.org/dev/peps/pep-0008/

文件名：小写字母+下划线 file_example.py

类名：大写字母开头 ClassExample

方法名： 小写字母+下划线 function_example

每行长度不超过80字符，使用4个空格而非tab缩进

## pythonic写法

### if语句使用 if condition而不是 if condition == True

```python
if condition:  # 等同于
    pass
if not condition:  # 等同于 if condition == False
    pass
```

### 判断对象是否为空

None是单例，在代码运行时具有全局唯一的内存地址，因此在判断一个对象是否为空是需要使用：

```python
if obj is None:
    # some code
```

而如果判断一个对象是有类型无内容的，例如“空字符串”、“空列表”、数字0时，可以使用if not，省略判断具体的内容：

```python
s = ""
if not s:
    # some code

l = []
if not l:
    # some code

num = 0
if not num:
    # some code
```

对于类似这样if a的写法，系统首先去调用a的__ nonzero __ ()去判断a是否为空，并返回True/False，若一个对象没有定义__ nonzero__ ()，就去调用它的__ len __()来进行判断（这里返回值为0代表空），若某一对象没有定义以上两种方法，则if a的结果永远为True

### 使用串联比较

```python
# 不推荐
if a > 0 and a <= 10:
    # some code

# 推荐
if 0 < a <= 10:    
    # some code
```

### if-else语句优化

简单的if-else可以优化到一行

```python
# 优化前
if some_condition：
    name = 'a'
else:
    name = 'b'

# 优化后
name = 'a' if some_condition else 'b'
```

适当利用return、break、continue等，省略多余的else语句

```python
# 优化前
def check(condition):
    if condition:
        return True
    else:
        return False

# 优化后
def check(condition):
    if condition:
        return True
    return False
```

减少if-else嵌套，降低圈复杂度

```python
# 优化前
if condition_a:
    if condition_b:
        # do something 1
    else:
        # do something 2
else:    
    if condition_b:
        # do something 3
    else:
        # do something 4

# 优化后
if condition_a and condition_b:
    # do something 1
elif condition_a：
    # do something 2
elif condition_b:
    # do something 3
else:
    # do something 4
```

### 使用列表推导式和生成器

list的append操作会导致内存重分配，开销较高，建议使用列表推导式

```python
# 优化前
my_list_a = [1,2,3,4,5]
my_list_b = []
for i in my_list_a：
    my_list_b.append(a*10)

# 优化后
my_list_a = [1,2,3,4,5]
my_list_b = [i*10 for i in my_list_a]
```

迭代器生成的方式，开销小于列表推导式，在列表需要顺序访问时可以使用迭代器生成的方式。

该方式只有当迭代器被调用时，才会去计算值。

```python
my_list_a = [1,2,3,4,5] 
def my_func(x):
    print('start calculate %s' % x)
    return x * 10

my_list_b = [my_func(i) for i in my_list_a]
# 会立即计算
"""
start calculate 1
start calculate 2
start calculate 3
start calculate 4
start calculate 5
"""

my_gen_b = (my_func(i) for i in my_list_a)
# 不会执行计算 
for j in my_gen_b:
    print('lazy calculate %s' % j)
    # 此时才会计算
    """
    start calculate 1
    lazy calculate 10
    start calculate 2
    lazy calculate 20
    start calculate 3
    lazy calculate 30
    start calculate 4
    lazy calculate 40
    start calculate 5
    lazy calculate 50
    """
```

### 避免使用range

for循环遍历可迭代对象，如列表、tuple、字典等，尽量避免使用range。

如果一定要访问下标，使用enumerate。

```python
# 不推荐
for i in range(len(my_list)):
    do_something(my_list[i])

# 推荐
for v in my_list:
    do_something(v)

# 推荐
for i,v in enumerate(my_list): 
    print('index：%s' % i)
    print('value：%s' % v)    
```

### 限制函数输入输出

Python 3.5以上，在函数中限制输入输出变量类型，可以做到类似强类型语言的功能，在函数运行时检测输入输出是否合法。

```python
from typing import List
def my_func(keyword:str) -> List[dict]:
    """
    :param keyword: 输入字符串类型
    :return: 输出一个字典组成的列表
    """
    # some code

# 支持自定义的类
class MyClass：
     pass

def my_func_2(obj:MyClass):
    # some code
```

### 使用from xx import xxx 代替 import xx

好处：减少import引起的系统开销和重复引用，同时在写代码时就清楚自己需要调用模块下的哪个功能，必要时使用 as 区分不同模块的引用

```python
# 不推荐
import os
import sys
os.path.xxx()
sys.path.xxx()

# 推荐
from os import path as os_path
from sys import path as sys_path
os_path.xxx()
sys_path.xxx()
```

### 判断对象类型

使用isinstance(obj,Class)而非type(obj)==Class或type(obj) is Class

```python
class A:
    pass

class B(A):
    pass

a = A()
b = B()

type(b) == B  # ==操作执行开销很大
>>> True

type(b) is B 
>>> True

type(b) is A # type is操作无法判断继承关系
>>> False

isinstance(b,A)
>>> True

isinstance(b,B) # 推荐做法
>>> True
```

## 函数化编程：使用map、filter代替复杂的操作

函数式编程是一种编程范式，将计算机运算视为函数运算，并且避免使用程序状态及易变对象。

**函数式编程的特征**

- **stateless**：函数不维护任何状态。

- **immutable**：输入数据发生变化时，返回新的数据集。

- **惰性求值**：表达式不在它被绑定到变量之后就立即求值，而是在该值被取用的时候求值。

- **确定性**：所谓确定性，就是像在数学中那样，f(x) = y 这个函数无论在什么场景下，都会得到同样的结果。

应用函数式编程，函数之间没有共享的变量，而是通过参数和返回值传递数据，可以重点关注做什么而非怎么做。

根据 **Algorithm = Logic +Control** ，在Python中使用map、reduce、filter，实际上改变的是 Control 的部分，即改变算法执行的策略，而不修改真正的业务Logic。

### lambda

Python中可以用 [lambda](https://links.jianshu.com/go?to=https%3A%2F%2Fdocs.python.org%2Fzh-cn%2F3%2Freference%2Fexpressions.html%23lambda) 关键字来创建一个小的**匿名函数**。

例如，这个lambda函数返回两个参数的和： lambda a, b: a+b 。

Lambda函数可以在需要函数对象的任何地方使用。在语法上，仅限于单个表达式。从语义上来说，它们只是正常函数定义的语法糖。

### map

map对传入的可迭代对象中每一个元素，执行一个func操作，并将结果作为新的可迭代对象返回。

先看一个示例，下面的代码使用常规的面向过程方式，将一个字符串中所有小写字母转换为大写：

```python
lowname = ['hello','world']
upper_name =[] 
for i in range(len(lowname)):
    upper_name.append( lowname[i].upper() )
```

面向过程的写法通过一个循环读取所有输入，依次进行转换。

而函数式的写法，将转换过程抽象成一个函数，然后在调用时不需要使用循环，而是使用map关键字:

```python
def toUpper(item):
      return item.upper()

upper_name = map(toUpper, ['hello','world'])
```

在builtins.py文件中，可以查看map的定义：

```python
map(func, *iterables) --> map object

Make an iterator that computes the function using arguments from each of the iterables.  Stops when the shortest iterable is exhausted.
```

即，map将func函数应用于传入序列的每个元素，并将结果作为新的list返回。map抽象了运算规则，使代码更易阅读。

函数func可以为一个具体的函数，也可以为一个lambda函数，例如下面的代码会把nums列表中每一个数乘3。

```python
nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10] 
# 面向对象写法
newnums = []
for i in nums:
    newnums.append(i*3)

# 面向对象优化写法
newnums = [i*3 for i in nums]

# 函数式编程写法,开销更低
newnums = map(lambda x: x*3, nums)
```

func参数的类型是一个function对象，只需要写函数名，不需要加括号。

### reduce

reduce对在参数序列中的元素，执行函数function，这个函数必须接收两个参数，reduce把结果继续与序列的下一个元素进行累积计算。

在Python3中，使用reduce需要先从functool中引入，在_functools.py中可以查看reduce函数的定义。

```python
reduce(function, sequence[, initial]) -> value


Apply a function of two arguments cumulatively to the items of a sequence,
from left to right, so as to reduce the sequence to a single value.

For example, reduce(lambda x, y: x+y, [1, 2, 3, 4, 5]) calculates ((((1+2)+3)+4)+5).  If initial is present, it is placed before the items of the sequence in the calculation, and serves as a default when the
sequence is empty.
```

再看一个简单的示例，对一个列表中所有元素求和，非函数式编程的写法如下：

```python
nums = [2, -5, 9, 7, -2, 5, 3, 1, 0, -3, 8]
result = 0

for i in nums:
    result += i
```

使用reduce，可以隐藏数组遍历求和控制流程，让代码的业务逻辑更清晰：

```python
from functools import reduce

nums = [2, -5, 9, 7, -2, 5, 3, 1, 0, -3, 8]
result = reduce(lambda x,y:x+y, nums)
```

当函数变复杂时，reduce的收益就会更明显，例如，将序列转换为整数：

```python
from functools import reduce

nums = [2, 5, 9, 7, 2, 5, 3, 1, 0, 3, 8]
result = reduce(lambda x,y:x*10+y, nums)
# result = 25972531038
```

### filter

filter应用于过滤序列，以一个判断函数和可迭代对象作为参数，返回序列中满足判断函数的元素组成的列表。

```
filter(function or None, iterable) --> filter object

Return an iterator yielding those items of iterable for which function(item) is true. If function is None, return the items that are true.
```

例如，过滤出一个列表中所有奇数：

```python
def is_odd(n):
    return n % 2 == 1

newlist = filter(is_odd, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
```

函数式编程三套件map、reduce、filter，都属于简化控制流程的函数。适当使用可以使代码更清晰易读，更聚焦于业务处理逻辑。例如，写一个计算数组中所有正数平均值的函数，使用面向过程的写法如下：

```python
# 计算数组中正数的平均值
num = [2, -5, 9, 7, -2, 5, 3, 1, 0, -3, 8]

def calcute_average(num):
    positive_num_cnt = 0
    positive_num_sum = 0
    average = 0
    for i in range(len(num)):
        if num[i] > 0:
            positive_num_cnt += 1
            positive_num_sum += num[i]

    if positive_num_cnt > 0:
        average = positive_num_sum / positive_num_cnt

    return average
```

而使用函数式编程写法如下：

```python
def calcute_average2(num):
    positive_num = list(filter(lambda x: x > 0, num)) # 过滤正数
    return reduce(lambda x, y: x + y, positive_num) / len(positive_num)  # average = 正数列表求和/正数个数
```

注意：python3中filter函数的返回值为一个filter对象，需要转换成list对象才能使用reduce，而python2中可以直接写

```python
positive_num = filter(lambda x: x > 0, num)
```

可以看到，这种方法通过去掉循环体，解耦了控制逻辑与业务逻辑，去掉了控制逻辑中的临时变量，代码重点在描述“做什么”。

## 数据结构和算法

### 保存最后N个元素

使用collections.deque可以实现，deque是一个先进先出的队列

### 找到最大或最小的N个元素

数据量较小推荐使用heapq.nlargest()和heapq.nsmallest()

数据量较大推荐使用collections.deque

### 在字典中将键映射到多个值上

使用collections.defaultdict()

### 让字典保持有序

使用collections.OrderedDict，比如Json编码时需要精确控制各字段的顺序，可以在OrderedDict中构建数据即可

注意：OrderedDict内部维护了一个双向链表，所以本质上OrderedDict的大小是普通字典的2倍多

### 将字典的键值对反转过来

使用zip()函数即可

### 在两个字典中寻找相同点

```python
# Find keys in common
a.keys() & b.keys()

# Find keys in a that are not in b
a.keys() - b.keys()

# Find (key,value) pairs in common
a.items() & b.items()
```

### 从序列中移除重复项且保持元素间顺序不变

```python
def deque(items, key=None):
    seen = set()
    for item in items:
        val = item if key is None else key(item)
        if val not in seen:
            yield item
            seen.add(val)
            
tmp = [1, 2, 2, 3, 3]
for i in deque(tmp, ):
  	print(i)
```

### 通过公共键对字典列表排序

```python
rows = [
    {'frame': "Brain"},
    {"frame": "David"},
    {"frame": "John"},
    {"frame": "Big"}
]

from operator import itemgetter
rows_by_name = sorted(rows, key=itemgetter("frame"))
```

### 对不原生支持比较操作的对象排序

```python
class User:
    def __init__(self, user_id):
        self.user_id = user_id
    def __repr__(self):
        return 'User({})'.format(self.user_id)
        
users = (User(23), User(2), User(18))

sorted(users, key=lambda u: u.user_id)

from operator import attrgetter
sorted(users, keys=attrgetter("user_id"))
```

### 从字典中提取子集

利用字典推导式(dictionary comprehension)

```python
prices = {
    "ACE": 45.23,
    "AAPL": 612.78,
    "IBM": 205.55,
    "HPQ": 37.20,
    "FB": 10.75
}

p1 = {key:value for key, value in prices.items() if value > 200}

tech_names = {"AAPL", "IBM", "HPQ", "MSFT"}
p2 = {key:value for key, value in prices.items() if key in tech_names}
```

### 将名称映射到序列的元素中

可以使用collections.namedtuple()

```python
from collections import namedtuple
Subscriber = namedtuple("Subscriber", ["addr", "joined"])
```

### namedtuple的微妙用法

```python
from collections import namedtuple

Stock = namedtuple('Stock', ['name', 'shares', 'price', 'date', 'time'])

# Create a prototype instance
stock_prototype = Stock('', 0, 0.0, None, None)

# Function to convert a dictonary to a Stock
def dict_to_stock(s):
    return stock_prototype._replace(**s)
```

### 将多个字典映射合并为单个字典映射

可以使用collections.ChainMap类

```python
a = {"x": 1, "z": 3}
b = {"y": 2, "z": 4}

from collections import ChainMap
c = ChainMap(a, b)    # 注意，这里如果有重复的键，会采用第一个映射中所对应的值，即z=3
```

## 字符串和文本

### fnmatch模块提供了两个函数——fnmatch()和fnmatchcase()可用来执行匹配

```python
addresses = [
    '5412 N CLARK ST',
    '1060 W ADDISON ST',
    '1039 W GRANVILLE AVE',
    '2122 N CLARK ST',
    '4802 N BROADWAY',
]

from fnmatch import fnmatchcase
[addr for addr in addresses if fnmatchcase(addr, '* ST')]
```

### 对齐文本字符串

对于基本的字符串对齐要求，可以使用字符串的ljust()、rjust()、center()方法

### 字符串连接及合并

```python
.join()
.format()
```

**Bad Smell**

```python
s = ''
for p in parts:
    s += p

这段代码使用+操作符做大量的字符串连接是非常低效的，原因是由于内存拷贝和垃圾收集产生影响。每个+=操作都会创建一个新的字符串对象
```

**Good Case**

```python
data = ['ACME', 50, 811]
','.join(str(d) for d in data)
','.join(list(map(int, data)))
```

### 给字符串中的变量名做插值处理

```python
# 方式一
s = '{name} has {n} message'
s.format(name='Guido', n=3)

# 方式二
name = 'Guido'
n = 3
s.format_map(vars())
```

有关vars()的一个微妙的特性是它也能作用于类的实例上

```python
class Info:
    def __init__(self, name, n)
        self.name = name
        self.n = n

a = Info('Guido', 3)
s.format_map(vars(a))
```

### 以固定列数重新格式化文本

使用textwrap模块来重新格式化文本的输出

## 数组、日期和时间

### 同二进制、八进制和十六进制数打交道

将一个整数转换为二进制、八进制或十六进制的文本字符串形式，只需分别使用内建的bin()、oct()、hex()函数即可

```python
x = 1234
bin(x) # 转换为二进制
oct(x) # 转换为十进制
hex(x) # 转换为十六进制
```

### 从字节串中打包和解包大整数

将字节解释为整数，使用int.from_bytes()

将大整数转换为字节串，使用int.to_bytes()

### 处理无穷大和NaN

```python
a = float('inf')
b = float('-inf')
c = float('nan')

# 检测是否出现了这些值
math.isinf()
math.isnan()
```

### 分数的计算

可以使用fractions模块

```python
from fractions import Fraction
a = Fraction(5, 4)
b = Fraction(7, 16)
print(a + b)
```

### 随机选择

如果想从序列中随机挑选出元素，可以使用random.choice()

如果想取样出N个元素，将选出的元素移除以做进一步的考察，可以使用random.sample()

如果只是想在序列中原地打乱元素的顺序，可以使用random.shuffle()

```python
import random
values = [1, 2, 3, 4, 5]

random.chocie(values) # 结果为2
random.sample(values, 2) # 结果为[6 , 2]
random.shuffle(values) # 结果为[2, 4, 3, 1, 5]
```

如果想产生随机整数，可以使用random.randint()

如果想产生0-1之间均匀分布的浮点数值，可以使用random.random()

如果要得到由N个随机比特位所表示的整数，可以使用random.getrandbits()

## 迭代器和生成器

### 反向迭代

如果想要反向迭代序列中的元素，可以使用内建的reversed()函数实现反向迭代，但是反向迭代只有在待处理的对象拥有可确定的大小或对象实现了`__reversed__`()特殊方法时才能奏效。可以考虑在自定义的类上实现反向迭代

```python
class Countdown:
    def __init__(self, start):
        self.start = start
        
    # Forward iterator
    def __iter__(self):
        n = self.start
        while n > 0:
            yield n
            n -= 1
    
    # Reverse iterator
    def __reversed__(self):
        n = 1
        while n <= self.start:
            yield n 
            n += 1
```

### 对迭代器做切片操作

可以使用itertools.islice()进行操作。因为迭代器和生成器是没法执行普通的切片操作的，因为不知道它们的长度是多少。islice()产生的结果是一个迭代器，它可以产生出所需要的切片元素，但这是通过访问并丢弃所有起始索引之前的元素来实现的。

```python
import itertools
for x in itertools.islice(c, 10, 20):
    print(x)
```

### 跳过可迭代对象中的前一部分元素

可以使用itertools.dropwhile()函数或者itertools.islice()函数

### 迭代所有可能的组合或排列

可以使用itertools.permutations()函数，它接受一个元素集合，将其中所有的元素重排列为所有可能的情况，并以元组序列的形式返回

```python
items = ['a', 'b', 'c']
from itertools import permutations
for p in permutataions(items):
    print(p)
```

可以使用itertools.combinations()可产生输入序列中所有元素的全部组合形式

```python
from itertools import combinations
for c in combinations(items, 3):
    print(c)
```

可以使用itertools.combinations_with_replacement()函数

```python
from itertools import combinations_with_replacement
for c in combinations_with_replacement(items, 3):
    print(c)
```

### 同时迭代多个序列

可以使用zip()函数来同时迭代多个序列，但需要注意的是zip(a, b)的工作原理是创建出一个迭代器，该迭代器可产生出元组(x, y)，这里的x取自序列a，而y取自序列b。当其中某个输入序列中没有元素可以继续迭代时，整个迭代过程结束。即整个迭代的长度和其中最短的输入序列长度相同

```python
xpts = [1, 5, 4, 2, 10, 7]
ypts = [101, 78, 37, 15, 62, 99]
for x, y in zip(xpts, ypts):
    print(x, y)
```

也可以使用itertools.zip_longest()

```Python
from itertools import zip_longest
for i in zip_longest(a, b):
    print(i)
```

### 在不同的容器中进行迭代

如果想对许多对象执行相同的操作，但这些对象包含在不同的容器中，希望可以避免写出嵌套的循环处理，保持代码可读性的情况下可以使用itertools.chain()方法来解决。需要注意的是itertools.chain()可接受一个或多个可迭代对象作为参数，然后它会创建一个迭代器，该迭代器可连续访问并返回提供的每个可迭代对象中的元素。尽管区别很小，但chain()比首先将各个序列合并在一起然后再迭代更高效。

```python
from itertools import chain
a = [1, 2, 3, 4]
b = ['x', 'y', 'z']
for x in chain(a, b):
    print(x)
```

### 扁平化处理嵌套型的序列

假设有一个嵌套型的序列，想将它扁平化处理为一列单独的值。

```python
from collections import Iterable

def flatten(items, ignore_types=(str, bytes)):
    for x in items:
        if isinstance(x, Iterable) and not isinstance(x, ignore_types):
            yield from flatten(x)
        else:
            yield x

items = [1, 2, [3, 4, [5, 6], 7], 8]
for x in flatten(items):
    print(x)
```

### 合并多个有序序列，再对整个有序序列进行迭代

假设有一组有序序列，想对它们合并在一起之后的有序序列进行迭代，可以使用heapq.merge()函数

```python
import heapq
a = [1, 4, 7, 10]
b = [2, 5, 6, 11]

for c in heapq.merge(a, b):
    print(c)
```

## 文件和I/O

### 将输出重定向到文件中

如果想将print()函数的输出重定向到一个文件中，可以参考如下代码块

```python
with open('somefile.txt', 'rt') as f:
    print('Hello, world', file=f)
```

### 对已不存在的文件执行写入操作

如果想将数据写入到一个文件中，但只在该文件已不在文件系统中时才这么做，可以使用open()函数中的x模式。

```python
with open('somefile', 'xt') as f:
    f.write('Hello\n')
```

### 读写压缩的数据文件

如果需要读写以gzip或bz2个市压缩过的数据，可参考如下代码

```python
import gzip
with gzip.open("somefile.gz", "rt") as f:
    text = f.read()

import bz2
with bz2.open("somefile.bz2", "rt") as f:
    text = f.read()
```

### 以固定大小对内容记录进行迭代

可以利用iter()和functools.partial()来完成

```python
from functools import partial
RECORD_SIZE = 32
with open("somefile.data", "rb") as f:
    records = iter(partial(f.read, RECORD_SIZE), 'b')
    for r in records:
        ....
```

### 对二进制文件做内存映射

首先解释下内存映射，即将文件或者其他的对象映射到进程的地址空间。实现文件磁盘地址和进程虚拟空间地址之间的一一映射关系。实现这样的映射关系后，进程就可以采用指针的方式读写操作这一段内存，而系统会自动回写脏页面到对应的文件磁盘上，即完成了对文件的操作而不必再调用read,write等系统调用函数。相反，内核空间对这段区域的修改也直接反映用户空间，从而可以实现不同进程间的文件共享。

```python
import os
import mmap

def memory_map(filename, access=mmap.ACCESS_WRITE):
    size = os.path.getsize(filename)
    fd = os.open(filename, os.O_RDWR)
    return mmap.mmap(fd, size, access=access)
    
size = 1000000
with open('data', 'wb') as f:
    f.seek(size-1)
    f.write(b'\x00')
```

### 处理路径名

```python
import os
path = '/Users/beazley/Data/data.csv'

# Get the last component of the path
os.path.basename(path) # output: data.csv

# Get the directory name
os.path.dirname(path) #output: '/Users/beazley/Data'

# Join path components together
os.path.join('tmp', 'data', os.path.basename(path)) # output: 'tmp/data/data.csv'

# Expand the user's home directory
path = '~/Data/data.csv'
os.path.expanduser(path) # output: '/Users/beazley/Data/data.csv'

# Split the file extension
os.path.splitext(path) # output: ('~/Data/data', '.csv')
```

### 文件名匹配

```python
import glob
pyfiles = glob.glob("somedir/*.py")

from fnmatch import fnmatch
pyfiles = [name for name in os.listdir('somedir') if fnmatch(name. '*.py')]
```

### 创建临时文件和目录

当程序运行时，需要创建临时文件或目录以便使用。在这之后，希望将这些文件和目录销毁掉

```python
from temfile import TemporaryFile

with TemporaryFile('w+t') as file:
    f.write('Hello World\n')
    f.write('Testing\n')
    
    f.seek(0)
    data = f.read()
```

## 数据编码与处理

### 读写CSV数据

若想要读写csv文件中的数据，可以使用csv库来处理

```python
import csv
with open('stock.csv') as f:
    f_csv = csv.reader(f)
    headers = next(f_csv)
    for row in f_csv:
        # Process row
        ...
```

```python
from collections import namedtuple
with open('stock.csv') as f:
    f_csv = csv.reader(f)
    headings = next(f_csv)
    Row = namedtuple('Row', headings)
    for r in f_csv:
        row = Row(*r)
        # Process row
        ...
```

也可使用字典序列来读取数据

```python
import csv
with open('stocks.csv') as f:
    f_csv = csv.DictReader(f)
    for row in f_csv:
        # process row
        ...
```

### 读写JSON数据

若想将深层次嵌套结构或有许多字段的JSON结构体打印出来，可以考虑使用pprint模块中的pprint()函数

```python
from urllib.request import urlopen
import json
u = urlopen("http://search.twitter.com/search.json?q=python&rpp=5")
resp = json.loads(u.read().decode('utf-8'))

from pprint import pprint
pprint(resp)
```

若想将JSON解码出来的数据转换为其他类型的对象，可以为json.loads()方法提供object_pairs_hook或者object_hook参数

```python
s = '{"name: "ACME", "shares": 50, "prices": 490.1}'

# Convert to OrderedDict
from collections import OrderedDict
data = json.loads(s, object_pairs_hook=OrderedDict)

# Convert to Python Object
class JSONObject:
    def __init__(self, d):
        self.__dict__ = d
    
data = json.loads(s, object_hook=JSONObject)
```

若想将类实例序列化为JSON，可以考虑如下方式：

```python
def serialize_instance(obj):
    d = { '__classname__': type(obj).__name__ }
    d.update(vars(obj))
    return d
```

若想将类实例再重新转换为json，可以考虑如下方式：

```python
classes = {'Point': Point}
def unserialize_object(d):
    clsname = d.pop('__classname__', None)
    if clsname:
        cls = classes[clsname]
        obj = cls.__new__(cls)
        for key, values in d.items():
            setattr(obj, key, value)
            return obj
    else:
        return d
```

### 将元数据信息附加到函数参数上

如果已经编写好了一个函数，希望能为函数加一些额外的信息

```python
def add(x:int, y:int)->int:
    return x+y
    
# 函数的注解只会保存在函数的__annotations__属性中
>>> add.__annotations__
```

### 让带有N个参数的可调用对象以较少的参数形式调用

如果需要减少函数的参数数量，应该使用functools.partial()。函数partial()允许我们给一个或多个参数指定固定的值

```python
def spam(a, b, c, d):
    print(a, b, c, d)

>>> from functools import partial
>>> s1 = partial(spam, 1)
>>> s1(2, 3, 4)
1 2 3 4
>>> s1(4, 5, 6)
1 4 5 6
```

**实战使用: partial()常常可用来调整其他库中用到的回调函数的参数签名**

```python
def output_result(result, log=None):
    if log is not None:
        log.debug('Got: %r', result)

def add(x, y):
    return x+y

if __name__ == '__main__':
    import logging
    from multiprocessing import Pool
    from functools import partial
    
    logging.basicConfig(level=logging.DEBUG)
    log = logging.getLogger('test')
    
    p=Pool()
    p.apply_async(add, (3, 4), callback=partial(output_result, log=log)
    o.close()
    p.join()
```

### 在回调函数中携带额外的状态

在编写需要使用回调函数的代码（比如，时间处理例程、完成回调等），但是希望回调函数可以携带额外的状态以便在回调函数内部使用

```python
def apply_sync(func, args, *, callback):
     # Compute the result
    result = func(*args)
    
    # Invoke the callback with the result
    callback(result)

def print(result):
    print('Got:', result)

def add(x+y):
    return x+y

if __name__ == '__main__':
  	# todo check
    apply_sync(add, (2, 3), callback=print_result)
```

### 访问定义在闭包内的变量

希望通过函数来扩展闭包，使得在闭包内层定义的变量可以被访问和修改

```python
def smaple():
    n = 0
    # Closure function
    def func():
        print('n=', n)
    
    # Accessor methods for n
    def get_n():
        return n
    
    def set_n(value):
        nonlocal n
        n = value
        
    # Attach as function attributes
    func.get_n = get_n
    func.set_n = set_n
    return func
    
>>> f = sample()
>>> f()
n = 0
>>> f.set_n(10)
>>> f()
n = 10
>>> f.get_n()
10
```

## 类与对象

### 打印实例所产生的输出

```python
class Pair:
    def __init__(self, x, y)
        self.x = x
        self.y = y
    
    def __repr__(self):
        return 'Pair({0.x!r}, {0.y!r}'.format(self)
        
    def __str__(self):
        return '({0.x!s}, {0.y!s})'.format(self)
```

`__str__`：通过`str(object)`以及内置函数`format()`和`print()`调用以生成一个对象的“非正式”或格式良好的字符串表示。返回值必须是**字符串对象**。

  `__repr__`：是由`repr()`内置函数调用，用来输出一个对象的“官方”字符串表示。返回值必须是**字符串对象**，此方法通常被用于调试。内置类型 `object` 所定义的默认实现会调用 `object.__repr__()`。

### 自定义字符串的输出格式

```python
_formats = {
    'ymd': '{d.year} - {d.month} - {d.day}',
    'mdy': '{d.month}/{d.day}/{d.year}',
    'dmy': '{d.day}/{d.month}/{d.year}'
}

class Date:
    def __init__(self, year, month, day):
        self.year = year
        self.month = month
        self.day = day
    
    def __format__(self, code):
        if code == '':
            code = 'ymd'
        fmt = _formats[code]
        return fmt.fotmat(d=self)
```

### 让对象支持上下文管理协议

希望让对象支持上下文管理协议，要让对象能够兼容with语句，需要实现`__enter__`()和`__exit__`()方法

```python
from socket import socket, AF_INET, SOCK_STREAM

class LazyConnection:
    def __init__(self, address, family=AF_INET, type=SOCK_STREAM):
        self.address = address
        self.family = AF_INET
        self.type = SOCK_STREAM
        self.sock = None
    
    def __enter__(self):
        if self.sock is not None:
            raise RuntimeError('Already connected')
        self.sock = socket(self.family, self.type)
        self.sock.connect(self.address)
        return self.sock
    
    def __exit__(self, exc_ty, exc_val, tb):
        self.sock.close()
        self.sock = None
        
if __name__ == '__main__':
    from functools import partial
    
    with conn as s:
        s.send(b'GET /index.html HTTP/1.0\r\n')
        s.send(b'HOST: www.python.org\r\n')
        s.send(b'\r\n')
        resp = b''.join(iter(partial(s.recv, 8192), b''))
```

### 创建大量实例时如何节省内存

对于那些主要用作简单数据结构的类，通常可以在类定义中增加`__slot__`属性，以此来大量减少对内存的使用

```python
class Date:
    __slots__ = ['year', 'month', 'day']
    def __init__(self, year, month, day):
        self.year = year
        self.month = month
        self.day = day
```

当定义了`__slots__`属性时，Python会针对实例采用一种更加紧凑的内部表示，不再是让每个实例都创建一个`__dict__`字典，现在的实例是围绕一个固定长度的小型数组来构建的。**有个缺点是无法再对实例添加任何新的属性，被限制只允许使用`__slots__`中列出的属性名。**

### 让属性具有惰性求值的能力

想将一个只读的属性定义为property属性方法，只有在访问它时才参与计算。但是，一旦访问了该属性，希望把计算出的值缓存起来，不要每次访问它时都重新计算。（利用描述符类来实现）

```python
class lazyproperty:
     def __init__(self, func):
         self.func = func
     
     def __get__(self, instance, cls):
         if instance is None:
             return self
         else:
             value = self.func(instance)
             setattr(instance, self.func.__name__, value)
             return value
             
 import math
 class Circle:
     def __init__(self, radius):
         self.radius = radius
     
     @lazyproperty
     def area(self):
         print("Computing area")
         return math.pi * self.radius ** 2
     
     @lazyproperty
     def perimeter(self):
         print("Computing perimeter")
         return 2 * math.pi * self.radius
         
 >>> c = Circle(4.0)
 >>> c.radius
 4.0
 >>> c.area
 Computing area
 50.26548245743669
 >>> c.area
 50.26548245743669
 >>> c.perimeter
 Computing perimeter
 25.132741228718345
 >>> c.perimeter
 25.132741228718345 
```

### 简化数据结构的初始化过程

假设编写了很多类，都当作数据结构来用，可以将初始化数据结构的步骤归纳到一个单独的init函数中，并将其定义在一个公共的基类中

```python
class Structure:
    _fields = []
    def __init__(self, *args):
        if len(args) != len(self._fields):
            raise TypeError("Expected {} arguments".formate(len(self._fields)))
        for name, vlaue in zip(self._fields, args):
            setattr(self, name, value)
    
if __name__ == '__main__':
    class Stock(Structure):
        _fields = ['name', 'shares', 'price']
    
    class Point(Structure):
        _fields = ['x', 'y']
    
    class Circle(Structure):
        _fileds = ['radius']
        def area(self):
            return math.pi * self.raidus ** 2
```

### 定义一个接口或抽象基类

想定义一个类作为接口或者是抽象基类，这样可以在此之上执行类型检查并确保在子类中实现特定方法。抽象基类不能被直接实例化，相反，抽象基类是给其他类当作基类使用，这些子类需要实现基类中的要求的方法

```python
from abc import ABCMeta, abstractmethod

class IStream(metaclass=ABCMeta):
    @abstractmethod
    def read(self, maxbytes=-1):
        pass
    
    @abstractmethod
    def write(self, data):
        pass

class SocketStream(IStream):
    def read(self, maxbytes=-1):
        ...
    
    def write(self, data):
        ...
```

抽象基类的主要用途是强制规定所需的编程接口。例如，一种看待IStream基类的方式就是在高层次指定一个接口规范，使其允许读取和写入数据

```python
def serialize(obj, stream):
    if not isinstance(stream, IStream):
        raise TypeError('Expected an IStream')
```

### 实现一种数据模型或类型系统

希望自定义各种各样的数据结构，但是对于某些特定的属性，想对允许赋值给它们的值强制添加一些限制。

```python
# Base class. Uses a descriptor to set a value
class Descriptor:
    def __init__(self, name=None, **opts):
        self.name = name
        for key, value in opts.items():
            setattr(self, key, value)
    
    def __set__(self, instance, value):
        instance.__dict__[self.name] = value
        
# Descriptor for enforcing types
class Typed(Descriptor):
    expected_type = type(None)
    def __set__(self, instance, value):
        if not instance(value, self.expected_type):
            raise TypeError('expected ' + str(self.expected_type)
        super().__set__(instance, value)
        
# Descriptor for enforcing values
class Unsigned(Descriptor):
    def __set__(self, instance, value):
        if value < 0:
            raise ValueError('Expected > 0')
        super().__set__(instance, value)
        
class MaxSized(Descriptor):
    def __init__(self, name=None, **opts):
        if 'size' not in opts:
            raise TypeError('missing size option')
        super().__init__(name, **opts)
        
    def __set__(self, instance, value):
        if len(value) >= self.size:
            raise ValueError('size must be < ' + str(self.size))
        super().__set__(instance, value)
```

### 实现带有状态的对象或状态机

**Bad Smell**

```python
class Connection:
    def __init__(self):
        self.state = 'CLOSED'
    
    def read(self):
        if self.state != "OPEN":
            raise RuntimeError('Not open')
        print('reading')
    
    def write(self, data):
        if self.state != 'OPEN':
            raise RuntimeError('Not open')
        print('writing')
    
    def open(self):
        if self.state == 'OPEN':
            raise RuntimeError('Already open')
        self.state = 'OPEN'
    
    def close(self):
        if self.state == 'CLOSED':
            raise RuntimeError('Already closed')
        self.state = 'CLOSED'
```

**Good Case**

```python
class Connection:
    def __init__(self):
        self.new_state(ClosedConnectionState)
    
    def new_state(self, newstate):
        self._state = newstate
    
    def read(self):
        return self._state.read(self)
    
    def write(self, data):
        return self._state.write(self, data)
    
    def open(self):
        return self._state.open(self)
        
    def close(self):
        return self._state.close(self)
        
class ConnectionState:
    @staticmethod
    def read(conn):
        raise NotImplementedError()
    
    @staticmethod
    def write(conn, data):
        raise NotImplementedError()
    
    @staticmethod
    def open(conn):
        raise NotImplementedError()
    
    @staticmethod
    def close(conn):
        raise NotImplementedError()
        
class ClosedConnectionState(ConnectionState):
    @staticmethod
    def read(conn):
        raise RuntimeError('Not open')
    
    @staticmethod
    def write(conn, data):
        raise RuntimeError('Not open')
    
    @staticmethod
    def open(conn):
        conn.new_state(OpenConnectionState)
    
    @staticmethod
    def close(conn):
        raise RuntimeError('Already closed')
        
class OpenConnectionState(ConnectionState):
    @staticmethod
    def read(conn):
        print('reading')
    
    @staticmethod
    def write(conn, data):
        print('writing')
    
    @staticmethod
    def open(conn):
        raise RuntimeError('Already open')
    
    @staticmethod
    def close(conn):
        conn.new_state(ClosedConnectionState)
```

### 调用对象上的方法

使用operator.methodcaller()方法

```python
mport math

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    def __repr__(self):
        return 'Point({!r:}, {!r:}}'.format(self.x, self.y)
    
    def distance(self, x, y):
        return math.hypot(self.x - x, self.y - y)
        
>>> p = Point(3, 4)
>>> d = operator.methodcaller('distance', 0, 0)
>>> d(p)
```


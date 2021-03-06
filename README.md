# top100url

## 目标

现有100GB URL文件，利用1GB可用内存，筛选出出现次数前100的所有URL及其出现次数。

## 思路

1. 读入原始输入文件，将文件分成多个小文件
2. 对每个小文件进行map操作，从url映射到«hash,count,url»的元组
3. 对映射之后的文件进行reduce操作，对url相同的条目规约
4. 用归并排序合并每个处理过的小文件，迭代执行直到只剩下一个文件
5. 在最终剩下的文件中找出现次数最多的100个url

如果url重复较多，这种方法的效率应该会比较好；如果url重复较少，这种方法可能会冗余存储，造成一定的空间浪费。

## 格式

假设输入文件中的url全部使用utf-8编码，即所有的url均已转换为ascii码的形式，不存在ascii码以外的字符。
url之间以空白字符分隔。

输出的结果文件包含url和其对应的统计次数，全部以换行符分隔。

因为主流的浏览器大多将url长度限制为65536，我在程序中假定url最大长度为65536。

## 代码

### src/

**config.h/config.cpp**

保存程序中一些参数的配置信息。
因为时间较少，我暂时没有添加动态修改参数的功能。

**utils.h**

定义了两个结构体`FileInfo`和`UrlCnt`。
`FileInfo`保存文件名和输出到文件的字节数。
`UrlCnt`保存一个url的hash值，统计值count和url字符串。

**input.h/input.cpp**

定义了带缓冲区的输入类`Input`。可以读取文本或二进制文件。

**output.h/output.cpp**

定义了带缓冲的输出类`Output`。可以向文本或二进制文件写入。

**partition.h/partition.cpp**

定义了对输入文件分块的类`Partition`。利用`Partiition`将输入文件分成一个个小文件。

**reduce.h/reduce.cpp**

定义了类`Reduce`，实现了对小文件的mapreduce操作。
当前程序使用4个线程并行对4个文件执行reduce操作。

**merge.h/merge.cpp**

定义了类`Merge`。利用归并排序合并小文件。形成总体的统计数据。
当前程序使用8个线程并行执行merge操作。

**main.cpp**

实现了top100url的整个流程，以及最后筛选前100url的操作。

### test/

**test.cpp**

测试程序

**gen_urls.cpp**

生成样例程序

## 运行

### 编译

编译top100url程序，程序使用了openmp

```
g++ \
        -O3 -std=c++14 -Wall -fopenmp \
        -o bin/top100url src/*.cpp
```

编译测试程序

```
g++ -o bin/test \
        test/test.cpp \
        src/input.cpp \
        src/output.cpp \
        src/partition.cpp \
        src/reduce.cpp \
        src/merge.cpp \
        -Og -std=c++14 -Wall
```

编译样例生成程序

```
g++ -o bin/gen_urls test/gen_urls.cpp src/output.cpp -O3 -std=c++14 -Wall
```

### 运行top100url

```
bin/top100url {inputfile} {outputfile}
```

### 运行测试程序

测试分块（所有测试的输出文件都在_test目录下）

```
bin/test partition < {inputfile}
```

测试reduce

```
bin/test reduce < _test/part-00001 > _test/iter-00-00001
```

测试merge

```
bin/test merge
```

查看urlcnt

```
bin/test urlcnt < _test/iter-00-00003  
```

### 生成样例

因为编码后的url内容全部是ascii值，且url中不包含空白字符，可以通过生成非空字符串来替代真实URL作为样例

```
bin/gen_urls 100000000 > resources/urls0.txt
```

## 结果

我通过下列命令执行了多次测试，测试结果均保持一致，内存最大用量可控制在800MB左右。

```
bin/gen_urls 100000000 > resources/urls0.txt
bin/top100url resources/urls0.txt results/result0.txt
```

## 题目描述

伊万喜欢打游戏。在游戏里有 $n$ 个任务。每个任务可以被升级一次，这样可以提高完成时的收益。每个任务有三个参数 $a_i, b_i, p_i$。

$a_i$：升级**前**完成任务的收益。  
$b_i$：升级**后**完成任务的收益。$(a_i < b_i)$
$p_i$：完成这个任务的概率。

每秒伊万都可以尝试一个任务，且他有 $p_i$ 的概率成功。
1. 如果伊万成功完成这个任务，他会获得：
    - 这个任务对应的收益。
    - 一次升级任意一个任务的机会。（不一定是他刚完成的这一个）

2. 如果伊万没有成功完成这个任务，他什么都得不到。

**任务在完成后不会消失**

伊万有 $t$ 秒来玩游戏，他想知道他 $t$ 秒之后期望收益的**最大值**。

## 输入格式

第一行有两个整数 $n$ 和 $t$，即任务的个数和总时间。

之后的 $n$ 行，每行包括一个任务的参数。  
参数包括三个数：$a_i, b_i, p_i$。

## 输出格式

一行：期望收益的最大值。

精度误差不超过 $10^{-6}$ 即可 AC。  
具体来说：假设你的答案是 $a$，std 的答案是 $b$，只要满足 $\frac{|a - b|}{\operatorname{max}(b, 1)} \leq 10^{-6}$ 即可 AC。

### 样例 #1

**输入**
```plaintext
3 2
3 1000 0.5
1 2 0.48
3 20 0.3
```

**输出**
```plaintext
252.2500000000000
```

### 样例 #2

**输入**
```plaintext
2 2
1 1000 0.1
2 3 0.2
```

**输出**
```plaintext
20.7200000000000
```

## 数据范围

$1 \leq n \leq 10^5$

$1 \leq t \leq 10^{10}$

$1 \leq a_i \leq b_i \leq 10^8$

$0 < p_i < 1$  
$p_i$ 最多有 9 位小数。

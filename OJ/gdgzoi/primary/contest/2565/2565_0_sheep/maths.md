举例：

$$
\begin{align*}
    S &= (1 + 2 + 4)(1 + 3 + 9)\\
      &= (2 + 4 + 3 + 9) + (2\times3) + (2\times9) + (4\times3) + (4\times9)\\
      &= 7\times13 = 91
\end{align*}
$$

可以看出 $S$ 即为 $2^3\times3^2 = 72$ 的因数和。  
推广到一般：

$$
\begin{align}
    S = (1 + p_1^{1b} + p_1^{2b} + \dots + p_1^{k_1b}) \times \dots \times(1 + p_m^{1b} + p_m^{2b} + \dots + p_m^{k_mb})
\end{align}
$$

等比数列求和公式：

$$
    S_n = \frac{a_1 \times (1 - q^n)}{1 - q} = \frac{a_1 - a_nq}{1 - q} = \frac{a_nq - a_1}{1 - q}
$$

$n$ 为项数，$S_n$ 为和，$q$ 为公比，$a_1$ 为首项，$a_n$ 为末项。  
此题中：

$$
\begin{align*}
    &n = m (m 为质因数个数)\\
    &q = p_i\\
    &a_1 = 1\\
    &a_n = p_i^{k_ib}
\end{align*}
$$

代入式中，可见：

$$
\begin{align}
    S &= \prod_{i = 1}^{m} \frac{p_i ^ {k_ib + 1} - 1}{p_i - 1}
\end{align}
$$

其中，除法取模用费马小定理求乘法逆元。

$$
\begin{align}
    S &= \prod_{i = 1}^{m} (p_i ^ {k_ib + 1} - 1) \times (p_i - 1) ^ {(mod - 2)}
\end{align}
$$
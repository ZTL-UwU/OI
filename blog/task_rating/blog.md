# 简单的任务难度评估的算法（ELO）

适用于简单的任务如题目，象棋谜题等。**不保证合适**

$$
P = \frac{1}{1 + 10 ^ {\frac{Rp - R_0}{400}}}\\
R_n = R_0 + K(O - P)
$$

其中 $R_n$ 为新 Rating，$R_0$ 为旧 Rating.

若玩家回答正确，$O = 1$，否则 $O = 0$.

$K_0$ 为常数，推荐为 $32$.

- 对于任务的 Rating 更新，$K = -\frac{(K_0 + \frac{1}{n})|R_0 -R_p|}{200}$，其中 $n$ 为尝试过该题的人数.

- 对于玩家的 Rating 更新，$K = K_0$.

## C++ 实现
```cpp
#include <iostream>
#include <cmath>

double puzzle_elo = 1500;
const double K0 = 32.0;
int n = 0;

int main()
{
    while (true)
    {
        // One attempt

        double player_elo, O;
        // Correct -> O = 1
        // Wrong   -> O = 0
        std::cin >> player_elo >> O;
        n++;

        const double P = 1.0 / (1 + std::pow(10.0, (puzzle_elo - player_elo) / 400.0));

        // Rating update
        puzzle_elo -= ((K0 + 1 / n) * std::fabs(((puzzle_elo - player_elo) / 200.0))) * (O - P);
        player_elo += K0 * (O - P);

        std::cout << "Puzzle: " << puzzle_elo << "\n" << "Player: " << player_elo << "\n";
    }

    return 0;
}
```

## Python 实现
```python
puzzle_elo = 1500
n = 0
K0 = 32

while True:
    player_elo = float(input('Player Rating: '))
    O = float(input('Correct?: '))
    n += 1

    P = 1 / (1 + 10 ** ((puzzle_elo - player_elo) / 400))

    puzzle_elo -= (K0 + 1 / n) * abs((puzzle_elo - player_elo) / 200) * (O - P)
    player_elo += K0 * (O - P)

    print('Puzzle: {}\nPlayer: {}'.format(puzzle_elo, player_elo))
```

## 参考资料：

- [Elo Rating Algorithm for the Purpose of Measuring Task Difficulty in Online Learning Environments](https://www.researchgate.net/publication/339667564_Elo_Rating_Algorithm_for_the_Purpose_of_Measuring_Task_Difficulty_in_Online_Learning_Environments)
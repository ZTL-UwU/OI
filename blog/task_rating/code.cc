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
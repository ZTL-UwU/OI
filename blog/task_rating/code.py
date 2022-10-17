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
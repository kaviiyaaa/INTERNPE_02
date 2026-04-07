#include <emscripten/emscripten.h>
#include <cstdlib>
#include <ctime>

static int player_score = 0;
static int computer_score = 0;
static int rounds = 0;

extern "C" {

EMSCRIPTEN_KEEPALIVE
void init_game() {
    srand((unsigned int)time(0));
    player_score = 0;
    computer_score = 0;
    rounds = 0;
}

EMSCRIPTEN_KEEPALIVE
int get_computer_choice() {
    return rand() % 3;  // 0=Rock, 1=Paper, 2=Scissors
}

// Returns: 0=draw, 1=player wins, 2=computer wins
EMSCRIPTEN_KEEPALIVE
int play_round(int player, int computer) {
    rounds++;
    if (player == computer) return 0;
    if ((player == 0 && computer == 2) ||
        (player == 1 && computer == 0) ||
        (player == 2 && computer == 1)) {
        player_score++;
        return 1;
    }
    computer_score++;
    return 2;
}

EMSCRIPTEN_KEEPALIVE
int get_player_score()   { return player_score; }

EMSCRIPTEN_KEEPALIVE
int get_computer_score() { return computer_score; }

EMSCRIPTEN_KEEPALIVE
int get_rounds()         { return rounds; }

}
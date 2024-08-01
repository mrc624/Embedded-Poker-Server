#include <stdbool.h>

#define POKER_NAME_LEN 20
#define POKER_PLAY_ATTRIBUTES 3;
#define DEFAULT_NAME "DEFAULT"
#define POKER_PLAYER_MAX 10
#define DEFAULT_BUY_INS 0
#define DEFAULT_GAIN 0

struct poker_player{
    char name[POKER_NAME_LEN + 1];
    unsigned short int buy_ins;
    signed long int gain;
};

enum poker_player_index{
    POKER_NAME,
    POKER_BUY_INS,
    POKER_GAIN,
    POKER_NUM_STATS
};

unsigned short int get_total_buy_in(struct poker_player *data);
struct poker_player init_player(struct poker_player *player);
void print_player_to_terminal(struct poker_player *player);
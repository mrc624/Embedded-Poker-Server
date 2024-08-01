#include <stddef.h>
#include <stdio.h>
#include "poker.h"

unsigned short int get_total_buy_in(struct poker_player *data)
{
    unsigned short int total;
    while(data->buy_ins != 0)
    {
        total += data->buy_ins;
    }
    return total;
}

struct poker_player init_player(struct poker_player *player)
{
    sprintf(player->name, "%s" ,DEFAULT_NAME);
    player->buy_ins = DEFAULT_BUY_INS;
    player->gain = DEFAULT_GAIN;
    return *player;
}

void print_player_to_terminal(struct poker_player *player)
{
    printf("-----PRINTING PLAYER-----\n");
    printf("Name: %s\nBuy Ins: %u\nGain: %ld\n", player->name, player->buy_ins, player->gain);
    printf("-----DONE PRINTING-----\n");
}
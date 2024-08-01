#include <stdio.h>
#include <stdlib.h>
#include "csv.h"
#include "poker.h"

bool csv_create(const char* name)
{
    if(csv_safe(name))
    {
        printf("Succesfully created %s file\n", name);
        return true;
    }
    else
    {   
        printf("Error in creating %s file\n", name);
        return false;
    }
}

bool csv_safe(const char* name)
{
    if(strlen(name) <= MAX_POKER_FILE_NAME_LEN)
    {
        FILE *file;

        char buf[MAX_POKER_FILE_NAME_LEN + PATH_POKER_LEN + 1];
        sprintf(buf,"%s%s", PATH_POKER, name);

        file = fopen(buf, "w");

        if(file == NULL)
        {
            printf("%s is not safe, Proposed path: %s\n", name, buf);
            fclose(file);
            return false;
        }
        else
        {
            printf("%s is safe, Path: %s\n", name, buf);
            fclose(file);
            return true;
        }
    }
    else
    {
        printf("Invalid file name: %s\n", name);
        return false;
    }

}

FILE* get_file(const char* name, const char* action)
{
    FILE* file;
    char buf[MAX_POKER_FILE_NAME_LEN + PATH_POKER_LEN + 1];
    sprintf(buf,"%s%s", PATH_POKER, name);
    file = fopen(buf, action);
    return file;
}

void print_file_to_terminal(FILE *file)
{
    signed char c;
    printf("-----FILE START-----\n");
    c = fgetc(file); 
    while (c != EOF) 
    { 
        printf ("%c", c); 
        c = fgetc(file); 
    }
    printf("-----FILE END-----\n");
    fclose(file);
}

struct poker_player get_player_from_file(const char* name, FILE* file)
{
    struct poker_player player;
    init_player(&player);
    bool name_found = false;
    char row[100];
    char *token;
    unsigned char count = 0;
    while (feof(file) != true)
    {
        name_found = false;
        fgets(row, sizeof(row), file);
        token = strtok(row, ",");
        count = 0;
        while(token != NULL)
        {
            switch(count)
            {
                case POKER_NAME:
                    if(strcmp(token, name) == 0)
                    {
                        name_found = true;
                        sprintf(player.name, "%s", token);
                    }
                    break;
                case POKER_BUY_INS:
                    if(name_found)
                    {
                        player.buy_ins = strtoul(token, NULL, 10);
                    }
                    break;
                case POKER_GAIN:
                    if(name_found)
                    {
                    player.gain = strtol(token, NULL, 10);
                    }
                    break;
                default:
                    printf("ERROR UNKNOWN CASE\n");
                    break;
            }
            count++;
            token = strtok(NULL, ",");
        }

    }

    return player;
}

#include <unistd.h>

bool player_exists(const char* name)
{
    FILE* file = get_file("net_data.csv", "r");
    if(file != NULL)
    {
        char row[100];
        char *token;
        while (feof(file) != true)
        {
            fgets(row, sizeof(row), file);
            token = strtok(row, ",");
            while(token != NULL)
            {
                printf("TOKEN: %s\n", token);
                if(strcmp(name, token) == 0)
                {
                    return true;
                }
                token = strtok(NULL, ",");
            }

        }
    }
    else
    {
        printf("ERROR IN PLAYER_EXISTS FUNCTION - FILE NULL");
    }
    return false;
}

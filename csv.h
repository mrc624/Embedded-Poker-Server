#include <stdbool.h>
#include <string.h>

#define PATH_POKER "./poker_files/"
#define PATH_POKER_LEN strlen(PATH_POKER)
#define MAX_POKER_FILE_NAME_LEN 20

bool csv_create(const char* name);
bool csv_safe(const char* name);
FILE* get_file(const char* name, const char* action);
void print_file_to_terminal(FILE *file);
struct poker_player get_player_from_file(const char* name, FILE* file);
bool player_exists(const char* name);
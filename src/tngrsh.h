#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



#define TNGRSHL_BUFSIZE 1024
#define TNGRSHL_TOK_BUFSIZE 64
#define TNGRSHL_TOK_DELIM " \t\r\n\a"
#define TNGRSHL_SPECIAL_TOKEN_DELIM "SPORT!"

// Core functions
void lets_party(void);
char *crack_a_block(void);
char **crack_a_sport(char *can);
int finish_your_sport(char **open_can);
int drinking_game_launch(char **mouthfuls);


//Builtins
int tngrsh_cd(char **args); //Swap blocks
int tngrsh_help(char **args); //Ask Ken
int tngrsh_exit(char **args); //GTFO before you have to help clean in the morning

char *builtin_str[] = {
	"sb",
	"ask_ken",
	"exit"
};

int (*builtin_func[]) (char **) = {
	&tngrsh_cd,
	&tngrsh_help,
	&tngrsh_exit
};

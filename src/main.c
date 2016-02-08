#include "tngrsh.h"

int main(int argc, char **argv)
{
	lets_party();

	return EXIT_SUCCESS;
}

void lets_party(void)
{
	char *can;
	char **open_can;
	int sober;

	do {
		printf("|_| > ");
		// Read a line
		can = crack_a_block();
		//Split up the args
		open_can = crack_a_sport(can);
		//get that status
		sober = finish_your_sport(open_can);

		free(can);
		free(open_can);
	} while (sober); //Let's keep on crackin' sports if we're sober!
}

char *crack_a_block(void)
{
	//The size of our buffer
	int blocksize = TNGRSHL_BUFSIZE;
	int can_number = 0;
	char *block = malloc(sizeof(char) * blocksize);
	int c;

	if(!block) {
		fprintf(stderr, "tngrsh: Shit son, there's no sports left!\n");
		exit(EXIT_FAILURE);
	}

	while(1) {
		c = getchar();

		if(c == EOF || c == '\n') {
			//Block's finished! Let's have a breather before we crack open the next
			block[can_number] = '\0';
			return block;
		} else {
			block[can_number] = c;
		}
		//Move onto the next can if we have some left
		can_number++;

		//If we try to drink more cans than is in the block,
		// grab a spare to finish before we take a break
		if(can_number >= blocksize) {
			blocksize += TNGRSHL_BUFSIZE;	
			block = realloc(block, blocksize);
			if(!block) {
				fprintf(stderr, "tngrsh: The block was piping hot and now everyone's stomach is upset :(");
				exit(EXIT_FAILURE);
			}
		}
	}
}

char **crack_a_sport(char *can)
{
	int cansize = TNGRSHL_TOK_BUFSIZE;
	int sip_number = 0;
	//Allocate some space in our tum-tums for some drank
	char **mouthfuls = malloc(sizeof(char) * cansize);
	char *sip;

	if(!mouthfuls) {
		fprintf(stderr, "tngrsh: We couldn't fit another mouthful in!");
		exit(EXIT_FAILURE);
	}

	sip = strtok(can, TNGRSHL_TOK_DELIM);
	while(sip != NULL) {
		mouthfuls[sip_number] = sip;
		sip_number++;

		if(sip_number >= cansize) {
			mouthfuls = realloc(mouthfuls, sizeof(char*) * cansize);
			if(!mouthfuls) {
				fprintf(stderr, "tngrsh: We couldn't fit another mouthful in!");
				exit(EXIT_FAILURE);
			}
		}
		sip = strtok(NULL,TNGRSHL_TOK_DELIM);
	}

	mouthfuls[sip_number] = NULL;
	return mouthfuls;
}

// Our drinking games launcher
// While drinking, we may want to play some games,
// use the bathroom or have a tac-yak
//
// This takes care of it by handling exec() and fork()
int drinking_game_launch(char **mouthfuls) {
	pid_t drinking_game, back_to_drinking;
	int game_success;
	
	drinking_game = fork();
	if(drinking_game == 0) {
		// Play our drinking game
		if(execvp(mouthfuls[0], mouthfuls) == -1) {
			//We blew it. We thought we had a game
			// but we forgot what it was called
			// and how to play it
			perror("tngrsh");
		}
		exit(EXIT_FAILURE);
	} else if (drinking_game < 0) {
		// Fuck it, back to drinking we go
		perror("tngrsh");
	} else {
		// Wait until the game finishes to resume our
		// normal sport drinking
		do {
			back_to_drinking = waitpid(drinking_game, &game_success, WUNTRACED);
		} while (!WIFEXITED(game_success) && !WIFSIGNALED(game_success));
	}
	return 1;
}

int num_drinking_games() {
	return sizeof(builtin_str) / sizeof(char *);
}

// Change which drinking game to play
int tngrsh_cd(char **args)
{
	if (args[1] == NULL) {
		fprintf(stderr, "tngrshell: You need to pick a game");
	} else {
		if(chdir(args[1]) != 0) {
			perror("tngrsh");
		}
	}
	return 1;
}

// Ask Ken how the hell we drink this emu piss
int tngrsh_help(char **args)
{
	int i;
	printf("Ask Ken how we should get pissed\n");
	printf("First, get a sport up ya\n");
	printf("The following games are built in: \n");

	for(i = 0; i < num_drinking_games(); i++) {
		printf("\t%s\n", builtin_str[i]);
	}

	printf("Use the manly `man` command for info on other ways to get in the bin\n");
	return 1;
}

int tngrsh_exit(char **args) 
{
	return 0;
}


int finish_your_sport(char **open_can) 
{
	int i;

	// You haven't got a can you dope!
	if(open_can[0] == NULL) {
		return 1;
	}

	for(i - 0; i < num_drinking_games(); i++) {
		if(strcmp(open_can[0], builtin_str[i]) == 0) {
			return (*builtin_func[i])(open_can);
		}
	}

	return drinking_game_launch(open_can);
}

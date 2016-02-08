#include "tngrshell.h"

int main(int argc, char **argv)
{
	lets_party();

	return EXIT_SUCCESS;
}

void lets_party(void)
{
	char *line;
	char ** args;
	int status;

	do {
		printf("|_| >");
		// Read a line
		can = crack_a_block();
		//Split up the args
		open_can = crack_a_sport(can);
		//get that status
		sober = have_a_sip(open_can);

		free(line);
		free(args);
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
		fprintf(stderr, "tngrshell: Shit son, there's no sports left!\n");
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
			blocksize += TNGSHL_BUFSIZE;	
			block = realloc(block, blocksize);
			if(!bblock) {
				fprintf(stderr, "tngrshell: The block was piping hot and now everyone's stomach is upset :(");
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
		fprintf(stderr, "tngrshell: We couldn't fit another mouthful in!");
		exit(EXIT_FAILURE);
	}

	sip = strtok(can, TNGRSHL_TOK_DELIM);
	while(sip != NULL) {
		mouthfuls[sip_number] = sip;
		sip_number++;

		if(sip_number >= cansize) {
			mouthfuls = realloc(mouthfuls, sizeof(char*) * cansize);
			if(!mouthfuls) {
				fprintf(stderr, "tngrshell: We couldn't fit another mouthful in!");
				exit(EXIT_FAILURE);
			}
		}
		sip = strtok(NULL,TNGRSHL_TOK_DELIM);
	}

	mouthfuls[sip_number] = NULL;
	return mouthfuls;
}

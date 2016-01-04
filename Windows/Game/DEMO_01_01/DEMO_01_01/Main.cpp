#include <stdio.h>


// defines for game loop states
#define GAME_INIT		1	// the game is initializing
#define GAME_MENU		2	// the game is in the menu mode
#define GAME_STARTING	3	// the game is about to run
#define GAME_RUN		4	// the game is now running
#define GAME_RESTART	5	// the game is going to restart
#define GAME_EXIT		6	// the game is exiting

// game globals
int game_state	= GAME_INIT;
int error		= 0;

void Init() 
{
	printf("Init\n");
}

int Menu() 
{
	printf("Menu\n");
	return GAME_STARTING;
}

void Setup_For_Run() 
{
	printf("Setup_For_Run\n");
}

void Clear() 
{
	printf("Clear\n");
}

void Get_Input() 
{
	printf("Get_Input\n");
}

void Do_Logic() 
{
	printf("Do_Logic\n");
}

void Render_Frame() 
{
	printf("Render_Frame\n");
}

void Wait() 
{
	printf("Wait\n");
}

void Fixup() 
{
	printf("Fixup\n");
}

void Release_And_Cleanup() 
{
	printf("Release_And_Cleanup\n");
}


int main()
{
	// implementation of main game loop
	while (GAME_EXIT != game_state)
	{
		// what state is game loop in
		switch (game_state)
		{
			// the game is initializing
		case GAME_INIT:
			{
				// allocate all memory and resources
				Init();

				// move to menu state
				game_state = GAME_MENU;
			} break;

			// the game is in the menu mode
		case GAME_MENU:
			{
				// call the main menu function and let it switch states
				game_state = Menu();
			} break;

			// the game is about to run
		case GAME_STARTING:
			{
				// this state is optional, but usually used to set things up right before the game is run
				// you might do a little more housekeeping here
				Setup_For_Run();
				game_state = GAME_RUN;
			}break;

			// the game is now running
		case GAME_RUN:
			{
				// this section contains the entire game logic loop
				// clear the display
				Clear();

				// get the input
				Get_Input();

				// perform logic and AI
				Do_Logic();

				// display the next frame of animation
				Render_Frame();

				// synchronize the display
				Wait();

				// the only way that state can be changed is thru user interaction in theinput section
				// or by maybe losing the game.
			} break;

			// the game is restarting
		case GAME_RESTART:
			{
				// this section is a cleanup state used to fix up any loose ends before running again
				Fixup();

				// switch states back to the menu
				game_state = Menu();
			} break;

			// the game is exiting
		case GAME_EXIT:
			{
				// if the game is in this state then it's time to bail,
				// kill everything and cross your fingers
				Release_And_Cleanup();

				// set the error word to whatever
				error = 0;
			} break;


		default:
			break;
		}
	}

	return (error);

	return 0;
}

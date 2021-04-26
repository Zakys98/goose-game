
#include "../include/game.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
	// Game* game = game_init();
	// game_create(game);
	// game_create_from_file(game, "./test_data.dat");
	
	// FILE* fout = fopen("./saved_game.dat", "w");
	// game_save(fout, game);

	Game* game1 = game_init();
	game_create(game1);
	game_create_from_file(game1, "./saved_game.dat");
	
	
	game_destroy(game1);
	//game_destroy(game);
	//fclose(fout);
	return 0;
}
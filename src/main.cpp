#include <game.h>

int main() {
	Game game;

	while (game.running()) {
		//Update
		game.update();

		//Render
		game.render();
	}
}
#include "game.hpp"
#include "board.hpp"
#include "piece.hpp"
#include <SFML/Graphics.hpp>

Game::Game() {
	window.create(sf::VideoMode(800, 800), "chess");
	window.setVerticalSyncEnabled(true);
	setupPieces();
}

Game::~Game() {
	window.close();
}

void Game::loop() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::White);
		board.draw(window);
		for (auto& p : whites) p.draw(window);
		for (auto& p : blacks) p.draw(window);
		window.display();
	}
}

void Game::setupPieces() {
	setupTeam(whites, Piece::White);
	setupTeam(blacks, Piece::Black);
}

void Game::setupTeam(Piece team[16], bool teamColor) {
	float sqsize = board.getSquareSize();
	char voffset = (teamColor * 8) + !teamColor;
	for (uint i = 0; i < 8; i++) {
		team[i].setTeam(teamColor);
		team[i].setLocation(i, 'a' + (voffset - 1), sqsize);

		team[8 + i].setTeam(teamColor);
		team[8 + i].setLocation(i, 'b' + (voffset - 1 - (2 * teamColor)), sqsize);
		team[8 + i].setType(PAWN);
	}

	team[0].setType(TOWER);
	team[7].setType(TOWER);
	team[1].setType(HORSE);
	team[6].setType(HORSE);
	team[2].setType(BISHOP);
	team[5].setType(BISHOP);
	team[3].setType(QUEEN);
	team[4].setType(KING);
}
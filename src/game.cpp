#include "headers/game.hpp"
#include "headers/board.hpp"
#include "headers/piece.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game() {
	window.create(sf::VideoMode(800, 800), "chess");
	window.setVerticalSyncEnabled(true);
	setupPieces();
	previousSelection = NULL;
}

Game::~Game() {
	window.close();
}

void Game::enventHandler() {
	sf::Vector2f cursorPosition = (sf::Vector2f)sf::Mouse::getPosition(window);
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			for (uint i = 0; i < 8; i++) {
				for (char j = 0; j < 8; j++) {
					Square& square = board.getSquare(Location(i, j));
					if (square.getShape().getGlobalBounds().contains(cursorPosition)) {
						if (previousSelection)
							previousSelection->deselect();
						previousSelection = square.select();
					}
				}
			}
		}
		// else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	}
}

void Game::loop() {
	while (window.isOpen()) {
		enventHandler();
		window.clear(sf::Color::Black);
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
	float sqsize = board.getSquare(Location(0, 0)).getSize();
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
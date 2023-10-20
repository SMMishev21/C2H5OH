#include "app.hpp"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

void App::initWindow() {
	this->voidTexture.loadFromFile("./Assets/void.png");
	this->wallTexture.loadFromFile("./Assets/tile.png");

	textureMap = {
		{0, this->voidTexture},
		{1, this->wallTexture},
	};

	map = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};

	for (int i = 0; i < 9; i++) {
		this->tiles.push_back(std::vector<Sprite>());
		for (int j = 0; j < 16; j++) {
			Sprite sprite;

			sprite.setTexture(textureMap[this->map[i][j]]);
			sprite.setPosition(j * 80, i * 80);
			this->tiles[i].push_back(sprite);
			this->tiles[i][j].setScale(5, 5);
		}
	}

	this->selectorBorder.setSize(Vector2f(80,80));
	this->selectorBorder.setOutlineThickness(-3);
	this->selectorBorder.setFillColor(Color::Transparent);
	this->selectorBorder.setOutlineColor(Color::White);
	this->selectorBorder.setPosition(1330, 20);

	this->characterSelector.setSize(Vector2f(80, 80));
	this->characterSelector.setOutlineThickness(-3);
	this->characterSelector.setFillColor(Color::Transparent);
	this->characterSelector.setOutlineColor(Color::White);
	this->characterSelector.setPosition(1430, 320);

	this->selectorVoid.setTexture(this->voidTexture);
	this->selectorWall.setTexture(this->wallTexture);

	this->selectorVoid.setPosition(1330, 20);
	this->selectorWall.setPosition(1330, 120);

	this->saveButton.setPosition(1350, 630);
	this->saveButton.setSize(Vector2f(140, 60));
	this->saveButton.setOutlineThickness(2);
	this->saveButton.setOutlineColor(Color::White);
	this->saveButton.setFillColor(Color(54, 201, 115));

	this->currentTile = 0;
	this->currentCharacter = 0;

	this->window.create(VideoMode(1560, 720), "Custom Map Builder");
	updateWindow();
}

void App::updateWindow() {
	while (this->window.isOpen()) {
		while (this->window.pollEvent(this->event)) {
			if (event.type == Event::Closed) {
				this->window.close();
			}
			else if (event.type == Event::MouseButtonPressed) {
				handleInput();
			}
		}

		renderWindow();
	}
}

void App::renderWindow() {
	this->window.clear(Color(0,0,0));

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 16; j++) {
			this->window.draw(tiles[i][j]);
		}
	}

	this->window.draw(this->selectorVoid);
	this->window.draw(this->selectorWall);
	//this->window.draw(this->characterSelector);

	this->window.draw(this->selectorBorder);

	this->window.draw(this->saveButton);

	this->window.display();
}

void App::handleInput() {
	if (this->event.mouseButton.button == 0) {
		float x = event.mouseButton.x;
		float y = event.mouseButton.y;

		if (x < 1280) {
			int tileX = x / 80;
			int tileY = y / 80;

			this->map[tileY][tileX] = this->currentTile;
			this->tiles[tileY][tileX].setTexture(textureMap[map[tileY][tileX]]);
			this->tiles[tileY][tileX].setScale(5, 5);
		}
		else {
			Vector2f voidStartPos(this->selectorVoid.getPosition().x, this->selectorVoid.getPosition().y);
			Vector2f voidEndPos(this->selectorVoid.getPosition().x + 80, this->selectorVoid.getPosition().y + 80);

			Vector2f wallStartPos(this->selectorWall.getPosition().x, this->selectorWall.getPosition().y);
			Vector2f wallEndPos(this->selectorWall.getPosition().x + 80, this->selectorWall.getPosition().y + 80);


			if (x >= voidStartPos.x && x <= voidEndPos.x && y >= voidStartPos.y && y <= voidEndPos.y) {
				this->selectorBorder.setPosition(Vector2f(1330, 20));
				this->currentTile = 0;
			}
			else if (x >= wallStartPos.x && x <= wallEndPos.x && y >= wallStartPos.y && y <= wallEndPos.y) {
				this->selectorBorder.setPosition(Vector2f(1330, 120));
				this->currentTile = 1;

			}

			//else if (x >= buttonStartPos.x && x <= buttonEndPos.x && y >= buttonStartPos.y && y <= buttonEndPos.y) {
			//	//saveLevel();
			//}
		}
	}
}

void App::saveLevel() {
	json _json;

	std::fstream file("./Maps/custom.json");
	_json["custom"] = json::array();

	for (int i = 0; i < 9; i++) {
		int row[16] = {};
		for (int j = 0; j < 16; j++) {
			row[j] = map[i][j];
		}

		_json["custom"].push_back(row);
	}

	std::string lvl = _json.dump();
	std::string temp = "";

	for (int i = 0; i < lvl.size(); i++) {
		if (lvl[i] == ',' && i >= 43 && i <= lvl.size() - 35 && lvl[i - 1] == ']') {
			temp += ", \n        ";
		}
		else {
			temp += lvl[i];
		}

		if (i == 315) {
			temp += ",\n        [" + std::to_string(this->currentCharacter) + "]\n    ";
		}
		else if (i == 316) {
			temp += "\n";
		}
		else if (i == 0) {
			temp += "\n    ";
		}
		else if (i == 9) {
			temp += "\n    ";
		}
		else if (i == 10) {
			temp += "\n        ";
		}
	}

	file.clear();
	file << temp;
	file.close();
}
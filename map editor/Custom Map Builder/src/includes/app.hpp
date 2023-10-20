#include "precompile.hpp"
#include <string>

class App {
public:
	void initWindow();
	void updateWindow();
	void renderWindow();
	void handleInput();
	void saveLevel();
private:
	int currentTile;
	int currentCharacter;
	RenderWindow window;
	Event event;
	Texture voidTexture;
	Texture wallTexture;
	Sprite selectorVoid;
	Sprite selectorWall;
	RectangleShape selectorBorder;
	RectangleShape characterSelector;
	RectangleShape saveButton;
	std::map<int, Texture> textureMap;
	std::vector<std::vector<int>> map;
	std::vector<std::vector<Sprite>> tiles;
};
﻿#include "MainMenu.h"

MainMenu::MainMenu(float width, float height, int kind_of_menu) {
	if (!font.loadFromFile("Fonts/HedvigLettersSans-Regular.ttf")) {
		cout << "No font is here" << endl;
	}
	if (kind_of_menu == 0) {

	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(Color::White);
	mainMenu[0].setString("Play");
	mainMenu[0].setCharacterSize(70);
	mainMenu[0].setPosition(400, 200);

	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color::White);
	mainMenu[1].setString("About");
	mainMenu[1].setCharacterSize(70);
	mainMenu[1].setPosition(400, 300);

	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(Color::White);
	mainMenu[2].setString("Exit");
	mainMenu[2].setCharacterSize(70);
	mainMenu[2].setPosition(400, 400);

	MainMenuSelected = -1;
	}
	if (kind_of_menu == 1) {

		mainMenu[0].setFont(font);
		mainMenu[0].setFillColor(Color::White);
		mainMenu[0].setString("Saper");
		mainMenu[0].setCharacterSize(70);
		mainMenu[0].setPosition(350, 200);

		mainMenu[1].setFont(font);
		mainMenu[1].setFillColor(Color::White);
		mainMenu[1].setString("Snake");
		mainMenu[1].setCharacterSize(70);
		mainMenu[1].setPosition(350, 300);

		mainMenu[2].setFont(font);
		mainMenu[2].setFillColor(Color::White);
		mainMenu[2].setString("Pac-xon");
		mainMenu[2].setCharacterSize(70);
		mainMenu[2].setPosition(350, 400);

		mainMenu[3].setFont(font);
		mainMenu[3].setFillColor(Color::White);
		mainMenu[3].setString("Samotnik");
		mainMenu[3].setCharacterSize(70);
		mainMenu[3].setPosition(350, 500);

		MainMenuSelected = -1;
	}
}
MainMenu::~MainMenu()
{
	
}

void MainMenu::draw(RenderWindow& window) {
	for (int i = 0; i < Max_main_menu; ++i) {
		window.draw(mainMenu[i]);
	}
}

//MoveUp
void MainMenu::MoveUp()
{
	if (MainMenuSelected - 1 >= 0) {
		mainMenu[MainMenuSelected].setFillColor(Color::White);
	
		MainMenuSelected--;
		if (MainMenuSelected == -1) {
			MainMenuSelected = 2;
		}
		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
}

//Move Down
void MainMenu::MoveDown() {
	if (MainMenuSelected + 1 <= 4)
	{
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected++;
		if (MainMenuSelected == 5)
		{
			MainMenuSelected = 0;
		}
		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
}
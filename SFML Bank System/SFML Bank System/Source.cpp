#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp>
#include<SFML/System.hpp>
#include<iostream>
using namespace std;
using namespace sf;



int main() {
	RenderWindow window(VideoMode(1728, 972), "haitham bank");
	Font font;
	font.loadFromFile("Roboto-Regular.ttf");
	Text text[12];
	for (int i = 0; i < 12; i++) {
		text[i].setFont(font);


		text[i].setFillColor(Color::White);
		text[i].setStyle(Text::Bold);
	}

	text[7].setString("Haitham Bank"); text[4].setString("Hallo Mr."); text[0].setString("Freeze Account"); text[1].setString("Unfreeze Account");
	text[7].setPosition(700, 32); text[4].setPosition(50, 20); text[0].setPosition(935, 485); text[1].setPosition(1268, 485);
	text[7].setCharacterSize(70); text[4].setCharacterSize(50); text[0].setCharacterSize(35); text[1].setCharacterSize(35);
	text[6].setString("Empoloyees"); text[5].setString("Users"); text[3].setString("Add Empoloyees"); text[2].setString("Manage Accounts");
	text[6].setPosition(150, 220); text[5].setPosition(700, 220); text[3].setPosition(1180, 240); text[2].setPosition(1180, 340);
	text[6].setCharacterSize(70); text[5].setCharacterSize(70); text[3].setCharacterSize(35); text[2].setCharacterSize(35);
	//empolyee
	text[8].setString("View queued users"); text[9].setString("View users"); text[10].setString("Approve"); text[11].setString("Reject");
	text[8].setPosition(1180, 240); text[9].setPosition(1235, 340); text[10].setPosition(1000, 485); text[11].setPosition(1370, 485);
	text[8].setCharacterSize(35); text[9].setCharacterSize(35); text[10].setCharacterSize(35); text[11].setCharacterSize(35);


	Texture x[14];
	x[0].loadFromFile("background.png");
	x[1].loadFromFile("bigbutton.png");
	x[2].loadFromFile("bigdarkbackground.png");
	x[3].loadFromFile("close.png");
	x[4].loadFromFile("entervaluesbackground.png");
	x[5].loadFromFile("header.png");
	x[6].loadFromFile("largedarkbackground.png");
	x[7].loadFromFile("mediumdarkbackground.png");
	x[8].loadFromFile("minimize.png");
	x[9].loadFromFile("options.png");
	x[10].loadFromFile("samllButton.png");
	x[11].loadFromFile("search.png");
	x[12].loadFromFile("smallDarkbackground.png");
	x[13].loadFromFile("viewBackground.png");

	Sprite background(x[0]), bigButton[2], bigDarkBackground(x[2]), close(x[3]),
		enterValuesBackground(x[4]), header(x[5]),
		largedarkbackground(x[6]), mediumdarkbackground(x[7]), minimize(x[8]), options(x[9])
		, smallButton[3], search(x[11]), smallDarkbackground(x[12]), viewBackground[3];
	for (int i = 0; i < 3; i++) {
		viewBackground[i].setTexture(x[13]);
		viewBackground[i].setPosition(120, 590 + 95 * i);
		smallButton[i].setTexture(x[10]);


	}
	for (int i = 0; i < 2; i++) {

		bigButton[i].setTexture(x[1]);

	}

	close.setPosition(1668, 20);
	options.setPosition(1170, 60);
	minimize.setPosition(1600, 52);
	largedarkbackground.setPosition(100, 450); largedarkbackground.setScale(1, 0.65);
	smallDarkbackground.setPosition(100, 200); smallDarkbackground.setScale(1, 1.1);
	header.setScale(1, 0.9);
	smallButton[0].setPosition(150, 470); smallButton[1].setPosition(900, 470); smallButton[2].setPosition(1250, 470);
	search.setPosition(410, 485); bigButton[0].setPosition(1100, 220); bigButton[1].setPosition(1100, 320);

	int n;
	cin >> n;


	while (window.isOpen()) {
		Event event;


		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				window.close();

			}

		}
		window.clear(Color::Transparent);
		window.draw(background);
		window.draw(largedarkbackground);
		window.draw(smallDarkbackground);
		for (int i = 0; i < 3; i++) {
			window.draw(viewBackground[i]);
			window.draw(smallButton[i]);
		}
		for (int i = 0; i < 2; i++) {
			window.draw(bigButton[i]);
		}

		window.draw(search);
		window.draw(header);
		window.draw(minimize);
		window.draw(options);
		window.draw(close);
		if (n == 1) {
			for (int i = 0; i < 8; i++) {
				window.draw(text[i]);
			}
		}
		else if (n == 2) {
			for (int i = 4; i < 12; i++) {
				window.draw(text[i]);
			}
		}
		window.display();
	}






}
#include<iostream>
#include<vector>
#include <fstream>
#include<sstream>
#include<string>
#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;
int thisUserIndex = 0;
int months;
int anotherUserIndex;
// GUI global variables 

RenderWindow window(sf::VideoMode(1920, 1080), "HaithamBank", Style::Default);
Font rockebFont, britanicFont, berlinSansFont;
Texture headerTexture, closeTexture, mininmizeTexture, optionsTexture, backgroundTexture, bigButtonTexture, smallButtonTexture, darkBackgroundTexture, darkBackgroundSmallTexture, enterValuesBackgroundTexture;


struct account
{
	string userName;
	string email;
	string password;
};
struct transaction {
	string transactionType = "";
	float transactionAmount = 0;
	string recepient = "";
};
struct user {
	account userAccount;
	vector<transaction> userTransaction;
	int age;
	float balance;
	string phoneNumber;
	int accountNum;
	bool frozen = false;
	int transactionCount = 0;

};


RectangleShape mouseRect(Vector2f(10,20));

// GUI entities struct 
struct bigDarkBox {
	Sprite background;
	Sprite valueField1;
	Sprite valueField2;
	Text amountTxt;
	Text Totxt;
	Text TransactionStatus;
};

struct Header {
	Sprite background, closeBtn, minimizeBtn, optionsBtn;
	Text goodMorning, user, haithamBank;

};
struct button {

	Text btnText;
	Sprite btnSprite;
};
struct balancePanel {
	Sprite panel;
	Text balnceText;
	Text amountText;
};

// system functions  

bool findPhone(string phoneNumber, vector<user> users);
bool findEmail(string email, vector<user> users);
bool find(string email, string password, vector<user> users);
bool find(int accounNumber, vector<user> users);

bool addEmployee(vector<user>& users);
bool signUp(vector<user>& users);
bool login(vector<user> users);
bool freeze(int accountNumber, vector<user>& users);
bool unFreeze(int accountNumber, vector<user>& users);

//second video
bool validBalance(user users, float amount);
void loan(vector<user>& users, float amount, bigDarkBox& bigBox);
void Withdraw(vector<user>& users, float amount, bigDarkBox& bigBox);
void transfer(vector<user>& users, float amount, int accNum, bigDarkBox& bigBox);
void viewTransactions(vector<user> users);

void write(vector<user> users);
void read(vector<user>& users);

//GUI functions

void btnIntializer(button btn[], int arrSize);
void sideButtonDrawer(button btn[], int arrSize);
void texturesAndFonts();
void balancePanelIntializer(balancePanel& panel);
void balancePanelDrawer(balancePanel& panel, vector<user> users);
void setbigDarkBoxTransferBalance(bigDarkBox&, button&);
void setHeader(Header& header,vector<user> users);
void setButton(button& btn);
void drawBigBox(bigDarkBox bigDarkbox, button btn, string transactionTag);
void drawHeader(Header header);
void sideBtnCollision(button btn[], int arrSize, string& s);

void functionCaller(string functionTag,string input1,string input,vector<user>& users, bigDarkBox& bigBox);



int main() {
	mouseRect.setFillColor(Color::Black);
	Mouse ms;
	vector<user>users;
	read(users);
	texturesAndFonts();
	bigDarkBox bigdarkBox;
	button btn,btn2,sideButtons[4];
	Header header;
	balancePanel panel;
	setbigDarkBoxTransferBalance(bigdarkBox, btn);
	setHeader(header,users);
	setButton(btn2);
	balancePanelIntializer(panel);
	btnIntializer(sideButtons, 4);
	////sprites 
	Sprite background;
	background.setTexture(backgroundTexture);
	////background modification
	background.setScale(1.5, 1.5);
	background.setPosition(-50, 0);
	string input,input2;
	Text inputText, inputText2;
	inputText.setFont(rockebFont);
	inputText.setFillColor(Color::White);
	inputText.setCharacterSize(40);
	inputText.setPosition(1050, 660);

	inputText2.setFont(rockebFont);
	inputText2.setFillColor(Color::White);
	inputText2.setCharacterSize(40);
	inputText2.setPosition(1050, 770);
	string functionTag;
	int inputIndex=0;
	while (window.isOpen())
	{
		mouseRect.setPosition(ms.getPosition().x-15, ms.getPosition().y-35);
		sideBtnCollision(sideButtons, 4,functionTag);
		if (functionTag != "Transfer Balance") {
			input2.resize(0);
		}
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == Event::TextEntered&&input.size()<6) {
				char c;
				c= static_cast<char>(event.text.unicode);
				if (inputIndex == 0) {
					if (isdigit(c)) {
						input += c;
					}
				}
				else {
						if (isdigit(c)) {
							input2 += c;
						}
					}
				}
			
		if (inputIndex == 0) {
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::BackSpace && input.size() > 0) {
				input.resize(input.size() - 1);
			}
		}
		else {
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::BackSpace && input2.size() > 0) {
				input2.resize(input2.size() - 1);
			}
		}
			if (functionTag != "Transfer Balance") {
				if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter && input.size() > 0) {
					functionCaller(functionTag, input, input2, users, bigdarkBox);
					input.resize(0);
				}
			}
			else {
				if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter && input.size() > 0) {
					inputIndex++;
					inputIndex %= 2;
				}
				if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter && inputIndex == 0) {
					functionCaller(functionTag, input, input2, users, bigdarkBox);
					input.resize(0);
					input2.resize(0);

				}

			}

		}
		inputText.setString(input);
		inputText2.setString(input2);
		window.clear();
		window.draw(background);
		sideButtonDrawer(sideButtons, 4);
		balancePanelDrawer(panel, users);
		drawBigBox(bigdarkBox, btn, functionTag);
		drawHeader(header);
		window.draw(mouseRect);
		window.draw(inputText);
		if (functionTag == "Transfer Balance") {
			window.draw(inputText2);
		}

		window.display();
	}


	write(users);

	return 0;

}

// functions implementation 
// system functions 

bool login(vector<user> users) {
	user temp;
	cout << "enter email" << endl;
	cin >> temp.userAccount.email;
	cout << "enter password" << endl;
	cin >> temp.userAccount.password;
	if (!find(temp.userAccount.email, temp.userAccount.password, users)) {
		cout << "email and password doesn't match" << endl;
		return false;
	}
	if (users[thisUserIndex].frozen == true) {
		cout << "this account is frozen" << endl;
		return false;
	}
	else {
		cout << "loged in successfully" << endl;
		cout << thisUserIndex << endl;
	}
}
bool signUp(vector<user>& users) {
	user temp;
	cout << "enter name\n";
	cin >> temp.userAccount.userName;
	cout << "enter email" << endl;
	cin >> temp.userAccount.email;
	if (findEmail(temp.userAccount.email, users) || temp.userAccount.email.find("@user.bank") == string::npos) {
		cout << "email is already in use enter another one make sure to include @user.bank\n";
		return false;
	}
	cout << "enter password" << endl;
	cin >> temp.userAccount.password;
	cout << "enter phone number" << endl;
	cin >> temp.phoneNumber;
	if (findPhone(temp.phoneNumber, users)) {
		cout << "phone number already taken" << endl;
		return false;
	}
	cout << "enter age" << endl;
	cin >> temp.age;
	if (temp.age < 21) {
		cout << "invalid age" << endl;
		return false;
	}
	cout << "enter balance" << endl;
	cin >> temp.balance;
	if (temp.balance < 300) {
		cout << "balance can't be less than 300 EGP " << endl;
		return false;

	}

	temp.accountNum = (rand() % 101) + 100;
	while (find(temp.accountNum, users)) {
		temp.accountNum = (rand() % 101) + 900;
	}
	users.push_back(temp);
	return true;
}
bool findPhone(string phoneNumber, vector<user> users)
{
	for (int i = 0; i < users.size(); i++) {
		if (phoneNumber == users[i].phoneNumber) {
			return true;
		}
	}
	return false;
}
bool findEmail(string email, vector<user> users) {
	for (int i = 0; i < users.size(); i++) {
		if (email == users[i].userAccount.email) {
			return true;
		}
	}
	return false;
}
bool find(string email, string password, vector<user> users) {
	for (int i = 0; i < users.size(); i++) {
		if (email == users[i].userAccount.email && password == users[i].userAccount.password) {
			thisUserIndex = i;
			return true;
		}
	}
	return false;
}
bool find(int accountNumber, vector<user> users) {
	for (int i = 0; i < users.size(); i++) {
		if (accountNumber == users[i].accountNum) {
			anotherUserIndex = i;
			return true;
		}
	}
	return false;
}
bool addEmployee(vector<user>& users) {
	user newEmployee;
	cout << "Enter employee name " << endl;
	cin >> newEmployee.userAccount.userName;
	cout << "Enter employee email " << endl;
	cin >> newEmployee.userAccount.email;
	if (findEmail(newEmployee.userAccount.email, users) || newEmployee.userAccount.email.find("@employee.bank") == string::npos) {
		cout << "Email already in use enter another one make sure that your email contains @employee.bank" << endl;
		return false;
	}
	cout << "Enter employee Password " << endl;
	cin >> newEmployee.userAccount.password;
	users.push_back(newEmployee);
	return true;
}
bool freeze(int accNum, vector<user>& users)
{
	if (!find(accNum, users)) {
		cout << "this user doesn't exist" << endl;
		return false;
	}
	else if (find(accNum, users)) {
		users[anotherUserIndex].frozen = true;
		cout << "frozen" << endl;
	}
	return true;
}
bool unFreeze(int accNum, vector<user>& users)
{
	if (!find(accNum, users)) {
		cout << "this user doesn't exist" << endl;
		return false;
	}
	else if (find(accNum, users)) {
		users[anotherUserIndex].frozen = false;
		cout << "active" << endl;
	}
	return true;

}

	//second video
bool validBalance(user users, float amount) {



		if (users.balance - amount <= 0) {
			return false;

		}
		if (amount < 50) {
			return false;

		}

		return true;


	}
void loan(vector<user>&users, float amount,  bigDarkBox& bigBox) {
		transaction loanTransaction;

		if (amount * 0.25 >= users[thisUserIndex].balance) {
			bigBox.TransactionStatus.setString("Rejected due to low balance ");
		}


		else {
			if (amount > 100000) {
				months = ((amount + users[thisUserIndex].balance) / amount) * 6;
			}
			else {
				months = (amount + users[thisUserIndex].balance) / amount;
			}
			bigBox.TransactionStatus.setString( "loan is accepted and have to be returned by " + to_string(months) + " months" );

			loanTransaction.transactionType = "loan";
			loanTransaction.transactionAmount = amount;
			loanTransaction.recepient = "you";
			users[thisUserIndex].balance += amount;
			users[thisUserIndex].transactionCount++;
			users[thisUserIndex].userTransaction.push_back(loanTransaction);

		}
	}
void Withdraw(vector<user>&users, float amount, bigDarkBox& bigBox) {
		transaction withdrawTransaction;
	
		if (!validBalance(users[thisUserIndex], amount)) {
		    bigBox.TransactionStatus.setString( "Not enough balance");
		}
		else {
			users[thisUserIndex].balance -= amount;
			users[thisUserIndex].transactionCount++;
			users[thisUserIndex].userTransaction.push_back(withdrawTransaction);
			users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionAmount = amount;
			users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].recepient = "noRecepient";
			users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionType = "withdrawl";

			bigBox.TransactionStatus.setString( "you have withdrawn " + to_string((int)amount));
			cout << thisUserIndex << endl;
		}

	};
void transfer(vector<user>&users, float amount,int accNum, bigDarkBox& bigBox) {

	
		transaction temp;
		
		if (users[thisUserIndex].balance - amount < 0) {
		   bigBox.TransactionStatus.setString( "Not enough balance");
		}
		else {
			
		
			if (find(accNum, users)) {
				users[thisUserIndex].balance -= amount;
				users[anotherUserIndex].balance += amount;
				users[thisUserIndex].transactionCount++;
				users[anotherUserIndex].transactionCount++;
				users[thisUserIndex].userTransaction.push_back(temp);
				users[anotherUserIndex].userTransaction.push_back(temp);
				// saving transaction for the sender
				users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionAmount = amount;
				users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].recepient = to_string(accNum);
				users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionType = "transfer";

				// saving transaction for the reciever 
				users[anotherUserIndex].userTransaction[users[anotherUserIndex].transactionCount - 1].transactionAmount = amount;
				users[anotherUserIndex].userTransaction[users[anotherUserIndex].transactionCount - 1].recepient = "you";
				users[anotherUserIndex].userTransaction[users[anotherUserIndex].transactionCount - 1].transactionType = "transfer";
				bigBox.TransactionStatus.setString("You have transferred amount of " + to_string((int)amount) + " to the account " + to_string(accNum) );
			}
			else {
				bigBox.TransactionStatus.setString( "This acount does not exist");
			}
		}
	};
void viewTransactions(vector<user> users) {
		int index = users[thisUserIndex].transactionCount - 1;
		for (int i = index; i >= 0; i--) {
			cout << "Transaction of type " << users[thisUserIndex].userTransaction[i].transactionType <<
				" with amount of " << users[thisUserIndex].userTransaction[i].transactionAmount <<
				" to " << users[thisUserIndex].userTransaction[i].recepient << endl;
			if (i == index - 4)
				break;
		}
	}

void write(vector<user> users) {

	fstream out("userData.txt", ios::out);
	if (!out) {
		cout << "file not found";
		return;
	}
	for (int i = 0; i < users.size() - 1; i++) {
		out << users[i].accountNum << " " << users[i].userAccount.userName << " " << users[i].userAccount.email << " " << users[i].phoneNumber << " " <<
			users[i].balance << " " << users[i].transactionCount << " " << users[i].age << " " << users[i].userAccount.password << " " << users[i].frozen << endl;
		for (int j = 0; j < users[i].transactionCount; j++) {
			out << users[i].userTransaction[j].recepient << " " << users[i].userTransaction[j].transactionType << " " << users[i].userTransaction[j].transactionAmount << endl;
		}

	}
	out.close();
}
void read(vector<user>& users) {
	user temp;
	transaction transactiontemp;

	ifstream in("userData.txt");
	if (!in) {
		cout << "file not found";
		return;
	}

	for (int i = 0; !in.eof(); i++) {
		in >> temp.accountNum >> temp.userAccount.userName >> temp.userAccount.email >> temp.phoneNumber >>
			temp.balance >> temp.transactionCount >> temp.age >> temp.userAccount.password >> temp.frozen;
		for (int j = 0; j < temp.transactionCount; j++) {
			temp.userTransaction.push_back(transactiontemp);
			in >> temp.userTransaction[j].recepient >> temp.userTransaction[j].transactionType >> temp.userTransaction[j].transactionAmount;

		}
		users.push_back(temp);
	}
	in.close();
}

	///GUI functiuons
void texturesAndFonts() {
		headerTexture.loadFromFile("Assets/header.png");
		closeTexture.loadFromFile("Assets/close.png");
		mininmizeTexture.loadFromFile("Assets/minimize.png");
		optionsTexture.loadFromFile("Assets/options.png");
		backgroundTexture.loadFromFile("Assets/background.png");
		bigButtonTexture.loadFromFile("Assets/big button.png");
		smallButtonTexture.loadFromFile("Assets/samll button.png");
		darkBackgroundTexture.loadFromFile("Assets/medium dark background.png");
		darkBackgroundSmallTexture.loadFromFile("Assets/small dark background.png");
		enterValuesBackgroundTexture.loadFromFile("Assets/enter values background.png");
		rockebFont.loadFromFile("Fonts/rockeb.ttf");
		britanicFont.loadFromFile("Fonts/BRITANIC.ttf");
		berlinSansFont.loadFromFile("Fonts/Berlin Sans FB Regular.ttf");
	}
void btnIntializer(button btn[], int arrSize) {
		string btnstring[4] = { "Transfer Balance","Withdraw","Last Transactions","Ask for a Loan" };

		for (int i = 0; i < arrSize; i++) {
			btn[i].btnSprite.setTexture(smallButtonTexture);
			btn[i].btnText.setFont(rockebFont);
			btn[i].btnText.setFillColor(Color::White);
			btn[i].btnSprite.setPosition(80, 500 + ((i) * 115));
			btn[i].btnSprite.setScale(1.2, 1.2);
			btn[i].btnText.setString(btnstring[i]);
		}
		btn[0].btnText.setPosition(130, 525);
		btn[1].btnText.setPosition(185, 643);
		btn[2].btnText.setPosition(125, 760);
		btn[3].btnText.setPosition(150, 875);
	}
void setButton(button& btn) {
	String textArr =  "Transfer Balance" ;
	btn.btnSprite.setTexture(bigButtonTexture);
	btn.btnSprite.setPosition(1000, 530);
	btn.btnSprite.setScale(1.1, 1.1);
	btn.btnText.setFont(rockebFont);
	btn.btnText.setFillColor(Color::White);
	btn.btnText.setPosition(1100, 555);
	btn.btnText.setString(textArr[0]);
}
void setbigDarkBoxTransferBalance(bigDarkBox& bigDarkbox, button& btn) {
	String textArr[2] = { "Amount","To" };
	bigDarkbox.background.setTexture(darkBackgroundTexture);
	bigDarkbox.background.setPosition(710, 500);
	bigDarkbox.background.setScale(1.11, 1.105);
	bigDarkbox.valueField1.setTexture(enterValuesBackgroundTexture);
	bigDarkbox.valueField1.setPosition(1000, 650);
	bigDarkbox.valueField2.setTexture(enterValuesBackgroundTexture);
	bigDarkbox.valueField2.setPosition(1000, 750);
	bigDarkbox.amountTxt.setFont(rockebFont);
	bigDarkbox.amountTxt.setString(textArr[0]);
	bigDarkbox.amountTxt.setFillColor(Color::White);
	bigDarkbox.amountTxt.setPosition(820, 670);
	bigDarkbox.Totxt.setFont(rockebFont);
	bigDarkbox.Totxt.setString(textArr[1]);
	bigDarkbox.Totxt.setFillColor(Color::White);
	bigDarkbox.Totxt.setPosition(870, 770);
	bigDarkbox.TransactionStatus.setFont(rockebFont);
	bigDarkbox.TransactionStatus.setFillColor(Color::White);
	bigDarkbox.TransactionStatus.setPosition(800, 840);
	setButton(btn);
}
void balancePanelIntializer(balancePanel& panel) {
	panel.panel.setTexture(darkBackgroundSmallTexture);
	panel.panel.setPosition(60, 250);
	panel.panel.setScale(1.16, 1.07);
	panel.balnceText.setFont(rockebFont);
	panel.balnceText.setString("Balance");
	panel.balnceText.setCharacterSize(80);
	panel.balnceText.setFillColor(Color::White);
	panel.balnceText.setPosition(150, 260);
	panel.amountText.setFont(rockebFont);
	panel.amountText.setString("0,0 EGP");
	panel.amountText.setCharacterSize(60);
	panel.amountText.setFillColor(Color::White);
	panel.amountText.setPosition(170, 350);

}
void setHeader(Header& header,vector<user> users) {
	String textArr[3] = { "Good Morning, ", "Loser","Haitham Bank" };
	header.background.setTexture(headerTexture);
	header.background.setPosition(0, -60);
	header.background.setScale(1.107, 1.5);
	header.closeBtn.setTexture(closeTexture);
	header.minimizeBtn.setTexture(mininmizeTexture);
	header.optionsBtn.setTexture(optionsTexture);
	header.closeBtn.setPosition(1850, 30);
	header.minimizeBtn.setPosition(1780, 45);
	header.optionsBtn.setPosition(1200, 75);
	header.goodMorning.setFont(berlinSansFont);
	header.goodMorning.setString(textArr[0]);
	header.goodMorning.setCharacterSize(60);
	header.goodMorning.setFillColor(Color::White);
	header.goodMorning.setPosition(50, 30);
	header.user.setFont(berlinSansFont);
	header.user.setString(users[thisUserIndex].userAccount.userName);
	header.user.setCharacterSize(70);
	header.user.setFillColor(Color::White);
	header.user.setPosition(100, 80);
	header.haithamBank.setString(textArr[2]);
	header.haithamBank.setFont(berlinSansFont);
	header.haithamBank.setCharacterSize(70);
	header.haithamBank.setFillColor(Color::White);
	header.haithamBank.setPosition(750, 45);
}
void sideButtonDrawer(button btn[], int arrSize)
	{
		for (int i = 0; i < arrSize; i++) {

			window.draw(btn[i].btnSprite);
			window.draw(btn[i].btnText);

		}
	}
void balancePanelDrawer(balancePanel& panel, vector<user> users)
{
	window.draw(panel.panel);
	panel.amountText.setString(to_string((int)users[thisUserIndex].balance));
	window.draw(panel.balnceText);
	window.draw(panel.amountText);
}
void drawBigBox(bigDarkBox bigDarkbox, button btn, string transactionTag ) {
	window.draw(bigDarkbox.background);
	window.draw(btn.btnSprite);
	btn.btnText.setString(transactionTag);
	window.draw(btn.btnText);
	window.draw(bigDarkbox.valueField1);
	window.draw(bigDarkbox.amountTxt);
	if (transactionTag == "Transfer Balance") {
		window.draw(bigDarkbox.valueField2);
		window.draw(bigDarkbox.Totxt);
	}
	window.draw(bigDarkbox.TransactionStatus);
}
void drawHeader(Header header) {
	window.draw(header.background);
	window.draw(header.closeBtn);
	window.draw(header.minimizeBtn);
	window.draw(header.optionsBtn);
	window.draw(header.haithamBank);
	window.draw(header.goodMorning);
	window.draw(header.user);
}
void sideBtnCollision(button btn[], int arrSize,string &s ) {

	for (int i = 0; i < arrSize; i++) {
		if (btn[i].btnSprite.getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {
			btn[i].btnText.setFillColor(Color{ 128, 128, 128 });
		}
		else {
			btn[i].btnText.setFillColor(Color::White);
		}
		if (btn[i].btnSprite.getGlobalBounds().intersects(mouseRect.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			s = btn[i].btnText.getString();
		}
	}

}
void functionCaller(string functionTag, string input1, string input2, vector<user>& users, bigDarkBox& bigBox)
{
	if (functionTag == "Transfer Balance") {
		transfer(users, stof(input1), stoi(input2),bigBox);
	}
	else if (functionTag == "Withdraw") {
		Withdraw(users, stof(input1), bigBox);
	}
	else if (functionTag == "Ask for a Loan") {
		loan(users, stof(input1),bigBox);
	}
	else {

	}
}

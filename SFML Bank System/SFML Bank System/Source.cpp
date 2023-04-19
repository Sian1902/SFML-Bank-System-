#include<iostream>
#include<vector>
#include<time.h>
#include<cstdlib>
#include <fstream>
#include<sstream>
#include<string>
#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;
int thisUserIndex = -1;
int months;
int anotherUserIndex;
// GUI global variables 

RenderWindow window(sf::VideoMode(1920, 1080), "Game Committee", Style::Default);
Font rockebFont, britanicFont, berlinSansFont;
Texture headerTexture, closeTexture, mininmizeTexture, darkBackgroundLargeTexture, optionsTexture, backgroundTexture, bigButtonTexture, smallButtonTexture, darkBackgroundTexture, darkBackgroundSmallTexture, enterValuesBackgroundTexture, viewBackgroundTexture, darkBackgroundBigTexture, searchTexture;



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
	int age = 0;
	float balance = 0;
	string phoneNumber = "0";
	int accountNum = 0;
	bool frozen = false;
	int transactionCount = 0;

};


RectangleShape mouseRect(Vector2f(10, 20));

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
	Sprite searchSprite;
};
struct balancePanel {
	Sprite panel;
	Text balnceText;
	Text amountText;
};
struct viewBackground {
	Sprite veiwSprite;
	Text viewText;
};
struct addEmpWindow {
	Sprite background;
	Sprite close;
	Sprite enterValueField[3];
	Text labels[3];
	Text addEmpStatus;
};
struct viewTransactionBox {
	Sprite background;
	Text Transactions[5];
	Sprite Fields[5];
};

struct signUpBox {
	Sprite background;
	Sprite valueField1;
	Sprite valueField2;
	Sprite valueField3;
	Sprite valueField4;
	Sprite valueField5;
	Sprite valueField6;
	Sprite Button1;
	Sprite Button2;
	Text value1;
	Text value2;
	Text value3;
	Text value4;
	Text value5;
	Text value6;
	Text heading1;
	Text buttonText1;
	Text buttonText2;
	Text failure;
};
struct signInBox {
	Sprite background;
	Sprite valueField1;
	Sprite valueField2;
	Sprite Button1;
	Sprite Button2;
	Text value1;
	Text value2;
	Text heading1;
	Text buttonText1;
	Text buttonText2;
	Text signInFailure;
};
// system functions  
bool login(vector<user> users, string email, string password, signInBox& signIn);
bool signUp(vector<user>& users, string username, string email, string password, string phonenumber, int age, float balance, signUpBox& box);
bool findPhone(string phoneNumber, vector<user> users);
bool findEmail(string email, vector<user> users);
bool find(string email, string password, vector<user> users);
bool find(int accountNumber, vector<user> users);
bool addEmployee(vector<user>& users, addEmpWindow& empWindow, string inputs[], balancePanel panel[]);
bool freeze(int accNum, vector<user>& users, int userIndex, viewBackground viewer[]);
bool unFreeze(int accNum, vector<user>& users, int userIndex, viewBackground viewer[]);
bool validBalance(user users, float amount);
void loan(vector<user>& users, float amount, bigDarkBox& bigBox);
void Withdraw(vector<user>& users, float amount, bigDarkBox& bigBox);
void transfer(vector<user>& users, float amount, int accNum, bigDarkBox& bigBox);
void viewTransactions(vector<user> users, viewTransactionBox& box);
void write(vector<user> users);
void read(vector<user>& users);
void texturesAndFonts();
void btnIntializer(button btn[], int arrSize);
void setbigDarkBoxTransferBalance(bigDarkBox& bigDarkbox, button& btn);
void balancePanelIntializer(balancePanel& panel);
void setHeader(Header& header);
void sideButtonDrawer(button btn[], int arrSize);
void balancePanelDrawer(balancePanel& panel, vector<user> users);
void drawBigBox(bigDarkBox bigDarkbox, button btn, string transactionTag, viewTransactionBox box);
void drawHeader(Header header, vector<user>users);
void sideBtnCollision(button btn[], int arrSize, string& s);
void functionCaller(string functionTag, string input1, string input2, vector<user>& users, bigDarkBox& bigBox, viewTransactionBox& box);
void setViewTransactionBox(viewTransactionBox& box);
void drawViewTransactions(viewTransactionBox box);
void initializeSignUp(signUpBox& box);
void drawSignUp(signUpBox box);
void drawSignUp(signUpBox box);
void initializeSignIn(signInBox& box);
void drawSignIn(signInBox box);
void adminPagebtnIntializer(button btn[], int arrSize);
void searchButtonInitializer(button& btn);
void searchButtonDrawer(button btn);
void viewbackgroundIntializer(viewBackground viewer[], int arrSize, vector<user> users);
void setButton(button& btn);
void adminPanelIntializer(balancePanel panel[], vector<user> users);
void adminPanelDrawer(balancePanel panel[]);
void adminPageButtonDrawer(button btn[], int arrSize);
void viewBackgroundDrawer(viewBackground view[], int arrSize);
void darkBoxBiginitializeradminPage(viewBackground& darkbox);
void darkBoxBigDraweradminPage(viewBackground darkbox);
void userTxtCollision(viewBackground viewer[], int arrSize, vector<user> users, int& accNumber, int& userIndex);
void freezeUnfreezeCollision(button btn[], int arrSize, int& index);
void adminPageFunctionCaller(int& index, vector<user>& users, int accNumber, viewBackground viewer[], int userIndex);
void SetSearchTxt(Text& searchBtnTxt);
void setAddEmployeesBox(addEmpWindow& empWindow);
void drawAddEmpWindow(addEmpWindow empWindow);
void checkAddEmpCollision(button btn[], int& adminPageInputIndex, addEmpWindow empWindow);
void setAddEmpText(Text inputTxt[]);
void drawAddEmpInputTxt(Text inputTxt[], int arrsize);
void userPage(vector<user>& users, Header header, Sprite background);
bool signInPage(vector<user> users, Header header, Sprite background);
bool signUpPage(vector<user>& users, Header header, Sprite background);
void adminPage(vector<user>& users, Header header, Sprite background);

int main() {
	vector<user> users;
	read(users);
	texturesAndFonts();
	srand(time(NULL));
	Header header;
	setHeader(header);
	////sprites 
	Sprite background;
	background.setTexture(backgroundTexture);
	////background modification
	background.setScale(1.5, 1.5);
	background.setPosition(-50, 0);
	mouseRect.setFillColor(Color::Black);
	if (signInPage(users, header, background)) {
		if (users[thisUserIndex].userAccount.email.find("@user.bank") != string::npos) {
			userPage(users, header, background);
		}
		else {
			adminPage(users, header, background);
		}
	}
	else {
		if (signUpPage(users, header, background)) {
			userPage(users, header, background);
		}
	}
	//adminPage(users, header, background);
	write(users);

	return 0;

}

// functions implementation 
// system functions 

bool login(vector<user> users, string email, string password, signInBox& signIn) {
	if (!find(email, password, users)) {
		signIn.signInFailure.setString("email and password doesn't match");
		return false;
	}
	if (users[thisUserIndex].frozen == true) {
		signIn.signInFailure.setString("this account is frozen");
		return false;
	}
	else {
		return true;
	}
}
bool signUp(vector<user>& users, string username, string email, string password, string phonenumber, int age, float balance, signUpBox& box) {
	user temp;
	email.resize(email.size() - 1);
	username.resize(username.size() - 1);
	password.resize(password.size() - 1);
	phonenumber.resize(phonenumber.size() - 1);

	temp.userAccount.userName = username;

	temp.userAccount.email = email;
	if (findEmail(temp.userAccount.email, users) || temp.userAccount.email.find("@user.bank") == string::npos) {
		box.failure.setString("email is already in use enter another one make sure to include @user.bank");
		return false;
	}
	temp.userAccount.password = password;

	temp.phoneNumber = phonenumber;
	if (findPhone(temp.phoneNumber, users)) {
		box.failure.setString("phone number already taken");
		return false;
	}
	temp.age = age;
	if (temp.age < 21) {
		box.failure.setString("invalid age");
		return false;
	}
	box.failure.setString("enter balance");
	temp.balance = balance;
	if (temp.balance < 300) {
		box.failure.setString("balance can't be less than 300 EGP ");
		return false;

	}

	temp.accountNum = (rand() % 101) + 100;
	while (find(temp.accountNum, users)) {
		temp.accountNum = (rand() % 101) + 900;
	}
	users.push_back(temp);
	thisUserIndex = users.size() - 1;
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
	email.resize(email.size() - 1);
	password.resize(password.size() - 1);
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
bool addEmployee(vector<user>& users, addEmpWindow& empWindow, string inputs[], balancePanel panel[]) {
	user temp;
	if (findEmail(inputs[1], users) || inputs[1].find("@employee.bank") == string::npos) {
		empWindow.addEmpStatus.setPosition(450, 880);
		empWindow.addEmpStatus.setCharacterSize(25);
		empWindow.addEmpStatus.setString("Email already in use enter another one \nor make sure that your email contains @employee.bank");
		return false;
	}
	users.push_back(temp);
	users[users.size() - 1].userAccount.userName = inputs[0];
	users[users.size() - 1].userAccount.email = inputs[1];
	users[users.size() - 1].userAccount.password = inputs[2];

	empWindow.addEmpStatus.setString("Employee added succesfully");

	return true;
}

bool freeze(int accNum, vector<user>& users, int userIndex, viewBackground viewer[])
{
	if (!find(accNum, users)) {
		return false;
	}
	else if (find(accNum, users)) {
		string userInfo, newUserInfo;
		users[anotherUserIndex].frozen = true;
		userInfo = viewer[userIndex].viewText.getString();
		userInfo.resize(userInfo.size() - 1);
		newUserInfo = userInfo + "1";
		viewer[userIndex].viewText.setString(newUserInfo);

	}
	return true;

}
bool unFreeze(int accNum, vector<user>& users, int userIndex, viewBackground viewer[])
{
	if (!find(accNum, users)) {
		return false;
	}
	else if (find(accNum, users)) {
		string userInfo, newUserInfo;
		users[anotherUserIndex].frozen = false;
		userInfo = viewer[userIndex].viewText.getString();
		userInfo.resize(userInfo.size() - 1);
		newUserInfo = userInfo + "0";
		viewer[userIndex].viewText.setString(newUserInfo);
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
void loan(vector<user>& users, float amount, bigDarkBox& bigBox) {
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
		bigBox.TransactionStatus.setString("loan is accepted and have to be returned by " + to_string(months) + " months");

		loanTransaction.transactionType = "loan";
		loanTransaction.transactionAmount = amount;
		loanTransaction.recepient = "you";
		users[thisUserIndex].balance += amount;
		users[thisUserIndex].transactionCount++;
		users[thisUserIndex].userTransaction.push_back(loanTransaction);

	}
}
void Withdraw(vector<user>& users, float amount, bigDarkBox& bigBox) {
	transaction withdrawTransaction;

	if (!validBalance(users[thisUserIndex], amount)) {
		bigBox.TransactionStatus.setString("Not enough balance");
	}
	else {
		users[thisUserIndex].balance -= amount;
		users[thisUserIndex].transactionCount++;
		users[thisUserIndex].userTransaction.push_back(withdrawTransaction);
		users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionAmount = amount;
		users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].recepient = "noRecepient";
		users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionType = "withdrawl";

		bigBox.TransactionStatus.setString("you have withdrawn " + to_string((int)amount));
		cout << thisUserIndex << endl;
	}

};
void transfer(vector<user>& users, float amount, int accNum, bigDarkBox& bigBox) {


	transaction temp;

	if (users[thisUserIndex].balance - amount < 0) {
		bigBox.TransactionStatus.setString("Not enough balance");
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
			bigBox.TransactionStatus.setString("You have transferred amount of " + to_string((int)amount) + " to the account " + to_string(accNum));
		}
		else {
			bigBox.TransactionStatus.setString("This acount does not exist");
		}
	}
};
void viewTransactions(vector<user> users, viewTransactionBox& box) {
	int index = users[thisUserIndex].transactionCount - 1;
	int j = 0;
	for (int i = index; i >= 0; i--) {
		//box.Transactions[j].setString("Transaction of Type " + users[thisUserIndex].userTransaction[i].transactionType + " with amount of " + to_string((int)users[thisUserIndex].userTransaction[i].transactionAmount) + " From " + to_string(users[thisUserIndex].accountNum) + " To " + users[thisUserIndex].userTransaction[i].recepient);
		box.Transactions[j].setString(users[thisUserIndex].userTransaction[i].recepient + "  " + users[thisUserIndex].userTransaction[i].transactionType + "  " + to_string((int)users[thisUserIndex].userTransaction[i].transactionAmount));
		j++;
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
	for (int i = 0; i < users.size(); i++) {
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

	while (in >> temp.accountNum) {
		in >> temp.userAccount.userName >> temp.userAccount.email >> temp.phoneNumber >>
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
	darkBackgroundBigTexture.loadFromFile("Assets/big dark background.png");
	enterValuesBackgroundTexture.loadFromFile("Assets/enter values background.png");
	viewBackgroundTexture.loadFromFile("Assets/view background.png");
	searchTexture.loadFromFile("Assets/search.png");
	rockebFont.loadFromFile("Fonts/rockeb.ttf");
	britanicFont.loadFromFile("Fonts/BRITANIC.ttf");
	berlinSansFont.loadFromFile("Fonts/Berlin Sans FB Regular.ttf");
	darkBackgroundLargeTexture.loadFromFile("Assets/large dark background.png");
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
	String textArr = "Transfer Balance";
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
void setHeader(Header& header) {
	String textArr[3] = { "Morning Mr, ", "Admin","Haitham Bank" };
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
	header.user.setString(textArr[1]);
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
void drawBigBox(bigDarkBox bigDarkbox, button btn, string transactionTag, viewTransactionBox box) {
	if (transactionTag == "Last Transactions") {
		drawViewTransactions(box);
	}
	else {
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

}
void drawHeader(Header header, vector<user> users) {
	window.draw(header.background);
	window.draw(header.closeBtn);
	window.draw(header.minimizeBtn);
	window.draw(header.optionsBtn);
	window.draw(header.haithamBank);
	window.draw(header.goodMorning);
	if (thisUserIndex == -1) {
		header.user.setString("guest 141");
	}
	else {
		header.user.setString(users[thisUserIndex].userAccount.userName);
	}
	window.draw(header.user);
}
void sideBtnCollision(button btn[], int arrSize, string& s) {

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
void functionCaller(string functionTag, string input1, string input2, vector<user>& users, bigDarkBox& bigBox, viewTransactionBox& box)
{
	if (functionTag == "Transfer Balance") {
		transfer(users, stof(input1), stoi(input2), bigBox);
	}
	else if (functionTag == "Withdraw") {
		Withdraw(users, stof(input1), bigBox);
	}
	else if (functionTag == "Ask for a Loan") {
		loan(users, stof(input1), bigBox);
	}
	else {
		viewTransactions(users, box);
	}
}
void setViewTransactionBox(viewTransactionBox& box) {
	box.background.setTexture(darkBackgroundTexture);
	box.background.setPosition(710, 500);
	box.background.setScale(1.11, 1.105);

	for (int i = 0; i < 5; i++) {

		box.Transactions[i].setFont(rockebFont);
		box.Transactions[i].setCharacterSize(30);
		box.Transactions[i].setPosition(800, 540 + (i * 75));
		box.Transactions[i].setFillColor(Color::White);


	}
	for (int i = 0; i < 5; i++) {
		box.Fields[i].setTexture(enterValuesBackgroundTexture);
		box.Fields[i].setPosition(750, 520 + (i * 75));
		box.Fields[i].setScale(1.75, 1);

	}


}
void drawViewTransactions(viewTransactionBox box) {
	window.draw(box.background);
	for (int i = 0; i < 5; i++) {
		window.draw(box.Transactions[i]);

	}
	for (int i = 0; i < 5; i++) {
		window.draw(box.Fields[i]);

	}

}
void initializeSignUp(signUpBox& box) {
	box.background.setTexture(darkBackgroundLargeTexture);
	box.background.setScale(1, 1.1);
	box.background.setOrigin(box.background.getLocalBounds().left + box.background.getLocalBounds().width / 2.0f, box.background.getLocalBounds().top + box.background.getLocalBounds().height / 2.0f);
	box.background.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 100);
	box.valueField1.setTexture(enterValuesBackgroundTexture);
	box.valueField1.setOrigin(box.valueField1.getLocalBounds().left + box.valueField1.getLocalBounds().width / 2.0f, box.valueField1.getLocalBounds().top + box.valueField1.getLocalBounds().height / 2.0f);
	box.valueField1.setPosition(Vector2f(box.background.getPosition().x + 450, box.background.getPosition().y - 300));
	box.valueField2.setTexture(enterValuesBackgroundTexture);
	box.valueField2.setOrigin(box.valueField2.getLocalBounds().left + box.valueField2.getLocalBounds().width / 2.0f, box.valueField2.getLocalBounds().top + box.valueField2.getLocalBounds().height / 2.0f);
	box.valueField2.setPosition(Vector2f(box.background.getPosition().x + 450, box.background.getPosition().y - 200));
	box.valueField3.setTexture(enterValuesBackgroundTexture);
	box.valueField3.setOrigin(box.valueField3.getLocalBounds().left + box.valueField3.getLocalBounds().width / 2.0f, box.valueField3.getLocalBounds().top + box.valueField3.getLocalBounds().height / 2.0f);
	box.valueField3.setPosition(Vector2f(box.background.getPosition().x + 450, box.background.getPosition().y - 100));
	box.valueField4.setTexture(enterValuesBackgroundTexture);
	box.valueField4.setOrigin(box.valueField4.getLocalBounds().left + box.valueField4.getLocalBounds().width / 2.0f, box.valueField4.getLocalBounds().top + box.valueField4.getLocalBounds().height / 2.0f);
	box.valueField4.setPosition(Vector2f(box.background.getPosition().x + 450, box.background.getPosition().y));
	box.valueField5.setTexture(enterValuesBackgroundTexture);
	box.valueField5.setOrigin(box.valueField5.getLocalBounds().left + box.valueField5.getLocalBounds().width / 2.0f, box.valueField5.getLocalBounds().top + box.valueField5.getLocalBounds().height / 2.0f);
	box.valueField5.setPosition(Vector2f(box.background.getPosition().x + 450, box.background.getPosition().y + 100));
	box.valueField6.setTexture(enterValuesBackgroundTexture);
	box.valueField6.setOrigin(box.valueField6.getLocalBounds().left + box.valueField6.getLocalBounds().width / 2.0f, box.valueField6.getLocalBounds().top + box.valueField6.getLocalBounds().height / 2.0f);
	box.valueField6.setPosition(Vector2f(box.background.getPosition().x + 450, box.background.getPosition().y + 200));
	box.value1.setFont(berlinSansFont);
	box.value1.setCharacterSize(26);
	box.value1.setString("Username:");
	box.value1.setOrigin(box.value1.getLocalBounds().left + box.value1.getLocalBounds().width / 2.0f, box.value1.getLocalBounds().top + box.value1.getLocalBounds().height / 2.0f); // Set the origin of the text to the center
	box.value1.setPosition(box.valueField1.getPosition() - Vector2f(350, 0));
	box.value2.setFont(berlinSansFont);
	box.value2.setString("Email:");
	box.value2.setCharacterSize(26);
	box.value2.setOrigin(box.value2.getLocalBounds().left + box.value2.getLocalBounds().width / 2.0f, box.value2.getLocalBounds().top + box.value2.getLocalBounds().height / 2.0f); // Set the origin of the text to the center
	box.value2.setPosition(box.valueField2.getPosition() - Vector2f(330, 0));
	box.value3.setFont(berlinSansFont);
	box.value3.setCharacterSize(26);
	box.value3.setString("Password:");
	box.value3.setOrigin(box.value3.getLocalBounds().left + box.value3.getLocalBounds().width / 2.0f, box.value3.getLocalBounds().top + box.value3.getLocalBounds().height / 2.0f); // Set the origin of the text to the center
	box.value3.setPosition(box.valueField3.getPosition() - Vector2f(350, 0));
	box.value4.setFont(berlinSansFont);
	box.value4.setString("Phone Number:");
	box.value4.setCharacterSize(26);
	box.value4.setOrigin(box.value4.getLocalBounds().left + box.value4.getLocalBounds().width / 2.0f, box.value4.getLocalBounds().top + box.value4.getLocalBounds().height / 2.0f); // Set the origin of the text to the center
	box.value4.setPosition(box.valueField4.getPosition() - Vector2f(380, 0));
	box.value5.setFont(berlinSansFont);
	box.value5.setString("Age:");
	box.value5.setCharacterSize(26);
	box.value5.setOrigin(box.value5.getLocalBounds().left + box.value5.getLocalBounds().width / 2.0f, box.value5.getLocalBounds().top + box.value5.getLocalBounds().height / 2.0f); // Set the origin of the text to the center
	box.value5.setPosition(box.valueField5.getPosition() - Vector2f(320, 0));
	box.value6.setFont(berlinSansFont);
	box.value6.setString("Balance:");
	box.value6.setCharacterSize(26);
	box.value6.setOrigin(box.value6.getLocalBounds().left + box.value6.getLocalBounds().width / 2.0f, box.value6.getLocalBounds().top + box.value6.getLocalBounds().height / 2.0f); // Set the origin of the text to the center
	box.value6.setPosition(box.valueField6.getPosition() - Vector2f(340, 0));
	box.Button1.setTexture(smallButtonTexture);
	box.Button1.setOrigin(box.Button1.getLocalBounds().left + box.Button1.getLocalBounds().width / 2.0f, box.Button1.getLocalBounds().top + box.Button1.getLocalBounds().height / 2.0f);
	box.Button1.setPosition(box.valueField6.getPosition() + Vector2f(0, 100));
	box.buttonText1.setFont(berlinSansFont);
	box.buttonText1.setString("Sign Up");
	box.buttonText1.setCharacterSize(26);
	box.buttonText1.setOrigin(box.buttonText1.getLocalBounds().left + box.buttonText1.getLocalBounds().width / 2.0f, box.buttonText1.getLocalBounds().top + box.buttonText1.getLocalBounds().height / 2.0f);
	box.buttonText1.setPosition(box.Button1.getPosition() + Vector2f(0, 0));
	box.heading1.setString("Already have an account?");
	box.heading1.setFont(berlinSansFont);
	box.heading1.setCharacterSize(36);
	box.heading1.setOrigin(box.heading1.getLocalBounds().left + box.heading1.getLocalBounds().width / 2.0f, box.heading1.getLocalBounds().top + box.heading1.getLocalBounds().height / 2.0f);
	box.heading1.setPosition(box.background.getPosition() - Vector2f(400, 100));
	box.Button2.setTexture(smallButtonTexture);
	box.Button2.setOrigin(box.Button2.getLocalBounds().left + box.Button2.getLocalBounds().width / 2.0f, box.Button2.getLocalBounds().top + box.Button2.getLocalBounds().height / 2.0f);
	box.Button2.setPosition(box.heading1.getPosition() + Vector2f(0, 100));
	box.buttonText2.setFont(berlinSansFont);
	box.buttonText2.setString("Sign In");
	box.buttonText2.setCharacterSize(26);
	box.buttonText2.setOrigin(box.buttonText2.getLocalBounds().left + box.buttonText2.getLocalBounds().width / 2.0f, box.buttonText2.getLocalBounds().top + box.buttonText2.getLocalBounds().height / 2.0f);
	box.buttonText2.setPosition(box.Button2.getPosition() + Vector2f(0, 0));
}
void drawSignUp(signUpBox box) {
	window.draw(box.background);
	window.draw(box.valueField1);
	window.draw(box.valueField2);
	window.draw(box.valueField3);
	window.draw(box.valueField4);
	window.draw(box.valueField5);
	window.draw(box.valueField6);
	window.draw(box.value1);
	window.draw(box.value2);
	window.draw(box.value3);
	window.draw(box.value4);
	window.draw(box.value5);
	window.draw(box.value6);
	window.draw(box.Button1);
	window.draw(box.Button2);
	window.draw(box.buttonText1);
	window.draw(box.heading1);
	window.draw(box.buttonText2);
}
void initializeSignIn(signInBox& box) {
	box.background.setTexture(darkBackgroundLargeTexture);
	box.background.setScale(1, 1.1);
	box.background.setOrigin(box.background.getLocalBounds().left + box.background.getLocalBounds().width / 2.0f, box.background.getLocalBounds().top + box.background.getLocalBounds().height / 2.0f);
	box.background.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 100);
	box.valueField1.setTexture(enterValuesBackgroundTexture);
	box.valueField1.setOrigin(box.valueField1.getLocalBounds().left + box.valueField1.getLocalBounds().width / 2.0f, box.valueField1.getLocalBounds().top + box.valueField1.getLocalBounds().height / 2.0f);
	box.valueField1.setPosition(Vector2f(box.background.getPosition().x + 450, box.background.getPosition().y - 100));
	box.valueField2.setTexture(enterValuesBackgroundTexture);
	box.valueField2.setOrigin(box.valueField2.getLocalBounds().left + box.valueField2.getLocalBounds().width / 2.0f, box.valueField2.getLocalBounds().top + box.valueField2.getLocalBounds().height / 2.0f);
	box.valueField2.setPosition(Vector2f(box.background.getPosition().x + 450, box.background.getPosition().y));
	box.value1.setFont(berlinSansFont);
	box.value1.setCharacterSize(26);
	box.value1.setString("Email:");
	box.value1.setOrigin(box.value1.getLocalBounds().left + box.value1.getLocalBounds().width / 2.0f, box.value1.getLocalBounds().top + box.value1.getLocalBounds().height / 2.0f); // Set the origin of the text to the center
	box.value1.setPosition(box.valueField1.getPosition() - Vector2f(330, 0));
	box.value2.setFont(berlinSansFont);
	box.value2.setString("Password:");
	box.value2.setCharacterSize(26);
	box.value2.setOrigin(box.value2.getLocalBounds().left + box.value2.getLocalBounds().width / 2.0f, box.value2.getLocalBounds().top + box.value2.getLocalBounds().height / 2.0f); // Set the origin of the text to the center
	box.value2.setPosition(box.valueField2.getPosition() - Vector2f(350, 0));
	box.Button1.setTexture(smallButtonTexture);
	box.Button1.setOrigin(box.Button1.getLocalBounds().left + box.Button1.getLocalBounds().width / 2.0f, box.Button1.getLocalBounds().top + box.Button1.getLocalBounds().height / 2.0f);
	box.Button1.setPosition(box.valueField2.getPosition() + Vector2f(0, 100));
	box.buttonText1.setFont(berlinSansFont);
	box.buttonText1.setString("Sign In");
	box.buttonText1.setCharacterSize(26);
	box.buttonText1.setOrigin(box.buttonText1.getLocalBounds().left + box.buttonText1.getLocalBounds().width / 2.0f, box.buttonText1.getLocalBounds().top + box.buttonText1.getLocalBounds().height / 2.0f);
	box.buttonText1.setPosition(box.Button1.getPosition() + Vector2f(0, 0));
	box.heading1.setString("Don't have an account?");
	box.heading1.setFont(berlinSansFont);
	box.heading1.setCharacterSize(36);
	box.heading1.setOrigin(box.heading1.getLocalBounds().left + box.heading1.getLocalBounds().width / 2.0f, box.heading1.getLocalBounds().top + box.heading1.getLocalBounds().height / 2.0f);
	box.heading1.setPosition(box.background.getPosition() - Vector2f(400, 100));
	box.Button2.setTexture(smallButtonTexture);
	box.Button2.setOrigin(box.Button2.getLocalBounds().left + box.Button2.getLocalBounds().width / 2.0f, box.Button2.getLocalBounds().top + box.Button2.getLocalBounds().height / 2.0f);
	box.Button2.setPosition(box.heading1.getPosition() + Vector2f(0, 100));
	box.buttonText2.setFont(berlinSansFont);
	box.buttonText2.setString("Sign Up");
	box.buttonText2.setCharacterSize(26);
	box.buttonText2.setOrigin(box.buttonText2.getLocalBounds().left + box.buttonText2.getLocalBounds().width / 2.0f, box.buttonText2.getLocalBounds().top + box.buttonText2.getLocalBounds().height / 2.0f);
	box.buttonText2.setPosition(box.Button2.getPosition() + Vector2f(0, 0));
	box.signInFailure.setFont(berlinSansFont);
	box.signInFailure.setCharacterSize(30);
	box.signInFailure.setPosition(1180, 900);
}
void drawSignIn(signInBox box) {
	window.draw(box.background);
	window.draw(box.valueField1);
	window.draw(box.valueField2);
	window.draw(box.value1);
	window.draw(box.value2);
	window.draw(box.heading1);
	window.draw(box.Button1);
	window.draw(box.Button2);
	window.draw(box.buttonText1);
	window.draw(box.buttonText2);
	window.draw(box.signInFailure);
}
void adminPagebtnIntializer(button btn[], int arrSize) {
	string btnstring[4] = { "add employees","manage accounts","freeze","unfreeze" };
	for (int i = 0; i < arrSize; i++) {
		btn[0].btnSprite.setTexture(smallButtonTexture);
		btn[0].btnText.setFont(rockebFont);
		btn[0].btnText.setFillColor(Color::White);
		btn[0].btnSprite.setPosition(1300, 260 + ((0) * 105));
		btn[0].btnSprite.setScale(1.3, 1.15);
		btn[0].btnText.setString(btnstring[0]);
	}
	for (int i = 0; i < arrSize; i++) {
		btn[i + 2].btnSprite.setTexture(smallButtonTexture);
		btn[i + 2].btnText.setFont(rockebFont);
		btn[i + 2].btnText.setFillColor(Color::White);
		btn[i + 2].btnSprite.setPosition(1000 + ((i) * 400), 520);
		btn[i + 2].btnSprite.setScale(1.1, 1.1);
		btn[i + 2].btnText.setString(btnstring[i + 2]);
	}
	btn[0].btnText.setPosition(1390, 280);
	btn[1].btnText.setPosition(1370, 390);
	btn[2].btnText.setPosition(1100, 550);
	btn[3].btnText.setPosition(1500, 550);
}
void searchButtonInitializer(button& btn) {
	btn.btnSprite.setTexture(smallButtonTexture);
	btn.btnSprite.setPosition(80, 520);
	btn.btnSprite.setScale(1.1, 1.1);
	btn.searchSprite.setTexture(searchTexture);
	btn.searchSprite.setPosition(350, 540);
}
void searchButtonDrawer(button btn) {

	window.draw(btn.btnSprite);
	window.draw(btn.searchSprite);
	window.draw(btn.btnText);

}
void viewbackgroundIntializer(viewBackground viewer[], int arrSize, vector<user> users) {
	string userTxt;
	for (int i = 0; i < arrSize; i++) {
		int j = rand() % users.size();

		userTxt = (to_string(users[j].accountNum) + " " + users[j].userAccount.userName + " " + to_string((int)users[j].balance) + "  " + to_string(users[j].frozen));
		cout << users[j].frozen << endl;
		viewer[i].veiwSprite.setTexture(viewBackgroundTexture);
		viewer[i].viewText.setFont(rockebFont);
		viewer[i].viewText.setPosition(150, 665 + ((i) * 115));
		viewer[i].viewText.setCharacterSize(40);
		viewer[i].viewText.setFillColor(Color::White);
		viewer[i].veiwSprite.setPosition(70, 650 + ((i) * 115));
		viewer[i].viewText.setString(userTxt);
		viewer[i].veiwSprite.setScale(1.16, 1.07);

	}
}
void adminPanelIntializer(balancePanel panel[], vector<user> users) {
	string str[] = { "users","employees" };
	panel[0].panel.setTexture(darkBackgroundSmallTexture);
	panel[0].panel.setPosition(60, 250);
	panel[0].panel.setScale(1.16, 1.07);

	panel[0].balnceText.setFont(rockebFont);
	panel[0].balnceText.setString(str[0]);
	panel[0].balnceText.setCharacterSize(80);
	panel[0].balnceText.setFillColor(Color::White);
	panel[0].balnceText.setPosition(150, 260);
	panel[0].amountText.setFont(rockebFont);
	panel[0].amountText.setString(to_string(users.size()));
	panel[0].amountText.setCharacterSize(60);
	panel[0].amountText.setFillColor(Color::White);
	panel[0].amountText.setPosition(170, 350);

}
void adminPanelDrawer(balancePanel panel[]) {
	window.draw(panel[0].panel);
	for (int i = 0; i < 2; i++) {
		window.draw(panel[i].balnceText);
		window.draw(panel[i].amountText);
	}
}
void adminPageButtonDrawer(button btn[], int arrSize)
{
	for (int i = 0; i < arrSize; i++) {

		window.draw(btn[i].btnSprite);
		window.draw(btn[i].btnText);

	}
}
void viewBackgroundDrawer(viewBackground view[], int arrSize)
{
	for (int i = 0; i < arrSize; i++) {

		window.draw(view[i].veiwSprite);
		window.draw(view[i].viewText);

	}
}
void darkBoxBiginitializeradminPage(viewBackground& darkbox) {
	darkbox.veiwSprite.setTexture(darkBackgroundBigTexture);
	darkbox.veiwSprite.setPosition(60, 500);
	darkbox.veiwSprite.setScale(1.16, 1.07);
}
void darkBoxBigDraweradminPage(viewBackground darkbox) {
	window.draw(darkbox.veiwSprite);
}
void userTxtCollision(viewBackground viewer[], int arrSize, vector<user> users, int& accNumber, int& userIndex) {
	string accNumStr;
	for (int i = 0; i < arrSize; i++) {
		if (viewer[i].veiwSprite.getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {
			viewer[i].viewText.setFillColor(Color{ 128, 128, 128 });
		}
		else {
			viewer[i].viewText.setFillColor(Color::White);
		}
		if (viewer[i].veiwSprite.getGlobalBounds().intersects(mouseRect.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			accNumStr = viewer[i].viewText.getString();
			accNumStr.resize(4);
			accNumber = stoi(accNumStr);
			find(accNumber, users);
			userIndex = i;
		}
	}
}
void freezeUnfreezeCollision(button btn[], int arrSize, int& index) {
	for (int i = 2; i < arrSize; i++) {
		if (btn[i].btnSprite.getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {
			btn[i].btnText.setFillColor(Color{ 128, 128, 128 });
		}
		else {
			btn[i].btnText.setFillColor(Color::White);

		}
		if (btn[i].btnSprite.getGlobalBounds().intersects(mouseRect.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			index = i - 2;
		}
	}

}
void adminPageFunctionCaller(int& index, vector<user>& users, int accNumber, viewBackground viewer[], int userIndex) {
	if (index == 0) {
		freeze(accNumber, users, userIndex, viewer);
	}
	else if (index == 1) {
		unFreeze(accNumber, users, userIndex, viewer);
	}
	else if (index == 2) {
		viewer[0].viewText.setString(to_string(users[anotherUserIndex].accountNum) + "  " + users[anotherUserIndex].userAccount.userName + "  " + to_string((int)users[anotherUserIndex].balance) + "  " + to_string(users[anotherUserIndex].frozen));
	}
	index = 3;

}
void SetSearchTxt(Text& searchBtnTxt) {
	searchBtnTxt.setFillColor(Color::White);
	searchBtnTxt.setPosition(150, 540);
	searchBtnTxt.setFont(rockebFont);
	searchBtnTxt.setCharacterSize(40);
}
void setAddEmployeesBox(addEmpWindow& empWindow) {
	String labelsTxt[3] = { "Employee Name","Employee Email","Employee Password" };
	empWindow.background.setTexture(darkBackgroundTexture);
	empWindow.background.setPosition(400, 400);
	empWindow.background.setScale(1, 1.5);
	empWindow.close.setTexture(closeTexture);
	empWindow.close.setPosition(1320, 450);
	for (int i = 0; i < 3; i++) {
		empWindow.enterValueField[i].setTexture(enterValuesBackgroundTexture);
		empWindow.enterValueField[i].setPosition(500, 480 + (i * 150));
		empWindow.labels[i].setFont(rockebFont);
		empWindow.labels[i].setString(labelsTxt[i]);
		empWindow.labels[i].setPosition(530, 440 + (i * 150));

	}
	empWindow.addEmpStatus.setFont(rockebFont);
	empWindow.addEmpStatus.setFillColor(Color::White);
	empWindow.addEmpStatus.setPosition(450, 890);
	empWindow.addEmpStatus.setCharacterSize(30);


}
void drawAddEmpWindow(addEmpWindow empWindow) {
	window.draw(empWindow.background);
	window.draw(empWindow.close);
	for (int i = 0; i < 3; i++) {
		window.draw(empWindow.enterValueField[i]);
		window.draw(empWindow.labels[i]);
	}
	window.draw(empWindow.addEmpStatus);
}
void checkAddEmpCollision(button btn[], int& adminPageInputIndex, addEmpWindow empWindow) {
	if (btn[0].btnSprite.getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {
		btn[0].btnText.setFillColor(Color{ 128,128,128,128 });
	}
	else {
		btn[0].btnText.setFillColor(Color::White);
	}
	if (btn[0].btnSprite.getGlobalBounds().intersects(mouseRect.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
		adminPageInputIndex = 1;
	}
	if (empWindow.close.getGlobalBounds().intersects(mouseRect.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
		adminPageInputIndex = 0;
	}
}
void setAddEmpText(Text inputTxt[]) {
	for (int i = 0; i < 3; i++) {
		inputTxt[i].setFillColor(Color::White);
		inputTxt[i].setFont(rockebFont);
		inputTxt[i].setPosition(530, 500 + (i * 150));
	}
}
void drawAddEmpInputTxt(Text inputTxt[], int arrsize) {
	for (int i = 0; i < arrsize; i++) {
		window.draw(inputTxt[i]);
	}
}


void userPage(vector<user>& users, Header header, Sprite background) {
	Mouse ms;
	bigDarkBox bigdarkBox;
	button btn, btn2, sideButtons[4];
	balancePanel panel;
	viewTransactionBox box;
	setbigDarkBoxTransferBalance(bigdarkBox, btn);
	setButton(btn2);
	balancePanelIntializer(panel);
	btnIntializer(sideButtons, 4);
	setViewTransactionBox(box);
	setHeader(header);

	string input, input2;
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


	int inputIndex = 0;
	while (window.isOpen())
	{
		mouseRect.setPosition(ms.getPosition().x - 15, ms.getPosition().y - 35);
		sideBtnCollision(sideButtons, 4, functionTag);
		if (functionTag != "Transfer Balance") {
			input2.resize(0);
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == Event::TextEntered && input.size() < 6) {
				char c;
				c = static_cast<char>(event.text.unicode);
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
					functionCaller(functionTag, input, input2, users, bigdarkBox, box);
					input.resize(0);
				}
			}
			else {
				if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter && input.size() > 0) {
					inputIndex++;
					inputIndex %= 2;
				}
				if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter && inputIndex == 0) {
					functionCaller(functionTag, input, input2, users, bigdarkBox, box);
					input.resize(0);
					input2.resize(0);

				}

			}

		}
		inputText.setString(input);
		inputText2.setString(input2);
		if (functionTag == "Last Transactions") {
			functionCaller(functionTag, input, input2, users, bigdarkBox, box);
		}
		window.clear();
		window.draw(background);
		drawHeader(header, users);
		sideButtonDrawer(sideButtons, 4);
		balancePanelDrawer(panel, users);
		drawBigBox(bigdarkBox, btn, functionTag, box);
		window.draw(inputText);
		if (functionTag == "Transfer Balance") {
			window.draw(inputText2);
		}
		window.display();

	}


}
bool signInPage(vector<user> users, Header header, Sprite background) {
	Mouse ms;
	signInBox signIn;
	initializeSignIn(signIn);
	Text inputText[2];
	for (int i = 0; i < 2; i++) {
		inputText[i].setFont(berlinSansFont);
		inputText[i].setCharacterSize(26);
		inputText[i].setPosition(1180, 522 + i * 100);
	}
	string input[2];
	int inputIndex = 0;
	while (window.isOpen()) {
		mouseRect.setPosition(ms.getPosition().x - 15, ms.getPosition().y - 35);
		Event event;
		while (window.pollEvent(event))
		{
			if (mouseRect.getGlobalBounds().intersects(signIn.Button1.getGlobalBounds())) {
				signIn.buttonText1.setFillColor(Color{ 128,128,128 });
				if (Mouse::isButtonPressed(Mouse::Left) && login(users, input[0], input[1], signIn)) {
					return true;
				}
			}
			else {
				signIn.buttonText1.setFillColor(Color::White);

			}
			if (mouseRect.getGlobalBounds().intersects(signIn.Button2.getGlobalBounds())) {
				signIn.buttonText2.setFillColor(Color{ 128,128,128 });
				if (Mouse::isButtonPressed(Mouse::Left)) {
					return false;
				}
			}
			else {
				signIn.buttonText2.setFillColor(Color::White);

			}

			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter && input[0].size() > 0) {
				inputIndex++;
				inputIndex %= 2;
			}
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter && inputIndex == 0) {
				cout << input[0] << endl << input[1] << endl;
				if (login(users, input[0], input[1], signIn))
				{
					return true;
				}

				input[0].erase();
				input[1].erase();

			}


			if (event.type == Event::TextEntered)
			{
				char c = static_cast<char>(event.text.unicode);
				input[inputIndex] += c;


			}

			if (Keyboard::isKeyPressed(Keyboard::BackSpace) && input[inputIndex].size() > 0)
			{
				input[inputIndex].resize(input[inputIndex].size() - 1);
			}


		}
		inputText[0].setString(input[0]);
		inputText[1].setString(input[1]);
		window.clear();
		window.draw(background);
		drawHeader(header, users);
		drawSignIn(signIn);
		for (int i = 0; i < 2; i++) {
			window.draw(inputText[i]);
		}
		window.display();

	}
	return true;
}
bool signUpPage(vector<user>& users, Header header, Sprite background) {
	Mouse ms;
	signUpBox box;
	initializeSignUp(box);
	Text inputText[6];
	for (int i = 0; i < 6; i++) {
		inputText[i].setFont(berlinSansFont);
		inputText[i].setCharacterSize(26);
		inputText[i].setString("123");
		inputText[i].setPosition(1180, 322 + i * 100);
	}
	string input[6];
	int inputIndex = 0;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter && input[0].size() > 0) {
				inputIndex++;
				inputIndex %= 6;
			}
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter && inputIndex == 0) {
				if (signUp(users, input[0], input[1], input[2], input[3], stoi(input[4]), stof(input[5]), box)) {


					return true;

				}

				for (int i = 0; i < 6; i++) {
					input[i].erase();
				}
			}


			if (event.type == Event::TextEntered)
			{
				if (inputIndex > 2) {
					if (isdigit(static_cast<char>(event.text.unicode)))
						input[inputIndex] += static_cast<char>(event.text.unicode);
				}
				else {
					input[inputIndex] += static_cast<char>(event.text.unicode);
				}


			}

			if (Keyboard::isKeyPressed(Keyboard::BackSpace) && input[inputIndex].size() > 0)
			{
				input[inputIndex].resize(input[inputIndex].size() - 1);
			}

		}
		for (int i = 0; i < 6; i++) {
			inputText[i].setString(input[i]);
		}
		window.clear();
		window.draw(background);
		drawHeader(header, users);
		drawSignUp(box);
		for (int i = 0; i < 6; i++) {
			window.draw(inputText[i]);
		}
		window.display();




	}

	return true;
}
void adminPage(vector<user>& users, Header header, Sprite background) {

	int indexFreezeNot = 3, accNumber = 0, userIndex = 0, adminPageInputIndex = 0, addEmployeeInputIndex = 0;
	user temp;
	mouseRect.setFillColor(Color::Black);
	Mouse ms;
	bigDarkBox bigdarkBox;
	button searchBtn, btn2, sideButtons[4];
	balancePanel panel[2];
	viewBackground viewbackground1, viewbackground[3], darkbox;
	addEmpWindow empWindow;
	Text searchBtnTxt, addEmpInputs[3];
	string searchBtnText, addEmpInputText[3];
	SetSearchTxt(searchBtnTxt);
	setAddEmpText(addEmpInputs);
	setHeader(header);
	setButton(btn2);
	adminPanelIntializer(panel, users);
	viewbackgroundIntializer(viewbackground, 3, users);
	adminPagebtnIntializer(sideButtons, 2);
	darkBoxBiginitializeradminPage(darkbox);
	setAddEmployeesBox(empWindow);
	searchButtonInitializer(searchBtn);

	while (window.isOpen())
	{
		mouseRect.setPosition(ms.getPosition().x - 15, ms.getPosition().y - 35);
		if (adminPageInputIndex == 0) {
			userTxtCollision(viewbackground, 3, users, accNumber, userIndex);
			freezeUnfreezeCollision(sideButtons, 4, indexFreezeNot);
			adminPageFunctionCaller(indexFreezeNot, users, accNumber, viewbackground, userIndex);
		}
		checkAddEmpCollision(sideButtons, adminPageInputIndex, empWindow);

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (adminPageInputIndex == 0) {
				if (event.type == Event::TextEntered && searchBtnText.size() < 4) {

					if (isdigit(static_cast<char>(event.text.unicode))) {
						searchBtnText += static_cast<char>(event.text.unicode);;
					}
				}
				if (event.type == Event::KeyReleased && event.key.code == Keyboard::BackSpace && searchBtnText.size() > 0) {
					searchBtnText.resize(searchBtnText.size() - 1);
				}
				if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter && searchBtnText.size() > 0) {
					if (find(stoi(searchBtnText), users)) {
						indexFreezeNot = 2;
						searchBtnText.resize(0);
						adminPageFunctionCaller(indexFreezeNot, users, accNumber, viewbackground, userIndex);
					}

				}
			}
			else if (adminPageInputIndex == 1) {

				if (event.type == Event::TextEntered && addEmpInputText[0].size() < 20) {


					if (addEmployeeInputIndex == 0) {
						addEmpInputText[0] += static_cast<char>(event.text.unicode);;
					}
					else if (addEmployeeInputIndex == 1) {
						addEmpInputText[1] += static_cast<char>(event.text.unicode);;
					}
					else if (addEmployeeInputIndex == 2) {
						if (isdigit(static_cast<char>(event.text.unicode))) {
							addEmpInputText[2] += static_cast<char>(event.text.unicode);
						}
					}

				}
				if (addEmployeeInputIndex == 0) {
					if (event.type == Event::TextEntered && event.text.unicode == '\b' && addEmpInputText[0].size() > 1) {
						addEmpInputText[0].resize(addEmpInputText[0].size() - 2);

					}
					if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter && addEmpInputText[0].size() > 0) {
						addEmpInputText[0].resize(addEmpInputText[0].size() - 1);
						addEmployeeInputIndex++;
						addEmployeeInputIndex %= 3;
					}

				}
				else if (addEmployeeInputIndex == 1) {
					if (event.type == Event::TextEntered && event.text.unicode == '\b' && addEmpInputText[1].size() > 1) {
						addEmpInputText[1].resize(addEmpInputText[1].size() - 2);
					}
					if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter && addEmpInputText[1].size() > 0) {
						addEmpInputText[1].resize(addEmpInputText[1].size() - 1);
						addEmployeeInputIndex++;
						addEmployeeInputIndex %= 3;
					}
				}
				else if (addEmployeeInputIndex == 2) {
					if (event.type == Event::TextEntered && event.text.unicode == '\b' && addEmpInputText[2].size() > 1) {
						addEmpInputText[2].resize(addEmpInputText[2].size() - 2);
					}
					if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter && addEmpInputText[2].size() > 0) {
						addEmpInputText[2].resize(addEmpInputText[2].size());
						addEmployeeInputIndex++;
						addEmployeeInputIndex %= 3;
						addEmployee(users, empWindow, addEmpInputText, panel);
						for (int i = 0; i < 3; i++) {
							addEmpInputText[i].resize(0);
						}

					}
				}


			}

		}
		searchBtnTxt.setString(searchBtnText);
		for (int i = 0; i < 3; i++) {
			addEmpInputs[i].setString(addEmpInputText[i]);
		}
		window.clear();
		window.draw(background);
		darkBoxBigDraweradminPage(darkbox);

		viewBackgroundDrawer(viewbackground, 3);

		adminPanelDrawer(panel);
		drawHeader(header, users);
		adminPageButtonDrawer(sideButtons, 4);
		searchButtonDrawer(searchBtn);
		window.draw(searchBtnTxt);
		if (adminPageInputIndex == 1) {
			drawAddEmpWindow(empWindow);
			drawAddEmpInputTxt(addEmpInputs, 3);
		}
		window.draw(mouseRect);
		window.display();
	}


}
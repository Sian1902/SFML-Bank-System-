#include<iostream>
#include<vector>
#include <fstream>
#include<sstream>
#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;
int thisUserIndex = 0;
int months;
int anotherUserIndex;
// GUI global variables 
RenderWindow window(sf::VideoMode(1920, 1080), "HaithamBank", Style::Default);
Font rockebFont, britanicFont, berlinSansFont;
Texture headerTexture, closeTexture, mininmizeTexture, optionsTexture, backgroundTexture, bigButtonTexture, smallButtonTexture, darkBackgroundTexture, darkBackgroundSmallTexture, enterValuesBackgroundTexture, viewBackgroundTexture, darkBackgroundBigTexture, searchTexture;

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

// GUI entities struct 
struct bigDarkBox {
	Sprite background;
	Sprite valueField1;
	Sprite valueField2;
	Text amountTxt;
	Text Totxt;
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
void loan(vector<user>& users, float amount);
void Withdraw(vector<user>& users);
void transfer(vector<user>& users);
void viewTransactions(vector<user> users);
//GUI functions
void btnIntializer(button btn[], int arrSize);
void sideButtonDrawer(button btn[], int arrSize);
void texturesAndFonts();
void balancePanelIntializer(balancePanel& panel);
void balancePanelDrawer(balancePanel& panel);
void setHeader(Header& header);
void setButton(button& btn);
void drawBigBox(bigDarkBox bigDarkbox, button btn);
void drawHeader(Header header);
void viewbackgroundIntializer(viewBackground viewer[], int arrSize);
void viewBackgroundDrawer(viewBackground view[], int arrSize);
void darkBoxBiginitializer(viewBackground& darkbox);
void darkBoxBigDrawer(viewBackground darkbox);
void searchButtonDrawer(button btn);
void searchButtonInitializer(button& btn, string str);
void adminPanelIntializer(balancePanel panel[]);
void adminPanelDrawer(balancePanel panel[]);

int main() {
	texturesAndFonts();
	bigDarkBox bigdarkBox;
	button btn, btn2, sideButtons[4];
	Header header;
	balancePanel panel[2];
	viewBackground viewbackground1,viewbackground[3],darkbox;
	setHeader(header);
	setButton(btn2);
	adminPanelIntializer(panel);
	btnIntializer(sideButtons, 2);
	darkBoxBiginitializer(darkbox);
	viewbackgroundIntializer(viewbackground, 3);
	searchButtonInitializer(btn,"search");
	////sprites 
	Sprite background;
	background.setTexture(backgroundTexture);
	////background modification
	background.setScale(1.5, 1.5);
	background.setPosition(-50, 0);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(background);
		darkBoxBigDrawer(darkbox);
		
		viewBackgroundDrawer(viewbackground,3);

		adminPanelDrawer(panel);
		drawBigBox(bigdarkBox, btn);
		drawHeader(header);
		sideButtonDrawer(sideButtons, 4);
		searchButtonDrawer(btn);
		window.display();
	}

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
void loan(vector<user>& users, float amount) {
	transaction loanTransaction;

	if (amount * 0.25 >= users[thisUserIndex].balance) {
		cout << "Rejected due to low balance " << endl;
	}


	else {
		if (amount > 100000) {
			months = ((amount + users[thisUserIndex].balance) / amount) * 6;
		}
		else {
			months = (amount + users[thisUserIndex].balance) / amount;
		}
		cout << "loan is accepted and have to be returned by " << months << " months" << endl;

		loanTransaction.transactionType = "loan";
		loanTransaction.transactionAmount = amount;
		users[thisUserIndex].balance += amount;
		users[thisUserIndex].transactionCount++;
		users[thisUserIndex].userTransaction.push_back(loanTransaction);

	}
}
void Withdraw(vector<user>& users) {
	float amount;
	transaction withdrawTransaction;
	cout << "Please enter the amount needed to withdraw" << endl;
	cin >> amount;
	if (!validBalance(users[thisUserIndex], amount)) {
		cout << "Not enough balance" << endl;
	}
	else {
		users[thisUserIndex].balance -= amount;
		users[thisUserIndex].transactionCount++;
		cout << withdrawTransaction.transactionAmount << endl;
		users[thisUserIndex].userTransaction.push_back(withdrawTransaction);
		users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionAmount = amount;
		users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].recepient = "noRecepient";
		users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionType = "withdrawl";

		cout << "you have withdrawn " << amount << " with remaining balance " << users[thisUserIndex].balance << " " << "in your account " << endl;
		cout << thisUserIndex << endl;
	}

};
void transfer(vector<user>& users) {
	float amount;
	int accNum;
	string accNumString;
	transaction temp;
	cout << "Please Enter the amount you need to transfer\n";
	cin >> amount;
	if (users[thisUserIndex].balance - amount < 0) {
		cout << "Not enough balance\n";
	}
	else {
		cout << "Please Enter the account number that you want to transfer this amount to\n";
		cin >> accNum;
		if (find(accNum, users)) {
			users[thisUserIndex].balance -= amount;
			users[anotherUserIndex].balance += amount;
			users[thisUserIndex].transactionCount++;
			users[anotherUserIndex].transactionCount++;
			accNumString = to_string(accNum);
			users[thisUserIndex].userTransaction.push_back(temp);
			users[anotherUserIndex].userTransaction.push_back(temp);
			// saving transaction for the sender
			users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionAmount = amount;
			users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].recepient = accNumString;
			users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionType = "transfer";

			// saving transaction for the reciever 
			users[anotherUserIndex].userTransaction[users[anotherUserIndex].transactionCount - 1].transactionAmount = amount;
			users[anotherUserIndex].userTransaction[users[anotherUserIndex].transactionCount - 1].recepient = to_string(users[thisUserIndex].accountNum);
			users[anotherUserIndex].userTransaction[users[anotherUserIndex].transactionCount - 1].transactionType = "transfer";
			cout << "You have transferred amount of " << amount << " to the account " << accNum << endl;
		}
		else {
			cout << "This acount does not exist" << endl;
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
}
void btnIntializer(button btn[], int arrSize) {
	string btnstring[4] = { "add employees","manage accounts","freeze","unfreeze" };
	for (int i = 0; i < arrSize; i++) {
		btn[i].btnSprite.setTexture(smallButtonTexture);
		btn[i].btnText.setFont(rockebFont);
		btn[i].btnText.setFillColor(Color::White);
		btn[i].btnSprite.setPosition(1300, 260 + ((i) * 105));
		btn[i].btnSprite.setScale(1.3, 1.15);
		btn[i].btnText.setString(btnstring[i]);
	}
	for (int i = 0; i < arrSize; i++) {
		btn[i+2].btnSprite.setTexture(smallButtonTexture);
		btn[i+2].btnText.setFont(rockebFont);
		btn[i+2].btnText.setFillColor(Color::White);
		btn[i+2].btnSprite.setPosition(1000 + ((i) * 400), 520);
		btn[i+2].btnSprite.setScale(1.1, 1.1);
		btn[i+2].btnText.setString(btnstring[i+2]);
	}
	btn[0].btnText.setPosition(1390, 280);
	btn[1].btnText.setPosition(1370, 390);
	btn[2].btnText.setPosition(1100, 550);
	btn[3].btnText.setPosition(1500, 550);
}
void searchButtonInitializer(button& btn,string str) {
	btn.btnSprite.setTexture(smallButtonTexture);
	btn.btnText.setFont(rockebFont);
	btn.btnText.setFillColor(Color::White);
	btn.btnSprite.setPosition(80 , 520);
	btn.btnSprite.setScale(1.1, 1.1);
	btn.searchSprite.setTexture(searchTexture);
	btn.searchSprite.setPosition(350, 540);
	btn.btnText.setString(str);
	btn.btnText.setPosition(150, 540);
}
void searchButtonDrawer(button btn) {

	window.draw(btn.btnSprite);
	window.draw(btn.searchSprite);
	window.draw(btn.btnText);
	
}
void viewbackgroundIntializer(viewBackground viewer[], int arrSize) {
	for (int i = 0; i < arrSize; i++) {
		viewer[i].veiwSprite.setTexture(viewBackgroundTexture);
		viewer[i].viewText.setFont(rockebFont);
		viewer[i].viewText.setFillColor(Color::White);
		viewer[i].veiwSprite.setPosition(70, 650 + ((i) * 115));
		viewer[i].veiwSprite.setScale(1.16, 1.07);
	}
	viewer[0].viewText.setPosition(0, 525);
	viewer[1].viewText.setPosition(0, 643);
	viewer[2].viewText.setPosition(0, 760);
	viewer[3].viewText.setPosition(0, 875);
}
void setButton(button& btn) {
	String textArr[4] = { "Transfer Balance","Withdraw","Last Transactions","Ask for a Loan" };
	btn.btnSprite.setTexture(bigButtonTexture);
	btn.btnSprite.setPosition(1000, 530);
	btn.btnSprite.setScale(1.1, 1.1);
	btn.btnText.setFont(rockebFont);
	btn.btnText.setFillColor(Color::White);
	btn.btnText.setPosition(1100, 555);
	btn.btnText.setString(textArr[0]);
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
void adminPanelIntializer(balancePanel panel[]) {
	string str[] = { "users","empoloyees" };
	panel[0].panel.setTexture(darkBackgroundSmallTexture);
	panel[0].panel.setPosition(60, 250);
	panel[0].panel.setScale(1.16, 1.07);
	for (int i = 0; i < 2; i++) {

		panel[i].balnceText.setFont(rockebFont);
		panel[i].balnceText.setString(str[i]);
		panel[i].balnceText.setCharacterSize(80);
		panel[i].balnceText.setFillColor(Color::White);
		panel[i].balnceText.setPosition(150+ (i * 300), 260);
		panel[i].amountText.setFont(rockebFont);
		panel[i].amountText.setString("0");
		panel[i].amountText.setCharacterSize(60);
		panel[i].amountText.setFillColor(Color::White);
		panel[i].amountText.setPosition(170 + (i * 300), 350);
	}
}
void adminPanelDrawer(balancePanel panel[]) {
	window.draw(panel[0].panel);
	for (int i = 0; i < 2; i++) {
		window.draw(panel[i].balnceText);
		window.draw(panel[i].amountText);
	}
}
void setHeader(Header& header) {
	String textArr[3] = { "Morning Mr, ", "Loser","Haitham Bank" };
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
void viewBackgroundDrawer(viewBackground view[], int arrSize)
{
	for (int i = 0; i < arrSize; i++) {

		window.draw(view[i].veiwSprite);
		window.draw(view[i].viewText);

	}
}
void balancePanelDrawer(balancePanel& panel)
{
	window.draw(panel.panel);
	window.draw(panel.balnceText);
	window.draw(panel.amountText);
}
void drawBigBox(bigDarkBox bigDarkbox, button btn) {
	window.draw(bigDarkbox.background);
	window.draw(btn.btnSprite);
	window.draw(btn.btnText);
	window.draw(bigDarkbox.valueField1);
	window.draw(bigDarkbox.valueField2);
	window.draw(bigDarkbox.amountTxt);
	window.draw(bigDarkbox.Totxt);
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

void darkBoxBiginitializer(viewBackground& darkbox) {
	darkbox.veiwSprite.setTexture(darkBackgroundBigTexture);
	darkbox.veiwSprite.setPosition(60,500);
	darkbox.veiwSprite.setScale(1.16, 1.07);
}
void darkBoxBigDrawer(viewBackground darkbox) {
	window.draw(darkbox.veiwSprite);
}
#pragma once

#include<iostream>
#include "Entities.h"
#include "FileServices.h"
using namespace std;

int card_count = 4;

Card** cards = new Card * [card_count] {
	new Card{ new char[30]{"4169785895581221"},new char[5]{"1111"},
	new char[50]{"Tural Eliyev"},1000,NULL,NULL },

		new Card{ new char[30]{"4169885744996353"},new char[5]{"2222"},
		new char[50]{"Nergiz Quliyeva"},550,NULL,NULL },

		new Card{ new char[30]{"4169475788996121"},new char[5]{"3333"},
		new char[50]{"Arif Mammadov"},742,NULL,NULL },

		new Card{ new char[30]{"4169748585963223"},new char[5]{"4444"},
		new char[50]{"Eli Eliyev"},11254,NULL,NULL }
};

void ShowTransaction(Transaction* transaction) {
	cout << "<===================>" << endl;
	cout << "Info : " << transaction->info << endl;
	cout << "Date : " << transaction->date << endl;
}
void ShowCard(Card* card) {
	cout << "    <<CARD INFO>>    " << endl;
	cout << "Person : " << card->person << endl;
	cout << "PAN : " << card->pan << endl;
	cout << "PIN";
	for (size_t i = 0; i < strlen(card->pin); i++)
	{
		cout << "*";
	}cout << endl;
	cout << "Balance : " << card->balance << "$" << endl;
	for (size_t i = 0; i < card->count; i++)
	{
		ShowTransaction(card->transactions[i]);
	}
}

#include<fstream>
#include<Windows.h>

bool FileExist(const char* filename) {
	ifstream infile(filename);
	return infile.good();
}

Card** result = nullptr;
int total_count = 0;

Card* GetCard(const char* pan, const char* pin) {
	for (size_t i = 0; i < total_count; i++)
	{
		if (strcmp(result[i]->pan, pan) == 0 && strcmp(result[i]->pin, pin) == 0) {
			return result[i];
		}
	}
	return nullptr;
}
Card* GetCardByPAN(const char* pan) {
	for (size_t i = 0; i < total_count; i++)
	{
		if (strcmp(result[i]->pan, pan) == 0) {
			return result[i];
		}
	}
	return nullptr;
}

void ShowMenu() {
	cout << "Show Balance [1]" << endl;
	cout << "Get Cash     [2]" << endl;
	cout << "Card To Card [3]" << endl;
	cout << "Show History [4]" << endl;
	cout << "Exit         [0]" << endl;
}

void ShowCashMenu()
{
	cout << "Select money type " << endl;
	cout << "10$    [1]" << endl;
	cout << "20$    [2]" << endl;
	cout << "50$    [3]" << endl;
	cout << "100$   [4]" << endl;
	cout << "Other  [5]" << endl;
}
void Start() {
	if (!FileExist("cards.bin")) {
		WriteFile(cards, card_count);
	}

	/*for (size_t i = 0; i < total_count; i++)
	{
		ShowCard(result_cards[i]);
	}*/
	while (true)
	{
	    result = ReadFile(total_count);

		cout << "Enter card PAN(16 number characters)" << endl;
		char* pan = new char[20]{};
		cin.getline(pan, 20);
		cout << "Enter card PIN(4 number characters)" << endl;
		char* pin = new char[20]{};
		cin.getline(pin, 20);
		auto card = GetCard(pan, pin);
		system("cls");
		if (card == nullptr) {
			cout << "WRONG" << endl;
			continue;
		}
		while (true)
		{
			cout << "Welcome " << card->person << endl;
			Sleep(2000);
			system("cls");
			ShowMenu();
			int select = 0;
			cin >> select;
			Sleep(1000);
			if (select == 1) {
				cout << "Your Balance : " << card->balance << "$" << endl;
			}
			else if (select == 2) {
				system("cls");
				ShowCashMenu();
				int choice = 0;
				cin >> choice;

				double cash = 0;
				if (choice == 1) {
					cash = 10;
				}
				else if (choice == 2) {
					cash = 20;
				}
				else if (choice == 3) {
					cash = 50;
				}
				else if(choice==4){
					cash = 100;
				}
				else if (choice == 5) {
					cout << "Enter Money : " << endl;
					cin >> cash;
				}
				if (cash <= card->balance) {
					card->balance -= cash;
					cout << "You get money successfully" << endl;
					Sleep(1000);
			        WriteFile(result, card_count);
				}
				else {
					cout << "You do not have enough money" << endl;
				}
			}
			else if (select == 3) {
				cin.ignore();
				cin.clear();
				cout << "Receiver Card PAN : " << endl;
				char* pan = new char[20]{};
				cin.getline(pan, 20);

				auto receiverCard = GetCardByPAN(pan);
				if (receiverCard == nullptr) {
					cout << "Wrong Card" << endl;
					Sleep(1500);
					break;
				}
				else {
					cout << "Enter money" << endl;
					double money = 0;
					cin >> money;
					if (money <= card->balance) {
						card->balance -= money;
						receiverCard->balance += money;
					}
					else {
						cout << "You do not have enought money" << endl;
					}
				}

				WriteFile(result, card_count);
			}
			else if (select == 0) {
				system("cls");
				cin.ignore();
				cin.clear();
				break;
			}
			system("pause");
			
		}
	}
}

//Add TransactionToCard
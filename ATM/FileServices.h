#pragma once
#include<iostream>
using namespace std;
#include"Entities.h"
// card_count
//pan
//pin
//person
//balance
//count
  //info
  //date
void WriteFile(Card** cards, int& count) {
	FILE* file;
	fopen_s(&file, "cards.bin", "wb");
	fwrite(&count, sizeof(int), 1, file);
	for (size_t i = 0; i < count; i++)
	{
		//for every card item
		int l1 = strlen(cards[i]->pan);
		fwrite(&l1, sizeof(int), 1, file);
		fwrite(cards[i]->pan, sizeof(char), l1, file);

		int l2 = strlen(cards[i]->pin);
		fwrite(&l2, sizeof(int), 1, file);
		fwrite(cards[i]->pin, sizeof(char), l2, file);

		int l3 = strlen(cards[i]->person);
		fwrite(&l3, sizeof(int), 1, file);
		fwrite(cards[i]->person, sizeof(char), l3, file);

		fwrite(&cards[i]->balance, sizeof(double), 1, file);

		fwrite(&cards[i]->count, sizeof(int), 1, file);
		for (size_t k = 0; k < cards[i]->count; k++)
		{
			int len1 = strlen(cards[i]->transactions[k]->info);
			fwrite(&len1, sizeof(int), 1, file);
			fwrite(cards[i]->transactions[k]->info, sizeof(char), len1, file);

			int len2 = strlen(cards[i]->transactions[k]->date);
			fwrite(&len2, sizeof(int), 1, file);
			fwrite(cards[i]->transactions[k]->date, sizeof(char), len2, file);
		}
	}
	fclose(file);
}

Card** ReadFile(int& totalcount) {
	FILE* file;
	fopen_s(&file, "cards.bin", "rb");

	fread_s(&totalcount, sizeof(int), sizeof(int), 1, file);
	Card** cards = new Card*[totalcount]{};

	for (size_t i = 0; i < totalcount; i++)
	{
		int l1 = 0;
		fread_s(&l1, sizeof(int), sizeof(int), 1, file);
		char* pan = new char[l1 + 1]{};
		fread_s(pan, l1, sizeof(char), l1, file);

		int l2 = 0;
		fread_s(&l2, sizeof(int), sizeof(int), 1, file);
		char* pin = new char[l2 + 1]{};
		fread_s(pin, l2, sizeof(char), l2, file);

		int l3 = 0;
		fread_s(&l3, sizeof(int), sizeof(int), 1, file);
		char* person = new char[l3 + 1]{};
		fread_s(person, l3, sizeof(char), l3, file);

		double balance = 0;
		fread_s(&balance, sizeof(double), sizeof(double), 1, file);

		int t_count = 0;
		fread_s(&t_count, sizeof(int), sizeof(int), 1, file);

		Transaction** transactions = new Transaction * [t_count] {};
		for (size_t i = 0; i < t_count; i++)
		{
			int len1 = 0;
			fread_s(&len1, sizeof(int), sizeof(int), 1, file);
			char* info = new char[len1 + 1]{};
			fread_s(info, len1, sizeof(char), len1, file);

			int len2 = 0;
			fread_s(&len2, sizeof(int), sizeof(int), 1, file);
			char* date = new char[len2 + 1]{};
			fread_s(date, len2, sizeof(char), len2, file);
			transactions[i] = new Transaction{ info,date };
		}

		cards[i] = new Card{ pan,pin,person,balance,t_count,transactions };
	}
	fclose(file);
	return cards;
}
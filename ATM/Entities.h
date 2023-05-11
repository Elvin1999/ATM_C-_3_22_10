#pragma once

struct Transaction {
	char* info;
	const char* date = __DATE__;
};

struct Card {
	char* pan;
	char* pin;
	char* person;
	double balance;
	int count = 0;
	Transaction** transactions;
};

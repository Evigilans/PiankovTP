#pragma once
#include <stdio.h>
#include <stdlib.h>

const int ADMIN = 1;
const int OPERATOR = 2;

void clearScreen() {
}

void printMenu() {
	printf("\n\n\n\n\n============================== MAIN MENU: ==============================\n");
}

void printMenuOptions(const int args, const char** argv) {
	for (int i = 0; i < args; i++) {
		printf("%d.%s\n", i + 1, argv[i]);
	}
}

void exitMenu(int *numb) {
	*numb = 1;
}
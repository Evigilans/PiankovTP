#pragma once
#include <stdio.h>
#include "operator.h"
#include "admin.h"
#include "utils.h"

void mainMenu(int role) {
	switch (role) {
	case 1:
		adminMenu();
        break;
	case 2:
        operatorMenu();
        break;
	default:
		break;
	}
}

void adminMenu() {
    do {
        char answer[2];

        clearScreen();
        printMenu();
        printMenuOptions(adminFunctionsCount, adminFunctions);

        scanf("%s", answer);

        switch (answer[0]) {
            case '1':
                addClient();
                break;
            case '2':
                deleteClient();
                break;
            case '3':
                addAccount();
                break;
            case '4':
                deleteAccount();
                break;
            case '5':
                withdrawMoney();
                break;
            case '6':
                changeAccountType();
                break;
            case '7':
                exitMenu(&adminIsExit);
                break;
        }

    } while (!adminIsExit);
}

void operatorMenu() {
	do {
        char answer[2];

        clearScreen();
		printMenu();
		printMenuOptions(operatorFunctionsCount, operatorFunctions);

        scanf("%s", answer);

		switch (answer[0]) {
		case '1':
			addMoney();
			break;
		case '2':
			transfer();
			break;
		case '3':
			exitMenu(&operatIsExit);
			break;
		}

	} while (!operatIsExit);
}
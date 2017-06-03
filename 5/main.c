#include "authorization.h"
#include "menu.h"

int main() {
	int role = 0;
	do {
		role = authorization();
		if (!role) {
            clearScreen();
			invalidAuthorization();
		}
	} while (role == 0);

	mainMenu(role);
	return 0;
}
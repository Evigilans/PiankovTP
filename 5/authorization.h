#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

char buffLogin[100];
const char* roles[] = {"Admin", "Operator"};

int enterApp() {
    int successfulEnter = 0;
    const char* login = (const char*)calloc(100, sizeof(char));
    char password[100];
    sqlite3 *db;
    int rc = sqlite3_open("Bank.bd", &db);
    char *err_msg = 0;
    sqlite3_stmt *res;

    printf("-----------------------------AUTHORIZATION-----------------------------\n");
    printf("LOGIN: ");
    scanf("%s", login);
    printf("PASSWORD: ");
    scanf("%s", password);

    char *sql = "SELECT Password FROM bankusers WHERE Name = @name";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int idx = sqlite3_bind_parameter_index(res, "@name");
        sqlite3_bind_text(res, idx, login, -1, SQLITE_STATIC);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW) {
        if (strcmp(sqlite3_column_text(res, 0), password) == 0) {
            printf("Succecfull login!\n");
            strcpy(buffLogin, login);
            successfulEnter = 1;
        }
    }

    sqlite3_finalize(res);
    sqlite3_close(db);
    free(login);

    return successfulEnter;
}

int getRole() {
    sqlite3 *db;
    int rc = sqlite3_open("Bank.bd", &db);
    char *err_msg = 0;
    sqlite3_stmt *res;

    char *sql = "SELECT Role FROM bankusers WHERE Name = @name";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int idx = sqlite3_bind_parameter_index(res, "@name");
        sqlite3_bind_text(res, idx, buffLogin, -1, SQLITE_STATIC);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW) {
        for (int i = 0; i < 2; i++) {
            if (strcmp(sqlite3_column_text(res, 0), roles[i]) == 0) {
                printf("Your role: %s\n", roles[i]);
                sqlite3_finalize(res);
                sqlite3_close(db);
                return (i + 1);
            }
        }
    }

    return 0;
}

void invalidAuthorization() {
	printf("Invalid login or password! Check login and password and try again.\n");
}

int authorization() {
    int role = 0;
    if (enterApp() == 1) {
        role = getRole();
    }
    return role;
}
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

const char* operatorFunctions[] = {"Add money on a card.", "Transfer money between accounts.", "Exit"};
const int operatorFunctionsCount = 3;

int operatIsExit = 0;

void setMoney(int ID, int money) {
    sqlite3 *db;
    int rc = sqlite3_open("Bank.bd", &db);
    char *err_msg = 0;
    sqlite3_stmt *res;

    char *sql = "UPDATE bankaccounts SET Balance = @balance WHERE AccountID = @id";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int idx1 = sqlite3_bind_parameter_index(res, "@balance");
        sqlite3_bind_int(res, idx1, money);
        int idx2 = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_int(res, idx2, ID);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    sqlite3_finalize(res);
    sqlite3_close(db);
}

int countAccounts(int userID) {
    sqlite3 *db;
    int rc = sqlite3_open("Bank.bd", &db);
    char *err_msg = 0;
    sqlite3_stmt *res;

    char *sql = "SELECT count(*) AS \"accounts\" FROM bankaccounts WHERE OwnerID = @id";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int idx = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_int(res, idx, userID);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    int accs = sqlite3_column_int(res, 0);

    sqlite3_finalize(res);
    sqlite3_close(db);

    return accs;
}

int getCurrentBalance(int ID) {
    sqlite3 *db;
    int rc = sqlite3_open("Bank.bd", &db);
    char *err_msg = 0;
    sqlite3_stmt *res;

    char *sql = "SELECT Balance FROM bankaccounts WHERE AccountID = @id";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int idx = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_int(res, idx, ID);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    int balance = sqlite3_column_int(res, 0);

    sqlite3_finalize(res);
    sqlite3_close(db);

    return balance;
}

void addMoney() {
    int ID;
    int money;

    printf("Enter account ID to transfer money: ");
    scanf("%d", &ID);
    printf("Enter sum for transfer: ");
    scanf("%d", &money);
    money += getCurrentBalance(ID);

    sqlite3 *db;
    int rc = sqlite3_open("Bank.bd", &db);
    char *err_msg = 0;
    sqlite3_stmt *res;

    char *sql = "UPDATE bankaccounts SET Balance = @balance WHERE AccountID = @id";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int idx1 = sqlite3_bind_parameter_index(res, "@balance");
        sqlite3_bind_int(res, idx1, money);
        int idx2 = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_int(res, idx2, ID);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_DONE) {
        printf("Money transferred successful!\n");
    } else {
        printf("Operation error!\n");
    }

    sqlite3_finalize(res);
    sqlite3_close(db);
}

void transfer() {
    int ID;
    int accounts;
    int accSource, accDestination;
    int sum;
    int maxMoney;

    printf("Enter user ID to transfer money between accounts: ");
    scanf("%d", &ID);
    accounts = countAccounts(ID);

    if (accounts == 0) {
        printf("This user has no accounts in bank!\n");
        return;
    } if (accounts == 1) {
        printf("This user has only one account in bank!\n");
        return;
    }

    printf("Enter source account ID to transfer money from: ");
    scanf("%d", &accSource);
    printf("Enter destination account ID to transfer money to: ");
    scanf("%d", &accDestination);
    printf("Enter money to transfer: ");
    scanf("%d", &sum);

    maxMoney = getCurrentBalance(accSource);
    if (sum > maxMoney) {
        printf("Entered sum is too big!\n");
        return;
    }
    setMoney(accSource, getCurrentBalance(accSource) - sum);
    setMoney(accDestination, getCurrentBalance(accDestination) + sum);
    printf("Money transfered successfully!\n");
}


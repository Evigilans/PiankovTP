#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

const char* types[] = {"checking", "savings"};
const char* adminFunctions[] = {"Add client", "Delete Client", "Add account for client", "Delete client account", "Withdraw money from the account.", "Change account type", "Exit"};
const int adminFunctionsCount = 7;
int adminIsExit = 0;

void deleteClientAccounts(int ID) {
    sqlite3 *db;
    int rc = sqlite3_open("Bank.bd", &db);
    char *err_msg = 0;
    sqlite3_stmt *res;

    char *sql = "DELETE FROM bankaccounts WHERE OwnerID = @id";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int idx = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_int(res, idx, ID);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_step(res);
    sqlite3_finalize(res);
    sqlite3_close(db);
}

void sayGoodBye(int ID) {
    char name[100];
    sqlite3 *db;
    int rc = sqlite3_open("Bank.bd", &db);
    char *err_msg = 0;
    sqlite3_stmt *res;

    char *sql = "SELECT Name FROM bankclients WHERE ClientID = @id";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int idx = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_int(res, idx, ID);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_step(res);
    printf("Good bye, %s!\n", sqlite3_column_text(res, 0));
    sqlite3_finalize(res);
    sqlite3_close(db);
}

void addClient() {
    const char* name = (const char*)calloc(100, sizeof(char));
    sqlite3 *db;
    int rc = sqlite3_open("Bank.bd", &db);
    char *err_msg = 0;
    sqlite3_stmt *res;

    printf("Enter name of new client: ");
    scanf("%s", name);

    char *sql = "INSERT INTO bankclients (Name, HasOverdraft) VALUES (@name, 0)";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int idx = sqlite3_bind_parameter_index(res, "@name");
        sqlite3_bind_text(res, idx, name, -1, SQLITE_STATIC);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    printf("Thank you for choosing our bank, %s!\n", name);

    sqlite3_finalize(res);
    sqlite3_close(db);
    free(name);
}

void deleteClient() {
    int ID;
    char name[100];
    sqlite3 *db;
    int rc = sqlite3_open("Bank.bd", &db);
    char *err_msg = 0;
    sqlite3_stmt *res;

    printf("Enter ID of client to delete: ");
    scanf("%d", &ID);

    sayGoodBye(ID);
    deleteClientAccounts(ID);

    char *sql = "DELETE FROM bankclients WHERE ClientID = @id";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int idx = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_int(res, idx, ID);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_step(res);

    sqlite3_finalize(res);
    sqlite3_close(db);
}

void addAccount() {
    int ID;
    int type;
    sqlite3 *db;
    int rc = sqlite3_open("Bank.bd", &db);
    char *err_msg = 0;
    sqlite3_stmt *res;

    printf("Enter cient ID to create account: ");
    scanf("%d", &ID);
    printf("Enter type of account: ");
    scanf("%d", &type);

    char *sql = "INSERT INTO bankaccounts (OwnerID, Type, Balance, Overdrafted, DaysOfOverdraft) VALUES (@id, @type, 0, 0, 0)";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int idx1 = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_int(res, idx1, ID);
        int idx2 = sqlite3_bind_parameter_index(res, "@type");
        sqlite3_bind_int(res, idx2, type);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    printf("Account created successfully!\n");

    int step = sqlite3_step(res);

    sqlite3_finalize(res);
    sqlite3_close(db);
}

void deleteAccount() {
    int ID;
    char name[100];
    sqlite3 *db;
    int rc = sqlite3_open("Bank.bd", &db);
    char *err_msg = 0;
    sqlite3_stmt *res;

    printf("Enter ID of account to delete: ");
    scanf("%d", &ID);

    char *sql = "DELETE FROM bankaccounts WHERE AccountID = @id";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int idx = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_int(res, idx, ID);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    printf("Account deleted successfully!\n");

    sqlite3_step(res);

    sqlite3_finalize(res);
    sqlite3_close(db);
}

void withdrawMoney()
{
    sqlite3 *db;
    int rc = sqlite3_open("Bank.bd", &db);
    sqlite3_stmt *res;

    char name[100];
    printf("Enter the name of client:\n");
    scanf("%s", name);

    char* sql = "SELECT bankaccounts.AccountID, bankaccounts.Type, bankaccounts.Balance, HasOverdraft, bankaccounts.Overdrafted, bankaccounts.DaysOfOverdraft FROM bankclients INNER JOIN bankaccounts ON bankclients.ClientID = bankaccounts.OwnerID WHERE Name = @name";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc == SQLITE_OK)
    {
        int idx = sqlite3_bind_parameter_index(res, "@name");
        sqlite3_bind_text(res, idx, name, -1, SQLITE_STATIC);
    }

    int step = sqlite3_step(res);
    printf("%d\n", step);
    if (sqlite3_step(res) == SQLITE_ROW)
    {
        printf("Select account ID to withdraw:\n");
        do
        {
            int type = sqlite3_column_int(res, 1);
            int balance = sqlite3_column_int(res, 2);
            int over = sqlite3_column_int(res, 3);
            int overBalance = sqlite3_column_int(res, 4);
            int days = sqlite3_column_int(res, 5);

            if (type && over && overBalance > 200 && days > 30)
            {
                continue;
            }

            printf("\t%d %s account with %d$ balance\n", sqlite3_column_int(res, 0), types[type], balance);
            if (type)
            {
                printf(" with");
                if (!over)
                {
                    printf("out");
                }
                printf(" overdraft");
                if(over)
                {
                    printf(" %d$", overBalance);
                    printf(" over %d days", days);
                }
                printf(";\n");
            }
        }while (sqlite3_step(res) == SQLITE_ROW);

        int ID;
        scanf("%d", &ID);

        sql = "SELECT bankaccounts.Type, bankaccounts.Balance, HasOverdraft, bankaccounts.Overdrafted, ClientID FROM bankclients INNER JOIN bankaccounts ON bankclients.ClientID = bankaccounts.OwnerID WHERE Name = @name AND bankaccounts.AccountID = @id";
        rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
        if (rc == SQLITE_OK)

        {
            int idx = sqlite3_bind_parameter_index(res, "@id");
            sqlite3_bind_int(res, idx, ID);
            idx = sqlite3_bind_parameter_index(res, "@name");
            sqlite3_bind_text(res, idx, name, -1, SQLITE_STATIC);
        }

        if (sqlite3_step(res) == SQLITE_ROW)
        {
            printf("Enter the summ to withdraw:\n");
            int summ;
            scanf("%d", &summ);

            int type = sqlite3_column_int(res, 0);
            int balance = sqlite3_column_int(res, 1);
            int hasOver = sqlite3_column_int(res, 2);
            int over = 0;
            if(hasOver)
            {
                over = sqlite3_column_int(res, 3);
            }

            if ((type && balance < summ && (200 - over) < (summ - balance)) || (!type && balance < summ))
            {
                printf("Can't to withdraw so much!\n");
            }
            else
            {
                int isChanged = 0;
                if(type && balance < summ)
                {
                    if (!hasOver)
                    {
                        isChanged = 1;
                        hasOver = 1;
                    }
                    over = 200 + balance - summ;
                    balance = 0;
                }
                else
                {
                    balance -= summ;
                }

                if (isChanged)
                {
                    int owner = over = sqlite3_column_int(res, 4);
                    sql = "UPDATE bankclients SET HasOverdraft = 1 WHERE ClientID = @id";
                    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
                    if (rc == SQLITE_OK)
                    {
                        int idx = sqlite3_bind_parameter_index(res, "@id");
                        sqlite3_bind_int(res, idx, owner);
                    }
                    sqlite3_step(res);

                    sql = "UPDATE bankaccounts SET Overdraft = @over, DaysOfOverdraft = 0 WHERE AccountID = @id";
                    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
                    if (rc == SQLITE_OK)
                    {
                        int idx = sqlite3_bind_parameter_index(res, "@over");
                        sqlite3_bind_int(res, idx, over);
                        idx = sqlite3_bind_parameter_index(res, "@id");
                        sqlite3_bind_int(res, idx, ID);
                    }
                    sqlite3_step(res);
                }

                sql = "UPDATE bankaccounts SET Balance = @balance WHERE AccountID = @id";
                rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
                if (rc == SQLITE_OK)
                {
                    int idx = sqlite3_bind_parameter_index(res, "@balance");
                    sqlite3_bind_int(res, idx, balance);
                    idx = sqlite3_bind_parameter_index(res, "@id");
                    sqlite3_bind_int(res, idx, ID);
                }
                sqlite3_step(res);
            }
        }
        else
        {
            printf("Invalid account ID!\n");
        }
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
}

void changeAccountType() {
    int ID;
    int type;
    sqlite3 *db;
    int rc = sqlite3_open("Bank.bd", &db);
    char *err_msg = 0;
    sqlite3_stmt *res;

    printf("Enter account ID to change type: ");
    scanf("%d", &ID);
    printf("Enter new type of account: ");
    scanf("%d", &type);

    char *sql = "UPDATE bankaccounts SET Type = @type WHERE AccountID = @id";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int idx1 = sqlite3_bind_parameter_index(res, "@type");
        sqlite3_bind_int(res, idx1, type);
        int idx2 = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_int(res, idx2, ID);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }


    int step = sqlite3_step(res);
    printf("Account type changed successfully!\n");

    sqlite3_finalize(res);
    sqlite3_close(db);
}
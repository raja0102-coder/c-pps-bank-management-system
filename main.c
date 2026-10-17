#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILENAME "bank_accounts.txt"

typedef struct {
    int accNo;
    char name[50];
    float balance;
} Account;

void createAccount();
void viewAccount();
void depositMoney();
void withdrawMoney();

int main() {
    int choice;

    while (1) {
        printf("\n==================================================\n");
        printf("      BANK ACCOUNT MANAGEMENT SYSTEM              \n");
        printf("==================================================\n");
        printf("  1. Create New Bank Account\n");
        printf("  2. Check Balance & Details\n");
        printf("  3. Deposit Funds\n");
        printf("  4. Withdraw Funds\n");
        printf("  5. Exit & Save\n");
        printf("==================================================\n");
        printf("Enter your choice (1-5): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("[ERROR] Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                viewAccount();
                break;
            case 3:
                depositMoney();
                break;
            case 4:
                withdrawMoney();
                break;
            case 5:
                printf("\n[SAVED] Exiting program. Account records saved to '%s'.\n", FILENAME);
                return 0;
            default:
                printf("\n[ERROR] Invalid option! Please choose between 1 and 5.\n");
        }
    }

    return 0;
}

// 1. Create New Account
void createAccount() {
    FILE *fp = fopen(FILENAME, "a");
    if (fp == NULL) {
        printf("    [ERROR] Could not open database file!\n");
        return;
    }

    Account acc;
    printf("\n--- CREATE BANK ACCOUNT ---\n");
    printf("    Enter Account Number : ");
    scanf("%d", &acc.accNo);
    printf("    Enter Holder Name    : ");
    scanf("%s", acc.name);
    printf("    Initial Deposit (Rs) : ");
    scanf("%f", &acc.balance);

    fprintf(fp, "%d %s %.2f\n", acc.accNo, acc.name, acc.balance);
    fclose(fp);
    printf("    [SUCCESS] Bank account created successfully!\n");
}

// 2. View Account Details & Balance
void viewAccount() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("\n    [INFO] No accounts database found.\n");
        return;
    }

    int targetAcc;
    printf("\n--- ACCOUNT INQUIRY ---\n");
    printf("    Enter Account Number : ");
    scanf("%d", &targetAcc);

    Account acc;
    bool found = false;

    while (fscanf(fp, "%d %s %f", &acc.accNo, acc.name, &acc.balance) != EOF) {
        if (acc.accNo == targetAcc) {
            printf("\n    [FOUND] Account Summary:\n");
            printf("    Account Number : %d\n", acc.accNo);
            printf("    Holder Name    : %s\n", acc.name);
            printf("    Current Balance: Rs. %.2f\n", acc.balance);
            found = true;
            break;
        }
    }

    if (!found) {
        printf("\n    [NOT FOUND] Account %d does not exist.\n", targetAcc);
    }

    fclose(fp);
}

// 3. Deposit Money
void depositMoney() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("\n    [INFO] No accounts database found.\n");
        return;
    }

    int targetAcc;
    float amount;
    printf("\n--- DEPOSIT FUNDS ---\n");
    printf("    Enter Account Number : ");
    scanf("%d", &targetAcc);
    printf("    Enter Amount to Add  : ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("    [ERROR] Invalid deposit amount.\n");
        fclose(fp);
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("    [ERROR] Temporary file error!\n");
        fclose(fp);
        return;
    }

    Account acc;
    bool found = false;

    while (fscanf(fp, "%d %s %f", &acc.accNo, acc.name, &acc.balance) != EOF) {
        if (acc.accNo == targetAcc) {
            acc.balance += amount;
            found = true;
            printf("    [SUCCESS] Deposited Rs. %.2f. New Balance: Rs. %.2f\n", amount, acc.balance);
        }
        fprintf(temp, "%d %s %.2f\n", acc.accNo, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (!found) {
        printf("    [NOT FOUND] Account %d not found.\n", targetAcc);
    }
}

// 4. Withdraw Money
void withdrawMoney() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("\n    [INFO] No accounts database found.\n");
        return;
    }

    int targetAcc;
    float amount;
    printf("\n--- WITHDRAW FUNDS ---\n");
    printf("    Enter Account Number : ");
    scanf("%d", &targetAcc);
    printf("    Enter Amount to Deduct: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("    [ERROR] Invalid withdrawal amount.\n");
        fclose(fp);
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("    [ERROR] Temporary file error!\n");
        fclose(fp);
        return;
    }

    Account acc;
    bool found = false;

    while (fscanf(fp, "%d %s %f", &acc.accNo, acc.name, &acc.balance) != EOF) {
        if (acc.accNo == targetAcc) {
            found = true;
            if (acc.balance >= amount) {
                acc.balance -= amount;
                printf("    [SUCCESS] Withdrew Rs. %.2f. New Balance: Rs. %.2f\n", amount, acc.balance);
            } else {
                printf("    [ERROR] Insufficient balance! Current Balance: Rs. %.2f\n", acc.balance);
            }
        }
        fprintf(temp, "%d %s %.2f\n", acc.accNo, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (!found) {
        printf("    [NOT FOUND] Account %d not found.\n", targetAcc);
    }
}

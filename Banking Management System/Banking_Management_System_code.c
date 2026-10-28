#include <stdio.h>
#include <string.h>
#include <ctype.h>
struct user
{
    char name[20];
    int account_no;
    int pin;
    char gender;
    float balance;
};
void CreateAccount()
{
    FILE *ptr = NULL;
    struct user acc;
    ptr = fopen("account.dat", "ab");
    if (ptr == NULL)
    {
        printf("file not exsit");
        return;
    }
    printf("Enter your name:");
    scanf("%s", acc.name);
    for (int i = 0; acc.name[i] != '\0'; i++)
    {
        if (!isalpha(acc.name[i]))
        {
            printf("Enter name in alphabet:");
            fclose(ptr);
            return;
        }
    }
    printf("Enter your account number:");
    if (scanf("%d", &acc.account_no) != 1)
    {
        printf("please enter only numbers");
        fclose(ptr);
        return;
    }
    if (acc.account_no < 10000000 || acc.account_no > 99999999)
    {
        printf("Please enter exactly 8 digits account number\n");
        fclose(ptr);
        return;
    }
    printf("Enter your gender M,F,O:");
    scanf(" %c", &acc.gender);
    if (acc.gender != 'M' &&
        acc.gender != 'F' &&
        acc.gender != 'O' &&
        acc.gender != 'm' &&
        acc.gender != 'f' &&
        acc.gender != 'o')
    {
        printf("Enter only M, F or O\n");
        fclose(ptr);
        return;
    }

    printf("Enter your balance:");
    if (scanf("%f", &acc.balance) != 1)
    {
        printf("Support only digit");
        fclose(ptr);
        return;
    }
    if (acc.balance < 0)
    {
        printf("Balance cannot be negative\n");
        fclose(ptr);
        return;
    }
    printf("Enter your 4 digit pin:");
    if (scanf("%d", &acc.pin) != 1)
    {
        printf("please enter only numbers");
        fclose(ptr);
        return;
    }
    if (acc.pin < 1000 || acc.pin > 9999)
    {
        printf("please enter only for digit");
        fclose(ptr);
        return;
    }
    FILE *check;
    struct user temp;

    check = fopen("account.dat", "rb");

    if (check != NULL)
    {
        while (fread(&temp, sizeof(temp), 1, check))
        {
            if (temp.account_no == acc.account_no)
            {
                printf("Account Number Already Exists\n");

                fclose(check);
                fclose(ptr);

                return;
            }
        }

        fclose(check);
    }

    fwrite(&acc, sizeof(acc), 1, ptr);
    fclose(ptr);
    printf("Account created successfully\n");
}

void viewAccount()
{
    FILE *ptr = NULL;
    int account_no;
    int pin;
    int found = 0;
    struct user acc;
    ptr = fopen("account.dat", "rb");
    if (ptr == NULL)
    {
        printf("file does not exsit");
        return;
    }
    printf("Enter your Account number:");
    if (scanf("%d", &account_no) != 1)
    {
        printf("Please enter only digit");
        fclose(ptr);
        return;
    }
    printf("Enter your pin:");

    if (scanf("%d", &pin) != 1)
    {
        printf("Please enter only 4 digit number\n");
        fclose(ptr);
        return;
    }

    if (pin < 1000 || pin > 9999)
    {
        printf("PIN must be exactly 4 digits\n");
        fclose(ptr);
        return;
    }
    while (fread(&acc, sizeof(acc), 1, ptr))
    {
        if (acc.account_no == account_no && acc.pin == pin)
        {
            printf("Your Name is %s\n", acc.name);
            printf("Your Account number is %d\n", acc.account_no);
            printf("Your Gender %c\n", acc.gender);
            printf("Your Balance %f\n", acc.balance);
            found = 1;
            break;
        }
    }
    fclose(ptr);
    if (found == 0)
    {
        printf("Account not found\n");
    }
}
void DepositMoney()
{
    FILE *ptr = NULL;
    int account_no;
    int pin;
    float deposit;
    int found = 0;
    struct user acc;
    ptr = fopen("account.dat", "rb+");
    if (ptr == NULL)
    {
        printf("file does not exsit");
        return;
    }
    printf("Enter the Account number:");
    if (scanf("%d", &account_no) != 1)
    {
        printf("Please enter only digit");
        fclose(ptr);
        return;
    }
    printf("Enter your pin:");

    if (scanf("%d", &pin) != 1)
    {
        printf("Please enter only 4 digit number\n");
        fclose(ptr);
        return;
    }

    if (pin < 1000 || pin > 9999)
    {
        printf("PIN must be exactly 4 digits\n");
        fclose(ptr);
        return;
    }
    while (fread(&acc, sizeof(acc), 1, ptr))
    {
        if (acc.account_no == account_no && acc.pin == pin)
        {
            printf("Your Account Balance is %f:", acc.balance);
            printf("\nPlease enter the amount you want to Deposit");
            if (scanf("%f", &deposit) != 1)
            {
                printf("Please enter only digit");
                fclose(ptr);
                return;
            }
            if (deposit <= 0)
            {
                printf("Invalid deposit amount\n");
                fclose(ptr);
                return;
            }
            else
            {

                acc.balance += deposit;
                printf("\nYour New Account Balance %f:", acc.balance);
                fseek(ptr, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, ptr);
                printf("Amount was Deposit succesfully\n");
                found = 1;
                break;
            }
        }
    }
    fclose(ptr);
    if (found == 0)
    {
        printf("Account not found\n");
    }
}
void WithdrwaMoney()
{
    FILE *ptr = NULL;
    int account_no;
    int pin;
    int withdraw;
    int found = 0;
    struct user acc;
    ptr = fopen("account.dat", "rb+");
    if (ptr == NULL)
    {
        printf("file does not exsit");
        return;
    }
    printf("Enter the Account number:");
    if (scanf("%d", &account_no) != 1)
    {
        printf("Please enter only digit");
        fclose(ptr);
        return;
    }
    printf("Enter your pin:");

    if (scanf("%d", &pin) != 1)
    {
        printf("Please enter only 4 digit number\n");
        fclose(ptr);
        return;
    }

    if (pin < 1000 || pin > 9999)
    {
        printf("PIN must be exactly 4 digits\n");
        fclose(ptr);
        return;
    }
    while (fread(&acc, sizeof(acc), 1, ptr))
    {
        if (acc.account_no == account_no && acc.pin == pin)
        {
            printf("Your Account Balance is %f:", acc.balance);
            printf("\nPlease enter the amount you want to withdraw:");
            if (scanf("%d", &withdraw) != 1)
            {
                printf("Please enter only digit");
                fclose(ptr);
                return;
            }
            if (acc.balance < withdraw)
            {
                printf("Insufficent balance\n");
                found = 1;
                break;
            }
            else
            {

                acc.balance -= withdraw;
                printf("\nYour New Account Balance %f:", acc.balance);
                fseek(ptr, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, ptr);
                printf("Amount was Withdraw succesfully\n");
                found = 1;
                break;
            }
        }
    }
    fclose(ptr);
    if (found == 0)
    {
        printf("Account not found\n");
    }
}
void CheckBalance()
{
    FILE *ptr = NULL;
    int account_no;
    int pin;
    int found = 0;
    struct user acc;
    ptr = fopen("account.dat", "rb");
    if (ptr == NULL)
    {
        printf("file does not exsit");
        return;
    }
    printf("Enter the Account number:");
    if (scanf("%d", &account_no) != 1)
    {
        printf("Please enter only digit");
        fclose(ptr);
        return;
    }
    printf("Enter your pin:");

    if (scanf("%d", &pin) != 1)
    {
        printf("Please enter only 4 digit number\n");
        fclose(ptr);
        return;
    }

    if (pin < 1000 || pin > 9999)
    {
        printf("PIN must be exactly 4 digits\n");
        fclose(ptr);
        return;
    }
    while (fread(&acc, sizeof(acc), 1, ptr))
    {
        if (acc.account_no == account_no && acc.pin == pin)
        {
            printf("your Balance is %f", acc.balance);
            found = 1;
            break;
        }
    }
    fclose(ptr);
    if (found == 0)
    {
        printf("Account not found\n");
    }
}

int main()
{

    int choice;
    do
    {
        printf("======MENU=====\n");
        printf("1.Create Account\n");
        printf("2.view Account\n");
        printf("3.Deposit Money\n");
        printf("4.Withdrwa Money\n");
        printf("5.Check Balance\n");
        printf("6.Exit\n");
        printf("enter the choice:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            CreateAccount();
            break;
        case 2:
            viewAccount();
            break;

        case 3:
            DepositMoney();
            break;

        case 4:
            WithdrwaMoney();
            break;

        case 5:
            CheckBalance();
            break;

        case 6:
            printf("Thankyou for using the system");
            break;
        default:
            printf("Invalid choice");
        }
    } while (choice != 6);

    return 0;
}

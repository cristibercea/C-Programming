#include "interface.h"
#include "services.h"
#include "domain.h"

void show_interface(){printf("\nEnter code \"1\" to sign in, code \"2\" to sign up or \"0\" to stop the app: ");}
void no_account_message(){printf("\nYou do not have this type of account!\n");}
void show_balance(float balance){printf("\n The account balance is: %.2f$ \n",balance);}
void exit_app(){printf("\n ~Program execution stopped!");}

int action_read(int n){
    /**
    function that limits the user to inserting valid input in the console
    param: n - biggest number of a command (or max day/month/year(=31/12/2024))
    return: x - a semi-valid input (command/day/month/year)
    **/
    int x;
    while(scanf("%d",&x)!=1) {
        printf("\n  Error - Input must be an integer number! Try again: ");
        while (getchar() != '\n');
    }
    if(x>n){
        printf("\n  Error - Input must be a number between 0 and %d! Try again: ", n);
        return action_read(n);
    }
    return x;
}

void clean_read_string(char x[]){
    /**
    cleans whitespaces at the end of a string
    param: x[] - string to be formatted
    **/
    int n=strlen(x)-1;
    while(x[n]==' '){
        x[n]='\0';
        n--;
    }
}

void sign_in_menu(){
    /**
    main sign-in menu. Here is made the verification of the correlation between a given name and a given password
    An error message is printed if the given password does not correspond to the given name
    **/
    printf("\n  <Sign in>\n");
    char name[71],pass[51];
    name[0]=pass[0]='\0';
    printf("Username: ");
    fgets(name, sizeof(name)-1, stdin);
    if(name[strlen(name)-1]=='\n') name[strlen(name)-1]='\0';
    clean_read_string(name);
    printf("Password: ");
    fgets(pass, sizeof(pass)-1, stdin);
    if(pass[strlen(pass)-1]=='\n') pass[strlen(pass)-1]='\0';
    if(verify_login_details(name,pass)) {printf("\n  Welcome, %s!\n",name); strcpy(filename,name);}
    else{
        printf("Error - Incorrect password or username.\n");
        sign_in_menu();
    }
}

void sign_up_menu(){
    /**
    main sign-up menu. Here is created the corelation between a name and a password
    After the confirmation of the password, the name and the pass are stored into accounts_repo.txt file
    **/
    printf("\n  <Sign up>\n");
    char name[71],pass[51],confirm_pass[51];
    name[0]=pass[0]=confirm_pass[0]='\0';
    printf("Username: ");
    fgets(name, sizeof(name)-1, stdin);
    if(name[strlen(name)-1]=='\n') name[strlen(name)-1]='\0';
    clean_read_string(name);
    printf("Password: ");
    fgets(pass, sizeof(pass)-1, stdin);
    if(pass[strlen(pass)-1]=='\n') pass[strlen(pass)-1]='\0';
    printf("Confirm Password: ");
    fgets(confirm_pass, sizeof(confirm_pass)-1, stdin);
    if(confirm_pass[strlen(confirm_pass)-1]=='\n') confirm_pass[strlen(confirm_pass)-1]='\0';
    if(!strcmp(confirm_pass,pass))
        if(!verify_duplicate_account(name)){
            printf(" [i] Account created successfully!\n");
            save_account(name,pass);
        }
        else{
            printf("Error - An account with the same name already exists.\n");
            sign_up_menu();
        }
    else{
        printf("Error - Password confirmation error.\n");
        sign_up_menu();
    }
}

int accounts_management_menu(){
    printf("\n  Main Menu:\n");
    printf("1. Create a new account (savings, checking or credit account);\n");
    printf("2. Delete an existing account;\n");
    printf("3. Make transactions;\n");
    printf("0. Log out.\n");
    printf("\n Enter the number of desired action: ");
    return action_read(3);
}

int account_selection_menu(){
    printf("\n  Select an account to make transactions. Insert:\n");
    printf("1 - to select the credit account;\n");
    printf("2 - to select the savings account;\n");
    printf("3 - to select the checking account.\n>>> ");
    return action_read(3);
}

int transaction_menu(){
    printf("\n  Insert:\n");
    printf("~1 - to make a deposit;\n");
    printf("~2 - to make a withdraw;\n");
    printf("~3 - to make a payment;\n");
    printf("~4 - to make a transfer;\n");
    printf("~5 - to generate account balance;\n");
    printf("~6 - to generate account statement;\n");
    printf("~7 - to generate account expense report;\n");
    printf("~8 - to generate account transactions register;\n");
    printf("~0 - exit to Main Menu.\n>>> ");
    return action_read(8);
}

int user_account_creation_menu(){
    printf("\nInsert:\n  1 - to create a credit account;\n  2 - to create a savings account;\n  3 - to create a checking account;\n  0 - cancel action. \n >>>");
    return action_read(3);
}

int user_account_deletion_menu(){
    printf("\nInsert:\n  1 - to delete an existing credit account;\n  2 - to delete an existing savings account;\n  3 - to delete an existing checking account;\n  0 - cancel action. \n >>>");
    return action_read(3);
}

int register_type_menu(){
    printf("\nInsert:\n  1 - to generate transaction register in a CSV file;\n  2 - to generate transaction register in an Excel file;\n  3 - to generate transaction register in a PDF file;\n  0 - cancel action. \n >>>");
    return action_read(3);
}

int set_date(char s[10]){
    /**
    in: type of data to be read(a day, a month, or a year)
    this function will not allow:
        -a day-number bigger than 31
        -a month-number bigger than 12
        -a year-number bigger than 2024
    returns: the data scanned
    **/
    int x;
    if(strcmp(s,"day")==0){
        printf("Insert the day of the transaction: ");
        x=action_read(31);
    }
    else if(strcmp(s,"month")==0){
        printf("Insert the month of the transaction: ");
        x=action_read(12);
    }
    else if(strcmp(s,"year")==0){
        printf("Insert the year of the transaction: ");
        x=action_read(2024);
    }
    return x;
}

float set_amount(){
    /**
    scans the amount introduced in the console
    return: float number = amount
    **/
    float s;
    printf("Insert the transaction's amount ($): ");
    while(scanf("%f",&s)!=1) {
        printf("\n Error - Input must be a real number! Try again: ");
        while (getchar() != '\n');
    }
    return s;
}

struct transaction new_transaction(char type[],char description[]){
    /**
    function that reads and returns a valid transaction
    params: type-the type of transaction(deposit,withdrawal,payment,transfer)
            description-"~none~" if it is not needed, or "", if it is to be read
    return: a valid transaction struct
    **/
    struct transaction x;
    x.day=set_date("day");
    x.month=set_date("month");
    x.year=set_date("year");
    if(time_validator(x.year,x.month,x.day)){
        x.amount=set_amount();
        if(strcmp(description,"~none~")==0)
            strcpy(x.description,description);
        else{
            getchar();
            printf("Insert %s receiver's name(company or person): ",type);
            fgets(x.description, sizeof(x.description), stdin);
            if(x.description[strlen(x.description)-1]=='\n') x.description[strlen(x.description)-1]='\0';
        }
        strcpy(x.type,type);
    }else return new_transaction(type,description);
    printf("\n [i] Transaction successful!\n");
    return x;
}

void generate_statement(int n,float balance,struct transaction * p){
    /**
    function that generates the balance of user's account
    param: n - number of elements in the dynamic-allocated array
    **/
    if(n==0) printf("\nYou have not made any transaction yet!\n");
    else{
        printf("\n      Account Statement:\n");
        for(int i=0;i<n;i++){
            char descr[71];
            if(strcmp("deposit",(p+i)->type)==0||strcmp("withdrawal",(p+i)->type)==0) strcpy(descr,"(The Bank)");
            else strcpy(descr,(p+i)->description);
            printf("%d. Date: %2d/%2d/%4d;        Type: %10s;        Receiver: %s;        ",i+1,(p+i)->day,(p+i)->month,(p+i)->year,(p+i)->type,descr);
            if(strcmp("deposit",(p+i)->type)==0) printf("+%.2f$\n",(p+i)->amount);
            else printf("-%.2f$\n",(p+i)->amount);
        }
        printf("-----------------------------------------------------------------------------------------------\n");
        printf("Your current balance:     %.2f$\n",balance);
    }
}

void generate_expense_report(int n,struct transaction * p){
    /**
    function that generates the expense report of user's account
    param: n - number of elements in the dynamic-allocated array
    **/
    float sum=0;
    int counter=0;
    printf("\n      Expense Report:\n");
    for(int i=0;i<n;i++)
        if(strcmp("deposit",(p+i)->type)!=0){
            char descr[71];
            counter++;
            if(strcmp("withdrawal",(p+i)->type)==0) strcpy(descr,"(The Bank)");
            else strcpy(descr,(p+i)->description);
            printf("%d. Date: %2d/%2d/%4d;        Type: %10s;        Receiver: %s;        ",counter,(p+i)->day,(p+i)->month,(p+i)->year,(p+i)->type,descr);
            printf("-%.2f$\n",(p+i)->amount);
            sum+=(p+i)->amount;
        }
    if(counter==0) printf("\nYou have no expenses yet!\n");
    else{
        printf("-----------------------------------------------------------------------------------------------\n");
        printf("Your total expenses:    %.2f$\n",sum);
    }
}

#include "interface.h"
#include "services.h"
#include "domain.h"

///PROTOTYPES
void create_user_account();
void delete_user_account();
void make_transaction();
void deposit(int n);
void withdraw(int n);
void pay(int n);
void transfer(int n);
void generate_transactions_register(int n,char account_type[]);
int load_from_file(int n,char path[]);
void store_in_file(int n,char path[]);
void store_in_custom_file(int n,char path[]);

struct transaction *p; ///the pointer to the main dynamic-allocated transaction array

///DEFINITIONS
void account_sign_up(){
    /**
    function that manages the sign-up of a new client
    **/
    getchar();
    sign_up_menu();
}

void account_sign_in(){
    /**
    function that manages the sign-in of a new client and prepares the fileaname
    **/
    getchar();
    sign_in_menu();
    int command=-1;
    strcat(filename,".txt");
    while(command!=0){
        command=accounts_management_menu();
        switch(command){
            case 1:
                create_user_account();
                break;
            case 2:
                delete_user_account();
                break;
            case 3:
                make_transaction();
                break;
        }
    }
}

void create_user_account(){
    /**
    function that creates a new banking account of a type (credit,savings,checking)
    prepares the path to the file where older transactions are stored
    if the user already has the given type of account, the function prints an error message
    this function detects and interdicts the creation of 2 accounts of the same type per client
    **/
    int type=user_account_creation_menu();
    if(type!=0){
        char path[1000],info[10];
        switch(type){
            case 1:
                strcpy(info,"credit");
                strcpy(path,"Acc_credit/");
                break;
            case 2:
                strcpy(info,"savings");
                strcpy(path,"Acc_savings/");
                break;
            case 3:
                strcpy(info,"checking");
                strcpy(path,"Acc_checking/");
                break;
        }
        strcat(path,filename);
        FILE *f=fopen(path,"r");
        if(f==NULL) {printf("\n [i]Successfully created a %s account!\n", info); f=fopen(path,"w");}
        else printf("\n [i]You already have a %s account!\n", info);
        fclose(f);
    }
}

void delete_user_account(){
    /**
    function that deletes an existing account
    it, basically, deletes the file that stores the account's transactions data
    **/
    int type=user_account_deletion_menu();
    if(type!=0){
        char path[1000],info[10];
        switch(type){
            case 1:
                strcpy(info,"credit");
                strcpy(path,"Acc_credit/");
                break;
            case 2:
                strcpy(info,"savings");
                strcpy(path,"Acc_savings/");
                break;
            case 3:
                strcpy(info,"checking");
                strcpy(path,"Acc_checking/");
                break;
        }
        strcat(path,filename);
        if(remove(path)==0) printf("\n [i]A %s account has been successfully deleted (all data has been erased)!\n", info);
        else printf("\n [i] You do not have any active %s accounts!\n",info);
    }
}

void select_account(char path[],char account_type[]){
    /**
    function that searches for a client account of a given type and, if it exists, creates the path to in;
    if the mentioned file does not exist, the function prints an error message
    param: char path[] = a string that will contain the path to the desired file(account), if it exists
    **/
    int type=account_selection_menu();
    switch(type){
        case 1:
            if(verify_account_existence("Acc_credit/",filename)){
                strcpy(path,"Acc_credit/");
                strcpy(account_type,"'s credit account");
                strcat(path,filename);
            }else no_account_message();
            break;
        case 2:
            if(verify_account_existence("Acc_savings/",filename)){
                strcpy(path,"Acc_savings/");
                strcpy(account_type,"'s savings account");
                strcat(path,filename);
            }else no_account_message();
            break;
        case 3:
            if(verify_account_existence("Acc_checking/",filename)){
                strcpy(path,"Acc_checking/");
                strcpy(account_type,"'s checking account");
                strcat(path,filename);
            }else no_account_message();
            break;
        }
}

void make_transaction(){
    /**
    function that manages transactions
    gets the path to the client acc. file(if it exists) and manages banking functionalities, based on what command the user gives
    prepares the dynamic-allocated struct transactions array, and empties it at the end
    **/
    char path[1000]="", account_type[25];
    select_account(path,account_type);
    if(strcmp(path,"")!=0){
        int command=-1;
        int n=0; ///number of transaction structures to be allocated
        p=NULL;
        n=load_from_file(n,path);
        while(command!=0){
            command=transaction_menu();
            switch(command){
                case 1:
                    n++;
                    deposit(n);
                    break;
                case 2:
                    n++;
                    withdraw(n);
                    break;
                case 3:
                    n++;
                    pay(n);
                    break;
                case 4:
                    n++;
                    transfer(n);
                    break;
                case 5:
                    show_balance(generate_balance(n,p));
                    break;
                case 6:
                    generate_statement(n,generate_balance(n,p),p);
                    break;
                case 7:
                    generate_expense_report(n,p);
                    break;
                case 8:
                    generate_transactions_register(n,account_type);
                    break;
            }
        }
        store_in_file(n,path);
        free(p);
    }
}

void deposit(int n){
    /**
    function that creates a new deposit transaction
    param: n - number of elements in the dynamic-allocated array
    **/
    if(n==1) p=(struct transaction *) malloc(n*sizeof(struct transaction));
    else p=realloc(p,n*sizeof(struct transaction));
    *(p+n-1)=new_transaction("deposit","~none~");
}

void withdraw(int n){
    /**
    function that creates a new withdrawal transaction
    param: n - number of elements in the dynamic-allocated array
    **/
    if(n==1) p=(struct transaction *) malloc(n*sizeof(struct transaction));
    else p=realloc(p,n*sizeof(struct transaction));
    *(p+n-1)=new_transaction("withdrawal","~none~");
}

void pay(int n){
    /**
    function that creates a new payment transaction
    param: n - number of elements in the dynamic-allocated array
    **/
    if(n==1) p=(struct transaction *) malloc(n*sizeof(struct transaction));
    else p=realloc(p,n*sizeof(struct transaction));
    *(p+n-1)=new_transaction("payment","");
}

void transfer(int n){
    /**
    function that creates a new transfer transaction
    param: n - number of elements in the dynamic-allocated array
    **/
    if(n==1) p=(struct transaction *) malloc(n*sizeof(struct transaction));
    else p=realloc(p,n*sizeof(struct transaction));
    *(p+n-1)=new_transaction("transfer","");
}

float generate_balance(int n,struct transaction *p){
    /**
    function that generates the balance of user's account
    param: n - number of elements in the dynamic-allocated array
    return: float balance - user account's balance
    **/
    float balance=0;
    for(int i=0;i<n;i++)
        if(strcmp("deposit",(p+i)->type)==0) balance+=(p+i)->amount;
        else balance-=(p+i)->amount;
    return balance;
}

void generate_transactions_register(int n,char account_type[]){
    /**
    function that generates the transactions register of user's account
    param: n - number of elements in the dynamic-allocated array
    **/
    char filename2[85],path[200]="D:/";
    strcpy(filename2,filename);
    filename2[strlen(filename2)-4]='\0';
    strcat(filename2,account_type);
    int type=register_type_menu();
    switch(type){
        case 1://CSV
            strcat(filename2,".csv");
            break;
        case 2://Excel
            strcat(filename2,".xls");
            break;
        case 3://PDF
            strcat(filename2,".pdf");
            break;
    }
    if(type!=0){
        strcat(path,filename2);
        store_in_custom_file(n,path);
        printf("\n File successfully generated at path: \"%s\"\n",path);
        if(type==3) printf(" Note: It is recommended to open the new generated file with WordPad or NotePad.\n");
        else printf(" Note: It is recommended to open the new generated file with WordPad or Excel.\n");
    }
}

int load_from_file(int n,char path[]){
    /**
    if the file is not empty, loads all transactions from an account file to the dynamic allocated
    array of structures (in memory)
    **/
    FILE *f=fopen(path,"r");
    int day, month, year;
    float amount;
    while(1){
        char type[18],description[71];
        fscanf(f, "%d", &day);
        fgetc(f);
        fscanf(f, "%d", &month);
        fgetc(f);
        fscanf(f, "%d", &year);
        fgetc(f);
        fscanf(f, "%f", &amount);
        fgetc(f);
        fgets(type, 17 ,f);
        fgets(description,70,f);
        if(feof(f))  break;
        if(type[strlen(type)-1]=='\n') type[strlen(type)-1]='\0';
        if(description[strlen(description)-1]=='\n') description[strlen(description)-1]='\0';
        n++;
        if(n==1) p=(struct transaction*) malloc(n*sizeof(struct transaction));
        else p=realloc(p,n*sizeof(struct transaction));
        (p+n-1)->day=day;
        (p+n-1)->month=month;
        (p+n-1)->year=year;
        (p+n-1)->amount=amount;
        strcpy((p+n-1)->type,type);
        strcpy((p+n-1)->description,description);
    }
    fclose(f);
    return n;
}

void store_in_file(int n,char path[]){
    /**
    stores all transactions from the in-memory dynamic-allocated array of structures into the user account file
    **/
    FILE *f=fopen(path,"w");
    for(int i=0;i<n;i++){
        fprintf(f, "%d\n", (p+i)->day);
        fprintf(f, "%d\n", (p+i)->month);
        fprintf(f, "%d\n", (p+i)->year);
        fprintf(f, "%.2f\n", (p+i)->amount);
        fprintf(f, "%s\n", (p+i)->type);
        fprintf(f, "%s\n", (p+i)->description);
    }
    fclose(f);
}

void store_in_custom_file(int n,char path[]){
    /**
    stores all transactions from the in-memory dynamic-allocated array of structures into an excel/csv/pdf file
    **/
    FILE *f=fopen(path,"w");
    for(int i=0;i<n;i++){
        char descr[71];
        if(strcmp("deposit",(p+i)->type)==0||strcmp("withdrawal",(p+i)->type)==0) strcpy(descr,"(The Bank)");
        else strcpy(descr,(p+i)->description);
        fprintf(f,"%d. Date: %2d/%2d/%4d;        Type: %10s;        Receiver: %s;        ",i+1,(p+i)->day,(p+i)->month,(p+i)->year,(p+i)->type,descr);
        if(strcmp("deposit",(p+i)->type)==0) fprintf(f,"+%.2f$\n",(p+i)->amount);
        else fprintf(f,"-%.2f$\n",(p+i)->amount);
    }
    fprintf(f,"-----------------------------------------------------------------------------------------------\n");
    fprintf(f,"Your account's balance:     %.2f$\n",generate_balance(n,p));
    fclose(f);
}

#include "domain.h"

void save_account(char name[71],char pass[51]){
    /**
    function that stores into the accounts_repo.txt file the password and the name of the client
    param: name[] - the name of the client
           pass[] - the password set by the client
    **/
    FILE *f=fopen("accounts_repo.txt","a");
    fprintf(f,"%s\n",name);
    fprintf(f,"%s\n",pass);
    fclose(f);
}

int verify_duplicate_account(char name[71]){
    /**
    function that verifies if there already exists another client with the same name in accounts_repo.txt file
    param: name[] - the name of the client
    return: 0 - if the account name does not exist in the file
            1 - if the account name exists in the file
    **/
    FILE *f=fopen("accounts_repo.txt","r");
    if(f==NULL){
        perror("Error opening file");
        return 0;
    }
    char read_name[71],pass[51];
    while(1){
        read_name[0]=pass[0]='\0';
        fgets(read_name,sizeof(read_name)-1,f);
        if(feof(f)) break;
        fgets(pass,sizeof(pass)-1,f);
        if(feof(f)) break;
        if(read_name[strlen(read_name)-1]=='\n') read_name[strlen(read_name)-1]='\0';
        if(!strcmp(name,read_name)) {fclose(f); return 1;}
    }
    fclose(f);
    return 0;
}

int verify_login_details(char name[71],char pass[51]){
    /**
    function that verifies if the password and the name given by the user at sign-in are valid(they correspond with data in accounts_repo.txt file)
    param: name[] - the name inserted by the client
           pass[] - the password given by the client
    return: 0 - if the account name does not correspond to the given password
            1 - if the account name corresponds to the given password
    **/
    FILE *f=fopen("accounts_repo.txt","r");
    if(f==NULL){
        perror("Error opening file");
        return 0;
    }
    char read_name[71],read_pass[51];
    while(1){
        read_name[0]=read_pass[0]='\0';
        fgets(read_name,sizeof(read_name)-1,f);
        if(feof(f)) break;
        fgets(read_pass,sizeof(read_pass)-1,f);
        if(feof(f)) break;
        if(read_name[strlen(read_name)-1]=='\n') read_name[strlen(read_name)-1]='\0';
        if(read_pass[strlen(read_pass)-1]=='\n') read_pass[strlen(read_pass)-1]='\0';
        if(!strcmp(name,read_name) && !strcmp(pass,read_pass)) {fclose(f); return 1;}
    }
    fclose(f);
    return 0;
}

int verify_account_existence(char folder[],char filename[]){
    /**
    function that verifies if an account has been created
    params: folder-folder name, folowed by "/"
            filename-file name, defined as: client_name + ".txt"
    return: 1 - if the searched file can be opened for read (so this file already exists)
            0 - if the searched file can not be opened for read (it does not exist)
    **/
    char path[1000];
    strcpy(path,folder);
    strcat(path,filename);
    FILE *f=fopen(path,"r");
    if(f==NULL) return 0;
    else{fclose(f); return 1;}
}

int LeapYear(int n){
    /**
    verifies if n is a leap year
    returns: 1, if n is leap year
             0, else
    **/
    if((n%4==0)&&(n%100!=0)) return 1;
    if(n%400==0) return 1;
    return 0;
}

int time_validator(int y, int m, int d){
    /**
    validates the date of the newly read transaction
    prints error messages to help the user correct their mistakes
    return: 1, if everything is fine
            0, if date is not valid
    **/
    int ok=0;
    if(y<=0) {ok=1; printf(" Error - The year is a natural number, bigger than 0!\n");}
    if(m<=0) {ok=1; printf(" Error - The month is a natural number, bigger than 0!\n");}
    if(d<=0) {ok=1; printf(" Error - The day is a natural number,bigger than 0!\n");}
    if(m>12) {ok=1; printf(" Error - There are only 12 months in a year!\n");}
    switch (m){
        case 1:{
            if(d>31) {ok=1; printf(" Error - January has only 31 days!\n");}
            break;
        }
        case 2:{
            if(LeapYear(y)){
                if(d>29) {ok=1; printf(" Error - February has only 29 days, in leap years!\n");}
            }else
                if(d>28) {ok=1; printf(" Error - February has only 28 days, in normal years!\n");}
            break;
        }
        case 3:{
            if(d>31) {ok=1; printf(" Error - March has only 31 days!\n");}
            break;
        }
        case 4:{
            if(d>30) {ok=1; printf(" Error - April has only 30 days!\n");}
            break;
        }
        case 5:{
            if(d>31) {ok=1; printf(" Error - May has only 31 days!\n");}
            break;
        }
        case 6:{
            if(d>30) {ok=1; printf(" Error - June has only 30 days!\n");}
            break;
        }
        case 7:{
            if(d>31) {ok=1; printf(" Error - July has only 31 days!\n");}
            break;
        }
        case 8:{
            if(d>31) {ok=1; printf(" Error - August has only 31 days!\n");}
            break;
        }
        case 9:{
            if(d>30) {ok=1; printf(" Error - September has only 30 days!\n");}
            break;
        }
        case 10:{
            if(d>31) {ok=1; printf(" Error - October has only 31 days!\n");}
            break;
        }
        case 11:{
            if(d>30) {ok=1; printf(" Error - November has only 30 days!\n");}
            break;
        }
        case 12:{
            if(d>31) {ok=1; printf(" Error - December has only 31 days!\n");}
            break;
        }
    }
    if(ok==0) return 1;
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

///GLOBAL DECLARATIONS

int n=0;
struct transaction{
    int day, month, year;
    char description[200];
    float amount;
    char type[8];
}data[10000]; ///main struct of transactions data


///TEST CODE ZONE

int LeapYear(int n);
float calculateBalance(struct transaction data[]);
struct transaction loadFromFile(FILE *read);

void test_loadFromFile(){ ///note: float values are computer aproximations of real numbers
    FILE *read=fopen("FinancialDataTESTVALUES.txt","r");
    struct transaction a={1,1,1,"interesting description\n",124.89,"income"};
    struct transaction b=loadFromFile(read);
    assert(b.amount-a.amount<=0.000001);
    assert(b.day==a.day);
    assert(b.month==a.month);
    assert(b.year==a.year);
    assert(strcmp(a.description,b.description)==0);
    assert(strcmp(a.type,b.type)==0);
    fclose(read);
}

void test_calculateBalance(){ ///note: float values are computer aproximations of real numbers
    struct transaction a[]={{12,2,3257,"",100,"income"},{10,12,1247,"",500,"income"},{10,12,1247,"",200,"expense"}};
    assert(calculateBalance(a)-400<0.000000001);
    //assert(calculateBalance(a)==400); //assertion error
    struct transaction b[]={{12,2,3257,"",100.57,"income"},{10,12,1247,"",500.72,"income"},{10,12,1247,"",201.29,"expense"}};
    assert(calculateBalance(b)-400<0.000000001);
}

void test_LeapYear(){
    //assert(LeapYear(2000)==0); //good assertion error
    assert(LeapYear(2000));
    assert(!LeapYear(1982));
    assert(LeapYear(4572));
    assert(!LeapYear(3462));
}

void testbench(){///test functions caller
    test_LeapYear();
    test_calculateBalance();
    test_loadFromFile();
}


///APP CODE ZONE

int set_date(char s[10]){
    /**
    in: type of data to be read(a day, a month, or a year
    returns: the data scanned
    **/
    int x;
    if(strcmp(s,"day")==0)
        printf("  > Insert the day of the transaction: ");
    else if(strcmp(s,"month")==0)
        printf("  > Insert the month of the transaction: ");
    else if(strcmp(s,"year")==0)
        printf("  > Insert the year of the transaction: ");
    scanf("%d", &x);
    return x;
}

float set_amount(){
    /**
    scans the amount introduced in the console
    return: amount
    **/
    float s;
    printf("  > Insert the transaction's amount ($): ");
    scanf("%f", &s);
    return s;
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
    validates the date of the newly red transaction
    prints error messages to help the user correct his mistakes
    return: 1, if everything is fine
            0, if date is not valid
    **/
    int ok=0;
    if(y<=0) {ok=1; printf("  [!] The year is a natural number, bigger than 0!\n");}
    if(m<=0) {ok=1; printf("  [!] The month is a natural number, bigger than 0!\n");}
    if(d<=0) {ok=1; printf("  [!] The day is a natural number,bigger than 0!\n");}
    if(m>12) {ok=1; printf("  [!] There are only 12 months in a year!\n");}
    switch (m){
        case 1:{
            if(d>31) {ok=1; printf("  [!] January has only 31 days!\n");}
            break;
        }
        case 2:{
            if(LeapYear(y)){
                if(d>29) {ok=1; printf("  [!] February has only 29 days, in leap years!\n");}
            }else
                if(d>28) {ok=1; printf("  [!] February has only 28 days, in normal years!\n");}
            break;
        }
        case 3:{
            if(d>31) {ok=1; printf("  [!] March has only 31 days!\n");}
            break;
        }
        case 4:{
            if(d>30) {ok=1; printf("  [!] April has only 30 days!\n");}
            break;
        }
        case 5:{
            if(d>31) {ok=1; printf("  [!] May has only 31 days!\n");}
            break;
        }
        case 6:{
            if(d>30) {ok=1; printf("  [!] June has only 30 days!\n");}
            break;
        }
        case 7:{
            if(d>31) {ok=1; printf("  [!] July has only 31 days!\n");}
            break;
        }
        case 8:{
            if(d>31) {ok=1; printf("  [!] August has only 31 days!\n");}
            break;
        }
        case 9:{
            if(d>30) {ok=1; printf("  [!] September has only 30 days!\n");}
            break;
        }
        case 10:{
            if(d>31) {ok=1; printf("  [!] October has only 31 days!\n");}
            break;
        }
        case 11:{
            if(d>30) {ok=1; printf("  [!] November has only 30 days!\n");}
            break;
        }
        case 12:{
            if(d>31) {ok=1; printf("  [!] December has only 31 days!\n");}
            break;
        }
    }
    if(ok==0) return 1;
    printf("\n  [i] Please rectify transaction data.\n");
    return 0;
}

void add_transaction(){
    /**
    reads data and creates a new transaction in the "data" structure
    **/
    data[n].day=set_date("day");
    data[n].month=set_date("month");
    data[n].year=set_date("year");
    if(time_validator(data[n].year,data[n].month,data[n].day)){
        getchar();
        printf("  > Insert a brief description of the transaction(200 characters max): \n");
        fgets(data[n].description, sizeof(data[n].description), stdin);
        data[n].amount=set_amount();
        getchar();
        printf("  > Insert the type of the transaction(income or expense): \n");
        fgets(data[n].type, 8, stdin);
        if(strcmp(data[n].type,"expense")!=0) data[n].type[6]='\0';
        if(strcmp(data[n].type,"income")==0 || strcmp(data[n].type,"expense")==0){
            printf("\n    <!>  Data successfully saved  <!>\n");
            n++;
        }else{
            printf("  [!] Transaction type must be \"income\" or \"expense\"! \n");
            printf("  [i] Please rectify transaction data.\n");
        }
    }
}

void showTransactions(){
    /**
    prints the list of all recent transactions
    **/
    if(n>0){
        printf("\n    Transactions list(older first):\n\n");
        for(int i=0;i<n;i++)
            printf(">> %d.  Date: %d.%d.%d,   Amount: %.2f$,   Type: %s     -Description: %s",i+1, data[i].day, data[i].month, data[i].year, data[i].amount, data[i].type, data[i].description);
    }else printf("  [!] There are no transactions saved!");
}

float calculateBalance(struct transaction data[]){
    /**
    calculates the balance
    returns: a float number representing user's balance
    **/
    float money=0;
    for(int i=0;i<n;i++)
        if(strcmp(data[i].type,"income")) money-=data[i].amount;
        else money+=data[i].amount;
    return money;
}

void balance(){
    /**
    calculates and prints the balance of user's account
    **/
    if(n>0){
        float money;
        money=calculateBalance(data);
        printf(">> Your balance is: %.2f$", money);
    }
    else
        printf("  [!] There are no saved transactions!");
}

void periodTransactions(){
    /**
    searches and prints transactions made in a user specified period
    input: dates of start and finish of the period
    out: corresponding transactions or error message
    **/
    int d1,m1,y1,d2,m2,y2,ok=0;
    char s[11];
    getchar();
    printf("\n    >>> Insert the start of the period ( date format: dd.mm.yyyy ): \n");
    fgets(s,11,stdin);
    d1=(s[0]-'0')*10+(s[1]-'0');
    m1=(s[3]-'0')*10+(s[4]-'0');
    y1=(s[6]-'0')*1000+(s[7]-'0')*100+(s[8]-'0')*10+(s[9]-'0');
    if(time_validator(y1,m1,d1)){
        s[0]='\0';
        getchar();
        printf("\n    >>> Insert the end of the period ( date format: dd.mm.yyyy ): \n");
        fgets(s,11,stdin);
        d2=(s[0]-'0')*10+(s[1]-'0');
        m2=(s[3]-'0')*10+(s[4]-'0');
        y2=(s[6]-'0')*1000+(s[7]-'0')*100+(s[8]-'0')*10+(s[9]-'0');
        if(time_validator(y2,m2,d2)){
            if((y1<y2)||(m1<m2&&y1==y2)||(d1<d2&&m1==m2&&y1==y2)){
                for(int i=0;i<n;i++)
                    if((y1<data[i].year&&y2>data[i].year)||(y1<=data[i].year&&y2>=data[i].year&&m1<data[i].month&&m2>data[i].month)||(y1<=data[i].year&&y2>=data[i].year&&m1<=data[i].month&&m2>=data[i].month&&d1<=data[i].day&&d2>=data[i].day)){
                        if(ok==0) printf("\n    Transactions list in given period (older first):\n\n");
                        printf(">> %d.  Date: %d.%d.%d,   Amount: %.2f$,   Type: %s     -Description: %s",i+1, data[i].day, data[i].month, data[i].year, data[i].amount, data[i].type, data[i].description);
                        ok=1;
                    }
                if(ok==0) printf("\n  [i] There is no transaction in the given period.\n");
            }else printf("\n  [!] Invalid period. Start date must be earlier than end date!\n");
        }else printf("\n  [!] Invalid end date!\n");
    }else printf("\n  [!] Invalid start date!\n");
}

void storeInFile(struct transaction x, FILE *write){
    /**
    makes the actual transfer between struct vector and file (prints a transaction's data into the file)
    **/
    fprintf(write, "%d\n", x.day);
    fprintf(write, "%d\n", x.month);
    fprintf(write, "%d\n", x.year);
    fprintf(write, "%.2f\n", x.amount);
    fprintf(write, "%s %s", x.type, x.description);
}

struct transaction loadFromFile(FILE *read){
    /**
    does the data storing transfer, from file to the struct vector
    returns: x, a future element of data[] (a transaction)
    **/
    struct transaction x;
    char aux[210];
    int t=0;
    fscanf(read, "%d", &x.day);
    fscanf(read, "%d", &x.month);
    fscanf(read, "%d", &x.year);
    fscanf(read, "%f", &x.amount);
    fgetc(read);
    fgets(aux, 210 ,read);
    if(aux[6]==' '){
        strcpy(x.type,"income");
        for(int i=7;i<=strlen(aux);i++)
            x.description[t]=aux[i], t++;
    }else{
        strcpy(x.type,"expense");
        for(int i=8;i<=strlen(aux);i++)
            x.description[t]=aux[i], t++;
    }
    if(strcmp(x.description,"\n")==0 || strcmp(x.description,"<~none~>")==0) strcpy(x.description,"<~none~>");
    return x;
}

void Store(){
    /**
    prepares the data storing and the file
    **/
    FILE *write=fopen("FinancialData.txt","w");
    for(int i=0;i<n;i++) storeInFile(data[i],write);
    fclose(write);
    printf("\n  [i] Successfully stored %d transactions!\n",n);
}

void Load(){
    /**
    prepares the data loading and the file
    **/
    FILE *read=fopen("FinancialData.txt","r");
    while(1){
        struct transaction x=loadFromFile(read);
        if(feof(read)) break;
        data[n]=x;
        n++;
    }
    fclose(read);
    printf("\n  [i] Successfully loaded %d transactions!\n",n);
}

void TaskSelect(int com){ ///selects the task to complete, depending on "com"
    switch(com){
        case 1:
            add_transaction();
            break;
        case 2:
            showTransactions();
            break;
        case 3:
            balance();
            break;
        case 4:
            periodTransactions();
            break;
        case 5:
            Store();
            break;
        case 6:
            Load();
            break;
        case 0:
            printf("\n\n  [i] Program execution has stopped. Any unsaved activity was deleted! \n");
            break;
    }
}

void interface(){  ///prints the app's main menu
    printf("  <$>=================================|WELCOME|=================================<$>\n\n\n");
    printf("    ~Select code 1 to add transaction \n");
    printf("    ~Select code 2 to display list with previous transactions \n");
    printf("    ~Select code 3 to calculate account balance\n");
    printf("    ~Select code 4 to recive a summary of income and expenses for a specific period\n");
    printf("    ~Select code 5 to save latest financial data (this save will override the last save) \n");
    printf("    ~Select code 6 to load latest financial data (adds transactions saved in previous sessions to the current one) \n");
    printf("\n    [i] Transaction types allowed: income, expense \n");
    printf("\n    ~Select code 0(zero) to exit the app...\n\n\n  <$>==============================(~FINANCE APP~)==============================<$>\n");
}

int command_read(){
    /**
    reads the command until it is a valid one
    return: a valid command
    **/
    int x;
    printf("\n      ---> Insert a code to make an action: ");
    scanf("%d",&x);
    if(x>6||x<0){
        printf("\n  [!] Invalid input!");
        x=command_read();
    }
    return x;
}

int main(){
    testbench();
    int command=-1;
    interface();
    while(command!=0){
        command=command_read();
        TaskSelect(command);
    }
    return 0;
}

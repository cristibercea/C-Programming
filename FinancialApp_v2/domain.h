#ifndef DOMAIN_H_INCLUDED
    #define DOMAIN_H_INCLUDED

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    struct transaction{ ///base struct of transactions data
            int day, month, year;
            char description[71];//used for transfers and payments to store the name of the receiver
            float amount;
            char type[12];
        };

    void save_account(char name[71],char pass[51]);
    int verify_duplicate_account(char name[71]);
    int verify_login_details(char name[71],char pass[51]);
    int verify_account_existence(char folder[],char filename[]);
    int time_validator(int y, int m, int d);
    int LeapYear(int n);

#endif // DOMAIN_H_INCLUDED

#ifndef SERVICES_H_INCLUDED
    #define SERVICES_H_INCLUDED

    char filename[75];

    void account_sign_in();
    void account_sign_up();
    void clean_read_string();
    float generate_balance(int n,struct transaction *p);

#endif // SERVICES_H_INCLUDED

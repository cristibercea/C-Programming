#ifndef INTERFACE_H_INCLUDED
    #define INTERFACE_H_INCLUDED

    void clean_read_string(char x[]);
    void show_interface();
    int action_read();
    void exit_app();
    void sign_in_menu();
    void sign_up_menu();
    int accounts_management_menu();
    int user_account_creation_menu();
    int user_account_deletion_menu();
    int transaction_menu();
    int account_selection_menu();
    void no_account_message();
    void show_balance(float balance);
    struct transaction new_transaction(char type[],char description[]);
    void generate_statement(int n,float balance,struct transaction * p);
    void generate_expense_report(int n,struct transaction * p);
    int register_type_menu();

#endif // INTERFACE_H_INCLUDED

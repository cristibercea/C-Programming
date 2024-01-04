#include "tests.h"

int main()
{
    testbench();
    while(1){
        show_interface();
        int login_command=action_read(2);
        if(login_command==0){
            exit_app();
            return 0;
        }
        if(login_command==1)
            account_sign_in();
        if(login_command==2)
            account_sign_up();
    }
    return 0;
}

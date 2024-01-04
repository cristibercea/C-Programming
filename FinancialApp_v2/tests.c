#include "tests.h"
#include <assert.h>

void test_LeapYear(){
    //assert(LeapYear(2000)==0); //good assertion error
    assert(LeapYear(2000));
    assert(!LeapYear(1982));
    assert(LeapYear(4572));
    assert(!LeapYear(3462));
}

void test_calculateBalance(){
    struct transaction a[]={{12,2,1257,"",100,"deposit"},{10,12,1247,"",500,"deposit"},{10,12,1247,"",200,"withdraw"}};
    assert(generate_balance(3,a)==400);
    struct transaction b[]={{12,2,1257,"",99.57,"deposit"},{10,12,1247,"",500.72,"deposit"},{10,12,1247,"",200.29,"payment"}};
    assert(generate_balance(3,b)==400);
    struct transaction c[]={{12,2,1257,"",100,"transfer"},{10,12,1247,"",500,"deposit"},{10,12,1247,"",200,"payment"}};
    //assert(generate_balance(3,c)==400); //good assertion error
    assert(generate_balance(3,c)==200);
}

void test_clean_read_string(){
    char x[30]="asfsr                  ";
    clean_read_string(x);
    assert(!strcmp(x,"asfsr"));
    //assert(!strcmp(x,"asfsr ")); //good assertion error
    strcpy(x,"abcdefg");
    clean_read_string(x);
    assert(!strcmp(x,"abcdefg"));
    //assert(!strcmp(x,"abcdef")); //good assertion error
}

void testbench(){
    test_LeapYear();
    test_calculateBalance();
    test_clean_read_string();
}

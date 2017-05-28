#include <iostream>
#include "hash.h"
#include <functional>
#include <string>

class eq{
public:
    bool operator()(const std::string& s1,const std::string& s2){
        return s1==s2;
    }

    };


int main(int argc, char *argv[])
{

    test_hash();

    return 0;
}

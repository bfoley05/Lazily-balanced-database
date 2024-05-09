#include <iostream>
#ifndef included
#define included

using namespace std;

class Member
{
    public:
        int ID;
        string name;
        string level;

        Member();
        ~Member();

        int getID();
        void setID(int value);

        string getName();
        string getLevel();
};

#endif

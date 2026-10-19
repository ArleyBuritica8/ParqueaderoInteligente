#ifndef PLACA_H
#define PLACA_H

#include <string>
using namespace std;

class Placa {
private:
    string ID;

public:
    Placa(string ID_);
    string getID();
};

#endif
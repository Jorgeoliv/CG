//
// Created by jose on 03-03-2018.
//

#ifndef ESTRUTURAS_PONTO_H
#define ESTRUTURAS_PONTO_H


#include <string>

using namespace std;

class Ponto {
private:
    float x;
    float y;
    float z;

public:
    Ponto();
    Ponto(float,float,float);
    Ponto(Ponto &p);
    float getX();
    float getY();
    float getZ();
    void setX(float);
    void setY(float);
    void setZ(float);
    string toString();

};


#endif //ESTRUTURAS_PONTO_H

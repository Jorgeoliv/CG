#ifndef __Ponto_H__
#define __Ponto_H__

#include <math.h>
#include <string>
#include "Ponto.h"

using namespace std;

class Triangulo {

private:
    Ponto *a;
    Ponto *b;
    Ponto *c;

public:
    Triangulo();

    Triangulo(Ponto *, Ponto *, Ponto *);

    Triangulo(Triangulo &t);

    Ponto *getA();

    Ponto *getB();

    Ponto *getC();

    void setA(Ponto*);

    void setB(Ponto*);

    void setC(Ponto*);

    string toString();
};
		

#endif
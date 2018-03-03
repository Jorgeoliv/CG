//
// Created by jose on 03-03-2018.
//

#include "Ponto.h"


Ponto::Ponto(){
    x=0;
    y=0;
    z=0;
}

Ponto::Ponto(float a,float b,float c){
    x=a;
    y=b;
    z=c;
}

Ponto::Ponto(Ponto &p){
    x=p.getX();
    y=p.getY();
    z=p.getZ();
}

float Ponto::getX(){
    return x;
}

float Ponto::getY(){
    return y;
}

float Ponto::getZ(){
    return z;
}

void Ponto::setX(float a){
    this->x=a;
}

void Ponto::setY(float b){
    y=b;
}

void Ponto::setZ(float c){
    z=c;
}

string Ponto::toString(){
    string res = to_string(x) + " " + to_string(y) + " " + to_string(z);
    return res;
}

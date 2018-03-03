#include "Triangulo.h"


Triangulo::Triangulo() {
	a = new Ponto();
	b = new Ponto();
	c = new Ponto();
}

Triangulo::Triangulo(Ponto* a, Ponto* b, Ponto* c){
	this->a=a;
	this->b=b;
	this->c=c;
}

Triangulo::Triangulo(Triangulo &t){}

//estes n sei bem

Ponto* Triangulo::getA(){
	return a;
}

Ponto* Triangulo::getB(){
	return b;
}

Ponto* Triangulo::getC(){
	return c;
}


void Triangulo::setA(Ponto* a){
	this->a=a;
}
void Triangulo::setB(Ponto* b){
	this->b=b;
}
void Triangulo::setC(Ponto* c){
	this->c=c;
}
//estes tbm n


string Triangulo::toString(){
	string res = a->toString() + "\n" + b->toString() + "\n" + c->toString() + "\n"; //aqui ver se pomos o \n no fim
	return res;
}
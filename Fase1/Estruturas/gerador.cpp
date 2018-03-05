#include <iostream>
#include <fstream>
#include <vector>
#include "Ponto.h"
using namespace std;


vector<Ponto*> plane(float lado){

	float coord = lado/2.0f;
	vector<Ponto*> pontos;
    //Plane
    
    Ponto *p = new Ponto(-coord, 0.0f, coord);
    pontos.push_back(p);
	p = new Ponto(coord, 0.0f, -coord);
	pontos.push_back(p);
    p = new Ponto(-coord, 0.0f, -coord);
    pontos.push_back(p);
    p = new Ponto(-coord, 0.0f, coord);
    pontos.push_back(p);
	p = new Ponto(coord, 0.0f, coord);
	pontos.push_back(p);
    p = new Ponto(coord, 0.0f, -coord);
    pontos.push_back(p);
    return pontos;
}

int comparaFigura(string a){

	if(a.compare("plane")==0) return 1;

	return 0;
}

int main (int argc, char** argv) {
  ofstream myfile;
  vector<Ponto*> pontos;

  int aux = comparaFigura(argv[1]);
  switch(aux){
  	case 1: {
  		myfile.open(argv[3]);
  		string tam(argv[2]);
  		float lado = stof(tam);
  		pontos = plane(lado);
  		break;
  	}

  	default: break; 
  }
  

  for(Ponto* p: pontos){
  	string escreve = p->toString();
  	myfile << escreve + "\n";
  }

  
  myfile.close();

  return 0;
}
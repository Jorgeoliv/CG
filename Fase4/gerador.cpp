#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include "Ponto.h"
#include "parser.h"
#include "Patch.h"
using namespace std;


Patch* extraiPatch(string filename){

    ifstream inputFileStream(filename);

    int count;

    string line;
    getline(inputFileStream, line);

    count = stoi(line);
    vector<vector<int>> indices;
    for(int i=0; i < count; i++){
        getline(inputFileStream, line);

        stringstream ss(line);
        vector<int> numbers;

        for(int k = 0; k < 16; k++) {
            string aux;
            ss >> aux;

            int j = stoi(aux);
            numbers.push_back(j);
            //cout << "IND: " << j << endl;
        }

        indices.push_back(numbers);
    }

    getline(inputFileStream, line);
    count = stoi(line);

    cout << "Pontos: " << count << endl;    

    vector<Ponto*> pontosControlo;

    for(int i=0; i < count; i++){
        getline(inputFileStream, line);

        stringstream ss(line);
        vector<float> numbers;

        for(int k = 0; k < 3; k++) {
            string aux;
            ss >> aux;

            float j = stof(aux);
            numbers.push_back(j);
        }

        Ponto *p = new Ponto(numbers.at(0),numbers.at(1),numbers.at(2));
        pontosControlo.push_back(p);

    }

    cout << "Tam: " << pontosControlo.size() << endl;

    Patch* res = new Patch(indices,pontosControlo);
    return res;

}

vector<Ponto*> torus(float raioTubo, float raioMaior, int fatias, int camadas, vector<Ponto*> * normais, vector<Ponto*> * texturas){

    Ponto* p;
    vector<Ponto*> pontos;

    float alpha = 2*M_PI / fatias;
    float beta = 2*M_PI / camadas;

    float x1, x2, x3, x4, y1, y2, z1, z2, y3, y4;
    float nx1,nx2, nx3, nx4, ny1, ny2, nz1, nz2, ny3, ny4;

    for(int i = 0; i<fatias; i++){
        for(int j = 0; j<camadas; j++){


            z1 = raioTubo*sin(beta*j);
            z2 = raioTubo*sin(beta*(j+1));

            y1 = (raioMaior + raioTubo*cos(beta*j))*sin(alpha*i);
            y2 = (raioMaior + raioTubo*cos(beta*j))*sin(alpha*(i+1));
            y3 = (raioMaior + raioTubo*cos(beta*(j+1)))*sin(alpha*i);
            y4 = (raioMaior + raioTubo*cos(beta*(j+1)))*sin(alpha*(i+1));

            x1 = (raioMaior + raioTubo*cos(beta*j))*cos(alpha*i);
            x2 = (raioMaior + raioTubo*cos(beta*j))*cos(alpha*(i+1));
            x3 = (raioMaior + raioTubo*cos(beta*(j+1)))*cos(alpha*i);
            x4 = (raioMaior + raioTubo*cos(beta*(j+1)))*cos(alpha*(i+1));

            nz1 = sin(beta*j);
            nz2 = sin(beta*(j+1));

            ny1 = (cos(beta*j))*sin(alpha*i);
            ny2 = (cos(beta*j))*sin(alpha*(i+1));
            ny3 = (cos(beta*(j+1)))*sin(alpha*i);
            ny4 = (cos(beta*(j+1)))*sin(alpha*(i+1));

            nx1 = (cos(beta*j))*cos(alpha*i);
            nx2 = (cos(beta*j))*cos(alpha*(i+1));
            nx3 = (cos(beta*(j+1)))*cos(alpha*i);
            nx4 = (cos(beta*(j+1)))*cos(alpha*(i+1));

            float ty1 = (float)i / (float) fatias;
            float tx1 = (float)j / (float) camadas;

            float ty2 = (float)(i+1) / (float) fatias;
            float tx2 = (float)(j+1) / (float) camadas;
            
            Ponto* n;
            //glBegin(GL_TRIANGLES);
            (*texturas).push_back(new Ponto(tx1,ty1,0));
            p = new Ponto(x1,y1,z1);
            n = new Ponto(nx1,ny1,nz1);
            pontos.push_back(p);
            (*normais).push_back(n);


                //glVertex3f(x1, y1, z1);
            (*texturas).push_back(new Ponto(tx2,ty1,0));
            p = new Ponto(x2,y2,z1);
            n = new Ponto(nx2,ny2,nz1);
            pontos.push_back(p);
            (*normais).push_back(n);
                //glVertex3f(x2, y2, z1);

            (*texturas).push_back(new Ponto(tx1,ty2,0));
            p = new Ponto(x3,y3,z2);
            n = new Ponto(nx3,ny3,nz2);
            pontos.push_back(p);
            (*normais).push_back(n);
                //glVertex3f(x3, y3, z2);

            (*texturas).push_back(new Ponto(tx1,ty2,0));
            p = new Ponto(x3,y3,z2);
            n = new Ponto(nx3,ny3,nz2);
            pontos.push_back(p);
            (*normais).push_back(n);
                //glVertex3f(x3, y3, z2);

            (*texturas).push_back(new Ponto(tx2,ty1,0));
            p = new Ponto(x2,y2,z1);
            n = new Ponto(nx2,ny2,nz1);
            pontos.push_back(p);
            (*normais).push_back(n);
                //glVertex3f(x2, y2, z1);

            (*texturas).push_back(new Ponto(tx2,ty2,0));
            p = new Ponto(x4,y4,z2);
            n = new Ponto(nx4,ny4,nz2);
            pontos.push_back(p);
            (*normais).push_back(n);
                //glVertex3f(x4, y4, z2);

            //glEnd();

        }
    }

    return pontos;

}


vector<Ponto*> cilindro(float radius, float height, int slices,vector<Ponto*> *normais,vector<Ponto*> *texturas) {

  Ponto* p;
  vector<Ponto*> pontos;

  float alpha = 2*M_PI / slices;
  float pxA, pxD, pzA, pzD;
  float lados = (float) slices;
  float tx1,tx2;
    for(int i=0; i<slices;i++){

    	float iaux = (float) i;
        pxA = radius * sin(alpha*i);
        pxD = radius * sin(alpha*(i+1));
        pzA = radius * cos(alpha*i);
        pzD = radius * cos(alpha*(i+1));

        tx1 = (iaux /lados);
        tx2 = ((iaux+1)/lados);

        //glBegin(GL_TRIANGLES);
        (*normais).push_back(new Ponto(0,-1,0));
        (*texturas).push_back(new Ponto(0.4375,0.1875,0));
        p = new Ponto(0,0,0);
        pontos.push_back(p);
            //glVertex3f(0,0,0);
        (*normais).push_back(new Ponto(0,-1,0));
        (*texturas).push_back(new Ponto(0.1875 * cos( (i+1) * alpha) + 0.4375,0.1875 * sin( (i+1) * alpha) + 0.1875,0));
        p = new Ponto(pxD,0,pzD);
        pontos.push_back(p);
            //glVertex3f(pxD, 0, pzD);
        (*normais).push_back(new Ponto(0,-1,0));
        (*texturas).push_back(new Ponto(0.1875 * cos( (i) * alpha) + 0.4375,0.1875 * sin( (i) * alpha) + 0.1875,0));
        p = new Ponto(pxA,0,pzA);
        pontos.push_back(p);
            //glVertex3f(pxA, 0, pzA);

        //----------------------------
        (*normais).push_back(new Ponto(sin((i+1)*alpha),0,cos((i+1)*alpha)));
        (*texturas).push_back(new Ponto(tx2,1,0));
        p = new Ponto(pxD,0,pzD);
        pontos.push_back(p);    
            //glVertex3f(pxD, 0, pzD); //1

        (*normais).push_back(new Ponto(sin((i)*alpha),0,cos((i)*alpha)));
        (*texturas).push_back(new Ponto(tx1,1,0));
        p = new Ponto(pxA,0,pzA);
        pontos.push_back(p); //2


        (*normais).push_back(new Ponto(sin((i)*alpha),0,cos((i)*alpha)));
        (*texturas).push_back(new Ponto(tx1,0.375,0));
        p = new Ponto(pxA,0,pzA);
        pontos.push_back(p);//3


        (*normais).push_back(new Ponto(sin((i+1)*alpha),0,cos((i+1)*alpha)));
        (*texturas).push_back(new Ponto(tx2,0.375,0));
        p = new Ponto(pxD,height,pzD);
        pontos.push_back(p); //4
 

        (*normais).push_back(new Ponto(sin((i+1)*alpha),0,cos((i+1)*alpha)));
        (*texturas).push_back(new Ponto(tx2,1,0));
        p = new Ponto(pxD,height,pzD);
        pontos.push_back(p);//5


            //glVertex3f(pxD, height, pzD);
        (*normais).push_back(new Ponto(sin((i)*alpha),0,cos((i)*alpha)));
        (*texturas).push_back(new Ponto(tx1,0.375,0));
        p = new Ponto(pxA,height,pzA);
        pontos.push_back(p);// 6
            //glVertex3f(pxA, height, pzA);
        //-----------------------------
        (*normais).push_back(new Ponto(0,1,0));
        (*texturas).push_back(new Ponto(0.8125,0.1875,0));
        p = new Ponto(0,height,0);
        pontos.push_back(p);
            //glVertex3f(0, height, 0);
        (*normais).push_back(new Ponto(0,1,0));
        (*texturas).push_back(new Ponto(0.1875 * cos( (i+1) * alpha) + 0.8125,0.1875 * sin( (i+1) * alpha) + 0.1875,0));
        p = new Ponto(pxA,height,pzA);
        pontos.push_back(p);
            //glVertex3f(pxA, height, pzA);
        (*normais).push_back(new Ponto(0,1,0));
        (*texturas).push_back(new Ponto(0.1875 * cos( (i) * alpha) + 0.8125,0.1875 * sin( (i) * alpha) + 0.1875,0));
        p = new Ponto(pxD,height,pzD);
        pontos.push_back(p);
            //glVertex3f(pxD, height, pzD);

        //glEnd();
    }

    return pontos;

}




vector<Ponto*> caixa(float sideX, float sideY, float sideZ, int divisions, vector<Ponto*> * normais, vector<Ponto*> * texturas) {
    const float deltaX = sideX/divisions;           // comprimento do lado de cada divisão em X
    const float deltaY = sideY/divisions;           // comprimento do lado de cada divisão em Y
    const float deltaZ = sideZ/divisions;           // comprimento do lado de cada divisão em Z
    const float maxX = sideX/2, minX = -maxX;       // valor máximo/mínimo que a variável em X pode tomar
    const float maxY = sideY/2, minY = -maxY;       // valor máximo/mínimo que a variável em Y pode tomar
    const float maxZ = sideZ/2, minZ = -maxZ; 

    float texturaX = 0.25f;
    float texturaY = (1.0f/3.0f);


    float xText1 = 0.25f;
    //float xText2 = (sideX+sideZ)/texturaX;
    float xText3 = 0.75f;

    float yText1 = (1.0f/3.0f);
    float yText2 = (1.0f/3.0f);

    float deltaXText = (texturaX)/(float)divisions; 
    float deltaYText = (texturaY)/(float)divisions;
    float deltaZText1 = (texturaX)/(float)divisions; 
    float deltaZText2 = (texturaY)/(float)divisions; 

    Ponto* nX1 = new Ponto(1,0,0);
    Ponto* nX2 = new Ponto(-1,0,0);
    Ponto* nY1 = new Ponto(0,1,0);
    Ponto* nY2 = new Ponto(0,-1,0);
    Ponto* nZ1 = new Ponto(0,0,1);
    Ponto* nZ2 = new Ponto(0,0,-1);

    Ponto* p;
    Ponto* t;
    vector<Ponto*> pontos;
    
    for(int i=0; i<divisions; i++){

        for(int j=0; j<divisions; j++){

            // base
            p = new Ponto(minX + i*deltaX, minY, minZ + j*deltaZ);
            t = new Ponto(xText1 + i*deltaXText, j*deltaZText2 ,0);
            pontos.push_back(p);
            (*normais).push_back(nY2);
            (*texturas).push_back(t);
            p = new Ponto(minX + (i+1)*deltaX, minY, minZ + (j+1)*deltaZ);
            t = new Ponto(xText1 + (i+1)*deltaXText, (j+1)*deltaZText2 ,0);
            pontos.push_back(p);
            (*normais).push_back(nY2);
            (*texturas).push_back(t);
            p = new Ponto(minX + i*deltaX, minY, minZ + (j+1)*deltaZ);
            t = new Ponto(xText1 + i*deltaXText, (j+1)*deltaZText2 ,0);
            pontos.push_back(p);
            (*normais).push_back(nY2);
            (*texturas).push_back(t);
            p = new Ponto(minX + i*deltaX, minY, minZ + j*deltaZ);
            t = new Ponto(xText1 + i*deltaXText, j*deltaZText2 ,0);
            pontos.push_back(p);
            (*normais).push_back(nY2);
            (*texturas).push_back(t);
            p = new Ponto(minX + (i+1)*deltaX, minY, minZ + j*deltaZ);
            t = new Ponto(xText1 + (i+1)*deltaXText, j*deltaZText2 ,0);
            pontos.push_back(p);
            (*normais).push_back(nY2);
            (*texturas).push_back(t);
            p = new Ponto(minX + (i+1)*deltaX, minY, minZ + (j+1)*deltaZ);
            t = new Ponto(xText1 + (i+1)*deltaXText, (j+1)*deltaZText2 ,0);
            pontos.push_back(p);
            (*normais).push_back(nY2);
            (*texturas).push_back(t);

            // topo
            p = new Ponto(minX + i*deltaX, maxY, minZ + j*deltaZ);
            t = new Ponto(xText1 + i*deltaXText, 1-j*deltaZText2 ,0);
            pontos.push_back(p);
            (*normais).push_back(nY1);
            (*texturas).push_back(t);
            p = new Ponto(minX + i*deltaX, maxY, minZ + (j+1)*deltaZ);
            t = new Ponto(xText1 + i*deltaXText, 1-(j+1)*deltaZText2 ,0);
            pontos.push_back(p);
            (*normais).push_back(nY1);
            (*texturas).push_back(t);
            p = new Ponto(minX + (i+1)*deltaX, maxY, minZ + (j+1)*deltaZ);
            t = new Ponto(xText1 + (i+1)*deltaXText, 1-(j+1)*deltaZText2 ,0);
            pontos.push_back(p);
            (*normais).push_back(nY1);
            (*texturas).push_back(t);
            p = new Ponto(minX + i*deltaX, maxY, minZ + j*deltaZ);
            t = new Ponto(xText1 + i*deltaXText, 1-j*deltaZText2 ,0);
            pontos.push_back(p);
            (*normais).push_back(nY1);
            (*texturas).push_back(t);
            p = new Ponto(minX + (i+1)*deltaX, maxY, minZ + (j+1)*deltaZ);
            t = new Ponto(xText1 + (i+1)*deltaXText, 1-(j+1)*deltaZText2 ,0);
            pontos.push_back(p);
            (*normais).push_back(nY1);
            (*texturas).push_back(t);
            p = new Ponto(minX + (i+1)*deltaX, maxY, minZ + j*deltaZ);
            t = new Ponto(xText1 + (i+1)*deltaXText, 1-j*deltaZText2 ,0);
            pontos.push_back(p);
            (*normais).push_back(nY1);
            (*texturas).push_back(t);


            // laterais
            p = new Ponto(minX, minY + i*deltaY, minZ + j*deltaZ);
            t = new Ponto(j*deltaZText1, yText1 + i*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nX2);
            (*texturas).push_back(t);
            p = new Ponto(minX, minY + i*deltaY, minZ + (j+1)*deltaZ);
            t = new Ponto((j+1)*deltaZText1, yText1 + i*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nX2);
            (*texturas).push_back(t);
            p = new Ponto(minX, minY + (i+1)*deltaY, minZ + (j+1)*deltaZ);
            t = new Ponto((j+1)*deltaZText1, yText1 + (i+1)*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nX2);
            (*texturas).push_back(t);
            p = new Ponto(minX, minY + i*deltaY, minZ + j*deltaZ);
            t = new Ponto(j*deltaZText1, yText1 + i*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nX2);
            (*texturas).push_back(t);
            p = new Ponto(minX, minY + (i+1)*deltaY, minZ + (j+1)*deltaZ);
            t = new Ponto((j+1)*deltaZText1, yText1 + (i+1)*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nX2);
            (*texturas).push_back(t);
            p = new Ponto(minX, minY + (i+1)*deltaY, minZ + j*deltaZ);
            t = new Ponto(j*deltaZText1, yText1 + (i+1)*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nX2);
            (*texturas).push_back(t);

            p = new Ponto(maxX, minY + i*deltaY, minZ + j*deltaZ);
            t = new Ponto(xText3 - j*deltaZText1, yText1 + i*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nX1);
            (*texturas).push_back(t);
            p = new Ponto(maxX, minY + (i+1)*deltaY, minZ + j*deltaZ);
            t = new Ponto(xText3 - j*deltaZText1, yText1 + (i+1)*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nX1);
            (*texturas).push_back(t);
            p = new Ponto(maxX, minY + (i+1)*deltaY, minZ + (j+1)*deltaZ);
            t = new Ponto(xText3 - (j+1)*deltaZText1, yText1 + (i+1)*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nX1);
            (*texturas).push_back(t);
            p = new Ponto(maxX, minY + i*deltaY, minZ + j*deltaZ);
            t = new Ponto(xText3 - j*deltaZText1, yText1 + i*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nX1);
            (*texturas).push_back(t);
            p = new Ponto(maxX, minY + (i+1)*deltaY, minZ + (j+1)*deltaZ);
            t = new Ponto(xText3 - (j+1)*deltaZText1, yText1 + (i+1)*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nX1);
            (*texturas).push_back(t);
            p = new Ponto(maxX, minY + i*deltaY, minZ + (j+1)*deltaZ);
            t = new Ponto(xText3 - (j+1)*deltaZText1, yText1 + i*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nX1);
            (*texturas).push_back(t);

            p = new Ponto(minX + j*deltaX, minY + i*deltaY, minZ);
            t = new Ponto(1 - j*deltaXText, yText2 + i*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nZ2);
            (*texturas).push_back(t);
            p = new Ponto(minX + j*deltaX, minY + (i+1)*deltaY, minZ);
            t = new Ponto(1 - j*deltaXText, yText2 + (i+1)*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nZ2);
            (*texturas).push_back(t);
            p = new Ponto(minX + (j+1)*deltaX, minY + (i+1)*deltaY, minZ);
            t = new Ponto(1 - (j+1)*deltaXText, yText2 + (i+1)*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nZ2);
            (*texturas).push_back(t);
            p = new Ponto(minX + j*deltaX, minY + i*deltaY, minZ);
            t = new Ponto(1 - j*deltaXText, yText2 + i*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nZ2);
            (*texturas).push_back(t);
            p = new Ponto(minX + (j+1)*deltaX, minY + (i+1)*deltaY, minZ);
            t = new Ponto(1 - (j+1)*deltaXText, yText2 + (i+1)*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nZ2);
            (*texturas).push_back(t);
            p = new Ponto(minX + (j+1)*deltaX, minY + i*deltaY, minZ);
            t = new Ponto(1 - (j+1)*deltaXText, yText2 + i*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nZ2);
            (*texturas).push_back(t);

            p = new Ponto(minX + j*deltaX, minY + i*deltaY, maxZ);
            t = new Ponto(xText1 + j*deltaXText, yText1 + i*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nZ1);
            (*texturas).push_back(t);
            p = new Ponto(minX + (j+1)*deltaX, minY + i*deltaY, maxZ);
            t = new Ponto(xText1 + (j+1)*deltaXText, yText1 + i*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nZ1);
            (*texturas).push_back(t);
            p = new Ponto(minX + (j+1)*deltaX, minY + (i+1)*deltaY, maxZ);
            t = new Ponto(xText1 + (j+1)*deltaXText, yText1 + (i+1)*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nZ1);
            (*texturas).push_back(t);
            p = new Ponto(minX + j*deltaX, minY + i*deltaY, maxZ);
            t = new Ponto(xText1 + j*deltaXText, yText1 + i*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nZ1);
            (*texturas).push_back(t);
            p = new Ponto(minX + (j+1)*deltaX, minY + (i+1)*deltaY, maxZ);
            t = new Ponto(xText1 + (j+1)*deltaXText, yText1 + (i+1)*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nZ1);
            (*texturas).push_back(t);
            p = new Ponto(minX + j*deltaX, minY + (i+1)*deltaY, maxZ);
            t = new Ponto(xText1 + j*deltaXText, yText1 + (i+1)*deltaYText ,0);
            pontos.push_back(p);
            (*normais).push_back(nZ1);
            (*texturas).push_back(t);
        }
    }
    return pontos;
}


vector<Ponto*> cone(float raio, float altura, int slices,int camadas, vector<Ponto*> *normais,vector<Ponto*> * texturas){


    float angulo = ((2*M_PI)/slices);
    float xA,zA,xP,zP;

    float nY = sqrt( pow(raio,2)+pow(altura,2) );
    nY = nY / camadas;

    Ponto * normalB = new Ponto(0,-1,0);

    Ponto* p;
    vector<Ponto*> pontos;

    float alturaIntermedia = altura / camadas;
    float stacks = (float) camadas;
    float fatias = (float) slices;

    for (int i=0; i < slices;i++) {


        xA = raio * sin(i*angulo);
        zA = raio * cos(i*angulo);


        xP = raio * sin((i+1)*angulo);
        zP = raio * cos((i+1)*angulo);

        
        //texturas.push_back(new Ponto((i/fatias),(j/camadas),0));
        p = new Ponto(0.0f, 0.0f, 0.0f);
        pontos.push_back(p);
        (*normais).push_back(normalB);

        //texturas.push_back(new Ponto((i/fatias),(j/camadas),0));
        p = new Ponto(xP, 0.0f, zP);
        pontos.push_back(p);
        (*normais).push_back(normalB);

        //texturas.push_back(new Ponto((i/fatias),(j/camadas),0));
        p = new Ponto(xA, 0.0f, zA);
        pontos.push_back(p);
        (*normais).push_back(normalB);

        for(int j=0; j < camadas; j++){




            float yA = j*alturaIntermedia;
            float yCima = (j+1)*alturaIntermedia;

            float raioIntermedioCima = raio * ((altura-yCima) /altura);
            float raioIntermedioBaixo = raio * ((altura-yA) /altura);

            xA = raioIntermedioBaixo * sin(i*angulo);
            zA = raioIntermedioBaixo * cos(i*angulo);


            xP = raioIntermedioBaixo * sin((i+1)*angulo);
            zP = raioIntermedioBaixo * cos((i+1)*angulo);

            float xACima = raioIntermedioCima * sin(i*angulo);
            float zACima = raioIntermedioCima * cos(i*angulo);

            float xPCima = raioIntermedioCima * sin((i+1)*angulo);
            float zPCima = raioIntermedioCima * cos((i+1)*angulo);

            (*texturas).push_back(new Ponto((i/fatias),(j/stacks),0));
            p = new Ponto(xA,yA,zA);
            pontos.push_back(p);
            (*normais).push_back(new Ponto(sin(i*angulo),nY,cos(i*angulo)));

            (*texturas).push_back(new Ponto((i/fatias),(j/stacks),0));
            p = new Ponto(xP,yA,zP);
            pontos.push_back(p);
            (*normais).push_back(new Ponto(sin((i+1)*angulo),nY,cos((i+1)*angulo)));

            (*texturas).push_back(new Ponto((i/fatias),(j/stacks),0));
            p = new Ponto(xPCima,yCima,zPCima);
            pontos.push_back(p);
            (*normais).push_back(new Ponto(sin((i+1)*angulo),nY,cos((i+1)*angulo)));

            (*texturas).push_back(new Ponto((i/fatias),(j/stacks),0));
            p = new Ponto(xA,yA,zA);
            pontos.push_back(p);
            (*normais).push_back(new Ponto(sin(i*angulo),nY,cos(i*angulo)));

            (*texturas).push_back(new Ponto((i/fatias),(j/stacks),0));
            p = new Ponto(xPCima,yCima,zPCima);
            pontos.push_back(p);
            (*normais).push_back(new Ponto(sin((i+1)*angulo),nY,cos((i+1)*angulo)));

            (*texturas).push_back(new Ponto((i/fatias),(j/stacks),0));
            p = new Ponto(xACima,yCima,zACima);
            pontos.push_back(p);
            (*normais).push_back(new Ponto(sin(i*angulo),nY,cos(i*angulo)));
        }

    }

    return pontos;

}

vector<Ponto*> esfera(float raio, int fatias, int camadas, vector<Ponto*>* normais, vector<Ponto*>* texturas){

    float alpha = (2*M_PI) / (float) fatias, beta = (M_PI) / (float) camadas;
    float x1, y1, z1, x2, y2, z2, x3, z3, x4,z4;

    vector<Ponto*> pontos;

    for(int i = 0; i<fatias; i++){

        for(int j = 0; j<camadas; j++) {

            y1 = raio * cos(beta*j);

            x1 = raio * sin(beta*j) * sin(alpha*i);
            z1 = raio * sin(beta*j) * cos(alpha*i);

            x2 = raio * sin(beta*j) * sin(alpha * (i+1));
            z2 = raio * sin(beta*j) * cos(alpha * (i+1));

            y2 = raio * cos(beta * (j+1));

            x3 = raio * sin(beta * (j+1)) * sin(alpha*i);
            z3 = raio * sin(beta * (j+1)) * cos(alpha*i);

            x4 = raio * sin(beta * (j+1)) * sin(alpha * (i+1));
            z4 = raio * sin(beta * (j+1)) * cos(alpha * (i+1));

            float tx1 = (float)i / (float) fatias;
            float ty1 = (float)j / (float) camadas;
            ty1=1-ty1;
            float tx2 = (float)(i+1) / (float) fatias;
            float ty2 = (float)(j+1) / (float) camadas;
            ty2=1-ty2;
            Ponto *p = new Ponto(x4, y2, z4);
            Ponto *p1 = new Ponto(x4/raio,y2/raio,z4/raio);
            Ponto *p2 = new Ponto(tx2,ty2,0);

            pontos.push_back(p);
            (*normais).push_back(p1);
            (*texturas).push_back(p2);

            p = new Ponto(x2, y1, z2);
            p1 = new Ponto(x2/raio,y1/raio,z2/raio);
            p2 = new Ponto(tx2,ty1,0);
            
            pontos.push_back(p);
            (*normais).push_back(p1);
            (*texturas).push_back(p2);


            p = new Ponto(x1, y1, z1);
            p1 = new Ponto(x1/raio,y1/raio,z1/raio);
            p2 = new Ponto(tx1,ty1,0);
            
            pontos.push_back(p);
            (*normais).push_back(p1);
            (*texturas).push_back(p2);

            p = new Ponto(x4, y2, z4);
            p1 = new Ponto(x4/raio,y2/raio,z4/raio);
            p2 = new Ponto(tx2,ty2,0);
            
            pontos.push_back(p);
            (*normais).push_back(p1);
            (*texturas).push_back(p2);

            p = new Ponto(x1, y1, z1);
            p1 = new Ponto(x1/raio,y1/raio,z1/raio);
            p2 = new Ponto(tx1,ty1,0);
            
            pontos.push_back(p);
            (*normais).push_back(p1);
            (*texturas).push_back(p2);

            p = new Ponto(x3, y2, z3);
            p1 = new Ponto(x3/raio,y2/raio,z3/raio);
            p2 = new Ponto(tx1,ty2,0);
            
            pontos.push_back(p);
            (*normais).push_back(p1);
            (*texturas).push_back(p2);

        }

    }

    return pontos;

}

vector<Ponto*> plane(float lado, vector<Ponto*> * normais, vector<Ponto*> * texturas){

  float coord = lado/2.0f;
  vector<Ponto*> pontos;
 
    //Plane
    Ponto* t1 = new Ponto(0,0,0);
    Ponto* t2 = new Ponto(0,1,0);
    Ponto* t3 = new Ponto(1,0,0);
    Ponto* t4 = new Ponto(1,1,0);
    Ponto* n = new Ponto(0,0,1);
    
    Ponto *p = new Ponto(-coord, 0.0f, coord);
    pontos.push_back(p);
    (*normais).push_back(n);
    (*texturas).push_back(t2);

    p = new Ponto(coord, 0.0f, -coord);
    pontos.push_back(p);
    (*normais).push_back(n);
    (*texturas).push_back(t3);

    p = new Ponto(-coord, 0.0f, -coord);
    pontos.push_back(p);
    (*normais).push_back(n);
    (*texturas).push_back(t1);

    p = new Ponto(-coord, 0.0f, coord);
    pontos.push_back(p);
    (*normais).push_back(n);    
    (*texturas).push_back(t2);

    p = new Ponto(coord, 0.0f, coord);
    pontos.push_back(p);
    (*normais).push_back(n);
    (*texturas).push_back(t4);

    p = new Ponto(coord, 0.0f, -coord);
    pontos.push_back(p);
    (*normais).push_back(n);
    (*texturas).push_back(t3);

    return pontos;
}




Ponto* crossProduct(Ponto* p1, Ponto* p2){

    float x = p1->getY()*p2->getZ() - p1->getZ()*p2->getY();
    float y = p1->getZ()*p2->getX() - p1->getX()*p2->getZ();
    float z = p1->getX()*p2->getY() - p1->getY()*p2->getX();

    return new Ponto(x,y,z);
}


Ponto* normalize(Ponto* p1) {
    float x = p1->getX(), y = p1->getY(), z = p1->getZ();
    float l = sqrt(x*x + y*y + z*z);

    return new Ponto(x/l, y/l, z/l);
}


Ponto* calculaBezierCurve(float t, Ponto* p1, Ponto* p2, Ponto* p3, Ponto* p4) {

    // valor de t invertido
    float it = 1.0f-t;

    float b0 = t*t*t;
    float b1 = 3*t*t*it;
    float b2 = 3*t*it*it;
    float b3 =  it*it*it;

    float x = b0*p1->getX() + b1*p2->getX() + b2*p3->getX() + b3*p4->getX() ;
    float y = b0*p1->getY() + b1*p2->getY() + b2*p3->getY() + b3*p4->getY() ;
    float z = b0*p1->getZ() + b1*p2->getZ() + b2*p3->getZ() + b3*p4->getZ() ;

    return new Ponto(x,y,z);
}


Ponto* calculaBezierTangente(float t, Ponto* p1, Ponto* p2, Ponto* p3, Ponto* p4) {

    // valor de t invertido
    float it = 1.0f-t;

    float b0 = 3*t*t;
    float b1 = -3*t*t + 6*t*it;
    float b2 = 3*it*it - 6*t*it;
    float b3 =  -3*it*it;

    float x = b0*p1->getX() + b1*p2->getX() + b2*p3->getX() + b3*p4->getX() ;
    float y = b0*p1->getY() + b1*p2->getY() + b2*p3->getY() + b3*p4->getY() ;
    float z = b0*p1->getZ() + b1*p2->getZ() + b2*p3->getZ() + b3*p4->getZ() ;

    return new Ponto(x,y,z);
}


Ponto* calcularBezierNormal(float u,float v, vector<Ponto*> pts_ctrl) {

    Ponto* temp[4];

    // Calcular tangente em U
    temp[0] = calculaBezierTangente(u,pts_ctrl[0],pts_ctrl[1],pts_ctrl[2],pts_ctrl[3]);
    temp[1] = calculaBezierTangente(u,pts_ctrl[4],pts_ctrl[5],pts_ctrl[6],pts_ctrl[7]);
    temp[2] = calculaBezierTangente(u,pts_ctrl[8],pts_ctrl[9],pts_ctrl[10],pts_ctrl[11]);
    temp[3] = calculaBezierTangente(u,pts_ctrl[12],pts_ctrl[13],pts_ctrl[14],pts_ctrl[15]);
    Ponto* p1 = calculaBezierCurve(v,temp[0],temp[1],temp[2],temp[3]);

    // Calcular tangente em V
    temp[0] = calculaBezierCurve(u,pts_ctrl[0],pts_ctrl[1],pts_ctrl[2],pts_ctrl[3]);
    temp[1] = calculaBezierCurve(u,pts_ctrl[4],pts_ctrl[5],pts_ctrl[6],pts_ctrl[7]);
    temp[2] = calculaBezierCurve(u,pts_ctrl[8],pts_ctrl[9],pts_ctrl[10],pts_ctrl[11]);
    temp[3] = calculaBezierCurve(u,pts_ctrl[12],pts_ctrl[13],pts_ctrl[14],pts_ctrl[15]);
    Ponto* p2 = calculaBezierTangente(v,temp[0],temp[1],temp[2],temp[3]);

    return normalize( crossProduct(p1, p2) );
}


Ponto* calculaBezierPatch(float u,float v, vector<Ponto*> pts_ctrl) {

    Ponto* temp[4];

    temp[0] = calculaBezierCurve(u,pts_ctrl[0],pts_ctrl[1],pts_ctrl[2],pts_ctrl[3]);
    temp[1] = calculaBezierCurve(u,pts_ctrl[4],pts_ctrl[5],pts_ctrl[6],pts_ctrl[7]);
    temp[2] = calculaBezierCurve(u,pts_ctrl[8],pts_ctrl[9],pts_ctrl[10],pts_ctrl[11]);
    temp[3] = calculaBezierCurve(u,pts_ctrl[12],pts_ctrl[13],pts_ctrl[14],pts_ctrl[15]);

    return calculaBezierCurve(v,temp[0],temp[1],temp[2],temp[3]);
}


vector<Ponto*> teapot(int divs, Patch* p, vector<Ponto*>* normais, vector<Ponto*>* texturas){

    vector<Ponto*> pontosTeapot;

    vector<vector<int>> indices = p->getIndices();
    vector<Ponto*> pontos = p->getPontos();

    for(int ind=0; ind < (int) indices.size(); ind++) {

        // Gerar pontos de controlo para o patch "ind"
        vector<Ponto*> pontos_controlo;
        for(int pc=0; pc<16; pc++){
            pontos_controlo.push_back(pontos[indices[ind][pc]]);
        }

        for (int i = 0; i < divs; ++i) {

            // calcular o valor do parametro U
            float u1 = (float) i / (divs);
            float u2 = (float) (i + 1) / (divs);

            for (int j = 0; j < divs; ++j) {

                // calcular o valor do parametro U
                float v1 = (float) j / (divs);
                float v2 = (float) (j+1) / (divs);

                // calcular os pontos da superficie
                Ponto* p1 = calculaBezierPatch(u1, v1, pontos_controlo);
                Ponto* p2 = calculaBezierPatch(u1, v2, pontos_controlo);
                Ponto* p3 = calculaBezierPatch(u2, v1, pontos_controlo);
                Ponto* p4 = calculaBezierPatch(u2, v2, pontos_controlo);

                // calcular as normais da superficie
                Ponto* n1 = calcularBezierNormal(u1, v1, pontos_controlo);
                Ponto* n2 = calcularBezierNormal(u1, v2, pontos_controlo);
                Ponto* n3 = calcularBezierNormal(u2, v1, pontos_controlo);
                Ponto* n4 = calcularBezierNormal(u2, v2, pontos_controlo);

                // calcular as texturas da superficie
                Ponto* t1 = new Ponto(u1, v1, 0);
                Ponto* t2 = new Ponto(u1, v2, 0);
                Ponto* t3 = new Ponto(u2, v1, 0);
                Ponto* t4 = new Ponto(u2, v2, 0);

                // inserir os pontos no vetor
                pontosTeapot.push_back(p1);
                pontosTeapot.push_back(p3);
                pontosTeapot.push_back(p4);
                pontosTeapot.push_back(p1);
                pontosTeapot.push_back(p4);
                pontosTeapot.push_back(p2);

                // inserir as normais no vetor
                (*normais).push_back(n1);
                (*normais).push_back(n3);
                (*normais).push_back(n4);
                (*normais).push_back(n1);
                (*normais).push_back(n4);
                (*normais).push_back(n2);

                // inserir as texturas no vetor
                (*texturas).push_back(t1);
                (*texturas).push_back(t3);
                (*texturas).push_back(t4);
                (*texturas).push_back(t1);
                (*texturas).push_back(t4);
                (*texturas).push_back(t2);

            }
        }
    }
    return pontosTeapot;
}


int comparaFigura(string a){

  if(a.compare("plane")==0) return 1;
  if(a.compare("box")==0) return 2;
  if(a.compare("cone")==0) return 3;
  if(a.compare("sphere")==0) return 4;
  if(a.compare("cylinder")==0) return 5;
  if(a.compare("torus")==0) return 6;
  if(a.compare("teapot")==0) return 7;

  return 0;
}

int main (int argc, char** argv) {
  ofstream myfile;
  vector<Ponto*> pontos;
  vector<Ponto*> normais;
  vector<Ponto*> texturas;
  char* nome_ficheiro;

  int aux = comparaFigura(argv[1]);
  switch(aux){
    case 1: {
      nome_ficheiro = argv[3];
      string tam(argv[2]);
      float lado = stof(tam);
      
      if(!(lado > 0)){
          printf("Erro, valor inválido do lado!\n");
          return 1;
        }

      pontos = plane(lado,&normais,&texturas);
      break;
    }

    case 2: {
      nome_ficheiro = argv[6];

      string aux1(argv[2]);
      float ladoX = stof(aux1);

      if(!(ladoX > 0)){
          printf("Erro, valor inválido do lado X!\n");
          return 1;
      }

      string aux2(argv[3]);
      float ladoY = stof(aux2);

      if(!(ladoY > 0)){
          printf("Erro, valor inválido do lado Y!\n");
          return 1;
      }

      string aux3(argv[4]);
      float ladoZ = stof(aux3);

      if(!(ladoZ > 0)){
          printf("Erro, valor inválido do lado Z!\n");
          return 1;
      }

      string aux4(argv[5]);
      int divisoes = stoi(aux4);

      if(!(divisoes > 0)){
          printf("Erro, valor inválido das divisões!\n");
          return 1;
      }

      pontos = caixa(ladoX, ladoY, ladoZ, divisoes,&normais,&texturas);
      break;
    }


    case 3: {
      nome_ficheiro = argv[6];
      string aux(argv[2]);
      float raio = stof(aux);

      if(!(raio > 0)){
          printf("Erro, valor inválido do raio!\n");
          return 1;
      }

      string aux2(argv[3]);
      float altura = stof(aux2);

      if(!(altura > 0)){
          printf("Erro, valor inválido da altura!\n");
          return 1;
      }

      string aux3(argv[4]);
      int fatias = stoi(aux3);

      if(!(fatias > 0)){
          printf("Erro, valor inválido das fatias!\n");
          return 1;
      }

      string aux4(argv[5]);
      int camadas = stoi(aux4);

      if(!(camadas > 0)){
          printf("Erro, valor inválido das camadas!\n");
          return 1;
      }

      pontos = cone(raio,altura,fatias,camadas,&normais,&texturas);
      break;
    }


    case 4:{
      nome_ficheiro = argv[5];

      string raio(argv[2]);
      float r = stof(raio); 

      if(!(r > 0)){
          printf("Erro, valor inválido do raio!\n");
          return 1;
      }

      string fatias(argv[3]);
      int f = stoi(fatias);
  
      if(!(f > 0)){
          printf("Erro, valor inválido das fatias!\n");
          return 1;
      }

      string camadas(argv[4]);
      int c = stoi(camadas);


      if(!(r > 0)){
          printf("Erro, valor inválido das camadas!\n");
          return 1;
      }

      pontos = esfera(r, f, c, &normais, &texturas);
      break;
    }

    case 5: {
      nome_ficheiro = argv[5];
      string aux(argv[2]);
      float raio = stof(aux);

      if(!(raio > 0)){
          printf("Erro, valor inválido do raio!\n");
          return 1;
      }

      string aux2(argv[3]);
      float altura = stof(aux2);

      if(!(altura > 0)){
          printf("Erro, valor inválido da altura!\n");
          return 1;
      }

      string aux3(argv[4]);
      int fatias = stoi(aux3);

      if(!(fatias > 0)){
          printf("Erro, valor inválido das fatias!\n");
          return 1;
      }

      pontos = cilindro(raio,altura,fatias,&normais,&texturas);
      break;
    }

    case 6: {
      nome_ficheiro = argv[6];
      string aux(argv[2]);
      float raioTubo = stof(aux);

      if(!(raioTubo > 0)){
          printf("Erro, valor inválido do raio!\n");
          return 1;
      }

      string aux2(argv[3]);
      float raioAnel = stof(aux2);

      if(!(raioAnel > 0)){
          printf("Erro, valor inválido da altura!\n");
          return 1;
      }

      string aux3(argv[4]);
      int fatias = stoi(aux3);

      if(!(fatias > 0)){
          printf("Erro, valor inválido das fatias!\n");
          return 1;
      }

      string aux4(argv[5]);
      int camadas = stoi(aux4);

      if(!(camadas > 0)){
          printf("Erro, valor inválido das camadas!\n");
          return 1;
      }

      pontos = torus(raioTubo,raioAnel,fatias,camadas,&normais,&texturas);
      break;
    }

    case 7: {
      nome_ficheiro = argv[4];
      string aux(argv[2]);
      float divisoes = stoi(aux);

      if(!(divisoes > 3)){
        printf("Erro, valor inválido de divisões!\n");
        return 1;
      }

      string input(argv[3]);
      Patch* p = extraiPatch(input);

      pontos = teapot(divisoes, p, &normais, &texturas);
      break;
    }

    default: printf("Opção inválida!");return 1; 
  }
  
  myfile.open(nome_ficheiro);

  myfile << pontos.size() << endl;
  for(Ponto* p: pontos){
    
    string escreve = p->toString();
    myfile << escreve << endl;
  }

  myfile << normais.size() << endl;
  for(Ponto* p: normais){

    string escreve = p->toString();
    myfile << escreve << endl;
  }

  myfile << texturas.size() << endl;
  int ki=0;
  for(Ponto* p: texturas){
    
    //cout << "Ind: " << ki << endl;

    if(p->getX()<0){
        cout << "TexX: " << p->getX() << endl;
    }


    if(p->getY()<0){
        cout << "TexY: " << p->getY() << endl;
    }


    if(p->getZ()<0){
        cout << "TexZ: " << p->getZ() << endl;
    }

    string escreve = p->toString();
    myfile << escreve << endl;
    ki++;
  }
  
  myfile.close();

  return 0;
}

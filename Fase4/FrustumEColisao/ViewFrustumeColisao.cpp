#include "ViewFrustumeColisao.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <GL/glut.h>

using namespace std;

ViewFrustumeColisao::ViewFrustumeColisao(){}

ViewFrustumeColisao::ViewFrustumeColisao(boolean e,vector<Ponto*> v,float o){
    esfera=e;

    if(e){
        raio = o;
    }

    else{
        pontosControlo = v;

        raio = sqrt(v.at(0)->getX()^2) + (v.at(0)->getY()^2) + (v.at(0)->getZ()^2);
    }


}

float distancia(float pl[4], float p[4]){

    float res = 0.0f;

    for(int i = 0; i < 4; i++){

        res += pl[i]*p[i];
    }

    return res;
}

void multiplicaMatriz(float p[4], float tg[4][4]){

    float aux[4];

    for(int i=0;i<4;i++){

        float valor = 0.0f;
        for(j=0;j<4;j++){
            valor += p[j]*tg[i][j];
        }

        aux[i] = valor;
    }

    for(int i = 0; i < 4; i++){
        p[i] = aux[i];
    }
}


bool estaDentroEsfera(float planos[6][4], float centro[4]){

        float distance;
        bool result = true;
        for(int i=0; i < 6; i++) {
            distance = distancia(planos[i],centro);
            if (distance < -raio)
                return false;
        }
        return(result);
}

bool estaDentroCaixa(float planos[6][4]){


    for(int i = 0; i < 6; i++){

        int p[3] = {0,0,0,1};
        p[0] = coordenadas[1];
        p[1] = coordenadas[3];
        p[2] = coordenadas[5];

        if (planos[i][0] >= 0)
            p[0] = coordenadas[0];

        if (planos[i][1] >=0)
            p[1] = coordenadas[2];

        if (planos[i][2] >= 0)
            p[2] = coordenadas[4];

        float distance = distancia(planos[i],p);

        if(p < 0) {
            return false;
        }

    }

    return true;

}

void ViewFrustumeColisao::atualizaCoordenadas(float pontos[8][4]){

    for(int i = 0; i < 3; i++){
        coordenadas[i] = pontos[0][i];
        coordenadas[i+1] = pontos[0][i];
    }

    for(int i = 1; i < 8; i++){

        for(j = 0; j < 3; j++){

            if(coordenadas[j] < pontos[i][j]){
                coordenadas[j] = pontos[i][j];
            }

            else{
                if(coordenadas[j+1] > pontos[i][j]){
                    coordenadas[j+1] = pontos[i][j];
                }
            }
        }
    }

}

bool ViewFrustumeColisao::estaDentro(float[6][4] planos){

    float[16] tg;

    glGetFloatv(GL_MODELVIEW_MATRIX,tg);

    if(esfera){
        float centro[4] = {0,0,0,1};
        multiplicaMatriz(centro,tg);

        return estaDentroEsfera(planos,centro);
    }

    else{

        float pontos[8][4];
        for(int i = 0; i<8; i++){
            pontos[i][0] = pontosControlo.at(i)->getX();
            pontos[i][1] = pontosControlo.at(i)->getY();
            pontos[i][2] = pontosControlo.at(i)->getZ();
            pontos[i][3] = 1.0f;
        }

        for(int i = 0; i < 8; i++){

            multiplicaMatriz(pontos[i],tg);
        }

        this->atualizaCoordenadas(pontos);

        estaDentroCaixa(planos);

    }
}

bool ViewFrustumeColisao::possoMover(float pY,float pX,float pZ,float r){
    return true;
}

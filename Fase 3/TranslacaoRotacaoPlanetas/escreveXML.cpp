#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <cstdlib>
#include <ctime>
using namespace std;


#define RAIO_SOL 6.963
#define RAIO_MER 0.314
#define RAIO_VEN 0.645
#define RAIO_TER 0.688
#define RAIO_MAR 0.437
#define RAIO_JUP 2.984
#define RAIO_SAT 2.614
#define RAIO_URA 1.528
#define RAIO_NEP 1.448
#define DIST_MER 2.781
#define DIST_VEN 4.733
#define DIST_TER 7.483
#define DIST_MAR 11.263
#define DIST_JUP 25.477
#define DIST_SAT 39.676
#define DIST_URA 55.167
#define DIST_NEP 71.925
#define DIST_FOG 69

#define MAXROTACAO 31
#define	PONTOS_TRANS 10


ofstream ficheiro;

void criaSol(string separador){
	ficheiro << separador << "<!--SOL-->" << endl;
// Inicio do grupo
	ficheiro << separador << "<group>" << endl;
//Transformacoes geometricas
	ficheiro << separador << "\t" << "<scale X=\"" << RAIO_SOL << "\" Y=\"" << RAIO_SOL << "\" Z=\"" << RAIO_SOL << "\" />" << endl;
//Modelos
	ficheiro << separador << "\t" << "<models>" << endl;
	ficheiro << separador << "\t\t" << "<model file = \"esfera.3d\"/>" << endl;
	ficheiro << separador << "\t" << "</models>" << endl;
// Fim do grupo
	ficheiro << separador << "</group>" << endl;
}

void criaMercurio(string separador){
	ficheiro << separador << "<!--MERCURIO-->" << endl;
// Inicio do grupo
	ficheiro << separador << "<group>" << endl;
//Translação
	ficheiro << separador << "\t" << "<translate time=\"" << 40 << "\">"  << endl;
	float x,z;
	float alpha = 2*M_PI / PONTOS_TRANS;
	float raio = RAIO_SOL+DIST_MER;
	for(int i=0; i<10; i++){
		x = cos(alpha*i) * raio;
		z = sin(alpha*i) * raio;
		ficheiro << separador << "\t\t" << "<point X=\"" << x << "\" Y=\"" << 0 << "\" Z=\"" << z << "\" />"  << endl;
	}
	ficheiro << separador << "\t" << "</translate>" << endl;
//Rotação em torno de si proprio
	ficheiro << separador << "\t" << "<rotate time=\"" << 100 << "\" axisX=\"" << 0 << "\" axisY=\"" << 1 << "\" axisZ=\"" << 0 << "\" />" << endl;
//Transformacoes geometricas
	//ficheiro << separador << "\t" << "<translate X=\"" << (RAIO_SOL+DIST_MER) << "\" Y=\"" << 0 << "\" Z=\"" << 0 << "\" />" << endl;
	ficheiro << separador << "\t" << "<scale X=\"" << RAIO_MER << "\" Y=\"" << RAIO_MER << "\" Z=\"" << RAIO_MER << "\" />" << endl;
//Modelos
	ficheiro << separador << "\t" << "<models>" << endl;
	ficheiro << separador << "\t\t" << "<model file = \"esfera.3d\"/>" << endl;
	ficheiro << separador << "\t" << "</models>" << endl;
// Fim do grupo
	ficheiro << separador << "</group>" << endl;
}

void criaVenus(string separador){
	ficheiro << separador << "<!--VENUS-->" << endl;
// Inicio do grupo
	ficheiro << separador << "<group>" << endl;
//Translaçao
	ficheiro << separador << "\t" << "<translate time=\"" << 50 << "\">"  << endl;
	float x,z;
	float alpha = 2*M_PI / PONTOS_TRANS;
	float raio = RAIO_SOL+DIST_VEN;
	for(int i=0; i<10; i++){
		x = cos(alpha*i) * raio;
		z = sin(alpha*i) * raio;
		ficheiro << separador << "\t\t" << "<point X=\"" << x << "\" Y=\"" << 0 << "\" Z=\"" << z << "\" />"  << endl;
	}
	ficheiro << separador << "\t" << "</translate>" << endl;

	int angulo = rand() % MAXROTACAO; //angulo de rotacao aleatorio entre 0 e 30
//Rotação em torno de si proprio
	ficheiro << separador << "\t" << "<rotate time=\"" << 411.684 << "\" axisX=\"" << 0 << "\" axisY=\"" << 1 << "\" axisZ=\"" << 0 << "\" />" << endl;

//Transformacoes geometricas
	ficheiro << separador << "\t" << "<rotate angle=\"" << angulo << "\" axisX=\"" << 0 << "\" axisY=\"" << 1 << "\" axisZ=\"" << 0 << "\" />" << endl;
	//ficheiro << separador << "\t" << "<translate X=\"" << (RAIO_SOL+DIST_VEN) << "\" Y=\"" << 0 << "\" Z=\"" << 0 << "\" />" << endl;
	ficheiro << separador << "\t" << "<scale X=\"" << RAIO_VEN << "\" Y=\"" << RAIO_VEN << "\" Z=\"" << RAIO_VEN << "\" />" << endl;
//Modelos
	ficheiro << separador << "\t" << "<models>" << endl;
	ficheiro << separador << "\t\t" << "<model file = \"esfera.3d\"/>" << endl;
	ficheiro << separador << "\t" << "</models>" << endl;
// Fim do grupo
	ficheiro << separador << "</group>" << endl;
}


void criaTerra(string separador){
	ficheiro << separador << "<!--TERRA-->" << endl;
// Inicio do grupo
	ficheiro << separador << "<group>" << endl;
//Translaçao
	ficheiro << separador << "\t" << "<translate time=\"" << 60 << "\">"  << endl;
	float x,z;
	float alpha = 2*M_PI / PONTOS_TRANS;
	float raio = RAIO_SOL+DIST_TER;
	for(int i=0; i<10; i++){
		x = cos(alpha*i) * raio;
		z = sin(alpha*i) * raio;
		ficheiro << separador << "\t\t" << "<point X=\"" << x << "\" Y=\"" << 0 << "\" Z=\"" << z << "\" />"  << endl;
	}
	ficheiro << separador << "\t" << "</translate>" << endl;

//Rotação em torno de si proprio
	ficheiro << separador << "\t" << "<rotate time=\"" << 1 << "\" axisX=\"" << 0 << "\" axisY=\"" << 1 << "\" axisZ=\"" << 0 << "\" />" << endl;

//Transformacoes geometricas
	//ficheiro << separador << "\t" << "<translate X=\"" << (RAIO_SOL+DIST_TER) << "\" Y=\"" << 0 << "\" Z=\"" << 0 << "\" />" << endl;
	ficheiro << separador << "\t" << "<scale X=\"" << RAIO_TER << "\" Y=\"" << RAIO_TER << "\" Z=\"" << RAIO_TER << "\" />" << endl;
//Modelos
	ficheiro << separador << "\t" << "<models>" << endl;
	ficheiro << separador << "\t\t" << "<model file = \"esfera.3d\"/>" << endl;
	ficheiro << separador << "\t" << "</models>" << endl;
// Fim do grupo
	ficheiro << separador << "</group>" << endl;
}

void criaMarte(string separador){
	ficheiro << separador << "<!--MARTE-->" << endl;
// Inicio do grupo
	ficheiro << separador << "<group>" << endl;

//Translaçao
	ficheiro << separador << "\t" << "<translate time=\"" << 90 << "\">"  << endl;
	float x,z;
	float alpha = 2*M_PI / PONTOS_TRANS;
	float raio = RAIO_SOL+DIST_MAR;
	for(int i=0; i<10; i++){
		x = cos(alpha*i) * raio;
		z = sin(alpha*i) * raio;
		ficheiro << separador << "\t\t" << "<point X=\"" << x << "\" Y=\"" << 0 << "\" Z=\"" << z << "\" />"  << endl;
	}
	ficheiro << separador << "\t" << "</translate>" << endl;

	int angulo = rand() % MAXROTACAO; //angulo de rotacao aleatorio entre 0 e 30

//Rotação em torno de si proprio
	ficheiro << separador << "\t" << "<rotate time=\"" << 1.1 << "\" axisX=\"" << 0 << "\" axisY=\"" << 1 << "\" axisZ=\"" << 0 << "\" />" << endl;

//Transformacoes geometricas
	ficheiro << separador << "\t" << "<rotate angle=\"" << angulo << "\" axisX=\"" << 0 << "\" axisY=\"" << 1 << "\" axisZ=\"" << 0 << "\" />" << endl;
	//ficheiro << separador << "\t" << "<translate X=\"" << (RAIO_SOL+DIST_MAR) << "\" Y=\"" << 0 << "\" Z=\"" << 0 << "\" />" << endl;
	ficheiro << separador << "\t" << "<scale X=\"" << RAIO_MAR << "\" Y=\"" << RAIO_MAR << "\" Z=\"" << RAIO_MAR << "\" />" << endl;
//Modelos
	ficheiro << separador << "\t" << "<models>" << endl;
	ficheiro << separador << "\t\t" << "<model file = \"esfera.3d\"/>" << endl;
	ficheiro << separador << "\t" << "</models>" << endl;
// Fim do grupo
	ficheiro << separador << "</group>" << endl;
}

void criaCintura(string separador){

    float r = 21.0;
    float alpha;
    float rr;
    float dim;
    float x,y,z;

    srand(31457);
    int meteoros = 0;
    float angulo =  100 / 582;

    ficheiro << separador << "<!--CINTURA-->" << endl;
// Inicio do grupo
	ficheiro << separador << "<group>" << endl;
//Transformacoes geometricas
	ficheiro << separador << "\t" << "<rotate angle=\"" << angulo << "\" X=\"" << 0 << "\" Y=\"" << 1 << "\" Z=\"" << 0 << "\" />" << endl;
	
    while (meteoros < 1000) {

        rr = rand() * 3.0/ RAND_MAX;
        alpha = rand() * 6.28 / RAND_MAX;
        dim = 0.02 + rand() * 0.04 / RAND_MAX;

        x = cos(alpha) * (rr + r);
        y = -1 + rand() * 2.0 / RAND_MAX;
        z = sin(alpha) * (rr + r);

        ficheiro << separador << "\t" << "<!--ASTEROIDE-->" << endl;
		// Inicio do grupo
			ficheiro << separador << "\t" << "<group>" << endl;
		//Transformacoes geometricas
			ficheiro << separador << "\t\t" << "<translate X=\"" << x << "\" Y=\"" << y << "\" Z=\"" << z << "\" />" << endl;
			ficheiro << separador << "\t\t" << "<scale X=\"" << dim << "\" Y=\"" << dim << "\" Z=\"" << dim << "\" />" << endl;
		//Modelos
		ficheiro << separador << "\t\t" << "<models>" << endl;
		ficheiro << separador << "\t\t\t" << "<model file = \"esferaAsteroide.3d\"/>" << endl;
		ficheiro << separador << "\t\t" << "</models>" << endl;

		ficheiro << separador << "\t" << "</group>" << endl;
        meteoros++;
    }

    ficheiro << separador << "</group>" << endl;
}

void criaJupiter(string separador){
	ficheiro << separador << "<!--JUPITER-->" << endl;
// Inicio do grupo
	ficheiro << separador << "<group>" << endl;
//Translaçao
	ficheiro << separador << "\t" << "<translate time=\"" << 150 << "\">"  << endl;
	float x,z;
	float alpha = 2*M_PI / PONTOS_TRANS;
	float raio = RAIO_SOL+DIST_JUP;
	for(int i=0; i<10; i++){
		x = cos(alpha*i) * raio;
		z = sin(alpha*i) * raio;
		ficheiro << separador << "\t\t" << "<point X=\"" << x << "\" Y=\"" << 0 << "\" Z=\"" << z << "\" />"  << endl;
	}
	ficheiro << separador << "\t" << "</translate>" << endl;
//Rotação em torno de si proprio
	ficheiro << separador << "\t" << "<rotate time=\"" << 0.41667 << "\" axisX=\"" << 0 << "\" axisY=\"" << 1 << "\" axisZ=\"" << 0 << "\" />" << endl;

//Transformacoes geometricas
	//ficheiro << separador << "\t" << "<translate X=\"" << (RAIO_SOL+DIST_JUP) << "\" Y=\"" << 0 << "\" Z=\"" << 0 << "\" />" << endl;
	ficheiro << separador << "\t" << "<scale X=\"" << RAIO_JUP << "\" Y=\"" << RAIO_JUP << "\" Z=\"" << RAIO_JUP << "\" />" << endl;
//Modelos
	ficheiro << separador << "\t" << "<models>" << endl;
	ficheiro << separador << "\t\t" << "<model file = \"esfera.3d\"/>" << endl;
	ficheiro << separador << "\t" << "</models>" << endl;
// Fim do grupo
	ficheiro << separador << "</group>" << endl;
}


void criaAneisSaturno(string separador){
	ficheiro << separador << "<!--ANEIS_SATURNO-->" << endl;
// Inicio do grupo
	ficheiro << separador << "<group>" << endl;

//Transformacoes geometricas
	ficheiro << separador << "\t" << "<rotate angle=\"" << 120 << "\" axisX=\"" << 1 << "\" axisY=\"" << 0.25 << "\" axisZ=\"" << 0.25 << "\" />" << endl;
	ficheiro << separador << "\t" << "<scale X=\"" << 1 << "\" Y=\"" << 1 << "\" Z=\"" << 0.01 << "\" />" << endl;
//Modelos
	ficheiro << separador << "\t" << "<models>" << endl;
	ficheiro << separador << "\t\t" << "<model file = \"torus.3d\"/>" << endl;
	ficheiro << separador << "\t" << "</models>" << endl;
// Fim do grupo
	ficheiro << separador << "</group>" << endl;
}

void criaSaturno(string separador){
	ficheiro << separador << "<!--SATURNO-->" << endl;
// Inicio do grupo
	ficheiro << separador << "<group>" << endl;
//Translação
	ficheiro << separador << "\t" << "<translate time=\"" << 200 << "\">"  << endl;
	float x,z;
	float alpha = 2*M_PI / PONTOS_TRANS;
	float raio = RAIO_SOL+DIST_SAT;
	for(int i=0; i<10; i++){
		x = cos(alpha*i) * raio;
		z = sin(alpha*i) * raio;
		ficheiro << separador << "\t\t" << "<point X=\"" << x << "\" Y=\"" << 0 << "\" Z=\"" << z << "\" />"  << endl;
	}
	ficheiro << separador << "\t" << "</translate>" << endl;
//Transformacoes geometricas

	ficheiro << separador << "\t" << "<rotate angle=\"" << 10 << "\" axisX=\"" << 0 << "\" axisY=\"" << 1 << "\" axisZ=\"" << 0 << "\" />" << endl;
	//ficheiro << separador << "\t" << "<translate X=\"" << (RAIO_SOL+DIST_SAT) << "\" Y=\"" << 0 << "\" Z=\"" << 0 << "\" />" << endl;
	//PRECISEI DE CRIAR UM NOVO GRUPO SO PARA RODAR SATURNO
	ficheiro << separador << "<group>" << endl;
//Rotação em torno de si proprio
	ficheiro << separador << "\t" << "<rotate time=\"" << 411.684 << "\" axisX=\"" << 0 << "\" axisY=\"" << 1 << "\" axisZ=\"" << 0 << "\" />" << endl;

	ficheiro << separador << "\t" << "<scale X=\"" << RAIO_SAT << "\" Y=\"" << RAIO_SAT << "\" Z=\"" << RAIO_SAT << "\" />" << endl;
//Modelos
	ficheiro << separador << "\t" << "<models>" << endl;
	ficheiro << separador << "\t\t" << "<model file = \"esfera.3d\"/>" << endl;
	ficheiro << separador << "\t" << "</models>" << endl;
	ficheiro << separador << "</group>" << endl;
	criaAneisSaturno(separador + "\t");
// Fim do grupo
	ficheiro << separador << "</group>" << endl;
}


void criaUrano(string separador){
	ficheiro << separador << "<!--URANO-->" << endl;
// Inicio do grupo
	ficheiro << separador << "<group>" << endl;
//Translação
	ficheiro << separador << "\t" << "<translate time=\"" << 225 << "\">"  << endl;
	float x,z;
	float alpha = 2*M_PI / PONTOS_TRANS;
	float raio = RAIO_SOL+DIST_URA;
	for(int i=0; i<10; i++){
		x = cos(alpha*i) * raio;
		z = sin(alpha*i) * raio;
		ficheiro << separador << "\t\t" << "<point X=\"" << x << "\" Y=\"" << 0 << "\" Z=\"" << z << "\" />"  << endl;
	}
	ficheiro << separador << "\t" << "</translate>" << endl;

	int angulo = rand() % MAXROTACAO; //angulo de rotacao aleatorio entre 0 e 30
//Rotação em torno de si proprio
	ficheiro << separador << "\t" << "<rotate time=\"" << 2/3 << "\" axisX=\"" << 0 << "\" axisY=\"" << 1 << "\" axisZ=\"" << 0 << "\" />" << endl;

//Transformacoes geometricas
	ficheiro << separador << "\t" << "<rotate angle=\"" << angulo << "\" axisX=\"" << 0 << "\" axisY=\"" << 1 << "\" axisZ=\"" << 0 << "\" />" << endl;
	//ficheiro << separador << "\t" << "<translate X=\"" << (RAIO_SOL+DIST_URA) << "\" Y=\"" << 0 << "\" Z=\"" << 0 << "\" />" << endl;
	ficheiro << separador << "\t" << "<scale X=\"" << RAIO_URA << "\" Y=\"" << RAIO_URA << "\" Z=\"" << RAIO_URA << "\" />" << endl;
//Modelos
	ficheiro << separador << "\t" << "<models>" << endl;
	ficheiro << separador << "\t\t" << "<model file = \"esfera.3d\"/>" << endl;
	ficheiro << separador << "\t" << "</models>" << endl;
// Fim do grupo
	ficheiro << separador << "</group>" << endl;
}

void criaNeptuno(string separador){
	ficheiro << separador << "<!--NEPTUNO-->" << endl;
// Inicio do grupo
	ficheiro << separador << "<group>" << endl;
//translaçao
	ficheiro << separador << "\t" << "<translate time=\"" << 250 << "\">"  << endl;
	float x,z;
	float alpha = 2*M_PI / PONTOS_TRANS;
	float raio = RAIO_SOL+DIST_NEP;
	for(int i=0; i<10; i++){
		x = cos(alpha*i) * raio;
		z = sin(alpha*i) * raio;
		ficheiro << separador << "\t\t" << "<point X=\"" << x << "\" Y=\"" << 0 << "\" Z=\"" << z << "\" />"  << endl;
	}
	ficheiro << separador << "\t" << "</translate>" << endl;
//Rotação em torno de si proprio
	ficheiro << separador << "\t" << "<rotate time=\"" << 0.5 << "\" axisX=\"" << 0 << "\" axisY=\"" << 1 << "\" axisZ=\"" << 0 << "\" />" << endl;


	int angulo = rand() % MAXROTACAO; //angulo de rotacao aleatorio entre 0 e 30

//Transformacoes geometricas
	ficheiro << separador << "\t" << "<rotate angle=\"" << angulo << "\" axisX=\"" << 0 << "\" axisY=\"" << 1 << "\" axisZ=\"" << 0 << "\" />" << endl;
	ficheiro << separador << "\t" << "<translate X=\"" << (RAIO_SOL+DIST_NEP) << "\" Y=\"" << 0 << "\" Z=\"" << 0 << "\" />" << endl;
	ficheiro << separador << "\t" << "<scale X=\"" << RAIO_NEP << "\" Y=\"" << RAIO_NEP << "\" Z=\"" << RAIO_NEP << "\" />" << endl;
//Modelos
	ficheiro << separador << "\t" << "<models>" << endl;
	ficheiro << separador << "\t\t" << "<model file = \"esfera.3d\"/>" << endl;
	ficheiro << separador << "\t" << "</models>" << endl;
// Fim do grupo
	ficheiro << separador << "</group>" << endl;
}

void criaFoguetao(string separador){
	ficheiro << separador << "<!--Foguetao-->" << endl;
// Inicio do grupo
	ficheiro << separador << "<group>" << endl;
	ficheiro << separador << "\t" << "<translate X=\"" << DIST_FOG << "\" Y=\"0\" Z=\"0\" />" << endl;
	ficheiro << separador << "\t" << "<scale X=\"0.8\" Y=\"0.8\" Z=\"0.8\" />" << endl;
    ficheiro << separador << "\t<models>" << endl;
    ficheiro << separador << "\t\t<model file=\"cilindro.3d\" />" << endl;
    //drawCylinder(raio, altura, 100);
    ficheiro << separador << "\t</models>" << endl;
    //glPushMatrix();
    ficheiro << separador << "\t<group>" << endl;
    ficheiro << separador << "\t\t<translate X=\"0\" Y=\"1\" Z=\"0\" />" << endl;
    ficheiro << separador << "\t" << "<scale X=\"0.8\" Y=\"0.8\" Z=\"0.8\" />" << endl;
    //glTranslatef(0, altura, 0);
    ficheiro << separador << "\t\t<models>" << endl;
    ficheiro << separador << "\t\t\t<model file=\"cone.3d\" />" << endl;
    //drawCone(raio, altura/4, 100, 100);
    ficheiro << separador << "\t\t</models>" << endl;
    ficheiro << separador << "\t</group>" << endl;
    //glPopMatrix();

    int alpha = 360/4;
    for(int i = 0; i<4; i++){
        //glPushMatrix();
        ficheiro << separador << "\t<group>" << endl;
        //assumindo que o raio do cilindro será 1
        ficheiro << separador << "\t\t\t<translate X=\"0\" Y=\"0.25\" Z=\"0\" />" << endl;
        ficheiro << separador << "\t\t<rotate angle=\"" << i*alpha << "\" axisX=\"0\" axisY=\"1\" axisZ=\"0\" />" << endl;
        //glTranslatef(0,raio/4,0);
        //glRotatef(i*alpha,0,1,0);
        ficheiro << separador << "\t\t<group>" << endl;
        ficheiro << separador << "\t\t\t<translate X=\"0.4\" Y=\"0\" Z=\"0\" />" << endl;
        //glTranslatef(raio,0,0);
        ficheiro << separador << "\t\t\t<rotate angle=\"-135\" axisX=\"0\" axisY=\"0\" axisZ=\"1\" />" << endl;
        //glRotatef(-135,0,0,1);
        ficheiro << separador << "\t" << "<scale X=\"0.3\" Y=\"0.7\" Z=\"0.3\" />" << endl;
        ficheiro << separador << "\t\t\t<models>" << endl;
        ficheiro << separador << "\t\t\t\t<model file=\"cone.3d\" />" << endl;
        //drawCone(raio/4, altura/2, 10, 10);
        ficheiro << separador << "\t\t\t</models>" << endl;
        ficheiro << separador << "\t\t</group>" << endl;
        ficheiro << separador << "\t</group>" << endl;
        //glPopMatrix();

    }

    ficheiro << separador << "</group>" << endl;
}


void criaFicheiro(){
	ficheiro << "<scene>" << endl;

	ficheiro << "\t<group>" << endl;

	string separador = "\t\t";
	criaSol(separador);
	criaMercurio(separador);
	criaVenus(separador);
	criaTerra(separador);
	criaMarte(separador);
	criaCintura(separador);
	criaJupiter(separador);
	criaSaturno(separador);
	criaUrano(separador);
	criaNeptuno(separador);
	criaFoguetao(separador);

	ficheiro << "\t</group>" << endl;

	ficheiro << "</scene>" << endl;

}

int main(){
	
	ficheiro.open("sistema_solar.xml");

 	srand(time(NULL));

	criaFicheiro();

	ficheiro.close();

}

#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace tinyxml2;
using namespace std;

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

Figura extraiFicheiro(string filename){
	Figura *figura = new Figura();

	ifstream inputFileStream(filename);

	int count;
    inputFileStream>>count;

    cout << count << endl;

	string line;
    getline(inputFileStream, line);

    cout << line << endl;

    for(int i=0;i<count;i++){
    	getline(inputFileStream, line);
    	cout << line << endl;
    	stringstream ss(line);
    	vector<int> numbers;

    	for(int k = 0; k < 3; k++) {
    		string aux;
    		ss >> aux; 
    		float j = stof(aux);
        	numbers.push_back(j);
        	cout << aux << " ";
        	cout << "" << endl;
    	}

    	Ponto *p = new Ponto(numbers.get(0),numbers.get(1),numbers.get(2));
    	figura->adicionaPonto(p);

    }

    return figura;

    // cout << line << endl;
}


vector<Figura> parseFile(){
	std::cout << "Passei 0\n";
	XMLDocument xmlDoc;
	XMLError eResult = xmlDoc.LoadFile("../Modelos.xml");
	std::cout << "Passei 1\n";
	XMLCheckResult(eResult);


	std::cout << "Passei 2\n";
	XMLNode * pRoot = xmlDoc.FirstChild();
	if (pRoot == nullptr); //return XML_ERROR_FILE_READ_ERROR;


	std::cout << "Passei 3\n";

	vector<Figura> figuras;

	XMLElement * pElement = pRoot->FirstChildElement("model");
	if (pElement == nullptr); //return XML_ERROR_PARSING_ELEMENT;

	while (pListElement != nullptr){

		const char* cenas = pElement->Attribute("file");
		if (cenas == nullptr);// return XML_ERROR_PARSING_ATTRIBUTE;


		std::cout << cenas << std::endl;

		string fich(cenas, strlen(cenas));


		Figura f = extraiFicheiro(fich);
		figuras.push_back(f);

		pElement = pListElement->NextSiblingElement("model");
	
	}

	return figuras;
}

int main(){

	parseFile();
}
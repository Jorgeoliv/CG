#include "tinyxml2.h"
#include <iostream>

using namespace tinyxml2;

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif


tinyxml2::XMLError parseFile(){
	std::cout << "Passei 0\n";
	XMLDocument xmlDoc;
	XMLError eResult = xmlDoc.LoadFile("Modelos.xml");
	std::cout << "Passei 1\n";
	XMLCheckResult(eResult);


	std::cout << "Passei 2\n";
	XMLNode * pRoot = xmlDoc.FirstChild();
	if (pRoot == nullptr) return XML_ERROR_FILE_READ_ERROR;


	std::cout << "Passei 3\n";

	XMLElement * pElement = pRoot->FirstChildElement("model");
	if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

	const char* cenas = pElement->Attribute("file");
	if (cenas == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;


	std::cout << cenas << std::endl;

}

int main(){

	parseFile();
}
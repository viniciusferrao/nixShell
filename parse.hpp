/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Simone Markenson
 * Linguagens de Programação - Turma 2009/1
 * Authors: 
 * -> Vinicius Figueiredo Ferrao
 * -> Victor Dabarian
 * -> Diego Santos Wanderley
 * Description: Header da Classe Parse
 */

#ifndef __PARSE_HPP__
#define __PARSE_HPP__

#include <iostream>
#include <string>
#include <sstream>

#include "const.hpp"

using namespace std;

class parseCommand {
	
private:
	char *parsedCommands[MAX_COMMAND_LENGTH];

public:
	//Dummy do construtor
	parseCommand();
	
	//Funções da classe
	char* convertStringToCharPointer(string, bool);
	char** splitString(string, bool);
	
};

#endif

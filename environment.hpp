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
 * Description: Header da Classe Environment
 */

#ifndef __ENVIRONMENT_HPP__
#define __ENVIRONMENT_HPP__

#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

using namespace std;

class environmentVariables {
	
private:
	struct passwd *pw;

public:
	//Dummy do construtor
	environmentVariables();
	
	//Funções da classe
	string getUsername();
	string getFullDirectoryPath();
	string getDirectoryName();
	
};

#endif

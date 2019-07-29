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
 * Description: Implementação da Classe Environment
 */

#include "environment.hpp"

//Dummy do construtor
environmentVariables::environmentVariables () {
	
}

//Apenas serve para pegar o nome de usuario de forma bonitinha
string environmentVariables::getUsername() {
	uid_t uid = getuid();
	pw = getpwuid(uid);

	return pw->pw_name;
}

//Bacalhau tenso que rolou aqui... não sei como usar a getcwd() com as strings do C++
string environmentVariables::getFullDirectoryPath() {
	char *directory;
	directory = (char*) malloc(sizeof(char)*255);
	directory = getcwd(directory,255);

	return static_cast<string>(directory);
}
	
//A ideia é procurar pela ultima barra e subtrair toda a string antes desta barra.
string environmentVariables::getDirectoryName() {
	size_t lastSlashPosition;
	lastSlashPosition = getFullDirectoryPath().find_last_of("/\\");

	return getFullDirectoryPath().substr(lastSlashPosition+1);
}

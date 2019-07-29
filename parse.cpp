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
 * Description: Implementação da Classe Parse
 */

#include "parse.hpp"

parseCommand::parseCommand() {
	
}

//Metodo que converte um string para char pointeiro
char* parseCommand::convertStringToCharPointer(string input, bool verbose) {
	char *convertedCommand;
	
	convertedCommand = static_cast<char*>(malloc(sizeof(char)*MAX_COMMAND_LENGTH));
	strcpy(convertedCommand, const_cast<char*>(input.c_str()));
	
	if (verbose) {
		cout << "Converteu: " << convertedCommand << endl;
	}
	
	return convertedCommand;
}

//Converte a string para char pointeiro já toda separada para alimentar o execvp();
char** parseCommand::splitString(string command, bool verbose) {
	int counter = 0;
	
	istringstream iss(command);
	
	do {
		string substring;
		iss >> substring;

		if (verbose) {
			cout << "Substring: " << substring << " -> ";
		}
		
		parsedCommands[counter++] = convertStringToCharPointer(substring, verbose);
		
	} while (iss);
	parsedCommands[--counter] = NULL;
	
	return parsedCommands;
}

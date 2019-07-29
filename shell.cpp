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
 * Description:
 * -> C++ Shell
 * -> Programa principal com função main();
 */

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

//Legacy C headers ou headers para sistemas não-POSIX (a.k.a Linux)
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

//Include de headers auxiliares
#include "error.hpp"
#include "const.hpp"

//Include das classes
#include "environment.hpp"
#include "parse.hpp"

using namespace std;

int main (int argc, char **argv) {
	bool verbose = false;

	//Laço de controle dos argumentos de entrada pela linha de comando
	if (argc > MAX_ARGS) {
		cout << "Número inválido de argumentos de execução" << endl;
		exit (INVALID_ARGUMENTS);
	}
	
	if (argv[1] != NULL) {
		string argument(argv[1]);
		if ((argument.compare("-v") == 0) || (argument.compare("--verbose") == 0)) {
			cout << "Modo verbose ativo." << endl;
			verbose = true;
		} else {
			cout << "Argumento inválido." << endl;
			exit (INVALID_ARGUMENTS);
		}
	}
	
	if (verbose) {
		cout << "Entrando no ambiente " << SHELL_NAME << "..." << endl;
	}
	
	//Classe que trata de todas as variaveis de ambiente
	environmentVariables myEnvironmentVariables;
	
	//String que vai guardar a entrada do usuario
	string command;

	//Laço de repetição do shell.
	while ((command.compare(CMD_EXIT)) != 0) {
		//Controle de processos filhos, caso exista algum processo zombie, este será destruido.
		int estado;
		pid_t pid; 
		if ((pid = waitpid(-1, &estado, WNOHANG)) > 0) {
			if (verbose) {
				cout << "Processo " << pid << " destruido!" << endl;
			}
		} else {
			if (verbose) {
				cout << "Nenhum processo filho destruido!" << endl;
			}
		}
		
		cout << SHELL_NAME << ":" << myEnvironmentVariables.getDirectoryName() << " " << myEnvironmentVariables.getUsername() << "$ ";
		getline(cin, command);
		
		//Halt no laço caso o usuário tenha dado apenas um enter no shell ou colocado apenas o comando de background
		if (command.length() == 0 || command.compare(CMD_BACKGROUND) == 0) {
			continue;
		}

		//Check do & para inicialização de processo em background e remoção do mesmo
		bool background = false;		
		if (command.find_last_of(CMD_BACKGROUND) == command.length()-1) {
			if (verbose) {
				cout << "Possível habilitador de modo background encontrado." << endl;
				cout << "Posição: " << command.find_last_of(CMD_BACKGROUND) << " | Comprimento: " << command.length() << endl; 
			}
			background = true;
			if (verbose) {
				cout << "Removendo & do commando:" << endl;
				cout << "Comando: " << command << " | "; 
			}
			command.erase(command.length()-1);
			if (verbose) {
				cout << "Removido: " << command << "." <<endl;
			}
		}

		//Inicio do parse da entrada feita pelo usuário
		parseCommand myParser;
		char **splittedCommands;
		
		//Alocação de memoria para a conversão do parser
		splittedCommands = static_cast<char**>(malloc(sizeof(char)*MAX_COMMAND_LENGTH));
		
		//Finalmente, nosso parser mágico
		splittedCommands = myParser.splitString(command, verbose);

		if (verbose) {
			cout << "Saí da classe de parse!" << endl;
		}
		
		//Verificação do comnando cd para mudar de diretorio
		if (splittedCommands[0] != NULL) {
			string check(splittedCommands[0]);
			if (check.compare("cd") == 0) {
				chdir(splittedCommands[1]);
				if (verbose) {
					cout << "Chamada chdir(); efetuada." << endl;
				}
				continue;
			}
		}
		
		//Execução das chamadas no filesystem
		if ((pid = fork()) == -1) {
			cerr << "Erro #" << errno << " na função fork(): " << strerror(errno) << endl;
		} else {
			if (pid == 0) {
				if (background == true) {
					cout << endl << splittedCommands[0] << ": rodando em background." << endl;
				}
				if (verbose) {
					cout << "Eu cheguei na execvp(); e meu PID é: " << getpid() << endl;
				}
				execvp(splittedCommands[0], splittedCommands);
				if (verbose) {
					cout << "Passei batido pela execvp(); vou finalizar com return " << OK << "." << endl;
				}
				return OK;
			} else {
				if (background == false)
					waitpid(pid, &estado, 0);
			}
		}
					
		//Liberar a memoria do splittedCommands;
		delete [] *splittedCommands;
	
	}
	
	if (verbose) {
		cout << "Saindo do ambiente " << SHELL_NAME << "." << endl;
	}
	
	return OK;

}

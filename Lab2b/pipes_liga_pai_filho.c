#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

//Para executar este programa, basta compilá-lo por linha de comando (gcc -o pipes_liga_pai_filho pipes_liga_pai_filho.c) e depois executá-lo utilizando o comando ./pipes_liga_pai_filho

int value = 5;

int main()
{
  pid_t pid;
	int fds[2]; 
	pipe(fds); 


	pid = fork();

	if (pid == 0) {
		printf("Entrei no filho!\n");
		value += 15;
		write(fds[1], &value, 2); 
		printf ("CHILD: value = %d\n",value); 
		return 0;
	}
	else if (pid > 0) 
    wait(NULL);
		read(fds[0], value,2); 
		printf ("PARENT: value = %d\n",value);
		return 0;
	}
}

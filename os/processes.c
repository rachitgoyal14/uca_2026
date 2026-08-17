#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	
	pid_t pid = fork();
	
	if (pid == 0) {
		printf("\n");
		// this code is being executed by the child process
		printf("In Child Process\n");
		// getppid => get parent process ID
		printf("ID of Parent Process: %d\n", getppid());
		// getpid => process ID of child process
		printf("ID of Child Process: %d\n", getpid());

	}
	
	else {
		// this code is being run by the parent process
		// pid => process ID of the child given to the parent process
		printf("\n");
		printf("\nIn Parent Process\n");
		printf("Process ID of the child: %d\n", pid);
		// getpid => prints the process ID of the parent
		printf("Process ID of the parent: %d\n", getpid());
		sleep(5);
	}

	return 0;
}

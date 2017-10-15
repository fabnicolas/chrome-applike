#include <stdlib.h>		// Standard library.
#include <stdio.h>		// Standard I/O support.
#include <sys/stat.h>	// Chmod.
#include <sys/wait.h>	// Wait.
#include <unistd.h>		// Fork, execl.

int main(void){
	char* shell_file = "./generated_linux_runtime.sh";		// Temporary name for shell to execute Chrome.
	const char *shell_code = "#!/bin/sh\n"					// It's a shell file.
	"google-chrome"											// The process name.
	" --app=http://finalgalaxy.github.io/vistriker-FE/"		// Link to website to render as app.
	" --force-app-mode"										// Force Chrome in app mode.
	" --hide-scrollbars"									// Additional flag for app mode.
	"&";													// Detach process when invoked.


	FILE *f = fopen(shell_file, "w");	// Open in write mode.
	if(f == NULL){
	    printf("Error generating file.\n");
	    exit(1);
	}
	fprintf(f, "%s", shell_code);	// Write shell code in a temporary .sh.
	fclose(f);
	printf("Launching application...\n");
	pid_t pid;
	if((pid=fork())==0){
    	chmod(shell_file, strtol("0777",0,8));				// Make .sh executable.
		execl("/bin/bash", "bash", shell_file, (char*)0);	// Launch .sh.
	}
	wait(NULL);		// Wait for child to finish...
	printf("Application launched, terminal is closing.\n");
	unlink(shell_file);		// Remove temporary .sh once app is started.
	exit(0);
}

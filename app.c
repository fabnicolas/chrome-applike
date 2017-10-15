#include <stdlib.h>		// Standard library.
#include <stdio.h>		// Standard I/O support.
#include <sys/stat.h>	// Chmod.
#include <unistd.h>		// Fork, execl.

#ifdef linux
#include <sys/wait.h>	// Wait (Linux-only).
#endif

int main(void){
	char* shell_file;		// Temporary name for shell to execute Chrome.
	const char *shell_code; // Shell batch/bash code.

	#ifdef _WIN32
		shell_file = "generated_windows_runtime.bat";			// Windows BAT file.
		shell_code = "@echo off\n"	// Don't show what BAT executes as commands.
		"SET URL=http://finalgalaxy.github.io/vistriker-FE/\n"	// Website link.
		"FOR /F \"skip=2 tokens=2,*\" %%A IN ('REG QUERY \"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\chrome.exe\" /v Path') DO SET CHROMEPATH=%%B\n"	// Try to detect from Windows Registry where C is installed and save it in CHROMEPATH variable.
		"\"%CHROMEPATH%/chrome\" --app=%URL% --force-app-mode --hide-scrollbars";	// Execute Chrome through CHROMEPATH variable.
	#endif

	#ifdef linux
		shell_file = "./generated_linux_runtime.sh";			// Linux BASH file.
		shell_code = "#!/bin/sh\n"								// It's a bash shell file.
		"google-chrome"											// The process name.
		" --app=http://finalgalaxy.github.io/vistriker-FE/"		// Website link.
		" --force-app-mode"										// Force Chrome in app mode.
		" --hide-scrollbars"									// Additional flag for app mode.
		"&";
	#endif

	FILE *f = fopen(shell_file, "w");	// Create shell file (so open it in write mode).
	if(f == NULL){
	    printf("Error generating file.\n");
	    exit(1);
	}
	fprintf(f, "%s", shell_code);	// Write shell code in a temporary script file.
	fclose(f);
	printf("Launching application...\n");

	#ifdef _WIN32
		system(shell_file);	// Just execute the BAT file.
	#endif

	#ifdef linux
		pid_t pid;
		if((pid=fork())==0){
			chmod(shell_file, strtol("0777",0,8));				// Make .sh executable.
			execl("/bin/bash", "bash", shell_file, (char*)0);	// Launch .sh.
		}
		wait(NULL);		// Wait for child to finish...
	#endif

	printf("Application launched.\n");
	unlink(shell_file);		// Remove temporary shell file once app is started.
	exit(0);
}

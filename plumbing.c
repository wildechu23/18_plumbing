#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <string.h>

#define READ 0
#define WRITE 1

int main() {
	int ptoc[2];
	int ctop[2];
	pipe(ptoc);
	pipe(ctop);

	int f;
	f = fork();

	if(f) {
		//p
		close(ptoc[READ]);
		close(ctop[WRITE]);
		
		char buffer[100];
		while(fgets(buffer, sizeof(buffer), stdin)) {
			char s[100];
			write(ptoc[WRITE], buffer, sizeof(buffer));
			read(ctop[READ], s, sizeof(s));
            
			printf("%s\n", s);
		}
	} else {
		//c
		close(ctop[READ]);
		close(ptoc[WRITE]);
		char s[100];
		while(read(ptoc[READ], s, sizeof(s))) {
			s[strlen(s)-1] = '\0';
            strcat(s, "<3");
            s[strlen(s)] = '\0';
            //printf("%s\n", s);
			write(ctop[WRITE], s, strlen(s)+1);
			s[0] = '\0';
		}
	}

	return 0;	
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv){
	int in_Fd, out_Fd, file_Flags;
	char *buffer = malloc(100*sizeof(char));
	memset(buffer,'\0',sizeof(buffer));
	if(argc>1&&argc<=3){
		if((in_Fd=open(argv[1], O_RDONLY))<0){
			perror("Open Copy");
			exit(1);
		}
		if((out_Fd=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC))<0){
			perror("Open Write");
                        exit(1);
		}
		
		while(read(in_Fd, buffer, 1)){
			if(*buffer!='\0'){
				lseek(out_Fd, lseek(in_Fd, 0, SEEK_CUR)-1, SEEK_SET);
				write(out_Fd, buffer, 1);
			}
		}
		free(buffer);
		close(in_Fd);
		close(out_Fd);		
	}else{
	}	
	return(EXIT_SUCCESS);
}

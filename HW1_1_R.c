#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //read，write......
#include <errno.h> //error
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> //open....
int main(int argc, char* argv[]){
	char *buffer = (char *)malloc(100 * sizeof(char)); //buffer for input
	memset(buffer, '\0', sizeof(buffer)); //initial to buffer		
	int file_Flags, has_Option, fd, c;
	if(argc>=1&&argc<=3){ //standard input
		if(argc>=2){ // file assigned
			has_Option = 1;
			file_Flags = O_WRONLY|O_CREAT|O_TRUNC; //file operation
			while((c=getopt(argc,argv,"a"))!=-1){
				if(c=='a')
					file_Flags = O_WRONLY|O_CREAT|O_APPEND;
				break;
			}
			fd = open (argv[argc-1], file_Flags);
		}
		while(read(0, buffer, 1)){
			write(1, buffer, sizeof(buffer));
			if(has_Option){
				write(fd, buffer, sizeof(buffer));
			}
		}
		free(buffer);
		close(fd);
	} else{ //non-standard input(Length error) 
	}
	//輸入錯誤及檔案例外錯誤未處理
	return (EXIT_SUCCESS);		
}

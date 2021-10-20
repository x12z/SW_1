#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> //DATA TYPES
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h> //DIR STRUCTER
#include <errno.h>  //ERRNO
#include <pwd.h> //PASSWORD FILE OPERATION
#include <ctype.h>
#define PROC_DIR "/proc"
uid_t userIdFromName(const char *name){
	struct passwd *pwd;
	if (name == NULL || *name =='\0'){ //WRONG_INPUT
		fprintf(stdout, "Wrong Name Input!\n");	
		exit(-1);
	}
	if ((pwd = getpwnam(name)) == NULL){
		if (errno == 0){
			fprintf(stdout, "%s : Not Found!\n", name);
			exit(-1);
		}else{
			perror("getpwnam: ");
			exit(-1);
		}
	}
	return pwd->pw_uid;
}
void search(char *file, uid_t uid){
	char *buffer = (char *)malloc(255  * sizeof(char));
	memset(buffer, '\0', 255);
	char *show_info = (char *)malloc(255  * sizeof(char));
	memset(show_info, '\0', 255);
	int is_User = 0;
	char *key=NULL, *value=NULL;
	FILE *ptr;
	if ((ptr=fopen(file, "r")) == NULL){
		return;
	}
	while (fgets(buffer, 255, ptr)!= NULL){
		key = strtok(buffer, ":");
		value = strtok(NULL, "");
		if (key!=NULL && value!=NULL){
			if (strcmp(key, "Uid") == 0){
				char *temp = (char *)malloc(255  * sizeof(char));
				memset(temp, '\0', 255);
				temp = strtok(value, "\t");
				if (temp != NULL){
					if (uid == atoi(temp)){
						is_User = 1;
					}
				}
				
			}
			if (strcmp(key, "Name") == 0)
				strcpy(show_info, value);
			if (strcmp(key, "Pid") == 0)
				strcat(show_info, value);
		}
		
	}
	if (is_User)
		fprintf(stdout, "%s", show_info);
	free(show_info);
	free(buffer);
	exit(0);
}

int main(int argc, char **argv){
	uid_t uid;
	DIR *dir_ptr;
	struct dirent *entry;
	char *dir_trace = (char *)malloc(255  * sizeof(char));
	memset(dir_trace, '\0',255);
	if (argc!= 2){
		fprintf(stdout, "Usage: %s <username>\n",argv[0]);
		exit(1);
	}	
	uid = userIdFromName(argv[1]);
	if ((dir_ptr=opendir(PROC_DIR)) == NULL){
		perror("Opendir: ");
		exit(1);
	}
	if (chdir(PROC_DIR) == -1){
		perror("Chdir: ");
		exit(1);
	}
	while ((entry = readdir(dir_ptr))!=NULL){  //searching for /proc
		if (entry->d_type == DT_DIR){  //file_type is director
			if (strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0){
				continue;
			}
			strcpy(dir_trace, PROC_DIR);
			strcat(dir_trace, "/");
			strcat(dir_trace, entry->d_name);  //trace dir with /proc/director
			strcat(dir_trace, "/status");
			search(dir_trace, uid);
		}
	}
	return(EXIT_SUCCESS);
}

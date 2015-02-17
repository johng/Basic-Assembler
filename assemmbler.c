#include <stdio.h>
#include <stdlib.h>

char* readline(char * line){
	
	char *output;
	output = (char *)malloc(8);

	if(*line == ';' ){

		return NULL;
	}
	
	if(*line == ':'){

	}

	//If not ':' or ';' split string into tokens

	char *token = strtok(line," ");

	if(token == "INC"){


	}else if(token == "DEC"){

	}else if(token == "JNZ"){


	}else if(token == "JNEG"){


	}else if(token == "STR"){

	}else if(token == "LDR"){


	}

	

	return line;
}

int main(int argc, char *argv[]){
	
	if(argc<1){
		printf("No arguments!\n");
		return 1;
	}
	// Reading the assembly file
	FILE *ptr_file;
	FILE *out_file;	

	ptr_file = fopen(*argv[1],"r");
	
	out_file = fopen("out.txt","w");
	
	if(!ptr_file || !out_file){
		return 1;
	}

	char buff[4096];
	while( fgets(buff,sizeof buff,ptr_file) != NULL){	
		
		fprintf(out_file, readline(buff));
		
	
	}

	fclose(ptr_file);
	fclose(out_file);
	
	return -1;

}

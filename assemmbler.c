#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binaryToInt(char * input){
	char * ptr;
	ptr = input;
	
	int out = 0;
	int mult = 1;
	while(*ptr!='\0'){
		
		if(*ptr == '1'){
			out += mult;
		}

		mult *= 2;
		++ptr;


	}
	return out;

}

char *strrev(char * str){

	char * p1, *p2;
	if(! str || ! *str){
		return str;
	}

	for(p1 = str,p2 =str+strlen(str) -1;p2 > p1; ++p1, --p2){
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}

	return str;

}

char* readline(FILE *out, char * line){
	
	

	int b0 = 0;
	int b1 = 0;
	if(*line == ';' ){

		return NULL;
	}
	
	if(*line == ':'){
		printf("change");
	
	}

	//If not ':' or ';' split string into tokens

	char *token;
	char s[2] = " ";
	size_t len = sizeof(line);
	char local[len+1];
	strcpy(local,line);
	token = strtok(local, s);	
	
	
	if(!strcmp(token,"INC")){
		
		b1 = 0;
		b0 = strtok(NULL," ")[1] - '0';
	
	}else if(!strcmp(token,"DEC")){
	
		b1 = 0;
		b0 = 2 + strtok(NULL, " ")[1] - '0';

	}else if(!strcmp(token,"JNZ")){
		b0 = 4;
		
		token = strtok (NULL, " ");
		if(*token == ':'){
		}else{
			b1 = strtol(token, NULL, 10);
		}
		

	}else if(!strcmp(token,"JNEG")){
	
		b0 = 6;
		token = strtok(NULL, " ");
		
		if(*token == ':'){

		}else{
			b1 = strtol(token, NULL, 10);
		}

	}else if(!strcmp(token,"STR")){
		
		b0 = 8 + *strtok(NULL, " ") - '0';
		token = strtok(NULL," ");
		if(*token == ':'){
		}else{
			b1 = strtol(token, NULL,10);
		}
	}else if(!strcmp(token,"LDR")){
		
		b0 = 10 + *strtok(NULL, " ") - '0';

		token = strtok(NULL, " ");
		
		if(*token == ':'){
		}else{
			b1 = strtol(token, NULL, 10);
		}
	
	}

	fprintf(out,"%x%x\n",b0,b1);

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

	ptr_file = fopen(argv[1],"r");
	
	out_file = fopen("out.txt","w");
	
	if(!ptr_file || !out_file){
		printf("Exit bad files");
		return 1;
	}

	char buff[4096];
	
	while( fgets(buff,sizeof buff,ptr_file) != NULL){		
		readline(out_file,buff);
	}
	
	fclose(ptr_file);
	fclose(out_file);
	
	return -1;
}

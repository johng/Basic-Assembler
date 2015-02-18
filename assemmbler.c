#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct label {
	int address;
	char * name;
	struct label * next;
}label;

void insertLabel(label ** insert, char * line, int n);

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

}
/*
	Debug function to print the contents of a label linked list
	to the terminal
*/
void printLabelList(label * root){
	if(root != NULL){
		printf("Address: %d Name: %s\n",root->address,root->name);
		printLabelList(root->next);
	}
}

/*
	Generates a linked list of labels
*/
void labelGenerator(char * line, int * n,label ** root){
	
	if(*line != ':'){
		if(*line != ';'){
			*n=*n+1;
		}
		return;
	}


	char * ptr;
	ptr = line;
	ptr++;

	insertLabel(root,ptr,*n);
}

/*
	Inserts entry into linked list of labels.
	If label is already present in the linked list the 
	insert operation will stop. 
*/
void insertLabel(label ** insert, char * line, int n){
	
	if(*insert == NULL){
	
		*insert  = (label *) malloc (sizeof(label));
		
		(*insert)->name = (char*)malloc(sizeof(line));
		strcpy((*insert)->name,line);
		(*insert)->address = n;
		(*insert)->next = NULL;
		
	}else{
		
		if( !strcmp((*insert)->name, line)){
			return;
		}else {
			insertLabel(&(*insert)->next,line,n);
		}
	}
}

/*
	Finds the address of a label from a given name
	If no address is found, return -1;
*/
int getAddress(char * name,label * list){
	char *ptr;
	ptr = name;
	if(*ptr == ':'){
		ptr++;
	}

	if(list!=NULL){
		if(!strcmp(list->name,ptr)){
			return list->address;
		}else{
			return getAddress(ptr,list->next);
		}
	}
	//End condition if nothing found at end of the list
	return -1;
}

void readline(FILE *out, char * line,label * addressList){
	
	

	int b0 = 0;
	int b1 = 0;
	if(*line == ';'){
		return ;
	}
	
	if(*line == ':'){
		return ;
	
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
			b1 = getAddress(token,addressList);
		}else{
			b1 = strtol(token, NULL, 10);
		}
		

	}else if(!strcmp(token,"JNEG")){
	
		b0 = 6;
		token = strtok(NULL, " ");
		
		if(*token == ':'){
			b1 = getAddress(token,addressList);
		}else{
			b1 = strtol(token, NULL, 10);
		}

	}else if(!strcmp(token,"STR")){
		
		b0 = 8 + *strtok(NULL, " ") - '0';
		token = strtok(NULL," ");
		if(*token == ':'){
			b1 = getAddress(token,addressList);
		}else{
			b1 = strtol(token, NULL,10);
		}
	}else if(!strcmp(token,"LDR")){
		
		b0 = 10 + *strtok(NULL, " ") - '0';

		token = strtok(NULL, " ");
		
		if(*token == ':'){
			b1 = getAddress(token,addressList);
		}else{
			b1 = strtol(token, NULL, 10);
		}
	
	}

	fprintf(out,"%x%x\n",b0,b1);

	return ;
}

int main(int argc, char *argv[]){

	if(argc<1){
		printf("No arguments!\n");
		return 1;
	}
	
	// Reading the assembly file
	FILE *ptr_file;
	FILE *out_file;

	label * root;
	root = NULL;

	ptr_file = fopen(argv[1],"r");
	
	out_file = fopen("out.txt","w");
	
	if(!ptr_file || !out_file){
		printf("Exit bad files");
		return 1;
	}

	char buff[4096];
	int n = 0;	
	while (fgets(buff,sizeof buff,ptr_file)!=NULL){
		labelGenerator(buff,&n,&root);
	}

	//Start at the top of file, ready for re reading;
	fseek(ptr_file,0,SEEK_SET);
	
	printLabelList(root);

	while( fgets(buff,sizeof buff,ptr_file) != NULL){		
		readline(out_file,buff,root);
	}

	
	fclose(ptr_file);
	fclose(out_file);
	
	return -1;
}

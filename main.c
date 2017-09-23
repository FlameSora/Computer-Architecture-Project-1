#include<stdio.h>


int main(int argc, char* argv[]){
	
	int i=0;
	FILE *file;
	char * line = NULL;
	size_t len = 0;
	ssize_t read; 
//	char * pch;		
	printf("%d\n",argc);

	for( i; i<argc ;i++){
		printf("%s",argv[i]);

	}
	
	file = fopen("example1.s","r");

	if(file == NULL) {
		printf("error");
	}

//	new_str = strcat("./Project1_examples/example1.s")
	printf("%c",argv[1][1]);	
	file = fopen("./Project1_examples/example1.s","r");
	if(file){
		printf("in \n");
		while ((read = getline(&line, &len,file))!=-1){
		//	printf("len is: %zu \n ",len);
			printf("Retrieved line of length %zu :\n",read);
			printf("%s",line);
		//	pch = strtok(line," ");
		//	printf("%s", pch);
		//	putchar(c);
		}
		fclose(file);
	}	
//	if (line)
//		free(line);

	printf("Hello World! \n");
	return 0;
}


#include<stdio.h>
#include<string.h>

int main(int argc, char* argv[]){
	
	int i=0;
	FILE *file;
	char * line = NULL;
	size_t len = 0;
	ssize_t read; 
	char * pch;
	int j=0;	
	char buf[1000];
	char *array[5];
	printf("%d\n",argc);

	for( i; i<argc ;i++){
		printf("%s",argv[i]);

	}
	
	file = fopen("example1.s","r");

	if(file == NULL) {
		printf("cannot read the file");
	}	
	file = fopen(argv[1],"r");
	if(file){
		while((read = getline(&line, &len,file))!=-1){
	//	while(!feof(file)){
		//	fgets(buf,1000,file);
			puts(line);
			pch = strtok(line,"\t ");
			printf("%s\n",pch);
			pch = strtok(NULL,"\t ");	
			while(pch!=NULL){
				printf("%s\n",pch);
				pch = strtok(NULL,"\t ");
			}
		}
		fclose(file);
	}
	
	printf("Hello World! \n");
	return 0;
}


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
	int num_data=-1;
	int checker=0;
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
			printf("line is: %s",line);
			pch = strtok(line,"\t ");
			printf("%s\n",pch);
		//	for (i = 0; i<strlen(pch);i++){
		//		printf("%d is : %c\n",i,pch[i]);
		//	}
		//	printf("pch length is: %zu\n",strlen(pch));
			printf("strcmp value is: %d\n",strcmp(pch,".data\n"));
			printf("strcmp value with text is: %d\n", strcmp(pch,".text\n"));
			if(strcmp(pch, ".data\n")==0){
				checker= 1;
			}
			if(strcmp(pch, ".text\n")==0){
				checker = 0;
			}
			if(checker ==1){
				num_data = num_data +1;	
			}
			pch = strtok(NULL,"\t ");	
			while(pch!=NULL){
				
				printf("%s\n",pch);
				pch = strtok(NULL,"\t ");
			}
		}
		fclose(file);
	}
	printf("%d\n",deciTobin(num_data*4));	
	printf("Hello World! \n");
	return 0;
}

int deciTobin(int deci){
	int binary=0;
	int counter=1;
	int remainder;
	while (deci!=0){
		remainder = deci%2;
		deci = deci/2;
		binary = binary + (remainder*counter);
		counter = counter*10;
	}
	return binary;
}





#include<stdio.h>


int main(int argc, char* argv[]){
	
	int i;
	FILE *file;
	char c;	
	printf("%d\n",argc);

	for( i; i<argc ;i++){
		printf("%s",argv[1]);

	}
		
	file = fopen(argv[1],"r");
	if(file){
		printf("in \n");
		while ((c = fgetc(file))!=EOF){
			printf("%c",c);
			putchar(c);
		}
		fclose(file);

	}
/*	if(file){
		while((c = getc(file))!=EOF)
			putchar(c);
		fclose(file);
	}
*/		
	printf("Hello World! \n");
	return 0;
}


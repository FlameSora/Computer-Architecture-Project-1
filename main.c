#include<stdio.h>


int main(int argc, char* argv[]){
	
<<<<<<< HEAD
	int i = 0;
=======
	int i=0;
>>>>>>> eeba7e9ff0c3304861e8684441cadfc92e9ba181
	FILE *file;
	char c;
		
	printf("%d\n",argc);

	for( i; i<argc ;i++){
		printf("%s",argv[i]);

	}
<<<<<<< HEAD
		
	file = fopen("example1.s","r");

	if(file == NULL) {
		printf("error");
	}

=======
//	new_str = strcat("./Project1_examples/example1.s")
	printf("%c",argv[1][1]);	
	file = fopen("./Project1_examples/example1.s","r");
>>>>>>> eeba7e9ff0c3304861e8684441cadfc92e9ba181
	if(file){
		printf("in \n");
		while ((c = fgetc(file))!=EOF){
			printf("%c",c);
		//	putchar(c);
		}
		fclose(file);

<<<<<<< HEAD
	}	

=======
	}
>>>>>>> eeba7e9ff0c3304861e8684441cadfc92e9ba181
	printf("Hello World! \n");
	return 0;
}


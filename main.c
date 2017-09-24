#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
	FILE *file;
	char * line = NULL;
	size_t len = 0;
	ssize_t read; 
	char *pch;	
	char *data[10];
	int dataidx = 0;
	int num_data=-1;
	int num_text=0;
	int checker=0;
	char* lineToBinary(char * line);
	file = fopen(argv[1],"r");
	if(file){
		while((read = getline(&line, &len,file))!=-1){
			printf("line is: %s",line);
			lineToBinary(line);
			pch = strtok(line,"\t ");
			printf("%s\n",pch);
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
			pch = strtok(NULL,"\n\t ,");

			if (checker == 0 && pch != NULL) {
				num_text = num_text + 1;
			}
			while(pch!=NULL){
				
				if (!strncmp(pch, ".word", 4)) {
					printf("I came in\n");
					pch = strtok(NULL,"\n\t ,");
					data[dataidx] = (char *)malloc(32);
					strcpy(data[dataidx],pch);
					printf("testing %c\n",data[dataidx][0]);
					printf("1: %d\n", dataidx);
					printf("2: %s\n", data[dataidx]);
					printf("3: %s\n", pch);
					dataidx++;
				}
				else {
				pch = strtok(NULL,"\n\t ,");
				}
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
int biLengthCal(int a){
	if(a==0)
		return 0;
	else if(a <10)
		return 1;
	else if(a<100)
		return 2;
	else if(a<1000)
		return 3;
	else if(a<10000)
		return 4;
	else if(a<100000)
		return 5;
}

char * hexto6bin(char* hex){
	int length;
	char *Binary = malloc(32);
	int j;
	char str[4];
	char temp;
	for(j=0;j<6;j++){
		Binary[j] = '0';
	}
	strcat(Binary,'123123');
	strcat(Binary,'999');
	printf("binary: %s\n",Binary);
	length = strlen(hex);
	for (j =0; j<length; j++){
		if(hex[j]=='0'){
			Binary

	return Binary;		
}	



char * makeRType(char *op, int rd, int rs, int rt, char* hex){
		char *Binary = malloc(32);
		int deciTobin(int deci);
		int length;
		char str[5];
		int i;
		int j;
		for(j=0;j<32;j++){
			Binary[j] = '0';
		}
		for(i =0;i<6;i++){
			Binary[i] = op[i];
		}
		for(i=6;i<11;i++){
			sprintf(str, "%d",deciTobin(rs));
			printf("str is: %s\n",str);
			length = biLengthCal(deciTobin(rs));
			if((10 - i - (5 - length))>=0){
				Binary[i+(5-length)] = str[i-6]; 
			}
		}
		for(i=11;i<16;i++){
			sprintf(str,"%d",deciTobin(rt));
			printf("str is: %s\n",str);
			length = biLengthCal(deciTobin(rt));
			if((15-i-(5-length))>=0){
				printf("%d, in loop\n",length);
				Binary[i+(5-length)] = str[i-11];
			}
		}
		for(i=16;i<21;i++){
			sprintf(str,"%d",deciTobin(rd));
			length = biLengthCal(deciTobin(rd));
			if((20 - i - (5-length))>=0){
				Binary[i+(5-length)] = str[i-16];
			}
		}
		for(i=21;i<26;i++){
			Binary[i] = '0';
		}
		for(i=26; i<32;i++){
			Binary[i] = hex[i-26];
		}
		return Binary;

}

char * makeIType(char *op, int rt, int rs, char * imm){
		char *Binary = malloc(32);
		int deciTobin(int deci);
		int length;
		char str[5];
		int i;
		int j;
		for(j=0;j<32;j++){
			Binary[j] = '0';
		}
		for(i =0;i<6;i++){
			Binary[i] = op[i];
		}
		for(i=6;i<11;i++){
			sprintf(str, "%d",deciTobin(rs));
			printf("str is: %s\n",str);
			length = biLengthCal(deciTobin(rs));
			if((10 - i - (5 - length))>=0){
				Binary[i+(5-length)] = str[i-6]; 
			}
		}
		for(i=11;i<16;i++){
			sprintf(str,"%d",deciTobin(rt));
			length = biLengthCal(deciTobin(rt));
			if((15-i-(5-length))>=0){
				Binary[i+(5-length)] = str[i-11];
			}
		}
		for(i=16;i<32;i++){
			Binary[i] = imm[i-16];
		}
}
		

char * makeJType(char *op, char*jTarget){
		char *Binary = malloc(32);
		int deciTobin(int deci);
		int i;
		int j;
		for(j=0;j<32;j++){
			Binary[j] = '0';
		}
		for(i =0;i<6;i++){
			Binary[i] = op[i];
		}
		for(i = 6;i<32;i++){
			Binary[i] = jTarget[i-6];
		}
}
		
char *lineToBinary(char * line){
	printf("in line");
	char * data[10];
	char *Binary=malloc(32);;
	int j;
	for(j =0;j<32;j++){
		Binary[j] = '0';
	}
	int index = 0;
	char *pch;
	int i;
	char str[5];
	int deciTobin(int deci);
	int length; 
	printf("in function \n");
	pch = strtok(line,"\n\t $");
	printf("pch is: %s\n",pch);
	data[index] = (char *)malloc(32);
	strcpy(data[index],pch);
	index++;
	pch = strtok(NULL,"\n\t $,");
	while (pch!=NULL){
		data[index] = (char *)malloc(32);
		strcpy(data[index],pch);
		pch = strtok(NULL,"\n\t $,");
		index++;
	}
	
	if(strcmp(data[0],"addiu")==0){
		printf("addiu in\n");
		printf("testing: %c\n",Binary[3]);
	}
	else if(strcmp(data[0],"addu")==0){
	}
	
	else if(strcmp(data[0],"and")==0){
		Binary = makeRType("000000",17,17,5,"999999");
		printf("testing hextobin 2b: %s\n",hexto6bin("2b"));			
	
	}

	else if(strcmp(data[0],"andi")==0){
	}
	else if(strcmp(data[0],"beq")==0){
	}
 
	else if(strcmp(data[0],"bne")==0){
	}
	else if(strcmp(data[0],"j")==0){
	}
	else if(strcmp(data[0],"jal")==0){
	}
	else if(strcmp(data[0],"jr")==0){
	}
	else if(strcmp(data[0],"lui")==0){
	}
	else if(strcmp(data[0],"lw")==0){
	}
	else if(strcmp(data[0],"la")==0){
	}
	else if(strcmp(data[0],"nor")==0){
	}
	else if(strcmp(data[0],"or")==0){
	}
	else if(strcmp(data[0],"ori")==0){
	}
	else if(strcmp(data[0],"sltiu")==0){
	}
	else if(strcmp(data[0],"sltu")==0){
	}
	else if(strcmp(data[0],"sll")==0){
	}
	else if(strcmp(data[0],"srl")==0){
	}
	else if(strcmp(data[0],"sw")==0){
	}
	else if(strcmp(data[0],"subu")==0){
	}
	printf("binary is %s\n",Binary);
	return Binary;

}
	






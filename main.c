#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char* argv[]){

	FILE *file;
	char * line = NULL;
	size_t len = 0;
	ssize_t read; 
	char *pch;
	char *data_name[10];	
	char *data_value[10];
	int dataidx = 0;
	char *proc_name[10];
	int proc_token[10];
	int proc_idx = 0;
	int num_data=-1;
	int num_text=0;
	int checker=0;
	char *output;

	// functions
	char *lineToBinary(char *line[4]);

	file = fopen(argv[1],"r");
	if(file){
		while((read = getline(&line, &len,file))!=-1){
			if(!strcmp(line, "\t.data\n")){
				checker= 1;
			}
			if (!strcmp(line, "\t.text\n")) {
				checker = 0;
			}
			int i = 0;
			for (i; i < 10; i++) {
				if (proc_token[i] >= 0) {
					proc_token[i]++;
				}
			}
			if(checker ==1){
				pch = strtok(line, "\n\t ,:");
				num_data = num_data +1;
				char *empty = "Empty";
				if (!strcmp(pch, ".word")) {
					data_name[dataidx] = (char *)malloc(6);
					strcpy(data_name[dataidx], empty);
				}
				while(pch!=NULL) {
					if (!strncmp(pch, "array", 5) || !strncmp(pch, "data", 4)) {
						data_name[dataidx] = (char *)malloc(6);
						strcpy(data_name[dataidx],pch);
						printf("%s :", data_name[dataidx]);
						pch = strtok(NULL, "\n\t ,:");
					}
					if (!strcmp(pch, ".word")) {
						pch = strtok(NULL, "\n\t ,:");
						data_value[dataidx] = (char *)malloc(32);
						strcpy(data_value[dataidx],pch);
						printf("%s\n", data_value[dataidx]);
						dataidx++;
					}
					else {
						pch = strtok(NULL,"\n\t ,:");
					}
				}
			}
			else {
				char *input[4];
				int input_idx = 0;
				char *name;

				pch = strtok(line, "\n\t ,:");
				name = pch;
				input[input_idx] = (char *)malloc(32);
				strcpy(input[input_idx], pch);
				printf("%s\n", input[input_idx]);
				input_idx++;
				pch = strtok(NULL, "\n\t ,:");
				if (pch == NULL) {
					printf("I'm in\n");
					proc_name[proc_idx] = (char *)malloc(10);
					strcpy(proc_name[proc_idx], name);
					proc_token[proc_idx] = 0;
					proc_idx++;
				}
				else {
					printf("I'm in again\n");
					while (pch != NULL) {
						input[input_idx] = (char *)malloc(32);
						strcpy(input[input_idx], pch);
						input_idx++;
						pch = strtok(NULL, "\n\t ,:");
					}
					printf("input :%s\n", input[1]);
					lineToBinary(input);
					num_text++;
				}
			}
			
		}	
		fclose(file);
	}
	int idx = 0;
	while (idx < dataidx) {
		if (strcmp(data_name[idx], "Empty")) { 
			printf("%s is:\n", data_name[idx]);
		}
		printf("%s\n", data_value[idx]);
		idx++;
	}
	int idx1 = 0;
	while (idx1 < proc_idx) {
		printf("%s :", proc_name[idx1]);
		printf("%d\n", proc_token[idx1]);
		idx1++;
	}
	
//	printf("%d\n",deciTobin(num_data*4));
//	printf("%d\n", deciTobin(num_text*4));
	return 0;
}

int deciTobin(int deci) {
	int binary = 0;
	int counter = 1;
	int remainder;
	while (deci!=0) {
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

/*char * hexto6bin(char* hex){
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
}*/	



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
		
char * lineToBinary(char *data[4]){
	printf("in function\n");
	printf("%s\n",data[1]);	
	char *Binary=malloc(32);;
	int j;
	for(j =0;j<32;j++){
		Binary[j] = '0';
	}
	int index = 0;
	int i;
	char str[5];
	int deciTobin(int deci);
	int length; 
	printf("testing2\n");
	if(strcmp(data[0],"addiu")==0){
		printf("addiu in\n");
		printf("testing: %c\n",Binary[3]);
	}
	else if(strcmp(data[0],"addu")==0){
	}
	
	else if(strcmp(data[0],"and")==0){
		Binary = makeRType("000000",17,17,5,"999999");
	//	printf("testing hextobin 2b: %s\n",hexto6bin("2b"));			
	
	}
/*
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
	}*/
	printf("binary is %s\n",Binary);
	return Binary;
}
	






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
	int rel_addr = 0;
	int num_data=-1;
	int num_text=0;
	int checker=-2;
	int current_pos = 0;
	char *output;

	// functions
	char *lineToBinary(char *line[4]);
	char *data_addr(char *data_list[10], const char *data, int high);
	char *hextoBin(char *number, int length);
	
	file = fopen(argv[1],"r");
	if(file){
		while((read = getline(&line, &len,file))!=-1){
			if(!strcmp(line, "\t.data\n")){
				checker= 1;
			}
			if (!strcmp(line, "\t.text\n")) {
				checker = 0;
			}
			if(checker ==1){
				pch = strtok(line, "\n\t ,$:");
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
						pch = strtok(NULL, "\n\t ,$:");
					}
					if (!strcmp(pch, ".word")) {
						pch = strtok(NULL, "\n\t ,$:");
						data_value[dataidx] = (char *)malloc(32);
						strcpy(data_value[dataidx],pch);
						dataidx++;
					}
					else {
						pch = strtok(NULL,"\n\t ,$:");
					}
				}
			}
			if(checker == 0){
				char *name;
				pch = strtok(line, "\n\t ,$:");
				name = pch;
				pch = strtok(NULL, "\n\t ,$:");
				if (pch == NULL) {
					proc_name[proc_idx] = (char *)malloc(10);
					strcpy(proc_name[proc_idx], name);
					proc_token[proc_idx] = rel_addr;
					proc_idx++;
				}
				else {
					if (!strcmp(name, "la")) {
						pch = strtok(NULL, "\n\t ,$:");
						printf("pch is :%s\n", pch);
						if (strcmp(data_addr(data_name, pch, 0), "0000000000000000") != 0) {
							printf("I got in\n");
							rel_addr++;
							num_text++;
						}
					}
					rel_addr++;
					num_text++;
				}
			}
		}	
		fclose(file);
	}
	file = fopen(argv[1], "r");
	rel_addr = 0;
	if (file) {
		while ((read = getline(&line, &len, file)) != -1) {
			if (checker == 1) {
				char *input[4];
				int input_idx = 0;
				char *name;
				
				printf("Current line is: %s\n", line);
				printf("Address is: %d\n", rel_addr);
				pch = strtok(line, "\n\t ,$:");
				printf("%s\n", pch);
				input[input_idx] = (char *)malloc(32);
				strcpy(input[input_idx], pch);
				input_idx++;
				pch = strtok(NULL, "\n\t ,$:");
				
				if (pch != NULL) {
					while(pch != NULL) {
						printf("%s\n", pch);
						if (input_idx == 2) {
							name = pch;
						}
						input[input_idx] = (char *)malloc(32);
						strcpy(input[input_idx], pch);
						input_idx++;
						pch = strtok(NULL, "\n\t ,$:");
					}
					if (!strcmp(input[0], "la")) {
						char *new_input[4];
						int i;
							
						for (i = 0; i<4; i++) {
							new_input[i] = (char *)malloc(32);
						}
						
						if (strcmp(data_addr(data_name, name, 0), "0000000000000000") != 0) {
							strcpy(new_input[0], "lui");
							strcpy(new_input[1], input[1]);
							strcpy(new_input[2], data_addr(data_name, input[2], 1));
							lineToBinary(new_input);
							
							strcpy(new_input[0], "ori");
							strcpy(new_input[1], input[1]);
							strcpy(new_input[2], input[1]);
							strcpy(new_input[3], data_addr(data_name, input[2], 0));
							lineToBinary(new_input);
							rel_addr++;
						}
						else {
							strcpy(new_input[0], "lui");
							strcpy(new_input[1], input[1]);
							strcpy(new_input[2], data_addr(data_name, input[2], 1));
							lineToBinary(new_input);
						}
					}
					else {
						lineToBinary(input);
					}
				rel_addr++;
				}
			}
			if (!strcmp(line, "\t.text\n")) {
				checker = 1;
			}
		}
	}
	int idx = 0;
	while (idx < dataidx) {
		if (strcmp(data_name[idx], "Empty")) { 
			printf("%s is at: ", data_name[idx]);
			printf("%s\n", data_addr(data_name, data_name[idx], 1));
			printf("%s\n", data_addr(data_name, data_name[idx], 0));
		}
		printf("%s\n", data_value[idx]);
		idx++;
	}
	int idx1 = 0;
	while (idx1 < proc_idx) {
		printf("Relative address of %s is:", proc_name[idx1]);
		printf("%d\n", proc_token[idx1]);
		idx1++;
	}
	printf("num_data is: %d\n", num_data);
	printf("num_text is: %d\n", num_text);

	printf("%zu\n", strlen(data_name[0]));

	printf("%s\n", hextoBin("0x3c8", 16));

	u binint[] = "00001111";
	binint = ~binint;
	printf("%s\n", binint);

	return 0;
}

// Decimal to binary number
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
// Length of binary number
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

char *data_addr(char *data_name[10], const char *data, int high) {
	char *addr = (char *)malloc(32);
	char *target = (char *)malloc(16);
	int idx = 0;
	int length;
	int i;
	
	addr[0] = '1';
	for (i=1; i<32; i++) {
		addr[i] = '0';
	}

	while (strcmp(data_name[idx], data)) {
		idx++;
	}
	
	idx = idx*4;
	idx = deciTobin(idx);
	length = biLengthCal(idx);

	char added[length];
	
	sprintf(added, "%d", idx);

	for (i = 0; i<length; i++) {
		addr[32-length+i] = added[i];
	}
	
	if (high == 1) {
		for (i = 0; i<16; i++) {
			target[i] = addr[i];
		}
	}
	else {
		for (i = 0; i<16; i++) {
			target[i] = addr[i+16];
		}
	}

	return target;
}


char * hextoBin(char* hex, int length){
	char *Binary = (char *)malloc(length);
	int i = strlen(hex);
	int j = 2;
	int k;
	const char binary[16][5] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
				    "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
	const char *digits = "0123456789abcdef";

	for (k = 0; k < length - 4*(i - 2); k++) {
		Binary[k] = '0';
	}
	
	while (hex[j]) {
		const char *v = strchr(digits, hex[j++]);
		if (v) {
			strcat(Binary, binary[v-digits]);
		}
	}
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
		
char * lineToBinary(char *data[4]){
	
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
	






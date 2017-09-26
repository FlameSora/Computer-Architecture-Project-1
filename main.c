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
	char *output;

	// functions
	char *lineToBinary(char *line[4],char* data_name[10], char*data_value[10], char *proc_name[10], int proc_token[10], int rel_addr);
	char *data_addr(char *data_list[10], const char *data, int high);
	char *hextoBin(char *number, int length);
	char *decitobin(int number, int length);
	
	
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
						pch = strtok(NULL, "\n\t ,$:");
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
						if (strcmp(data_addr(data_name, pch, 0), "0000000000000000") != 0) {
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
				
				printf("Current line: %s", line);
				printf("Current location: %d\n", rel_addr);
				pch = strtok(line, "\n\t ,$:");
				name = pch;
				input[input_idx] = (char *)malloc(32);
				strcpy(input[input_idx], pch);
				input_idx++;
				pch = strtok(NULL, "\n\t ,$():");
				
				if (pch != NULL) {
					while(pch != NULL) {
						input[input_idx] = (char *)malloc(32);
						strcpy(input[input_idx], pch);
						input_idx++;
						pch = strtok(NULL, "\n\t ,$():");
					}
					
					if (!strcmp(name, "la")) {
						if (strcmp(data_addr(data_name, input[2], 0), "0000000000000000") != 0) {
							rel_addr++;
							lineToBinary(input,data_name,data_value,proc_name,proc_token,rel_addr);
						}
						else {
							lineToBinary(input,data_name,data_value,proc_name,proc_token, rel_addr);
						}
					}
					else {
						lineToBinary(input, data_name, data_value, proc_name, proc_token, rel_addr);
					}
					rel_addr++;
				}
			}
			if (!strcmp(line, "\t.text\n")) {
				checker = 1;
			}
		}
		fclose(file);
	}
	int idx = 0;
	while (idx < dataidx) {
		if (strcmp(data_name[idx], "Empty")) { 
			printf("%s is at:\n ", data_name[idx]);
			printf("upper: %s\n", data_addr(data_name, data_name[idx], 1));
			printf("lower: %s\n", data_addr(data_name, data_name[idx], 0));
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

	return 0;
}

char *decitobin(int deci, int length) {
	char *binary_str = (char *)malloc(length);
	long long binary = 0;
	long long counter = 1;
	int negative = 0;
	int bin_length = 0;
	int remainer;
	int i;
	
	if (deci < 0) {
		negative = 1;
		deci = -deci;
	}
	while (deci!=0) {
		bin_length++;
		binary = binary + counter*(deci%2);
		deci = deci/2;
		counter = counter*10;
	}

	
	if (negative == 0) {
		for (i = 0; i < length - bin_length; i++) {
			binary_str[i] = '0';
		}
		for (i = length - 1; i > length - bin_length - 1; i--) {
			if (binary%10 == 1) {
				binary_str[i] = '1';
			}
			else {
				binary_str[i] = '0';
			}
			binary = binary/10;
		}
	}
	else {
		int init_length = bin_length + 2;
		char *init_value = (char *)malloc(init_length);
		init_value[0] = '0';
		init_value[1] = '1';
		for (i = init_length - 1; i > 1; i--) {
			if (binary%10 == 1) {
				init_value[i] = '0';
			}
			else {
				init_value[i] = '1';
			}
			binary = binary/10;
		}
		int overflow = 1;
		for (i = init_length - 1; i > -1; i--) {
			if (init_value[i] == '1' && overflow == 1) {
				init_value[i] = '0';
				overflow = 1;
			}
			else {
				if (init_value[i] == '0' && overflow == 0) {
					init_value[i] = '0';
					overflow = 0;
				}
				else {
					init_value[i] = '1';
					overflow = 0;
				}
			}
		}
		init_value[0] = '1';
		printf("%s\n", init_value);
		for (i = 0; i < length - init_length; i++) {
			binary_str[i] = '1';
		}
		for (i = 0; i < init_length; i++) {
			binary_str[length - init_length + i] = init_value[i];
		}
	}
	return binary_str;
}

// Decimal to binary number
int deciTobin(int deci) {
	int binary = 0;
	int counter = 1;
	int negative;
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
	int counter =0;
	while (a!=0){
		a =a/10;
		counter ++;
	}
	return counter;
}

char *data_addr(char *data_name[10], const char *data, int high) {
	char *addr = (char *)malloc(32);
	char *target = (char *)malloc(16);
	int idx = 0;
	int length;
	int i;
	
	for (i = 0; i<3; i++) {
		addr[i] = '0';
	}
	addr[3] = '1';
	for (i=4; i<32; i++) {
		addr[i] = '0';
	}
	while (strcmp(data_name[idx], data)) {
		idx++;
	}
	
	idx = idx*4;
	idx = deciTobin(idx);
	length = biLengthCal(idx);

	char *added = (char *)malloc(length);

	for (i = 0; i<length; i++) {
		if (idx%10 == 1) {
			added[length-1-i] = '1';
		}

		else {
			added[length-1-i] = '0';
		}
		idx = idx/10;
	}

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



char * makeRType(char *op, int rd, int rs, int rt,int shamt, char* hex){
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
			sprintf(str,"%d",deciTobin(shamt));
			length = biLengthCal(deciTobin(shamt));
			if((25 - i - (5-length))>=0){
				Binary[i+(5-length)] = str[i-21];
			}
			
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
		return Binary;
}
		

char * makeJType(char *op, char *jTarget){
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
		return Binary;
}
		
char * lineToBinary(char *data[4],char* data_name[10],char*data_value[10],char* proc_name[10],int proc_token[10],int rel_addr ){
	
	char *Binary=malloc(64);
	int j;
	for(j =0;j<32;j++){
		Binary[j] = '0';
	}
	char *targetBin = malloc(26);
 	for(j=0;j<26;j++){
		if(j == 5){
			targetBin[j] = '1';
		}
		else{
			targetBin[j] = '0';
		}
	}
	int index = 0;
	int i;
	char *hextoBin(char *hex, int length);
	char *decitobin(int deci, int length);
	char *data_addr(char *data_name[10], const char *data, int high);
	int deciTobin(int deci);
	int length; 
	int counter = 0;
	int target;

	// takes negative numbers
	if(strcmp(data[0],"addiu")==0){
//		if(strlen(data[3])>2 & data[3][1] =='x'){
//			char str[strlen(data[3]-2)];
//			strncpy(str, data[3]+2,strlen(data[3])-2);
//			printf("str is %s\n", str);
//		}	
//		Binary = "0000";
//		
	}
	else if(strcmp(data[0],"addu")==0){
		Binary = makeRType("000000", atoi(data[1]),atoi(data[2]),atoi(data[3]),0,"100000");
	}
	
	else if(strcmp(data[0],"and")==0){
		
		Binary = makeRType("000000",atoi(data[1]),atoi(data[2]),atoi(data[3]),0,"100100");	
	
	}
	else if(strcmp(data[0],"andi")==0){
	
	}
	// takes negative values
	else if(strcmp(data[0],"beq")==0){
		for (i = 0; i < 10; i++) {
			if (strcmp(proc_name[i], data[3]) == 0) {
				counter = i;
				break;
			}
		}
		char *offset = decitobin(proc_token[counter] - (rel_addr + 1), 16);
		Binary = makeIType("000100", atoi(data[2]), atoi(data[1]), offset);
	}
 	// takes negative values
	else if(strcmp(data[0],"bne")==0){
		for (i = 0; i < 10; i++) {
			if(strcmp(proc_name[i],data[3]) == 0) {
				counter = i;
				break;
			}
		}
		char *offset = decitobin(proc_token[counter] - (rel_addr + 1), 16);
		Binary = makeIType("000101", atoi(data[2]), atoi(data[1]), offset);
	}
	else if(strcmp(data[0],"j")==0){
		for( i = 0; i<10;i ++){
			if(strcmp(proc_name[i],data[1])==0){
				counter = i;
				break;
			}
		}
		target = proc_token[counter]*4;
		target = deciTobin(target)/100;
		length = biLengthCal(target);
		char str[length];
		sprintf(str, "%d",target);
		for(i = 0; i<length; i++){
			targetBin[25 - length +1 +i] = str[i];
		}
		Binary = makeJType("000010",targetBin);

	}	
	else if(strcmp(data[0],"jal")==0){	
		for( i = 0; i<10;i ++){
			if(strcmp(proc_name[i],data[1])==0){
				counter = i;
				break;
			}
		}
		target = proc_token[counter]*4;
		target = deciTobin(target)/100;
		length = biLengthCal(target);
		char str[length];
		sprintf(str, "%d",target);
		for(i = 0; i<length; i++){
			targetBin[25 - length +1 +i] = str[i];
		}
		Binary = makeJType("000011",targetBin);

	}
	else if(strcmp(data[0],"jr")==0){
		Binary = makeRType("000000",0,atoi(data[1]),0,0,"001000");		
	}	
	else if(strcmp(data[0],"lui")==0){
		char *imme;
		if (strlen(data[2]) > 3 && data[2][1] == 'x') {
			imme = hextoBin(data[2], 16);
		}
		else {
			imme = decitobin(atoi(data[2]), 16);
		}
		Binary = makeIType("001111", atoi(data[1]), 0, imme);
	}
	else if(strcmp(data[0], "la") == 0) {
		char *upper_addr = (char*)malloc(16);
		upper_addr = data_addr(data_name, data[2], 1);
		printf("%s\n", upper_addr);
		char *lower_addr = (char*)malloc(16);
		lower_addr = data_addr(data_name, data[2], 0);
		printf("%s\n", lower_addr);

		Binary = makeIType("001111", atoi(data[1]), 0, upper_addr);
		
		if (strcmp(lower_addr, "0000000000000000") != 0) {
			strcat(Binary, makeIType("001101", atoi(data[1]), atoi(data[1]), lower_addr));
		}
	}	
	// takes negative values
	else if(strcmp(data[0],"lw")==0){
		char *imme;
		if (strlen(data[2]) > 3 && data[2][1] == 'x') {
			imme = hextoBin(data[2], 16);
		}
		else {
			imme = decitobin(atoi(data[2]), 16);
		}
		Binary = makeIType("100011", atoi(data[1]), atoi(data[3]), imme);
	}
	else if(strcmp(data[0],"nor")==0){
		Binary = makeRType("000000",atoi(data[1]),atoi(data[2]),atoi(data[3]),0,"100111");	
	}
	else if(strcmp(data[0],"or")==0){
		Binary = makeRType("000000",atoi(data[1]),atoi(data[2]),atoi(data[3]),0,"100101");	
	}
	else if(strcmp(data[0],"ori")==0){
		char *imme;
		if (strlen(data[3]) > 3 && data[3][1] == 'x') {
			imme = hextoBin(data[3], 16);
		}
		else {
			imme = decitobin(atoi(data[3]), 16);
		}
		Binary = makeIType("001101", atoi(data[1]), atoi(data[2]), imme);
	}
	// takes negative values
	else if(strcmp(data[0],"sltiu")==0){
		char *imme;
		if (strlen(data[3]) > 3 && data[3][1] == 'x') {
			imme = hextoBin(data[3], 16);
		}
		else {
			imme = decitobin(atoi(data[3]), 16);
		}
		Binary = makeIType("001011", atoi(data[1]), atoi(data[2]), imme);
	}
	else if(strcmp(data[0],"sltu")==0){
		Binary = makeRType("000000", atoi(data[1]), atoi(data[2]), atoi(data[3]), 0, "101011");
	}
	else if(strcmp(data[0],"sll")==0){
		Binary = makeRType("000000",atoi(data[1]),0,atoi(data[2]),atoi(data[3]),"000000");
	}
	else if(strcmp(data[0],"srl")==0){
		
		Binary = makeRType("000000",atoi(data[1]),0,atoi(data[2]),atoi(data[3]),"000010");
	}
	// takes negative values
	else if(strcmp(data[0],"sw")==0){
		char *imme;
		if (strlen(data[2]) > 3 && data[2][1] == 'x') {
			imme = hextoBin(data[2], 16);
		}
		else {
			imme = decitobin(atoi(data[2]), 16);
		}
		Binary = makeIType("101011", atoi(data[1]), atoi(data[3]), imme);
	}
	else if(strcmp(data[0],"subu")==0){
		
		Binary = makeRType("000000",atoi(data[1]),atoi(data[2]),atoi(data[3]),0,"100011");
	}
	printf("binary is %s\n",Binary);
	return Binary;
}
	






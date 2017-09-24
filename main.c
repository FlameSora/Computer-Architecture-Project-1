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

	file = fopen(argv[1],"r");
	if(file){
		while((read = getline(&line, &len,file))!=-1){
			if (!strcmp(line, "\t.data\n")) {
				checker = 1;
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
					proc_name[proc_idx] = (char *)malloc(10);
					strcpy(proc_name[proc_idx], name);
					proc_token[proc_idx] = 0;
					proc_idx++;
				}
				else {
					while (pch != NULL) {
						input[input_idx] = (char *)malloc(32);
						strcpy(input[input_idx], pch);
						printf("%s\n", input[input_idx]);
						input_idx++;
						pch = strtok(NULL, "\n\t ,:");
					}
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

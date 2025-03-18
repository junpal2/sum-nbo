#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<netinet/in.h>

void error(const char* err){
	printf("%s", err);
	exit(1);
}

uint32_t readandsum(const char* filename){
	uint32_t sum=0;
	uint32_t num;
	uint32_t size=0;

	FILE* fp=fopen(filename, "rb");
	if(!fp)	error("file open error");
	
	fseek(fp,0,SEEK_END);
	size=ftell(fp);
	fseek(fp,0,SEEK_SET);
	if(size%sizeof(uint32_t)!=0) error("file size error");

	while(fread(&num, sizeof(uint32_t), 1, fp)==1){
		num=ntohl(num);
		sum+=num;
	}
	fclose(fp);
	return sum;
}

int main(int argc, char* argv[]){
	if(argc<2){
		fprintf(stderr,"%s <file1> [<file2>...]\n",argv[0]);
		return 1;
	}
	uint32_t res=0;
	for(int i=1; i<argc; i++){
		uint32_t num=readandsum(argv[i]);
		printf("%u(0x%04x)", num,num);
		if(i<argc-1){
			printf(" + ");
		}
		res+=num;
	}	
	printf(" = %u(0x%04x)\n",res,res);
	return 0;
}

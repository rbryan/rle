#include <stdio.h>
#include <stdlib.h>

typedef char byte;

void init_input_stream(const char* f);
void init_output_stream(const char *f);
int one_or_zero(byte b,int bit);
int get_bit();
void error(const char *e);
void close_output_stream();
void close_intput_stream();

int input_eof = 0;
FILE *isf=NULL;
FILE *osf=NULL;

int main(int argc, char**argv){
	
	if(argc<2) error("missing filename");

	init_input_stream(argv[1]);

	while(!input_eof)
		printf("%d\n",get_bit());


	return 0;

}

void error(const char *e){
	fprintf(stderr,"ERROR:%s\n",e);
	exit(1);
}

int get_bit(){
	static byte c=0;
	static int bit=9;//starts out greater than 8 to load first byte
	
	if(isf==NULL)
		error("get_bit(): input stream not initialized.");
	
	bit++;

	if(bit>8){
		c = (char) fgetc(isf);
		printf("%d\n",c);
		if(c=='\0'){
			input_eof = 1;
			return -1;	
		}
		bit = 0;
	}
	return one_or_zero(c,bit);
}

int one_or_zero(byte b,int bit){
	if((b & 1<<bit)==1<<bit){
		return 1;
	}else{
		return 0;
	}
}

void init_input_stream(const char* f){
	isf = fopen(f,"r");
	input_eof = 0;
}

void close_input_stream(){
	fclose(isf);
}

void close_output_stream(){
	fclose(osf);
}

void init_output_stream(const char *f){
	osf = fopen(f,"w");
}

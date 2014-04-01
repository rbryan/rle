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
void push_bit(int bit);
void flush_input_buf();
void flush_output_buf();

FILE *isf=NULL;
FILE *osf=NULL;
byte icb=0;
byte ocb=0;

int main(int argc, char**argv){
	int a;
	if(argc<3) error("missing filenames");

	init_input_stream(argv[1]);
	init_output_stream(argv[2]);

	while((a=get_bit())!=EOF)
		push_bit(a);
	flush_output_buf();

	return 0;

}

void error(const char *e){
	fprintf(stderr,"ERROR:%s\n",e);
	exit(1);
}

void flush_input_buf(){
	icb=0;
}

void flush_output_buf(){
	fputc(ocb,osf);
	ocb=0;
}

int get_bit(){
	static int bit=8;//starts out at 8 to load first byte
	
	if(isf==NULL)
		error("get_bit(): input stream not initialized.");
	
	bit++;

	if(bit>7){
		icb = (char) fgetc(isf);
		if(icb==EOF){
			return EOF;	
		}
		bit = 0;
	}
	return one_or_zero(icb,bit);
}

void push_bit(int b){
	static int bit=0;
	if(osf==NULL)
		error("push_bit(): output stream not initialized.");


	if(bit>7){
		fputc(ocb,osf);
		ocb=0;
		bit=0;
	}
	ocb |= b<<bit;
	bit++;

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

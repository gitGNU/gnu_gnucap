#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * const * argv){
	if(argc<2){
		exit(1);
	}

	FILE * template = fopen(argv[1],"r");

	char data = getchar();
	int s = 0;
	while( data != EOF ){
		char c = fgetc(template);
		if(s && c==' ' && '0' <= data && data <= '9'){
			data=' ';
		}else if(c=='~' && '0' <= data && data <= '9'){
			data='~';
			s=1;
		}else{
			s=0;
		}
		putchar(data);
		if(c==EOF) break;
	   data = getchar();
	}
	fclose(template);
	while( data != EOF ){
		putchar(data);
	   data = getchar();
	}
}

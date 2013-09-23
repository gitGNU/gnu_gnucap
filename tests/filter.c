#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * const * argv){
	if(argc<2){
		exit(1);
	}

	FILE * template = fopen(argv[1],"r");

	char data = getchar();
	int s = 0;
	char end = ' ';
	while( data != EOF ){
		char t = fgetc(template);
		if(t==EOF) break;
		if(s && t==' ' && '0' <= data && data <= '9'){
			data=' '; end=' ';
		}else if(s && t==end){
			data = end;
			end=' '; s=0;
//		}else if(s && data=='n'){
//			end=' '; s=0;
		}else if(s && ( t=='n' || t=='f' || t=='p' || t=='u' ) && '0' <= data && data <= '9'){
			data = t;
			end=' ';
			s=1;
		}else if(t=='~' && '0' <= data && data <= '9'){
			data='~';
			s=1;
		}else if(t=='~' && ( 'u' == data || 'n' == data || 'f' == data || 'p' == data )){
			end = data;
			data = '~';
			s = 1;
		}else{
			s = 0;
		}
		putchar(data);
	   data = getchar();
	}
	fclose(template);
	while( data != EOF ){
		putchar(data);
	   data = getchar();
	}
}

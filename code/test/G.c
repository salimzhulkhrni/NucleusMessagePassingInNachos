#include "syscall.h"


int main() {

	int* result;
	char* answer;

	int buffer = Send_Message("H","Message-Hello From G To H", -1);
	int buffer1 = Send_Message("I","Message-Hello From G TO I",-1);
	Wait_Answer(result,answer,buffer1);
	Wait_Answer(result,answer,buffer);
    Exit(0); 
}
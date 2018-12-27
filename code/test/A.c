#include "syscall.h"


int main() {

	int* result;
	char* answer;

	int buffer = Send_Message("B","Message-Hello From A",-1);
	Wait_Answer(result,answer,buffer);
    Exit(0); 
}
#include "syscall.h"


int main() {

	char* answer;
	int* result;

	int buffer = Send_Message("D","Message-Hello From C",-1);
	Wait_Answer(result,answer,buffer);
    Exit(0); 
}
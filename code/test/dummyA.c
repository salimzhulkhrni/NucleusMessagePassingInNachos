#include "syscall.h"

int main() {

	char* answer;
	int* result;

	int buffer = Send_Message("dummyB","Message-Hello From dummyA",-1);
	Wait_Answer(result,answer,buffer);
    Exit(0); 
}
#include "syscall.h"


int main() {

	char* message;
	int* result = 0;

	int buffer = Wait_Message("G",message,-1);
	Send_Answer(result,"Answer: Hello from I To G",buffer);
    Exit(0); 
}
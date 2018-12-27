#include "syscall.h"


int main() {

	char* message;
	int* result = 0;

	int buffer = Wait_Message("A",message,-1);
	Send_Answer(result,"Answer-Hello from B",buffer);
    Exit(0); 
}
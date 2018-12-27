#include "syscall.h"


int main() {

	char* message;
	int* result;
	char* answer;

	int buffer = Send_Message("second_program","Hello From First Program",-1);
	Wait_Answer(result,answer,buffer);
	Wait_Message("second_program",message,buffer);
	Send_Answer(result,"answer- Hello again from first program",buffer);
    Exit(0); 
}
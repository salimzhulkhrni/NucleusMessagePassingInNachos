#include "syscall.h"


int main() {

	char* message;

	int buffer = Wait_Message("C",message,-1);
    Exit(0); 
}
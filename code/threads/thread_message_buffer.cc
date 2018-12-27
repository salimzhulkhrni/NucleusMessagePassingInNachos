#include "thread_message_buffer.h"


ThreadMessageBuffer::ThreadMessageBuffer(){
	
	this->used = false;

}

void ThreadMessageBuffer::setBufferID(int id){

	bufferID = id;

}

int ThreadMessageBuffer::getBufferID(){

	return bufferID;

}


void ThreadMessageBuffer::setMessage(char* message){

	msg = message;
}

char* ThreadMessageBuffer::getMessage(){

	return msg;
}


void ThreadMessageBuffer::setSenderID(char* id){

	senderID = id;
}

char* ThreadMessageBuffer::getSenderID(){

	return senderID;
}

void ThreadMessageBuffer::setReceiverID(char* id){

	receiverID = id;
}

char* ThreadMessageBuffer::getReceiverID(){

	return receiverID;
}


void ThreadMessageBuffer::setAnswer(char* ans){

	answer = ans;
}

char* ThreadMessageBuffer::getAnswer(){

	return answer;
}

bool ThreadMessageBuffer:: getUsed(){

	return used;
}

void ThreadMessageBuffer::setUsed(bool value){

	used = value;
}

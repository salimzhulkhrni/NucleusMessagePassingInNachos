

using namespace std;

class ThreadMessageBuffer{

private:

	int bufferID;
	char* msg;
	char* senderID;
	char* receiverID;
	char* answer;
	bool used;


public:

	ThreadMessageBuffer();

	void setBufferID(int);

	int getBufferID();

	void setMessage(char*);

	char* getMessage();

	void setSenderID(char*);

	char* getSenderID();


	void setReceiverID(char*);

	char* getReceiverID();


	void setAnswer(char*);

	char* getAnswer();

	bool getUsed();

	void setUsed(bool);


};
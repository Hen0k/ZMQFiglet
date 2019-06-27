#include "zhelpers.h"
#define P_COM_LEN 16
#define BUFFER_LEN 50000

char buffer[BUFFER_LEN];
int doProcess(char *string) {
	// set the length of command array equal to len of
	// user string + other characters(figlet > figout).
	char command[strlen(string) + P_COM_LEN];
	// put the command together
	sprintf(command, "figlet %s > figout", string);
	
	char *createFile = "touch figout";
	// create the file
	system(createFile);
	// run the figlet comand on the string from user
	// and write it to the file
	system(command);

	FILE *fptr;
	if ((fptr = fopen("figout","r")) == NULL){
		printf("Error! opening file");

		// Program exits if the file pointer returns NULL.
		exit(1);
	}

	//char buffer[BUFFER_LEN];
	fscanf(fptr,"%[^\EOF]", buffer);
	
	fclose(fptr); 

	return 0;
}
int main(int argc, char const *argv[])
{
	/* code */
	//initialize the zmq context and create the socket
	void *context = zmq_ctx_new ();
	void *responder = zmq_socket (context, ZMQ_REP);
	int rc = zmq_bind (responder, "tcp://*:5555");
	assert (rc == 0);
	printf("Server Started\n");
	while(1)
	{
		//define the buffer that will hold the request
		char *request, *response;
		//char *formatedstr;
		//sprintf(response, "Fuck off\n");
		request = s_recv(responder);
		
		printf("recived %s\n", request);

		if (doProcess(request) != 0)
			s_send(responder, "Server Error. Unable to process data");

		else
			s_send (responder, buffer);
	}

	return 0;
}
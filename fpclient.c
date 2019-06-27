#include "zhelpers.h"
#define BUFFER_LEN 50000
int main (void)
{
	char *buffer;
	printf ("Connecting to hello world server...\n");
	void *context = zmq_ctx_new ();
	void *requester = zmq_socket (context, ZMQ_REQ);
	zmq_connect (requester, "tcp://localhost:5555");
	
	printf ("Sending Hello ...\n");
	s_send (requester, "Hello");
	buffer = s_recv (requester);
	printf ("Received:  \n%s\n", buffer);
	/*int request_nbr;

	for (request_nbr = 0; request_nbr != 10; request_nbr++) {
		char *buffer;
		printf ("Sending Hello %d...\n", request_nbr);
		s_send (requester, "Hello");
		buffer = s_recv (requester); 
		printf ("Received %s %d\n", buffer, request_nbr);
	}*/
	zmq_close (requester);
	zmq_ctx_destroy (context);
	return 0;
}
#include <pthread.h>

struct client {
	int socket;
	char tcp_buffer[1500];
	char receive_buffer[1500]; //TCP MTU size
	char requests[100][1024];
	int num_requests;
	int num_params;
	int incomplete;
	int last_index;

	pthread_mutex_t receive_buffer_lock; 
	pthread_mutex_t requests_lock; 
	pthread_mutex_t num_requests_lock; 
};
struct client *get_client();
void connect_server();
void disconnect();
void async_receive();
void async_send(char *data);
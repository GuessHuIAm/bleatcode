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
struct client *get_client(int client_ID);
int get_last_index();
void *handle_connections();
void disconnect(int client_ID);
void async_send(int client_ID, char *data);
void async_receive(int client_ID);
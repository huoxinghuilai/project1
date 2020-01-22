#include "data.h"


struct atguments *parse_data(int client_fd, char *buffer)
{
	struct arguments *arg;

	arg = (struct arguments *)malloc(sizeof(struct arguments));
	arg->sock_fd = client_fd;
	memcpy(arg, buffer, sizeof(struct argumments));

	return arg;
}

int main(int argc, char *argv[])
{
	int sock_fd;
	struct sockaddr_in *server;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	server = (struct sockaddr_in *)malloc(sizeof(struct sockadd_in));
	server->sin_family = AF_INET;
	server->sin_port = htons(8000);
	server->sin_addr.sa = inet_addr("127.0.0.1");

	if (bind(sock_fd, (struct sockaddr *)server, sizeof(struct sockaddr_in)) == -1) {

		printf("�޷��󶨶˿ڣ�����˿ں��Ƿ���ã�");
		return -1;
	}

	if (listen(sock_fd, 100) == -1) {

		printf("����������������");
		return -1��
	}

	while (1) {

		int client_fd, num =0;
		char buffer[4096] = {0};
		struct arguments *arg;
		struct sockaddr_in *client_addr;

		client_addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
		client_fd = accept(sock_fd, (struct sockaddr *)client_addr, sizeof(struct sockaddr_in));
		if (client_fd) {
				
			num = recv(client_fd, buffer, 4096);
			if (num != 0) {

				arg =  parse_data(client_fd, buffer);
				if (!fork()) {

					execve("/bin/bash ./process", arg, NULL);
				} else {

					printf("������ʱ�޷�����");
					return -1;
				}
			}
		} else {
			
			printf("�������");
			return -1;
		}
	}
}

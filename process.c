#include "data.h"

int main(int argc, char *argv[])
{
	int client_fd;
	struct arguments *arg;

	client_fd = (int)argv[0];
	arg = (struct arguments *)malloc(sizeof(struct arguments));
	memcpy(arg, argv[1], sizeof(struct arguments));

	if (!strcmp(arg->method, "set")) {
		
		char buffer[1024] = "�����ѱ��洢!";
		int num = send(client_fd, buffer);
		if (!num) {

			printf("���ݴ洢ʧ�ܣ������ԣ�\n");
			return -1��
		}
		return 0;
	}

	if (!strcmp(arg->method, "get")) {
		return 0;
	}
}

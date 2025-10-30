#include <stdio.h>
#include <stdlib.h>

int is_activated = 0;

int is_valid(char *serial) {
	int sum = 0;
	int valid = 0;
	for (int i = 0; serial[i]; i++) {
		if (serial[i] >= '0' && serial[i] <= '9')
			sum += serial[i] - '0';
		else {
			sum = 0;
			break;
		}
	}
	if (sum == 26)
		valid = 1;
	else
		printf("Invalid serial number!\n");
	return valid;
}

void ask_serial() {
	char serial[20];
	printf("Enter your serial number: ");
	scanf("%s", serial);
	is_activated = is_valid(serial);
}

int main() {
	ask_serial();
	if (!is_activated) {
		printf("No valid license!\n");
		exit(1);
	}
	printf("Hello world!\n");
	return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <stdint.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage: /%s <file 1> <file 2>\n", argv[1]);
		return 0;
	}

	if (access(argv[1], F_OK) == -1 || access(argv[2], F_OK) == -1) {
		printf("Please check file name.\n");
		return 0;
	}

	uint32_t first, second;
	FILE *file = fopen(argv[1], "r");
	fread(&first, sizeof(uint32_t), 1, file);
	fclose(file);

	file = fopen(argv[2], "r");
	fread(&second, sizeof(uint32_t), 1, file);
	fclose(file);

	first = htonl(first);
	second = htonl(second);

	printf ("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", first, first, second, second, first + second, first + second);
}

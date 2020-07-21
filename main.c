#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv)
{
	int pid = fork();

	while(1) {
		if (pid == 0) {
			reader();
			usleep(25978);
		} else {
			writer();
			usleep(425978);
		}	
	}

	return 0;
}

void reader(void) {
	FILE *fp = fopen("buffer","r+b");
	static int read = 0;
	static int last_printed_read = 0;
	char bp = 0;
	fseek(fp, read, NULL);
	read += fread(&bp, 1, 1, fp);
	fclose(fp);
	if (read > last_printed_read) {
		printf("\n                                      reader...");
		printf(" read 0x%02X (byte number %d)", bp, read);
		fflush(0);
		last_printed_read = read;
	}
}

void writer(void) {
	FILE *fp = fopen("buffer","a+b");
	static int wrote = 0;
	static char data = '1';
	wrote += fwrite(&data, 1, 1, fp);
	fclose(fp);
	printf("\nwriter...");
	printf(" wrote 0x%02X (byte number %d)", data, wrote);
	fflush(0);
	data++;
}

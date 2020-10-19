#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	uint8_t romdata[65536];
	FILE *f;
	f = fopen("kernel.bin", "r");

	fseek(f, 0L, SEEK_END);
	long pos = ftell(f);
	rewind(f);

	fread(romdata, pos, 1, f);

	for(int i=pos; i < 65536; i++) romdata[i] = 0x00;

	fclose(f);
	printf("// 64k E64-II kernel elmerucr (c)2020\n");
	printf("//\n\n");
	printf("#include <cstdint>\n\n");
	printf("uint8_t kernel[65536] =\n{");

	for(int i = 0; i<(65535); i++) {
		if(i%16 == 0) printf("\n\t");
		printf("0x%02x,", romdata[i]);
	}
	printf("0x%02x", romdata[(65536)-1]);
	printf("\n};\n");
	return 0;
}

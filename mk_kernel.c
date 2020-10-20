#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	uint8_t romdata[65536];

	// read
	FILE *f;
	f = fopen("unpatched_kernel.bin", "r");

	fseek(f, 0L, SEEK_END);
	long pos = ftell(f);

	printf("[mk_kernel] unpatched kernel size: %lu\n", pos);
	if( pos >= 65536L )
	{
		printf("[mk_kernel] too large, exiting...\n");
		return 1;
	}

	rewind(f);

	fread(romdata, pos, 1, f);

	for(int i=pos; i < 65536; i++) romdata[i] = 0x00;

	fclose(f);

	// write 64k output to cpp file
	f = fopen("kernel.cpp","w");

	fprintf(f, "// kernel.cpp elmerucr (c)2020\n");
	fprintf(f, "//\n\n");
	fprintf(f, "#include <cstdint>\n\n");
	fprintf(f, "uint8_t kernel[65536] =\n{");

	for(int i = 0; i<(65535); i++) {
		if(i%16 == 0) fprintf(f, "\n\t");
		fprintf(f, "0x%02x,", romdata[i]);
	}
	fprintf(f, "0x%02x", romdata[(65536)-1]);
	fprintf(f, "\n};\n");

	fclose(f);

	// write 64k output to bin file
	f = fopen("kernel.bin","wb");
	fwrite(romdata, sizeof(romdata), 1, f);
	fclose(f);

	return 0;
}

#include <stdint.h>
#include <stdio.h>
#include <time.h>

extern uint8_t cbm_cp437_font[];

int main(int argc, char *argv[]) {
	time_t t;
	time(&t);

	uint8_t kerneldata[262144];

	// read
	FILE *f;
	f = fopen("kernel_unpatched.bin", "r");

	fseek(f, 0L, SEEK_END);
	long pos = ftell(f);

	printf("[mk_kernel] kernel_unpatched.bin size: %lu bytes\n", pos);
	if( pos >= (262144L-4096L) )
	{
		printf("[mk_kernel] too large, exiting...\n");
		fclose(f);
		return 1;
	}

	// go back to beginning of file
	// read data
	rewind(f);
	fread(kerneldata, pos, 1, f);

	// fill up the rest of the final rom with zeroes
	for (int i=pos; i < 262144L; i++)
		kerneldata[i] = 0x00;

	// copy font to the right location
	for (int i=0; i<2048; i++)
		kerneldata[0x3f000 + i] = cbm_cp437_font[i];

	// close original unpatched bin file
	fclose(f);

	// write 256k output to cpp file
	printf("[mk_kernel] writing 256k image 'kernel.bin' and 'kernel.cpp' for inclusion in E64-II\n");
	f = fopen("kernel.cpp","w");

	fprintf(f, "/*\n");
	fprintf(f, " * E64-II-KERNEL (kernel.cpp) elmerucr (c)2021\n");
	fprintf(f, " *\n");
	fprintf(f, " * built-in kernel image for E64-II\n");
	fprintf(f, " * %s",ctime(&t));
	fprintf(f, " */\n\n");
	fprintf(f, "#include <cstdint>\n\n");
	fprintf(f, "uint8_t kernel[262144] = {");

	for(int i = 0; i<(262143); i++) {
		if(i%16 == 0) fprintf(f, "\n\t");
		fprintf(f, "0x%02x,", kerneldata[i]);
	}
	fprintf(f, "0x%02x", kerneldata[(262144)-1]);
	fprintf(f, "\n};\n");

	fclose(f);

	// write 256k output to bin file
	f = fopen("kernel.bin","wb");
	fwrite(kerneldata, sizeof(kerneldata), 1, f);
	fclose(f);

	return 0;
}

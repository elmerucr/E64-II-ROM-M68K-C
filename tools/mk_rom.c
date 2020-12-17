#include <stdint.h>
#include <stdio.h>
#include <time.h>

extern uint8_t cbm_cp437_font[];

int main(int argc, char *argv[]) {
	time_t t;
	time(&t);

	uint8_t romdata[262144];

	// read
	FILE *f;
	f = fopen("rom_unpatched.bin", "r");

	fseek(f, 0L, SEEK_END);
	long pos = ftell(f);

	printf("[mk_rom] rom_unpatched.bin size: %lu bytes\n", pos);
	if( pos >= (262144L-4096L) )
	{
		printf("[mk_rom] too large, exiting...\n");
		fclose(f);
		return 1;
	}

	// go back to beginning of file
	// read data
	rewind(f);
	fread(romdata, pos, 1, f);

	// fill up the rest of the final rom with zeroes
	for (int i=pos; i < 262144L; i++)
		romdata[i] = 0x00;

	// copy font to the right location
	for (int i=0; i<2048; i++)
		romdata[0x3f000 + i] = cbm_cp437_font[i];

	// close original unpatched bin file
	fclose(f);

	// write 256k output to cpp file
	printf("[mk_rom] writing 256k image 'rom.bin' and 'rom.cpp' for inclusion in E64-II\n");
	f = fopen("rom.cpp","w");

	fprintf(f, "/*\n");
	fprintf(f, " * E64-II-ROM (rom.cpp) elmerucr (c)2020\n");
	fprintf(f, " *\n");
	fprintf(f, " * built-in rom image for E64-II\n");
	fprintf(f, " * %s",ctime(&t));
	fprintf(f, " */\n\n");
	fprintf(f, "#include <cstdint>\n\n");
	fprintf(f, "uint8_t rom[262144] = {");

	for(int i = 0; i<(262143); i++) {
		if(i%16 == 0) fprintf(f, "\n\t");
		fprintf(f, "0x%02x,", romdata[i]);
	}
	fprintf(f, "0x%02x", romdata[(262144)-1]);
	fprintf(f, "\n};\n");

	fclose(f);

	// write 256k output to bin file
	f = fopen("rom.bin","wb");
	fwrite(romdata, sizeof(romdata), 1, f);
	fclose(f);

	return 0;
}

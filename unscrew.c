#include <stdio.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/md5.h"
#include "include/aes.c"
#include "include/aes_crypt.c"

// values from php_screw_plus.h
#define STRICT_MODE 0
const int maxBytes = 1024*1024*2;


const char* program_name;

void pm9screw_ext_fopen_plus(FILE* fp, char* cakey)
{
	struct	stat	stat_buf;
	char	*datap, *newdatap;
	char lenBuf[16];
	int	datalen, newdatalen=0;
	int	i;

	uint8_t enTag[16];
	uint8_t key[64];
	memset(key, 0, sizeof(key));
	memcpy(key, md5(cakey), 32);
	memcpy(enTag, key, 16);
	memset(lenBuf, 0, 16);
	fstat(fileno(fp), &stat_buf);
	datalen = stat_buf.st_size;
	datap = (char*)malloc(maxBytes);
	memset(datap, 0, sizeof(datap));
	fread(datap, datalen, 1, fp);
	fclose(fp);

	if(memcmp(datap, enTag, 16) == 0) {
		for(i=16; i<datalen; i++) {
			if(i<32)
				lenBuf[i-16] = datap[i];
			else
				datap[i-32] = datap[i];
		}
		screw_aes(0,datap,datalen,key,&datalen);
		datalen = atoi(lenBuf);
	} else if(STRICT_MODE) {
		datalen = 0;
	}

  for(i = 0; i < datalen; i++) {
    printf("%c", datap[i]);
  }

  free(datap);

}


void print_usage(FILE* stream, int exit_code)
{
	fprintf(stream, "Decrypt file that encrypted by php_screw_plus\n");
	fprintf(stream, "Usage: %s [Key] [Encrypted File]\n", program_name);
	exit(exit_code);
}


int main(int argc, char* argv[]) 
{

	program_name = argv[0];

	if (argc >2) {
		char* cakey = argv[1];
		FILE* f = fopen(argv[2], "r");

		pm9screw_ext_fopen_plus(f, cakey);

	} else {
		print_usage(stdout, 0);
	}


	return 0;
}

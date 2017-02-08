#include <stdio.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include "php_screw_plus.h"
#include "include/md5.h"
#include "include/aes.c"
#include "include/aes_crypt.c"

void pm9screw_ext_fopen_plus(FILE *fp)
{
	struct	stat	stat_buf;
	char	*datap, *newdatap;
	char lenBuf[16];
	int	datalen, newdatalen=0;
	int	i;
	uint8_t enTag[16];
	uint8_t key[64];
	memset(key, 0, sizeof(key));
	memcpy(key, md5(CAKEY), 32);
	memcpy(enTag, key, 16);

	memset(lenBuf, 0, 16);
	fstat(fileno(fp), &stat_buf);
	datalen = stat_buf.st_size;
	datap = (char*)malloc(maxBytes);
	memset(datap, 0, sizeof(datap));
	fread(datap, datalen, 1, fp);
	fclose(fp);

  // datap 에 암호화된 파일
  // printf("cryptkey %s\n", md5(CAKEY));
  // printf("read %d bytes\n", datalen);



	if(memcmp(datap, enTag, 16) == 0) {
		for(i=16; i<datalen; i++) {
			if(i<32)
				lenBuf[i-16] = datap[i];
			else
				datap[i-32] = datap[i];
		}
		screw_aes(0,datap,datalen,key,&datalen);
		datalen = atoi(lenBuf);
	}else if(STRICT_MODE){
		datalen = 0;
	}

  for(i = 0; i < datalen; i++) {
    printf("%c", datap[i]);
  }

  free(datap);

}



int main( int argc, const char* argv[] ) {

	FILE * f = fopen(argv[1], "r");
  // printf("IN: %s", argv[1]);

	pm9screw_ext_fopen_plus(f);
	return 0;
}

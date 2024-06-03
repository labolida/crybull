#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned char shiftBitLeft( unsigned char i ) {
    unsigned char r = i<<1;
    if (i&128){
        r=r+1;
    }
    return r;
}
unsigned char shiftBitRight( unsigned char i ) {
    unsigned char r = i>>1;
    if (i&1){
        r=r+128;
    }
    return r;
}

int main( int argc , char ** argv ) {
	if (argc==1) {
		printf("Crybull 2024 - cryptography - Linux 64-bits by http://leonardo.labolida.com                   \n" ) ;
		printf("This program is released under GNU GPL v3 license - https://www.gnu.org/licenses              \n" ) ;
		printf("Missing parameters. Expected: ACTION(ENCODE|DECODE) PASSWORD INPUT-FILENAME OUTPUT-FILENAME   \n" ) ;
		printf("  Example:   \n" ) ;
		printf("    crybull ENCODE MySecretPassword  secretMessage.txt  encryptedMessage.txt    \n" ) ;
		printf("    crybull DECODE MySecretPassword  encryptedMessage.txt  secretMessage.txt    \n\n" ) ;
	}else{
		char * action   = argv[1];                // STDIN.PARAM: ACTION ENCODE DECODE
		char * pwd      = argv[2];                // STDIN.PARAM: PASSWORD
		char * fn_in    = argv[3];                // STDIN.PARAM: INPUT-FILENAME
		char * fn_out   = argv[4];                // STDIN.PARAM: OUTPUT-FILENAME
		FILE * fp1 ;                              // FILE POINTER IN
		FILE * fp2 ;                              // FILE POINTER OUT
		int s=0;                                  // step (position in while)
		int c;                                    // char readed from file
        unsigned char r;                          // char result calc

		fp1 = fopen( fn_in  , "r");
		fp2 = fopen( fn_out , "w");
		while( (c = fgetc(fp1))!=EOF ) {
            r = (unsigned char) c;
			int p = pwd[ ( s % strlen(pwd) ) ];
			if (strcmp(argv[1],"ENCODE")==0) {
				r = (r^p)+p ;
                r = shiftBitLeft(r);
                fputc( r , fp2 );
			}
			if (strcmp(argv[1],"DECODE")==0) {
                r = shiftBitRight(r);
                r = (r-p)^p ;
				fputc( r , fp2 );
			}
			s++;
		}
		fclose(fp1);
		fclose(fp2);
	}
	printf("\n");
	return 0;
}


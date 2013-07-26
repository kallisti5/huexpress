#include "list_rom.h"
#include "utils.h"

#if defined(__linux__)
#include <limits.h>
#endif

#include "romdb.h"


unsigned long
filesize(FILE * fp)
{
	int prev = ftell(fp);
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, prev, SEEK_SET);
	return size;
}

/*

unsigned long pack_filesize(PACKFILE *F)
  {
   unsigned long old_pos,end;
   pack_ftell(F,(long*)&old_pos);

   end=old_pos;

   while (!pack_feof(F))
     {
      pack_getc(F);
      end++;
      }


   fseek(F,0,SEEK_END);
   fgetpos(F,(long*)&end);
   fseek(F,old_pos,SEEK_SET);
   return end;
   }
*/

uint32
CRC_file(char *name)
{
	FILE *F = fopen(name, "rb");
	uchar *tmp_data;
	uint32 taille, index, CRC = -1, true_size;

	if (!F)
		return -1;

	taille = filesize(F);
	true_size = taille & 0xFFFFF000;
	if (taille & 0x0FFF) {
		//fprintf(stderr,"HEADER OF 0X%X BYTES\n",taille & 0x0FFF);
		fseek(F, taille & 0x0FFF, SEEK_SET);
	}
	if (!(tmp_data = (uchar *) (malloc(true_size))))
		exit(-1);
	fread(tmp_data, true_size, 1, F);
	for (index = 0; index < true_size; index++) {
		tmp_data[index] ^= CRC;
		CRC >>= 8;
		CRC ^= TAB_CONST[tmp_data[index]];
	}
	free(tmp_data);
	CRC = ~CRC;
//      fprintf(stderr,"CRC = 0X%lX\n",CRC);
	fclose(F);
	return CRC;
}

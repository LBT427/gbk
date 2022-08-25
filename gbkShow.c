#include <sys/stat.h>
#include <stdio.h>
 
#define FILE_NAME "gbk-05.DZK"
#define STR_HZ "Äã"
 
int get_gbk_offset(char * hz_code)
{
	unsigned char high = hz_code[0];
	unsigned char low = hz_code[1];
 
	printf("high:%x, low:%x\n", high, low);
	
if (low < 0x80)
	{
		return ((high-0x81)*190 + (low-0x40))*32;
	}
	else
	{
		return ((high-0x81)*190 + (low-0x41))*32;
	}

}
 
unsigned char gbk_hz_buf[100000000];
unsigned char result[32];

long file_size(const char *file)
{
	int i = 0;
	int offset = 0;
    long length = -1;
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        return length;
    }
 
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);	
 
	rewind(fp);
 
	fread(gbk_hz_buf, 1, length, fp);
 
	offset = get_gbk_offset(STR_HZ);
 
	for (i = 0; i < 32; i++)
	{
		printf("0x%x, ", gbk_hz_buf[offset+i]);
        result[i] =gbk_hz_buf[offset+i];
		if ((i+1)%4 == 0)
		{
			printf("\n");
		}
	}
 
	printf("\n");
 
    fclose(fp);
    return length;
}
 




 
unsigned char Hz_code[] = {
0x10, 0x0, 0x13, 0xfc, 
0x56, 0x44, 0x38, 0x40,
0x13, 0xfc, 0x7c, 0x80,
0x29, 0x20, 0x29, 0xf8,
0x28, 0x20, 0x28, 0x20,
0x2b, 0xfc, 0x2c, 0x20,
0x28, 0x20, 0x40, 0x20,
0x0, 0x0, 0x0, 0x0
};
 
#define RIGHT_SHIFT_VAL(x, n) (((x)>>(n)) & 0x01)
 
void prt_one_Hz(void)
{
	int tbl_size = sizeof(result)/sizeof(char);
	short int temp_code = 0;
	int i = 0, j = 0;
 
	for (i = 0; i < tbl_size; i+=2)
	{
		temp_code = result[i]<<8 | result[i+1];
 
		for (j = 16; j > 0; j--)
		{
			if (RIGHT_SHIFT_VAL(temp_code, j-1))
			{
				printf("*");
			}
			else
			{
				printf("`");
			}
		}
 
		printf("\n");
	}
}
 

int main(void)
{
	long size = 0;
	
	size = file_size(FILE_NAME);//¶Á
 	prt_one_Hz();//»­
    getchar();
	return 0;
}
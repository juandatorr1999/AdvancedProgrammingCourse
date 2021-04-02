#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define END 240

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

unsigned char swapNibbles(unsigned char x) 
{ 
	return ( (x & 0x0F)<<4 | (x & 0xF0)>>4 ); 
} 



int main(int argc, char* argv[]) {
  int input_file, output_file;
  uint width, height, i;
  ulong txt_size;
  uchar *txt_data, *output_data, temp;

  if (argc != 3) {
      fprintf(stderr, "usage: %s origen destination\n", argv[0]);
      return -2;
  }

  if ( (input_file = open(argv[1], O_RDONLY)) < 0 ) {
    perror(argv[0]);
    return -3;
  }

  if ( (output_file = open(argv[2], O_WRONLY)) < 0 ) {
    perror(argv[0]);
    return -3;
  }



  txt_size = lseek(input_file, 0, SEEK_END);
  lseek(input_file, 0, SEEK_SET);
  

  txt_data = (uchar*) malloc(sizeof(uchar) * txt_size);
  if (txt_data == NULL) {
  	printf("%s: No memory space for TXT\n", argv[0]);
  	return -4;
  }

  output_data = (uchar*) malloc(sizeof(uchar) * txt_size);
  if (output_data == NULL) {
  	printf("%s: No memory space for TXT\n", argv[0]);
  	return -5;
  }

  read(input_file, txt_data, sizeof(uchar) * txt_size);

  for (i = 0; i < txt_size; i++) {
    output_data[i] = ( (txt_data[i] & 0x0F)<<4 | (txt_data[i] & 0xF0)>>4 );
    
  }
  

  
  
  // lseek(img_file, -block, SEEK_CUR);
  write(output_file, output_data, sizeof(uchar)* txt_size);
  print("done");

  free(txt_data);
  free(output_data);
  close(input_file);
  close(output_file);
  return 0;
}

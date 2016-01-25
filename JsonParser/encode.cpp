#include<stdlib.h>
#include<stdio.h>
#include<wchar.h>
#include<assert.h>

int utf8ToCp(unsigned* dist, unsigned char* src, size_t size){
    //convert utf8 to Unicode code point

    /*
    Char.number range | UTF - 8 octet sequence
    (hexadecimal) | (binary)
    -------------------- + -------------------------------------------- -
    0000 0000 - 0000 007F | 0xxxxxxx
    0000 0080 - 0000 07FF | 110xxxxx 10xxxxxx
    0000 0800 - 0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
    0001 0000 - 0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    */
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
	    *dist |= *ptr++;
	    *dist = (*dist << 6) | (*ptr++ & 0x7f);
	    dist++;
	}
	else if (*ptr < 0xf0){
	    //there byte
	    *dist |= *ptr++;
	    *dist = (*dist << 6) | (*ptr++ & 0x7f);
	    *dist = (*dist << 6) | (*ptr++ & 0x7f);
	    dist++;
	}
	else{
	    //four bytes
	    *dist |= *ptr++;
	    *dist = (*dist << 6) | (*ptr++ & 0x7f);
	    *dist = (*dist << 6) | (*ptr++ & 0x7f);
	    *dist = (*dist << 6) | (*ptr++ & 0x7f);
	    dist++;
	}
    }
    *dist = L'\0';
    return (dist - p);
}
void cpToUtf8(unsigned char* dist, unsigned* src, size_t size){
    //convert CodePoint to UTF8
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
    }
}
void utf16letToCp(wchar_t* dist, const unsigned char* src, size_t size){
}
void utf16beToCp(wchar_t* dist, const unsigned char* src, size_t size){
}
void utf32leToCp(wchar_t* dist, const unsigned char* src, size_t size){
}
void utf32beToCp(wchar_t* dist, const unsigned char* src, size_t size){
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
    cpToUtf8(buffer2, op, ss);

    for (int i = 0; i < size; i++){
	printf("%x-%x ", buffer[i], buffer2[i]);
    }
    FILE* ffp = fopen(output, "wb");
    fwrite(buffer2, 1, 1024, ffp);
    printf("here");
    return 0;
    

    
}
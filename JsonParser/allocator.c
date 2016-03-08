/*
written by 54niyu

user memory allocator
*/

#include"json.h"

int size =256;
int index = 0;
int init = 0;
jsonValue* memory;
jsonValue* createNode(nodeKind kind){
    if (init == 0){
	//init
	memory = (jsonValue*)malloc(sizeof(jsonValue)*size);
	if (memory == NULL){
	    perror("malloc");
	    exit(-1);
	}
	else{
	    init = 1;
	}
    }

    memset(memory+index, 0, sizeof(jsonValue));
    (memory + index)->nodekind = kind;
    return memory + index++;
}
char* smemory=NULL;
int sindex = 0;
int sinit = 0;
char* getString(int s){

    if (sinit == 0){
	smemory = (char*)malloc(512000);
	if (smemory == NULL){
	    perror("string malloc");
	    exit(-1);
	}
	sinit = 1;
    }

	if (sindex < 512000){
	    sindex += s + 1;
	    return smemory + sindex - s - 1;
	}

}
void freem(){
    free(memory);
}
#include"tokenier.h"
#include<math.h>

typedef enum{
	_Start,
	_String,
	_Number,
	_Error,
} State;

extern FILE* fp;
extern int size;
extern Token tokenStream[1024];


const int MAXBUFF = 5120;
const int MAXLINE = 512;

int line = 0;
char buffer[MAXLINE+MAXBUFF+1];
char* cp = &buffer[MAXLINE];
char* limit = &buffer[MAXLINE];

//Input buffer
void fillBuffer(){
    if (!feof(fp)){
	if (cp >= limit){
	    //init
	    limit = &buffer[MAXLINE];
	}
	else{
	    //move rest character to [MAXLINE-len,MAXLINE]  and refill from MAXLINE;
	    int len = limit - cp;
	    char* s = &buffer[MAXLINE - len];
	    while (cp != limit){
		*s++ = *cp++;
	    }
	    cp = &buffer[MAXLINE - len];
	}
	int bsize = fread(&buffer[MAXLINE], 1, MAXBUFF, fp);
	limit = &buffer[MAXLINE + bsize];
	printf("Read\n");
    }
}


void scan(){
	TokenType type = LCBracket;
	State state =_Start;
	char buff[102400];
	int index = 0;
	char c;

	while (cp<=limit){

	    if (limit - cp < 512)
		fillBuffer();
	    
		c = *cp;
		switch (state){
		case _Start:{
			if (isspace(c)){
			    if (c == '\n')
				line++;
				state = _Start;
			}
			else if (c == '+' || c == '-' || c == '.' || isdigit(c)){
				state = _Number;
				cp--;
			}
			else if (c == '\"'){
				state = _String;
			}
			else if (c == '['){
				tokenStream[size++].tokenType = LQBracket;
				state = _Start;
			}
			else if (c == ']'){
				tokenStream[size++].tokenType = RQBracket;
				state = _Start;
			}
			else if (c == '{'){
				tokenStream[size++].tokenType = LCBracket;
				state = _Start;
			}
			else if (c == '}'){
				tokenStream[size++].tokenType = RCBracket;
				state = _Start;
			}
			else if (c == ':'){
				tokenStream[size++].tokenType = Colon;
				state = _Start;
			}
			else if (c == ','){
				tokenStream[size++].tokenType = Comma;
				state = _Start;
			}
			else if (c == 'n'){
			    if (strncmp(cp, "null",4) == 0){
				tokenStream[size++].tokenType = Null;
				state = _Start;
				cp += 3;
			    }
			    else{
				state = _Error;
			    }
			}
			else if (c == 'f'){
			    if (strncmp(cp, "false",5) == 0){
				tokenStream[size++].tokenType = False;
				state = _Start;
				cp += 4;
			    }
			    else{
				state = _Error;
			    }
			}
			else if (c == 't'){
			    if (strncmp(cp, "true",4) == 0){
				tokenStream[size++].tokenType = True;
				state = _Start;
				cp += 3;
			    }
			    else{
				state = _Error;
			    }
			}
			else{
				state = _Error;
			}
		}; break;
		case _String:{
			if (c == '\\'){
			    //escaped character
			    buff[index++] = c;
			    c = *++cp;
			    buff[index++] = c;
			}
			else if(c=='\"'){
				buff[index] = '\0';
				tokenStream[size].tokenType = TokenType::String;
				tokenStream[size].attribute.stringVal = (char*)malloc(sizeof(buff));
				strcpy(tokenStream[size].attribute.stringVal, buff);
				size++;
				index = 0;
				state = _Start;
			}
			else{
			    buff[index++] = c;
			}
		}; break;
		case _Number:{
			//assci to in/double
			double val = 0;
			int negative = 1;
			if (c == '-'){
				negative = -1;
				c = *++cp;
			}
			else if (c == '+'){
				c = *++cp;
			}
			for (; isdigit(c);){
				val = val * 10 + c - '0';
				c = *++cp;
			}
			if (c == '.'){
				int metrices = 10;
				for (; isdigit(c = *++cp);){
					if (c != '0'){
						val += (double)(c - '0') / metrices;
					}
					metrices *= 10;
				}
				if (c == 'e' || c == 'E'){
					goto scen;
				}
				else{
					tokenStream[size].tokenType = Double;
					tokenStream[size++].attribute.doubleVal = val*negative;
					cp--;
				}
			}
			else if (c == 'e' || c == 'E'){
			scen:
				c = *++cp;
				int val2 = 0;
				int neg = 1;
				if (c == '+'){
				    c = *++cp;
				}
				else if (c == '-'){
				    c = *++cp;
					neg = -1;
				}
				for (; isdigit(c);){
					val2=val2 * 10 + c - '0';
					c = *++cp;
				}
				val2 *= neg;

				tokenStream[size].tokenType = Double;
				tokenStream[size++].attribute.doubleVal = val*negative*pow(10.0,val2);
				cp--;
			}
			else{
				tokenStream[size].tokenType = Int;
				tokenStream[size++].attribute.intVal = (int)val*negative;
				cp--;
			}
			state = _Start;
		}; break;
		case _Error:{
		    printf("Error at line %d      Info: %c\n", line,*cp);
		    return;
		};break;
		}
		cp++;
	}
}

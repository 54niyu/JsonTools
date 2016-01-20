#include"tokenier.h"
#include<math.h>

typedef enum{
	_Start,
	_String,
	_Number,
	_Error,
	_False,
	_True,
	_Null,

} State;

extern FILE* fp;
extern int size;
extern Token tokenStream[1024];

void scan(){
	TokenType type = LCBracket;
	State state =_Start;
	char buff[1024];
	int index = 0;
	char c;

	while (true){
		c = getc(fp);
//		putchar(c);	
		if (c == EOF)
			break;

		switch (state){
		case _Start:{
			if (isspace(c)){
				state = _Start;
			}
			else if (c == '+' || c == '-' || c == '.' || isdigit(c)){
				state = _Number;
				//	buff[index++] = c;
				fseek(fp, -1, SEEK_CUR);
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
				state = _Null;
			}
			else if (c == 'f'){
				state = _False;
			}
			else if (c == 't'){
				state = _True;
			}
			else{
				state = _Error;
			}
		}; break;
		case _String:{
			if (c != '\"'){
				buff[index++] = c;
			}
			else{
				buff[index] = '\0';
				tokenStream[size].tokenType = TokenType::String;
				tokenStream[size].attribute.stringVal = (char*)malloc(sizeof(buff));
				strcpy(tokenStream[size].attribute.stringVal, buff);
				size++;
				index = 0;
				state = _Start;
			}
		}; break;
		case _Number:{
			//if (isdigit(c)){
			//	buff[index++] = c;
			//}
			//else{
			//	tokenStream[size].tokenType = TokenType::Int;
			//	tokenStream[size].attribute.intVal = atoi(buff);
			//	fseek(fp, -1, SEEK_CUR);
			//	size++;
			//	index = 0;
			//	state = _Start;
			//}
			double val = 0;
			int negative = 1;
			if (c == '-'){
				negative = -1;
				c = getc(fp);
			}
			else if (c == '+'){
				c = getc(fp);
			}
			for (; isdigit(c);){
				val = val * 10 + c - '0';
				c = getc(fp);
			}
			if (c == '.'){
				int metrices = 10;
				for (; isdigit(c = getc(fp));){
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
					fseek(fp, -1, SEEK_CUR);;
				}
			}
			else if (c == 'e' || c == 'E'){
			scen:
				c = fgetc(fp);
				int val2 = 0;
				int neg = 1;
				if (c == '+'){
					c = fgetc(fp);
				}
				else if (c == '-'){
					c = fgetc(fp);
					neg = -1;
				}
				for (; isdigit(c);){
					val2=val2 * 10 + c - '0';
					c = fgetc(fp);
				}
				val2 *= neg;

				tokenStream[size].tokenType = Double;
				tokenStream[size++].attribute.doubleVal = val*negative*pow(10.0,val2);
				fseek(fp, -1, SEEK_CUR);
			}
			else{
				tokenStream[size].tokenType = Int;
				tokenStream[size++].attribute.intVal = (int)val*negative;
				fseek(fp, -1, SEEK_CUR);
			}

			state = _Start;

		}; break;
		case _Null:{
			if ((c ) != 'u'){
				state = _Error;
				break;
				
			}
			if ((c = getc(fp)) != 'l'){
				state = _Error;
				break;

			}
			if ((c = getc(fp)) != 'l'){
				state = _Error;
				break;
			}
			tokenStream[size++].tokenType = Null;
			state = _Start;
		}; break;
		case _True:{
			if ((c ) != 'r'){
				state = _Error;
				break;
			}
			if ((c = getc(fp)) != 'u'){
				state = _Error;
				break;
			}
			if ((c = getc(fp)) != 'e'){
				state = _Error;
				break;
			}
			tokenStream[size++].tokenType = True;
			state = _Start;
		}; break;
		case _False:{
			if ((c) != 'a'){
				state = _Error;
				break;
			}
			if ((c = getc(fp)) != 'l'){
				state = _Error;
				break;
			}
			if ((c = getc(fp)) != 's'){
				state = _Error;
				break;
			}
			if ((c = getc(fp)) != 'e'){
				state = _Error;
				break;
			}
			tokenStream[size++].tokenType = False;
			state = _Start;
		}; break;
		case _Error:{
			break;
		};break;
		}
	}
}

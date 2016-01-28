#include"json.h"
typedef enum{
	_Start,
	_String,
	_Number,
	_Error,
} State;

Token tokenValue;

int line = 0;
char* cp;
char* limit;;
static char buff[102400];

void getToken(){
	TokenType type = LCBracket;
	State state =_Start;

	int index = 0;
	char c;

	while (cp<=limit){

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
				tokenValue.tokenType = LQBracket;
				cp++;
				return;
			}
			else if (c == ']'){
				tokenValue.tokenType = RQBracket;
				cp++;
				return;
			}
			else if (c == '{'){
				tokenValue.tokenType = LCBracket;
				cp++;
				return;
			}
			else if (c == '}'){
				tokenValue.tokenType = RCBracket;
				cp++;
				return;
			}
			else if (c == ':'){
				tokenValue.tokenType = Colon;
				cp++;
				return;
			}
			else if (c == ','){
				tokenValue.tokenType = Comma;
				cp++;
				return;
			}
			else if (c == 'n'){
			    if (strncmp(cp, "null",4) == 0){
				tokenValue.tokenType = Null;
				cp += 4;
				return;
			    }
			    else{
				state = _Error;
			    }
			}
			else if (c == 'f'){
			    if (strncmp(cp, "false",5) == 0){
				tokenValue.tokenType = False;
				cp += 5;
				return;
			    }
			    else{
				state = _Error;
			    }
			}
			else if (c == 't'){
			    if (strncmp(cp, "true",4) == 0){
				tokenValue.tokenType = True;
				cp += 4;
				return;
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
				tokenValue.tokenType = TokenType::String;
				tokenValue.attribute.stringVal = (char*)malloc(sizeof(buff));
				strcpy(tokenValue.attribute.stringVal, buff);
				index = 0;
				cp++;
				return;
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
			    //fraction
				int metrices = 10;
				for (; isdigit(c = *++cp);){
					if (c != '0'){
						val += (double)(c - '0') / metrices;
					}
					metrices *= 10;
				}
				if (c == 'e' || c == 'E'){
					goto exponent;
				}
				else{
					tokenValue.tokenType = Double;
					tokenValue.attribute.doubleVal = val*negative;
					return;
				}
			}
			else if (c == 'e' || c == 'E'){
			    //exponent
			    exponent:
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

				tokenValue.tokenType = Double;
				tokenValue.attribute.doubleVal = val*negative*pow(10.0,val2);
				return;
			}
			else{
				tokenValue.tokenType = Int;
				tokenValue.attribute.intVal = (int)val*negative;
				return;
			}
			state = _Start;
		}; break;
		case _Error:{
		    printf("Error at line %d      Info: %s\n", line,cp);
		    return;
		};break;
		}
		cp++;
	}
}

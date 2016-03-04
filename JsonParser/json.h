#ifndef _JSON_H_
#define _JSON_H_
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>


//tokenier
typedef enum{
    //structural chararcters
    LQBracket, RQBracket, LCBracket, RCBracket, Colon, Comma,
    //values
    Int, Double,
    String,
    //literal names
    True, False, Null,
} TokenType;

typedef struct{
    TokenType tokenType;
    union {
	int intVal;
	double doubleVal;
	char* stringVal;
    } attribute;
} Token;
void getToken();
//void fillBuffer();
//tokenier end

//parser
typedef enum { ArrayK, ObjectK, KeyK, StringK, IntK, DoubleK, BooleanK, NullK } nodeKind;

typedef struct jsonvalue{
    struct jsonvalue* child;
    struct jsonvalue* subling;
    nodeKind nodekind;
    union {
	char* stringVal;
	int intVal;
	double doubleVal;
    } val;
} jsonValue;
jsonValue* JSON();
jsonValue* jsonParse(char* value);
jsonValue* createNode(nodeKind kind);
//parser end

//utils
int isInt(jsonValue* n);
int isDouble(jsonValue* n);
int isArray(jsonValue* n);
int isObject(jsonValue* n);
int isBool(jsonValue* n);
int isNull(jsonValue* n);
void setInt(jsonValue* n);
void setDouble(jsonValue* n);
void setArray(jsonValue* n);
void setObject(jsonValue* n);
void setBool(jsonValue* n);
void setNull(jsonValue* n);
//for Object
jsonValue* hasMember(jsonValue* n, const char *key);
int addMember(jsonValue* n, const char *key, jsonValue* value);
int addIntMember(jsonValue* n, const char *key, int value);
int addDoubleMember(jsonValue* n, const char* key, double value);
int addStringMember(jsonValue* n, const char* key, const char* value);
int addBooleanMember(jsonValue* n, const char* key, int value);
int addNullMember(jsonValue* n, const char* key);
//for Array
int addItem(jsonValue* n, jsonValue* value);
int addIntItem(jsonValue* n, int value);
int addDoubleItem(jsonValue* n, double value);
int addStringItem(jsonValue* n, const char* value);
int addBooleanItem(jsonValue* n, int value);
int addNullItem(jsonValue* n);
int getArrarySize(jsonValue* n);
jsonValue* getElement(jsonValue* arr, int index);
void removeElement(jsonValue* arr, int index);
void removeMember(jsonValue* obj, char* key);
void deleteValue(jsonValue* value);
void printJson(jsonValue* r, int tab);
//utils  end

//encode
int utf8ToCp(unsigned* dist, unsigned char* src, size_t size);
int cpToUtf8(unsigned char* dist, unsigned* src, size_t size);
int utf16leToCp(unsigned* dist, unsigned char* src, size_t size);
int cpToUtf16le(unsigned char* dist, unsigned* src, size_t size);
int utf16beToCp(unsigned* dist, unsigned char* src, size_t size);
int cpToUtf16be(unsigned char* dist, unsigned* src, size_t size);
int utf32leToCp(unsigned* dist, unsigned char* src, size_t size);
int cpToUtf32le(unsigned char* dist, unsigned* src, size_t size);
int utf32beToCp(unsigned* dist, unsigned char* src, size_t size);
int cpToUtf32be(unsigned char* dist, unsigned* src, size_t size);
//encode end
#endif
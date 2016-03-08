#include"json.h"
#include<time.h>


FILE* fp;
void test1(){
    jsonValue* json = createNode(ObjectK);
    jsonValue* arr = createNode(ArrayK);
    addMember(json, "Array", arr);
    addIntMember(json, "Int", 10);
    addDoubleMember(json, "Double", 12.2);
    addBooleanMember(json, "Boolean", 0);
    addBooleanMember(json, "True", 1);
    addNullMember(json, "Null");
    addStringMember(json, "Fuck", "fuck you assholes");
    jsonValue* arr2 = hasMember(json, "Array");
    if (arr != NULL){
	addIntItem(arr, 10);
	jsonValue* ob = createNode(ObjectK);
	addIntMember(ob, "haah", 12);
	addStringMember(ob, "History", "historyer");
	addIntItem(arr, 12);
	addStringItem(arr, "fuck you asshole");
	addItem(arr, ob);
    }
    printJson(json, 0);
    removeElement(arr, 3);
    printJson(json, 0);
    printf("%d", getArrarySize(arr));
}

void test2(){
    const char* filename = "E:\\test.json";
    const char* out = "E:\\out.json";


    if ((fp = fopen(filename, "r")) == NULL){
	printf("fail opne file\n");
	exit(-1);
    }

    char *val=(char*)malloc(102400);
    int size = fread(val, 1, 102400, fp);
    *(val + size) = '\0';

 //   long b = clock();
    jsonValue *tree = jsonParse(val);
 //   long c = clock();
//    printf(" %f\n", (double)((c-b) / CLK_TCK));
 //   jsonValue *se = getElement(tree, 3);
 //   removeMember(se, "readme");
  //  printJson(tree,2);
  //  freem();

}

int main(){

    test2();
	return 0;
}

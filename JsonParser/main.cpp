#include<stdlib.h>
#include<stdio.h>
#include"tokenier.h"
#include"parser.h"
#include"utils.h"

const int MAX = 1024;
Token tokenStream[MAX];
int size = 0;
FILE* fp;

int main(){

	  const char* filename = "E:\\test.json";

	if ((fp = fopen(filename, "r")) ==nullptr){
		printf("fail opne file\n");
		exit(-1);
	}
	double c = 10.;

	scan();

	TreeNode *tree = JSON();

	printJson(tree,0);

	printf("hahahah");
	return 0;
}
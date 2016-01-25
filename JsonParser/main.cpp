#include<stdlib.h>
#include<stdio.h>
#include"tokenier.h"
#include"parser.h"
#include"utils.h"


FILE* fp;
//
//int main(){
//
//	const char* filename = "E:\\test.json";
//	const char* out = "E:\\out.json";
//
//	freopen(out, "w", stdout);
//
//	if ((fp = fopen(filename, "r")) ==nullptr){
//		printf("fail opne file\n");
//		exit(-1);
//	}
//
//	fillBuffer();
//
//	TreeNode *tree = JSON();
//
//	printJson(tree,0);
//
//	return 0;
//}
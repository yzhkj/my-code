#include <stdio.h>
#include <stdlib.h>

#define sum(x)   (x)+(x)
#define empty              //空宏定义也是可以的
#define sqr(x)	(temp=x,temp*=temp) 

#define x_temp  3
#define y_temp  x_temp*2
#undef  x_temp
#define x_temp  2

#define TElemType int

int z_temp=y_temp;  

typedef struct BiTree{
	
	TElemType  data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree; 

void CreateBiTree(BiTree *T)
{
	TElemType ch;
	scanf("%c",&ch);
	if('#' == ch)
		*T = NULL;
	else{
		*T = (BiTree*)malloc(sizeof(BiTNode));
		if(!*T)
			return;
		(*T)->data = ch;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
		
	}
}

void PreOrderTraverse(BiTree T)
{
	if(T == NULL)
		return;
	printf("%c",T->data );
	PreOrderTraverse(T->lchild );
	PreOrderTraverse(T->rchild );
}

void PostOrderTraverse(BiTree T)
{
	if(T == NULL)
		return;
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
	printf("%c",T->data);
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int temp;
int main(void) 
{
//	int x=5;
//	char res;
//	res=sqr(x++);
//	printf("%d\n",res);
//	printf("sum(x)\n");
//	printf("%d\n",sum(x));
//	printf("%d\n",z_temp); 

	BiTree root;
	CreateBiTree(&root);
	PreOrderTraverse(root);
	printf("\n");
	PostOrderTraverse(root);
	return 0;
}



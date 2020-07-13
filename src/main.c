#include"interface.h"

int main()
{
		int issave = -1;
		Node_t *stulist=LoadStu();

		LoginMenu(stulist);
		printf("是否保存？ (1保存 （2 不保存 \n");
		scanf("%d",&issave);
		if(issave==1)
				SaveStu(stulist);
		DestroyList(&stulist);

}

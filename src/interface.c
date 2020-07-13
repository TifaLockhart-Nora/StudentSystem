#include"interface.h"

Node_t *CreateList()
{
	Node_t *head = malloc(sizeof(Node_t));
	SYSERR(NULL,==,head,"malloc error",NULL);
	head->data = NULL;		//链表的头节点不存储数据
	head->before = head->after = head;

	return head;
}


t_s32int InsertHeadList(Node_t *head,const void *data,t_s32int size)	//size就是要存入的数据的大小
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(NULL,==,data,"data is null",-1);
	SYSERR(size,<,1,"size must >= 1",-1);
	Node_t *newnode = malloc(sizeof(Node_t));	//创建新节点

	SYSERR(NULL,==,newnode,"malloc error",-1);
	newnode->data = malloc(size);	//为数据指针分配内存
	SYSERR(NULL,==,newnode->data,"malloc error",-1);
	memcpy(newnode->data,data,size);	//数据初始化

	newnode->after = head->after;	//改新节点的指针指向 
	newnode->before = head;
	head->after->before = newnode;	//改旧节点的指针指向 
	head->after = newnode;

	return FUNC_OK;
}


void ShowHeadList(Node_t *head,ShowFun_t showfun)	//从头部开始显示
{
	SYSERR(NULL,==,head,"head is null",);
	SYSERR(head->after,==,head,"list is empty",);
	Node_t *temp = head->after;
	while(temp != head && temp->data != NULL)	//包含尾
	{
		showfun(temp->data);	//调用函数指针显示
		temp = temp->after;		//向后移
	}
	printf("\n");
}


void ShowTailList(Node_t *head,ShowFun_t showfun)	//从尾部开始显示
{
	SYSERR(NULL,==,head,"head is null",);
	SYSERR(head->after,==,head,"list is empty",);
	Node_t *temp = head->before;		//找尾
	while(temp != head && temp->data != NULL)
	{
		showfun(temp->data);
		temp = temp->before;	//向前移
	}
	printf("\n");
}


t_s32int InsertTailList(Node_t *head,const void *data,t_s32int size)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(NULL,==,data,"data is null",-1);
	SYSERR(size,<,1,"size must >= 1",-1);
	Node_t *temp = head->before;

	Node_t *newnode = malloc(sizeof(Node_t));
	SYSERR(NULL,==,newnode,"malloc error",-1);
	newnode->data = malloc(size);
	SYSERR(NULL,==,newnode->data,"malloc error",-1);

	memcpy(newnode->data,data,size);
	newnode->after = head;
	newnode->before = temp;
	temp->after = newnode;
	
	head->before = newnode;
	return FUNC_OK;
}


Node_t *FindValueList(Node_t *head,const void *olddata,CmpFun_t cmpfun)
{
	SYSERR(NULL,==,head,"head is null",NULL);
	SYSERR(NULL,==,olddata,"data is null",NULL);
	Node_t *temp = head->after;
	while(temp != head && temp->data != NULL)	//包含尾
	{
		if(!cmpfun(temp->data,olddata))		//比较是否为要找的数据
			return temp;
		temp = temp->after;		//向下找
	}
	return NULL;		//如果没有找到则返回 NULL
}


t_s32int DeleteHeadList(Node_t *head)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(head->after,==,head,"list is empty",-1);
	Node_t *temp = head->after;	//提取第1个节点
	temp->after->before = head;	//修改指针指向
	head->after = temp->after;	
	free(temp->data);	//释放节点 
	free(temp);
	return FUNC_OK;
}


t_s32int DeleteTailList(Node_t *head)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(head->after,==,head,"list is empty",-1);
	Node_t *temp = head->before;	//提取最后1个节点
	temp->before->after = head;	//改指向 
	head->before = temp->before;
	free(temp->data);			//释放节点
	free(temp);
	return FUNC_OK;
}


Node_t *DeleteValueList(Node_t *head,const void *data,CmpFun_t cmpfun)
{
	SYSERR(NULL,==,head,"head is null",NULL);
	SYSERR(head->after,==,head,"list is empty",NULL);
	SYSERR(NULL,==,data,"data is null",NULL);
	Node_t *temp = head->after,*before = NULL;
	while(temp != head && temp->data != NULL)	//包含尾
	{
		if(!cmpfun(temp->data,data))	//比较
		{
			before = temp->before;		//保存前一个节点为的指针
			before->after = temp->after; //修改指向 
			temp->after->before = before;
			free(temp->data);		//释放节点
			free(temp);
			return before;		//返回前一个节点
		}
		temp = temp->after;		//向后找
	}
	return NULL;
}


t_s32int DestroyList(Node_t **head)
{
	SYSERR(NULL,==,*head,"head is null",-1);
	Node_t *temp = (*head)->after;
	Node_t *after = temp->after;
	while(temp != *head)	//包含尾
	{
		after = temp->after;	//保存下一个节点
		free(temp->data);		//释放节点
		free(temp);
		temp = after;		//向下移
	}
	free(*head);			//释放头节点
	*head = NULL;
	return FUNC_OK;
}


t_s32int SelectSortList(Node_t *head,CmpFun_t cmpfun)
{
	SYSERR(NULL,==,head,"head is null",-1);
	Node_t *inext,*jnext,*min;
	void *temp = NULL;
	for(inext = head->after; inext != head && inext->data != NULL; inext = inext->after){
		min = inext;
		for(jnext = inext->after; jnext != head && jnext->data != NULL; jnext = jnext->after){
			if(cmpfun(jnext->data,min->data) < 0)
				min = jnext;
		}
		if(min != inext){
			temp = min->data;
			min->data = inext->data;
			inext->data = temp;
		}
	}
	return FUNC_OK;
}







static t_s32int cid=0;
t_s32int GetCid()
{
	return ++cid;
}


void ShowStu(const void *data)
{
	const Stu_t *stu1=(const Stu_t *)data;
	printf("%d\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",stu1->cid,stu1->name,stu1->pass,stu1->age,stu1->classid,
			stu1->gchinese,stu1->gmath,stu1->gc,stu1->gsum,stu1->order);
}


Node_t *LoadStu()
{
	Node_t *head = CreateList();
	FILE *fp=fopen(STUFILE,"r");
	SYSERR(NULL,==,fp,"fopen error",head);
    fscanf(fp,"%d\n",&cid);	
	Stu_t t={0};
	while(fscanf(fp,"%d %s %s %d %d %d %d %d %d %d\n",&t.cid,t.name,t.pass,&t.age,&t.classid,&t.gchinese,&t.gmath,&t.gc,&t.gsum,&t.order) != EOF)
	{
		InsertHeadList(head,&t,sizeof(Stu_t));
		bzero(&t,sizeof(t));
	}
	fclose(fp);
	return head;
}

t_s32int SaveStu(Node_t *stuhead)
{
	SYSERR(NULL,==,stuhead,"stuhead is null",-1);
	FILE *fp=fopen(STUFILE,"w");
	SYSERR(NULL,==,fp,"fopen error",-1);
	fprintf(fp,"%d\n",cid);
	
	Node_t *temp=stuhead->after;
	Stu_t *stup=NULL;
	while(temp!=stuhead)
	{
			stup=(Stu_t *)temp->data;
			fprintf(fp,"%d %s %s %d %d %d %d %d %d %d\n",stup->cid,stup->name,stup->pass,
			  stup->age,stup->classid,stup->gchinese,stup->gmath,stup->gc,stup->gsum,stup->order);
			temp=temp->after;
	}
	fclose(fp);
	return FUNC_OK;
}
	
t_s32int AddStu(Node_t *stuhead,const Stu_t *stu)
{
	SYSERR(NULL,==,stuhead,"stuhead is null",-1);
	InsertHeadList(stuhead,stu,sizeof(Stu_t));
	printf("学号\t姓名\t密码\t年龄\t班号\t语文\t数学\tC语言\t总分\t名次\n");
	return FUNC_OK;
}

t_s32int CmpCid(const void *data1,const void *data2)
{
	const Stu_t *stu1 = (const Stu_t *)data1;
	const Stu_t *stu2 = (const Stu_t *)data2;
	return stu2->cid - stu1->cid;
}

t_s32int CmpName(const void *data1,const void *data2)
{
	const Stu_t *stu1 = (const Stu_t *)data1;
	const Stu_t *stu2 = (const Stu_t *)data2;
	return strcmp(stu1->name,stu2->name);
}

t_s32int CmpAge(const void *data1,const void *data2)
{
	const Stu_t *stu1 = (const Stu_t *)data1;
	const Stu_t *stu2 = (const Stu_t *)data2;
	return stu1->age - stu2->age;
}

t_s32int CmpClassid(const void *data1,const void *data2)
{
	const Stu_t *stu1=(const Stu_t *)data1;
	const Stu_t *stu2=(const Stu_t *)data2;
	return stu1->classid - stu2->classid;
}

t_s32int CmpGChinese(const void *data1,const void *data2)
{
	const Stu_t *stu1 = (const Stu_t *)data1;
	const Stu_t *stu2 = (const Stu_t *)data2;
	return stu1->gchinese - stu2->gchinese;
}

t_s32int CmpGMath(const void *data1,const void *data2)
{	
	const Stu_t *stu1 = (const Stu_t *)data1;
	const Stu_t *stu2 = (const Stu_t *)data2;
	return stu1->gmath - stu2->gmath;
}

	

t_s32int CmpGC(const void *data1,const void *data2)
{	
	const Stu_t *stu1 = (const Stu_t *)data1;
	const Stu_t *stu2 = (const Stu_t *)data2;
	return stu1->gc - stu2->gc;
}

t_s32int CmpSum(const void *data1,const void *data2)
{	
	const Stu_t *stu1 = (const Stu_t *)data1;
	const Stu_t *stu2 = (const Stu_t *)data2;
	return (stu1->gchinese + stu1->gmath + stu1->gc) - (stu2->gchinese + stu2->gmath + stu2->gc);
}

Node_t *FindStu(Node_t *stuhead,t_s32int mode,const Stu_t *stu)
{
		SYSERR(NULL,==,stuhead,"stuhead is null",NULL);	
		SYSERR(NULL,==,stu,"stu is null",NULL);	
		if(mode<1 || mode>3)
			return NULL;
		Node_t *newhead = CreateList();
		Node_t *result = stuhead;
			switch(mode)
			{
					case 1:
							result = FindValueList(stuhead,stu,CmpCid);
							if(NULL != result){
								Stu_t *stup = (Stu_t *)result->data;
								InsertHeadList(newhead,stup,sizeof(Stu_t));
							}
							break;
					case 2:
							while((result = FindValueList(result,stu,CmpName)) != NULL)
							{	
								Stu_t *stup = (Stu_t *)result->data;
								InsertHeadList(newhead,stup,sizeof(Stu_t));
							}
							break;
					case 3:
							while((result = FindValueList(result,stu,CmpClassid)) != NULL)
							{	
								Stu_t *stup = (Stu_t *)result->data;
								InsertHeadList(newhead,stup,sizeof(Stu_t));
							}
							break;
					default :
							break;
			}
	    	printf("学号\t姓名\t密码\t年龄\t班号\t语文\t数学\tC语言\t总分\t名次\n");
			ShowHeadList(newhead,ShowStu);
			return newhead;
			DestroyList(&newhead);
}

t_s32int DeleteStu(Node_t *stuhead,t_s32int mode ,const Stu_t *stu)
{			
		SYSERR(NULL,==,stuhead,"stuhead is null",-1);	
		SYSERR(NULL,==,stu,"stu is null",-1);	
		if(mode<1 || mode>3){
			return -1;
		}
		Node_t *temp = stuhead;
		t_s32int res = -1;
		switch (mode)
		{
			case 1:
				temp = DeleteValueList(stuhead,stu,CmpCid);
				if(NULL != temp){	
					res = 0;
				}
				break;
			case 2:
				while((temp = DeleteValueList(temp,stu,CmpName)) != NULL)
					;
				res = 0;
					break;
			case 3:
				while((temp = DeleteValueList(temp,stu,CmpClassid)) != NULL)
					;
				res = 0;
					break;
		}
		printf("学号\t姓名\t密码\t年龄\t班号\t语文\t数学\tC语言\t总分\t名次\n");
		return res;
}

Node_t *UpdataStu(Node_t *stuhead, Stu_t *olddata,t_s32int mode,Stu_t *newdata)
{
		SYSERR(NULL,==,stuhead,"stuhead is null",NULL);	
		SYSERR(NULL,==,olddata,"data is null",NULL);	
		SYSERR(NULL,==,newdata,"data is null",NULL);	
		if(mode<1 || mode>7){
			return NULL;
		}
		Node_t *result = FindValueList(stuhead,olddata,CmpCid);
		if(NULL == result){
			return NULL;
		}
		Stu_t *stu = (Stu_t *)result->data;
		switch(mode)
		{
			case 1:
					strcpy(stu->name,newdata->name);
					break;
			case 2:
					strcpy(stu->pass,newdata->pass);
					break;
			case 3:
					stu->age = newdata->age;
					break;
			case 4:
					stu->classid = newdata->classid;
					break;
			case 5:
					stu->gchinese = newdata->gchinese;
					break;
			case 6:
					stu->gmath = newdata->gmath;
					break;
			case 7:
					stu->gc = newdata->gc;
					break;	
		}
		stu->gsum=stu->gchinese + stu->gmath + stu->gc;
		printf("                                ");
		printf("修改后的数据\n");
	    printf("学号\t姓名\t密码\t年龄\t班号\t语文\t数学\tC语言\t总分\t名次\n");
		ShowStu(stu);
		return stuhead;
}

t_s32int SelectSortStu(Node_t *stuhead,t_s32int mode)
{
		SYSERR(NULL,==,stuhead,"stuhead is null",-1);
		if(mode < 1 || mode > 8){
			return -1;
		}
		switch(mode)
		{
				case 1:
					 SelectSortList(stuhead,CmpName);
					 break;		
				case 2:
					 SelectSortList(stuhead,CmpAge);
					 break;
				case 3:
					 SelectSortList(stuhead,CmpCid);
					 break;
				case 4:
					 SelectSortList(stuhead,CmpGChinese);
					 break;
				case 5:
					 SelectSortList(stuhead,CmpGMath);
					 break;
				case 6:
					 SelectSortList(stuhead,CmpGC);
					 break;
				case 7:
					 SelectSortList(stuhead,CmpClassid);
					 break;
				case 8:
					 SelectSortList(stuhead,CmpSum);
					 break;
		}
		SetStuOrder(stuhead);  
		printf("学号\t姓名\t密码\t年龄\t班号\t语文\t数学\tC语言\t总分\t名次\n");
		ShowTailList(stuhead,ShowStu);
		return FUNC_OK; 
}

t_s32int SetStuOrder(Node_t *stuhead)  
{
	SYSERR(NULL,==,stuhead,"stuhead is null",-1);
	
	t_s32int	 order = 0;	
	Node_t  *temp = stuhead->before;
	while(temp != stuhead && temp->data != NULL)
	{
			Stu_t *res = (Stu_t *)temp->data;
			res->order = ++order;
			temp = temp->before;		
	}
	return FUNC_OK;
}
	
		
t_s32int MyClear()
{
	t_s8char ch;
	while((ch = getchar()) != '\n'&&ch != EOF)
		;
	return FUNC_OK;
}

t_s32int LoginMenu(Node_t *stulist)
{
		t_s32int choose = -1;
		while(choose)
		{
				system("clear");
				printf("\n\n\n\n\n\n\n\n\n");
				printf("\t\t\t\t    本系统暂不支持学生登录,后续等待开发\n");
				printf("\t\t\t\t\t        请支持正版\n");
				printf("\t\t\t\t\t     ================\n");
				printf("\t\t\t\t\t     ||1 管理员登录||\n");
				printf("\t\t\t\t\t     ||2 学生登录  ||\n");
				printf("\t\t\t\t\t     ||0 退出      ||\n");
				printf("\t\t\t\t\t     ================\n");
				printf("\t\t\t\t Important  Tip:请按照提示进行'正确'的操作\n");
			lop:	
				printf("\t\t\t\t\t请输入你的选择:");				
				scanf("%d",&choose);
				printf("\n");
				if(choose<0 || choose>2){ 
					printf("\t\t\t\t\t你的输入有误\n");
					MyClear();
			goto lop;
				}
				switch(choose)
				{
					case 0:
							return FUNC_OK;
					case 1:
							WelcomeAdminMenu(stulist);  
							break;
					case 2:
							WelcomeStuMenu(stulist);
							break;
					default:
							printf("你的输入有误，请重新输入！");
							break;
				}
		}
		return FUNC_OK;
}


t_s32int WelcomeAdminMenu(Node_t *stulist)
{
	t_s32int  count = LOOPCOUNT;
	t_s8char  name[16] = {0};
	t_s8char  pass[16] = {0};
	while(count--)
	{
		system("clear");
		printf("\n\n\n\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t\t  请输入管理员的用户名:");
		scanf("%s",name);
		printf("\n");
		
		printf("\t\t\t\t\t  请输入管理员的密码:");
		scanf("%s",pass);

		if(!strcmp(name,ADMINNAME) && !strcmp(pass,ADMINPASS)){
			AdminMenu(stulist);
			return FUNC_OK;
		}
			printf("\t\t\t\t你的输入有误，还有%d次机会,按任意键继续",count);			
			getchar();
			getchar();
	}
	return FUNC_OK;
}


t_s32int AdminMenu(Node_t *stulist)
{
	t_s32int choose = -1;
	system("clear");
	while(choose)
	{
		printf("\n\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t\t管理员菜单:\n");
		printf("\t\t\t\t\t1.添加学生\t 2.删除学生\n");
		printf("\t\t\t\t\t3.修改学生\t 4.查找学生\n");
		printf("\t\t\t\t\t5.显示学生\t 0.退出\n");
		printf("\t\t\t\t\t请输入你的选择:");
		scanf("%d",&choose);
				while(choose<0 || choose>5)
				{ 
					printf("请输入正确的选项\n");
					MyClear();
					scanf("%d",&choose);
				}
		switch(choose)
		{
			case 1:
					AddStuMenu(stulist);
					system("clear");
					break;
			case 2:
					DeleteStuMenu(stulist);
					system("clear");
					break;
			case 3:
					UpdataStuMenu(stulist);
					system("clear");
					break;
			case 4:
					FindStuMenu(stulist);
					system("clear");
					break;
			case 5:
					ShowStuMenu(stulist);
					system("clear");
					break;
			default :
					break;		
		}
	}
	return FUNC_OK;
}


t_s32int AddStuMenu(Node_t *stulist)
{
    system("clear");
	t_s32int stucid;
	t_s32int choose = -1;
	Stu_t stu1 = {0};
	while(choose)
	{	
		stucid = GetCid();
		if(choose == 0){
			return FUNC_OK;
		}
		else{	
				printf("1.学生的学号是：%d\n",stucid);
				printf("2.请输入学生的姓名:\n");	
				scanf("%s",stu1.name);
				
				printf("3.请输入学生的密码:\n");
				scanf("%s",stu1.pass);

				printf("4.请输入学生的年龄:\n");
				scanf("%d",&stu1.age);
				
				printf("5.请输入学生的数学成绩:\n");
				scanf("%d",&stu1.gmath);
				
				printf("6.请输入学生的C语言成绩:\n");
				scanf("%d",&stu1.gc);
				
				printf("7.请输入学生的语文成绩:\n");
				scanf("%d",&stu1.gchinese);
				
				printf("8.请输入学生的班级:\n");
				scanf("%d",&stu1.classid);
			
				stu1.gsum = stu1.gmath + stu1.gchinese + stu1.gc;
				printf("9.学生的总成绩为:%d\n",stu1.gsum);
				stu1.cid = stucid;
				AddStu(stulist,&stu1);
				ShowTailList(stulist,ShowStu);
				printf("按任意键继续添加，返回管理员菜单请按0\n");
				scanf("%d",&choose);
				MyClear();
    			system("clear");
		}
	}
		return FUNC_OK;
}


t_s32int DeleteStuMenu(Node_t *stulist)
{
    system("clear");
	t_s32int choose = -1;
	Stu_t stu2 = {0};
	Node_t *result = stulist;
	while(choose)
	{
			printf("\n\n\n\n\n\n\n\n\n");
			printf("\t\t\t\t\t\t0 返回管理员菜单\n");
			printf("\t\t\t\t\t\t1 按学号删除\n"); 
			printf("\t\t\t\t\t\t2 按姓名删除\n");
			printf("\t\t\t\t\t\t3 按班级删除\n");
			printf("\t\t\t\t\t\t请输入你的选择:");
			scanf("%d",&choose);
				while(choose<0 || choose>3)
				{ 
					printf("\t\t\t\t\t\t请输入正确的选项:");
					MyClear();
					scanf("%d",&choose);
				}
		switch(choose)
		{
				case 0:
					   return FUNC_OK;
				case 1:
					   system("clear");
				loop:
					printf("请输入要删除学生的学号:\n");
					scanf("%d",&stu2.cid);
					MyClear();
					result = FindValueList(stulist,&stu2,CmpCid);
					if(NULL != result){
						DeleteStu(stulist,1,&stu2);
						break;
					}
						else{	
							printf("没有找到该学生的信息,请重新输入\n");
						}
						goto loop;
				case 2:
   					system("clear");
			lop:
					printf("请输入要删除学生的姓名:\n");
					scanf("%s",stu2.name);
						MyClear();
						result = FindValueList(stulist,&stu2,CmpName);
						if(NULL != result){
						DeleteStu(stulist,2,&stu2);
						break;
					}
					else{	
						printf("没有找到该学生的信息,请重新输入\n");
					}
			goto lop;
				case 3:
					system("clear");
			looop:
					printf("请输入要删除的班号:\n");
					scanf("%d",&stu2.classid);
					MyClear();
					result = FindValueList(stulist,&stu2,CmpClassid);
					if(NULL != result){
						DeleteStu(stulist,3,&stu2);
						break;
					}
					else{	
						printf("没有找到该学生的信息,请重新输入\n");
					}
					goto looop;
				default :
						break;
		}
				ShowHeadList(stulist,ShowStu);
				printf("按任意键继续删除，返回管理员菜单请按0\n");
				scanf("%d",&choose);
				MyClear();
    			system("clear");
	}
	return FUNC_OK;	
}


t_s32int FindStuMenu(Node_t *stulist)
{	
    system("clear");
	t_s32int  choose = -1;
	Stu_t  stu3 = {0};
	while(choose)
	{
		printf("\n\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t\t\t0 返回管理员菜单\n");
		printf("\t\t\t\t\t\t1 按学号查找\n"); 
		printf("\t\t\t\t\t\t2 按姓名查找\n");
		printf("\t\t\t\t\t\t3 按班级查找\n");
		printf("\t\t\t\t\t\t请输入你的选择:");
		scanf("%d",&choose);
		MyClear();
	while(choose< 0 || choose>3)
	{ 
		printf("请输入正确的选项\n");
		scanf("%d",&choose);
		MyClear();
	}
	switch(choose)
	{  
		case 0:
		    	return FUNC_OK;
		case 1:
				system("clear");
			lod:
				printf("请输入学生的学号：\n");
				scanf("%d",&stu3.cid);
				MyClear();
				Node_t *result = FindStu(stulist,1,&stu3);
				if(result->after == result){	
					system("clear");
					printf("本系统内没找到你要查找的学生,请重新输入正确的信息\n");
					goto lod;
				}
					break;
		case 2:
   				system("clear");
			lood:	
				printf("请输入学生的姓名:\n");
				scanf("%s",stu3.name); 
				MyClear();
				result = FindStu(stulist,2,&stu3);
				if(result->after == result){		
					system("clear");
					printf("本系统内没找到你要查找的学生，请重新输入正确的信息\n");
					goto lood;
				}	
					break;
		case 3:
				system("clear");
			loood:
				printf("请输入学生的班号:\n");
				scanf("%d",&stu3.classid); 
				MyClear();
				result = FindStu(stulist,3,&stu3);
				if(result->after == result){		
					system("clear");
					printf("本系统内没找到你要查找的学生，请重新输入正确的信息\n");
					goto loood;
				}	
					break;
		default:
				break;
	}
		printf("按任意键继续查找学生，返回管理员菜单请按0\n");
		scanf("%d",&choose);
		MyClear();
		if(choose == 0)
			return FUNC_OK;
    	system("clear");
	}
		return FUNC_OK;
}


t_s32int UpdataStuMenu(Node_t *stulist)
{
    system("clear");
	t_s32int choose;
	Stu_t oldstu = {0};
	Stu_t newstu = {0};	
adc:	

lod:
	printf("请输入学生的学号:\n");
	scanf("%d",&oldstu.cid);
	MyClear();
	Node_t *result=FindValueList(stulist,&oldstu,CmpCid);
	if(NULL != result){
		choose = -1;
	}
	else{	
		printf("没有找到该学生的信息,请重新输入\n");
goto lod;
	}
	while(choose)
	{
    	system("clear");
		printf("学号\t姓名\t密码\t年龄\t班号\t语文\t数学\tC语言\t总分\t名次\n");
		ShowStu(result->data);
		printf("\n\n\n\n\n\n\n ");
		printf("\t\t\t\t可以修改的数据有:\n");
		printf("\t\t\t\t1.修改学生的姓名\t 2.修改学生的密码\n");
		printf("\t\t\t\t3.修改学生的年龄\t 4.修改学生的班号\n");
		printf("\t\t\t\t5.修改学生的语文成绩\t 6.修改学生的数学成绩\n");
		printf("\t\t\t\t7.修改学生的C语言成绩\t 8.更换学生\n");
		printf("\t\t\t\t0.返回管理员菜单\n");
		printf("\t\t\t\t请输入你的选择:");
		scanf("%d",&choose);
				while(choose < 0 || choose > 8)
				{ 
					printf("请输入正确的选项\n");
					MyClear();
					scanf("%d",&choose);
				}
	switch(choose)
	{       
			case 0:
	 	        return FUNC_OK;
			case 1:
				printf("请输入新的名字:\n");
				scanf("%s",newstu.name);
				UpdataStu(stulist,&oldstu,1,&newstu);
				break;
			case 2:
				printf("请输入新的密码:\n");
				scanf("%s",newstu.pass);
				UpdataStu(stulist,&oldstu,2,&newstu);
				break;
			case 3:
				printf("请输入新的年龄:\n");
				scanf("%d",&newstu.age);
				UpdataStu(stulist,&oldstu,3,&newstu);
				break;
			case 4:
				printf("请输入新的班号:\n");
				scanf("%d",&newstu.classid);
				UpdataStu(stulist,&oldstu,4,&newstu);
				break;
			case 5:
				printf("请输入新的语文成绩:\n");
				scanf("%d",&newstu.gchinese);
				UpdataStu(stulist,&oldstu,5,&newstu);
				break;
			case 6:
				printf("请输入新的数学成绩:\n");
				scanf("%d",&newstu.gmath);
				UpdataStu(stulist,&oldstu,6,&newstu);
				break;
			case 7:
				printf("请输入新的C语言成绩:\n");
				scanf("%d",&newstu.gc);
				UpdataStu(stulist,&oldstu,7,&newstu);
				break;
			case 8:
				goto adc;
			default:
				break;
	}
		printf("按任意键继续修改此学生,返回管理员菜单请按0\n");
		scanf("%d",&choose);
		MyClear();
				if(choose == 0)
					return FUNC_OK;
    	system("clear");
	}
	return FUNC_OK;
}


t_s32int ShowStuMenu(Node_t *stulist)
{
    system("clear");
	t_s32int choose = -1;
	while(choose)
	{
		printf("1.按名字排序显示\t 2.按年龄排序显示\n");
		printf("3.按学号排序显示\t 4.按语文成绩排序\n");
		printf("5.按数学成绩排序显示\t 6.按C语言成绩排序\n");
		printf("7.按班号排序显示\t 8.按总分排序显示\n");
		printf("0.返回管理员菜单\n");
		printf("请输入你的选择:\n");
		scanf("%d",&choose);
				while(choose<0 || choose>8)
				{ 
					printf("请输入正确的选项\n");
					MyClear();
					scanf("%d",&choose);
				}
		if(choose < 0 || choose >= 9){		
   			system("clear");
			printf("你的输入有误,请重新输入你的选择：\n");
		}		           	
			else if(choose == 0)
					return FUNC_OK;
    			else{	
					SelectSortStu(stulist,choose);
					printf("按任意键重新选择排序方式,返回管理员菜单请按0\n");
					scanf("%d",&choose);
					MyClear();
    				system("clear");
				}
	}	
	return FUNC_OK;
}


t_s32int WelcomeStuMenu(Node_t *stulist)
{
	return FUNC_OK;
}

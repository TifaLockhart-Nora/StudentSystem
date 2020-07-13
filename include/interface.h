#ifndef INTERFACE_H
#define INTERFACE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LOOPCOUNT 3
#define ADMINNAME "admin"
#define ADMINPASS "admin"
#define STUFILE "student.dat"
#define FUNC_OK   0
#define FUNC_ERR  1
#define SYSERR(x,option,y,message,z)	if((x) option (y))		\
										{						\
											printf("%s %s %d error : %s\n",__FILE__,__func__,__LINE__,message);	\
											return z;			\
										}
typedef signed int  t_s32int;
typedef signed char t_s8char;
struct Student
{
		t_s32int cid;       //学生学号
		t_s8char name[32];  //学生姓名
		t_s8char pass[16];  //学生密码
		t_s32int age;       //学生年龄
		t_s32int gmath;     //数学成绩
		t_s32int gc;        //C语言成绩
		t_s32int gchinese;  //语文成绩
		t_s32int gsum;      //总分
		t_s32int order;     //序号
		t_s32int classid;   //班号
};
typedef struct Student Stu_t;

struct Node
{
	struct Node *before;	//指向前一个节点的指针
	void *data;				//数据指针
	struct Node *after;		//指向后一个节点的指针
};
typedef struct Node Node_t;
typedef void (*ShowFun_t)(const void *);
void ShowStu(const void *data);                                            //显示学生的信息
Node_t *LoadStu();                                                        //加载学生信息
Node_t *FindStu(Node_t *stuhead,t_s32int mode,const Stu_t *stu);               //查找学生
Node_t *UpdataStu(Node_t *stuhead,Stu_t *olddata,t_s32int mode,Stu_t *newdata);//按值修改学生
t_s32int GetCid();                                                              //学号自增
t_s32int SaveStu(Node_t *stuhead);                                             //保存学生信息
t_s32int AddStu(Node_t *stuhead,const Stu_t *stu);                              //添加学生
t_s32int DeleteStu(Node_t *stuhead,t_s32int mode ,const Stu_t *stu);//按值删除学生
t_s32int SelectSortStu(Node_t *stuhead,t_s32int mode);              //显示排序学生
t_s32int SetStuOrder(Node_t *stuhead);                         //设置学生序号
t_s32int CmpCid(const void *data1,const void *data2);          //比较学号
t_s32int CmpName(const void *data1,const void *data2);         //比较名字
t_s32int CmpClassid(const void *data1,const void *data2);      //比较班号
t_s32int CmpAge(const void *data1,const void *data2);          //比较年龄
t_s32int CmpGChinese(const void *data1,const void *data2);     //比较语文成绩
t_s32int CmpGMath(const void *data1,const void *data2);        //比较数学成绩
t_s32int CmpGC(const void *data1,const void *data2);           //比较C语言成绩
t_s32int CmpSum(const void *data1,const void *data2);          //比较总成绩

Node_t *CreateList();		//创建链表
Node_t *FindValueList(Node_t *head,const void *olddata,CmpFun_t cmpfun);	//按值查找 
Node_t *DeleteValuedList(Node_t *head,const void *data,CmpFun_t cmpfun);	//按值删除 
t_s32int InsertHeadList(Node_t *head,const void *data,t_s32int size);		//头部插入
t_s32int insertTailList(Node_t *head,const void *data,t_s32int size);		//尾部插入
t_s32int DeleteHeadList(Node_t *head);	//删除第1个节点
t_s32int DeleteTailList(Node_t *head);	//删除最后1个节点
t_s32int SelectSortList(Node_t *head,CmpFun_t cmpfun);	//排序
t_s32int DestroyList(Node_t **head);		//销毁链表
typedef t_s32int (*CmpFun_t)(const void *,const void *);	//比较函数指针
typedef void (*ShowFun_t)(const void *);
void ShowHeadList(Node_t *head,ShowFun_t showfun);	//从头向后显示
void ShowTailList(Node_t *head,ShowFun_t showfun);	//从尾向前显示


t_s32int LoginMenu(Node_t *stulist);//加载菜单
t_s32int WelcomeAdminMenu(Node_t *stulist);//管理员登录界面
t_s32int AdminMenu(Node_t *stulist);//管理员菜单
t_s32int AddStuMenu(Node_t *stulist);//添加学生菜单
t_s32int DeleteStuMenu(Node_t *stulist);//删除学生菜单
t_s32int FindStuMenu(Node_t *stulist);//查找学生菜单
t_s32int UpdataStuMenu(Node_t *stulist);//修改学生菜单
t_s32int ShowStuMenu(Node_t *stulist);//显示排序学生菜单
t_s32int WelcomeStuMenu(Node_t *stulist);
t_s32int MyClear();
#endif

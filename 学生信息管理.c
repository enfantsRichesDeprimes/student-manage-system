#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L sizeof(struct student)
FILE *fp;
struct birthday
{
	int year;
	int month;
	int day;
};
struct student
{
	long num;
	char name[12];
	char sex[2];
	struct birthday date;
	float score;
	struct student *next;
};
struct student*del(struct student*head,long n)
{
	struct student*p1,*p2;
	if(head==NULL) 
	{
		printf("A Wrong Operation\n");
		return NULL;
	}
	p1=head;
	while(n>p1->num&&p1->next!=NULL)
	{
		p2=p1;
		p1=p1->next;
	}
	
	if(n<p1->num||n>p1->num) printf("Not found");
	else if(p1==head) head=head->next;
	else if(p1->next==NULL) p2->next=NULL;
	else p2->next=p1->next;
	return head;
}
struct student*insert(struct student*head,struct student*p)
{
	struct student*p1,*p2=NULL; 
	p1=head;
	while(p1!=NULL&&p->num>p1->num&&p1->next!=NULL)
	{
		p2=p1;
		p1=p1->next;
	}
	if(head==NULL) 
	{
		head=p;	
	}
	else if(p1==head&&p1->next!=NULL) 
	{
		p->next=p1;
		head=p;
	}
	else if(p1->next==NULL&&p->num>p1->num&&p2==NULL) 
	{
		p1->next=p;
		p->next=NULL;
	}
	else if(p1->next==NULL&&p->num<p1->num&&p2==NULL)
	{
		p->next=p1;
		head=p;
	}
	else if(p2!=NULL&&p->num>p1->num)
	{   
		p1->next=p;
	    p->next=NULL;
	}
	else if(p2!=NULL&&p1->num>p->num)
	{
		p2->next=p;
		p->next=p1;
	}
	return head;
}
struct student*create()
{
	printf("Please enter student's information(学号=0 for exit)\n");
	printf("\n");
	int i=2;
	struct student*p,*p1,*p2;
	p=(struct student*)malloc(L);
	printf("\n");
	printf("请输入第1位同学的信息:\n");
	printf("学号:");
	scanf("%d",&p->num);
	if(p->num==0)
	{
		printf("finish\n");
		return NULL;
	} 
	getchar();
	printf("姓名:"); 
	gets(p->name);
	printf("性别(男/女):");
	gets(p->sex);
	printf("出生日期(xxxx.xx.xx):");
	scanf("%d.%d.%d",&p->date.year,&p->date.month,&p->date.day);
	p->next=NULL;
	if(p->date.year>2100||p->date.year<1900||p->date.month>12||p->date.month<1||p->date.day>31||p->date.day<1) 
	    {
	    	printf("输入有误（出生年份在1900--2100间)\n");
	    	return NULL;
		}
		printf("成绩:");
		scanf("%f",&p->score);
		if(p->score>100||p->score<0)
		{
			printf("输入超出范围(0--100)\n");
			return NULL;
		}
	while(1)
	{
		p1=(struct student*)malloc(L);
	    printf("\n");
	    printf("请输入第%d位同学的信息:\n",i);
	    printf("学号:");
	    scanf("%d",&p1->num);
	    if(p1->num==0)
	    {
	    	printf("finish\n");
		    break;
		}
	    getchar();
	    printf("姓名:"); 
	    gets(p1->name);
	    printf("性别(男/女):");
	    gets(p1->sex);
	    printf("出生日期(xxxx.xx.xx):");
	    scanf("%d.%d.%d",&p1->date.year,&p1->date.month,&p1->date.day);
	    if(p1->date.year>2100||p1->date.year<1900||p1->date.month>12||p1->date.month<1||p1->date.day>31||p1->date.day<1) 
	    {
	    	printf("输入有误（出生年份在1900--2100间）");
	    	return p;
		}
		printf("成绩:");
		scanf("%f",&p1->score); 
		if(p->score>100||p->score<0)
		{
			printf("输入超出范围(0--100)\n");
			return NULL;
		}
		p1->next=NULL;
	    i++;
	    p=insert(p,p1);
	}
	free(p1);
	return p;
}
void print(struct student*p)
{
	struct student *t;
	if(p==NULL) printf("Maybe there's nothing here\n");
	t=p;
	while(t!=NULL)
	{
		printf("%d\t%s\t%s\t%d.%d.%d\t %.2f\n",t->num,t->name,t->sex,t->date.year,t->date.month,t->date.day,t->score);
		t=t->next;
	}
	
}
struct student* browse(struct student *head)
{
	int test=1;
	struct student *t,*t1,*t2;
	t=head;
	if(t==NULL)
	{
		t=(struct student*)malloc(L);
		if(fscanf(fp,"%d\t%s\t%s%d.%d.%d%f",&t->num,t->name,&t->sex,&t->date.year,&t->date.month,&t->date.day,&t->score)<0) 
		{
			
			free(t);
			return NULL;
		}
		t->next=NULL;
		t1=(struct student*)malloc(L);
		while(fscanf(fp,"%d\t%s\t%s%d.%d.%d%f",&t1->num,t1->name,&t1->sex,&t1->date.year,&t1->date.month,&t1->date.day,&t1->score)>0)
		{
		    t1->next=NULL;
			t=insert(t,t1);
			t1=(struct student*)malloc(L);
		}
		free(t1);
		head=t;
	}
	else
	{
		t2=(struct student*)malloc(L);
		if(fscanf(fp,"%d\t%s\t%s%d.%d.%d%f",&t2->num,t2->name,&t2->sex,&t2->date.year,&t2->date.month,&t2->date.day,&t2->score)<0) 
		{
			
			free(t2);
			return NULL;
		}
		t2->next=NULL;
		t1=(struct student*)malloc(L);
		while(fscanf(fp,"%d\t%s\t%s%d.%d.%d%f",&t1->num,t1->name,&t1->sex,&t1->date.year,&t1->date.month,&t1->date.day,&t1->score)>0)
		{
		    t1->next=NULL;
			t2=insert(t2,t1);
			t1=(struct student*)malloc(L);
		}
		free(t1);
		head=t2;
	}
	return head;
}
int main()
{
	int a,n,m,c,c1,d;
	long b;
	char name_revise[12];
	struct student *p,*head,*t;
	head=NULL;
	printf("\t\t    ********Welcome to the system********\n");
	fp=fopen("学生信息.dat","a");
	if(fp==NULL)
	{
		fp=fopen("学生信息.dat","w");
	}
	printf("1.browse    2.search    3.insert    4.delete    5.create    6.revise    0.exit\n");
	scanf("%d",&a);
	while(a)
	{
		if(a==1)
		{
			fp=fopen("学生信息.dat","r");
			rewind(fp);
			printf("\n");
			head=browse(head);
			print(head);
			t=head;
			fp=fopen("学生信息.dat","w");
			
			while(t!=NULL)
			{
			    fprintf(fp,"%d\t%s\t%s\t%d.%d.%d  %.2f\n",t->num,t->name,t->sex,t->date.year,t->date.month,t->date.day,t->score);
				t=t->next;	
			}
			fclose(fp);
			fp=fopen("学生信息.dat","a");
		}
		
		
		if(a==2)
		{
			fp=fopen("学生信息.dat","r");
			rewind(fp);
			printf("\n");
		    head=browse(head);
		    t=head;
			printf("1.按学号查询\t2.按姓名查询\n");
			scanf("%d",&m);
			if(m==1)
			{
				printf("请输入学号:");
				scanf("%d",&b);
				while(t!=NULL&&t->num!=b) t=t->next;
				if(t!=NULL) printf("%d\t%s\t%s\t%d.%d.%d\t %.2f\n",t->num,t->name,t->sex,t->date.year,t->date.month,t->date.day,t->score);
				else printf("Not Found\n");
			}
			if(m==2)
			{
				char name_search[12];
				printf("请输入姓名:");
				scanf("%s",name_search);
				while(t!=NULL&&strcmp(name_search,t->name)!=0) t=t->next;
				if(t!=NULL) printf("%d\t%s\t%s\t%d.%d.%d\t %.2f\n",t->num,t->name,t->sex,t->date.year,t->date.month,t->date.day,t->score);
				else printf("Not Found\n");
			}
			fp=fopen("学生信息.dat","a");
		}
		
		
		if(a==3)
		{
			p=(struct student*)malloc(L);
	        printf("\n");
	        printf("请输入同学的信息:\n");
	        printf("学号:");
	        scanf("%d",&p->num);
	        if(p->num==0)
	        {
		        printf("finish\n");
		        continue;
	        } 
	        getchar();
	        printf("姓名:"); 
	        gets(p->name);
	        printf("性别(男/女):");
	        gets(p->sex);
	        printf("出生日期(xxxx.xx.xx):");
	        scanf("%d.%d.%d",&p->date.year,&p->date.month,&p->date.day);
            p->next=NULL;
            if(p->date.year>2100||p->date.year<1900||p->date.month>12||p->date.month<1||p->date.day>31||p->date.day<1) 
	        {
	    	printf("输入有误（出生年份在1900--2100间）");
	    	continue;
		    }
		    printf("成绩:");
		    scanf("%f",&p->score);
		    if(p->score>100||p->score<0)
		{
			printf("输入超出范围(0--100)\n");
			continue ;
		}
		    fp=fopen("学生信息.dat","r");
			rewind(fp);
			printf("\n");
		    head=browse(head);
            head=insert(head,p);
            t=head;
			fp=fopen("学生信息.dat","w");
			while(t!=NULL)
			{
			    fprintf(fp,"%d\t%s\t%s\t%d.%d.%d  %.2f\n",t->num,t->name,t->sex,t->date.year,t->date.month,t->date.day,t->score);
				t=t->next;	
			}
			fclose(fp);
			fp=fopen("学生信息.dat","a");
		}
		
		
		if(a==4)
		{
			printf("请输入需被删除学生的学号\n"); 
			scanf("%d",&n);
			fp=fopen("学生信息.dat","r");
			rewind(fp);
			printf("\n");
		    head=browse(head);
		    head=del(head,n);
		    t=head;
			fp=fopen("学生信息.dat","w");
			while(t!=NULL)
			{
			    fprintf(fp,"%d\t%s\t%s\t%d.%d.%d  %.2f\n",t->num,t->name,t->sex,t->date.year,t->date.month,t->date.day,t->score);
				t=t->next;	
			}
			fclose(fp);
			fp=fopen("学生信息.dat","a");
		}
		
		
		if(a==5)
		{
			printf("\n");
			head=create();
	        t=head;
	        while(t!=NULL)
	        {
		         fprintf(fp,"%d\t%s\t%s\t%d.%d.%d  %.2f\n",t->num,t->name,t->sex,t->date.year,t->date.month,t->date.day,t->score);
		          t=t->next;
	        }
	        fclose(fp);
			fp=fopen("学生信息.dat","a");
		}
		
		if(a==6)
		{
			fp=fopen("学生信息.dat","r");
			rewind(fp);
			printf("\n");
		    head=browse(head);
		    t=head;
		    printf("输入需被修改的学生的学号:");
		    scanf("%d",&c);
		    while(t!=NULL&&t->num!=c) t=t->next;
			if(t!=NULL) printf("%d\t%s\t%s\t%d.%d.%d\t %.2f\n",t->num,t->name,t->sex,t->date.year,t->date.month,t->date.day,t->score);
			else
			{
				printf("Not Found\n");
				continue;
			} 
		    
		    printf("1.学号  2.姓名  3.性别  4.生日  5.成绩\n");
		    scanf("%d",&c1);
		    if(c1==1)
		    {
		    	printf("请输入新的学号:");
		    	scanf("%d",&d);
		    	t->num=d;
		    	printf("%d\t%s\t%s\t%d.%d.%d\t %.2f\n",t->num,t->name,t->sex,t->date.year,t->date.month,t->date.day,t->score);
		    	t=head;
		    	head=browse(head);
		    	fp=fopen("学生信息.dat","w");
			    while(t!=NULL)
			    {
			         fprintf(fp,"%d\t%s\t%s\t%d.%d.%d  %.2f\n",t->num,t->name,t->sex,t->date.year,t->date.month,t->date.day,t->score);
				     t=t->next;	
			    }
			    fclose(fp);
			}
			if(c1==2)
			{
				printf("请输入新的姓名:");
				scanf("%s",name_revise);
				strcpy(t->name,name_revise);
				printf("%d\t%s\t%s\t%d.%d.%d\t %.2f\n",t->num,t->name,t->sex,t->date.year,t->date.month,t->date.day,t->score);
				t=head;
		    	fp=fopen("学生信息.dat","w");
			    while(t!=NULL)
			    {
			    fprintf(fp,"%d\t%s\t%s\t%d.%d.%d  %.2f\n",t->num,t->name,t->sex,t->date.year,t->date.month,t->date.day,t->score);
				t=t->next;	
			    }
			    fclose(fp);
			}
			if(c1==3)
			{
				char sex_revise[2];
				printf("请输入新的性别:");
				scanf("%s",&sex_revise);
				strcpy(t->sex,sex_revise);
				printf("%d\t%s\t%s\t%d.%d.%d\t %.2f\n",t->num,t->name,t->sex,t->date.year,t->date.month,t->date.day,t->score);
				fp=fopen("学生信息.dat","w");
			    while(t!=NULL)
			    {
			        fprintf(fp,"%d\t%s\t%s\t%d.%d.%d  %.2f\n",t->num,t->name,t->sex,t->date.year,t->date.month,t->date.day,t->score);
				    t=t->next;	
			    }
			    fclose(fp);
			}
			if(c1==4)
			{
				struct birthday revise;
				printf("请输入新的生日:");
				scanf("%d.%d.%d",&revise.year,&revise.month,&revise.day);
				if(revise.year>2100||revise.year<1900||revise.month>12||revise.month<1||revise.day>31||revise.day<1) 
	        {
	    	printf("输入有误（出生年份在1900--2100间）");
	    	continue;
		    }
				t->date.year=revise.year;
				t->date.month=revise.month;
				t->date.day=revise.day;
				printf("%d\t%s\t%s\t%d.%d.%d\t %.2f\n",t->num,t->name,t->sex,t->date.year,t->date.month,t->date.day,t->score);
				fp=fopen("学生信息.dat","w");
			    while(t!=NULL)
			    {
			        fprintf(fp,"%d\t%s\t%s\t%d.%d.%d  %.2f\n",t->num,t->name,t->sex,t->date.year,t->date.month,t->date.day,t->score);
				    t=t->next;	
			    }
			fclose(fp);
			}
			if(c1==5)
			{
				float score_revise;
				printf("请输入新的成绩:");
				scanf("%f",&score_revise);
				if(score_revise>100||score_revise<0)
		{
			printf("输入超出范围(0--100)\n");
			continue;
		}
				t->score=score_revise;
				printf("%d\t%s\t%s\t%d.%d.%d\t %.2f\n",t->num,t->name,t->sex,t->date.year,t->date.month,t->date.day,t->score);
				fp=fopen("学生信息.dat","w");
			    while(t!=NULL)
			    {
			       fprintf(fp,"%d\t%s\t%s\t%d.%d.%d  %.2f\n",t->num,t->name,t->sex,t->date.year,t->date.month,t->date.day,t->score);
				   t=t->next;	
			    }
			       fclose(fp);
			}
		    fp=fopen("学生信息.dat","a");
		}
		printf("1.browse    2.search    3.insert    4.delete    5.create    6.revise    0.exit\n");
		scanf("%d",&a);
	}
	fclose(fp);
} 

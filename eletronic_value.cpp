#pragma warning(disable: 4996)
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "eletronic_value.h"

void main(){
	char f_name_insert[50];
	char c;//Ŀ�ǵ� �Է�
	printf("���� ��� ������ ������ �Է��ϼ���\n");
	scanf("%s", f_name_insert);
	baseFile(f_name_insert);
	printf("\n����ġ ������ �������ϴ�.\n");
	

	printf("\n�������ϴ� ���ϸ��� �Է��ϼ���\n");//�ʱ�� test.cvs�� ����.
	scanf("%s", f_name_insert);
	file_bi(f_name_insert);//���Ϸ� ����� ���� ����Ʈ���� �ҷ���.

	printf("\n*******���ϴ� ��带 �Է��ϼ���*******\n");
	printf("*Y:�ش�⵵�� �� ����� M:���� �����*\n");
	printf("*S:�߰� ����    Q: ���������� ����   *\n");
	printf("**************************************\n");
	
	int y,m;//�⵵, ��, ���� ��뷮
	double m_u;
	while(1){
	printf("\nCommand> ");
		c = getch();
		putch(c);
		c = toupper(c);
		
		switch(c){
			case 'Y'://����Ʈ���� ����� �ش�⵵�� ã�ư�. ������� �ջ����
				printf("\n�� ����� �˰���� ������ �Է��Ͻÿ�!\n");
				scanf("%d",&y);
				bi_serch_year(y);
				break;
			case 'M':
				printf("\n�˻��ϰ���� �⵵�� ���� �� �� ������ �Է��Ͻÿ�\n");
				scanf("%d%d",&y,&m);
				bi_serch_year_month(y,m);
				break;
			case 'S'://����Ʈ�����߰�
				printf("�߰�:�� �� ��뷮\n");
				scanf("%d%d%lf",&y,&m,&m_u);
				insert_bt(y,m,cost(m_u,y,m),m_u);//�⵵, ��, ���ǻ�뷮,����� �Ѱ��ش�.
				break;
			case 'Q':
				printf("�����ϰ� ���� ������ �̸��� �����ÿ�");
				scanf("%s", f_name_insert);
				bi_file(f_name_insert,root);
				exit(1);
		}
	
	}

}
void baseFile(char*f_name)
{

	FILE *f;
	f = fopen(f_name, "r"); //������ ����.
	while (!feof(f)) {      //csv���� ���� , ���������� ���ڸ� �о���ش�!
		fscanf(f, "%d,%lf,%lf", &e_use[i],&e_base_cost[i],&e_add_cost[i]);
		i++;//������ ������ ��Ÿ����.
	}
	fclose(f);//������ ������ �۾��� ���ߴٸ� ������ �ݾ��ش�.
}

void file_bi(char*sub_f){
	int year,month;//�⵵ ��
	double month_use_mount;//���� ���� ��뷮;
	double month_cost;//�����.
	
	FILE *f;
	f = fopen(sub_f, "r"); //���Ͽ��� �о�´�.
	while (!feof(f)) {      
		fscanf(f, "%d, %d, %lf, %lf",&year,&month,&month_cost,&month_use_mount);
		insert_bt(year,month,month_cost,month_use_mount);
	}
	fclose(f);//������ ������ �۾��� ���ߴٸ� ������ �ݾ��ش�.
}

void insert_bt(int year, int month, double month_cost, double month_use_mount){

	tree_pointer temp;
	temp=(tree_pointer)malloc(sizeof(node));
	temp->year=year;//key�⵵
	for(int i = 0; i<12;i++){//�ϴ� �����Ϸ��°��� �ʱ�ȭ//���߿� ���Ҷ� �߰��� �����Ͱ� ������ ��������.
		temp->month_use_mount[i]=0.0;
		temp->month_cost[i]=0.0;
	}
	temp->month_use_mount[month-1]=month_use_mount; //�����뷮
	temp->month_cost[month-1]=month_cost;//���
	temp->right_child=temp->left_child=NULL;
	if(root==NULL){	root=temp;}
	else
	{
	   tree_pointer p,c; //��Ʈ�� ����ؼ� �ǲ���⸦ ����Ű�� �ֵ�.
		p=(tree_pointer)malloc(sizeof(node));
		c=(tree_pointer)malloc(sizeof(node));
		p=NULL;
		c=root;
		
		while(c){
			p=c;
			//�ش�⵵�� ������ ������ �ش� �⵵�� �����丸 �߰����ش�.
			if((c->year)==(temp->year)){//c=temp�� �Ұ�� ������ �ִ� �����Ͱ� �ٻ�����Ƿ� �ش� ���� �߰����ش�.
				c->month_use_mount[month-1]=month_use_mount; //�����뷮
				c->month_cost[month-1]=month_cost;//���
				break;
			}
			else if((c->year)>(temp->year)){ c=c->left_child;}
			else if((c->year)<(temp->year)){c=c->right_child;}
		}
			if((p->year)>(temp->year)){ p->left_child=temp;}
			else if((p->year)<(temp->year)){p->right_child=temp;}

	}

	

}

void bi_serch_year(int year){
	tree_pointer ptr;
	ptr=root;
	int serch=0;//ã������ �ܾ �ְ� ���� ��Ÿ����.
	double sum=0.0;
	while(ptr){
		if(ptr->year==year){
			for(int i=0;i<12;i++){sum+=ptr->month_cost[i];}
			printf("\n%d �⵵�� �� ������ %lf�Դϴ�.",year,sum);
			serch++;
			break;
			}
		else if((ptr->year)>year){ptr=ptr->left_child;}
		else if((ptr->year)<year){ptr=ptr->right_child;}
	}
	if(serch==0){printf("�ش�⵵�� �����ϴ�.");}
	
}

void bi_serch_year_month(int year, int month){
	int serch=0;
	tree_pointer ptr;
	ptr=root;
	while(ptr){
		if(ptr->year==year){
			if((ptr->month_cost[month-1]==0)){break;}//ó���� ����Ʈ���� �ҷ��ö� �Է¹��� ���� ���� 0���� �ʱ�ȭ ���ѳ��⿡ ���� ����.
			printf("\n%d�� %d���� �� ������ %lf �̰� �� ��뷮�� %lf �Դϴ�."
				,year,month,ptr->month_cost[month-1],ptr->month_use_mount[month-1]);
			serch++;
			break;}
		else if((ptr->year)>year){ptr=ptr->left_child;}
		else if((ptr->year)<year){ptr=ptr->right_child;}
	}
	if((serch==0)||(ptr->month_cost[month-1]==0)){printf("�ش絥���Ͱ� �������� �ʽ��ϴ�");}

}

double cost(double month_use_mount,int year,int month){
	double sum=0.0;
	//2016�� 8�� 7�� ������ ���� ����ó�� -50 ����
	if((year==2016)&&(month==7)){ 
		for(int i = 0 ;i<100  ; i++)
			{if(((double)e_use[i]<(month_use_mount-50.0))&&(month_use_mount-50.0)<=(double)e_use[i+1]){
				sum=e_base_cost[i+1]+(month_use_mount-50.0)*e_add_cost[i+1];}
			}
	}
	else if((year==2016)&&(month==8)){ 
		for(int i = 0 ;i<100  ; i++)
				{if(((double)e_use[i]<(month_use_mount-50.0))&&(month_use_mount-50.0)<=(double)e_use[i+1]){
					sum=e_base_cost[i+1]+(month_use_mount-50.0)*e_add_cost[i+1];}
				}
	}
	//�׿� ������ �κ��� �����ϴ� �̷���ó��
	else{
		for(int i = 0 ;i<100 ; i++)
		{  	 if(((double)e_use[i]<month_use_mount)&&month_use_mount<=(double)e_use[i+1]){
					sum=e_base_cost[i+1]+month_use_mount*e_add_cost[i+1];}
			}
	}

	
	return sum;
}

void bi_file(char*f_name,tree_pointer ptr){
	
	if(ptr){
		bi_file(f_name,ptr->left_child);
		insert_file(f_name,ptr);
		bi_file(f_name,ptr->right_child);
	}
	
	
}
void insert_file(char*f_name,tree_pointer ptr){
		FILE*f;
		f=fopen(f_name,"a");//��� a�� ������ �ִ� �����Ϳ� �߰��ؼ� �Է��ϴ°�!
		for(int i=0;i<12;i++){
			fprintf(f,"%d,%d,%lf,%lf\n",ptr->year,i+1,ptr->month_cost[i],ptr->month_use_mount[i]);
		}
		fclose(f);
}

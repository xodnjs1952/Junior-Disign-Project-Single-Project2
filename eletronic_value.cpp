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
	char c;//커맨드 입력
	printf("기준 비용 데이터 파일을 입력하세요\n");
	scanf("%s", f_name_insert);
	baseFile(f_name_insert);
	printf("\n기준치 상정이 끝났습니다.\n");
	

	printf("\n열고자하는 파일명을 입력하세요\n");//초기는 test.cvs로 연다.
	scanf("%s", f_name_insert);
	file_bi(f_name_insert);//파일로 저장된 것을 이진트리에 불러옴.

	printf("\n*******원하는 모드를 입력하세요*******\n");
	printf("*Y:해당년도의 총 전기료 M:월의 전기료*\n");
	printf("*S:추가 저장    Q: 파일저장후 종료   *\n");
	printf("**************************************\n");
	
	int y,m;//년도, 달, 달의 사용량
	double m_u;
	while(1){
	printf("\nCommand> ");
		c = getch();
		putch(c);
		c = toupper(c);
		
		switch(c){
			case 'Y'://이진트리에 저장된 해당년도를 찾아가. 전기료의 합산출력
				printf("\n총 요금을 알고싶은 연도를 입력하시오!\n");
				scanf("%d",&y);
				bi_serch_year(y);
				break;
			case 'M':
				printf("\n검색하고싶은 년도의 월을 년 월 순서로 입력하시오\n");
				scanf("%d%d",&y,&m);
				bi_serch_year_month(y,m);
				break;
			case 'S'://이진트리에추가
				printf("추가:년 월 사용량\n");
				scanf("%d%d%lf",&y,&m,&m_u);
				insert_bt(y,m,cost(m_u,y,m),m_u);//년도, 달, 달의사용량,비용을 넘겨준다.
				break;
			case 'Q':
				printf("저장하고 싶은 파일의 이름을 지으시오");
				scanf("%s", f_name_insert);
				bi_file(f_name_insert,root);
				exit(1);
		}
	
	}

}
void baseFile(char*f_name)
{

	FILE *f;
	f = fopen(f_name, "r"); //파일을 연다.
	while (!feof(f)) {      //csv파일 열면 , 을기준으로 숫자를 읽어와준다!
		fscanf(f, "%d,%lf,%lf", &e_use[i],&e_base_cost[i],&e_add_cost[i]);
		i++;//기준의 개수를 나타낸다.
	}
	fclose(f);//파일의 끝까지 작업을 다했다면 파일을 닫아준다.
}

void file_bi(char*sub_f){
	int year,month;//년도 월
	double month_use_mount;//월간 전기 사용량;
	double month_cost;//월비용.
	
	FILE *f;
	f = fopen(sub_f, "r"); //파일에서 읽어온다.
	while (!feof(f)) {      
		fscanf(f, "%d, %d, %lf, %lf",&year,&month,&month_cost,&month_use_mount);
		insert_bt(year,month,month_cost,month_use_mount);
	}
	fclose(f);//파일의 끝까지 작업을 다했다면 파일을 닫아준다.
}

void insert_bt(int year, int month, double month_cost, double month_use_mount){

	tree_pointer temp;
	temp=(tree_pointer)malloc(sizeof(node));
	temp->year=year;//key년도
	for(int i = 0; i<12;i++){//일단 저장하려는것을 초기화//나중에 더할때 중간에 데이터가 없으면 오류난다.
		temp->month_use_mount[i]=0.0;
		temp->month_cost[i]=0.0;
	}
	temp->month_use_mount[month-1]=month_use_mount; //전기사용량
	temp->month_cost[month-1]=month_cost;//비용
	temp->right_child=temp->left_child=NULL;
	if(root==NULL){	root=temp;}
	else
	{
	   tree_pointer p,c; //루트는 계속해서 맨꼭대기를 가리키고 있따.
		p=(tree_pointer)malloc(sizeof(node));
		c=(tree_pointer)malloc(sizeof(node));
		p=NULL;
		c=root;
		
		while(c){
			p=c;
			//해당년도의 정보가 있으면 해당 년도의 월개념만 추가해준다.
			if((c->year)==(temp->year)){//c=temp를 할경우 기존에 있던 데이터가 다사라지므로 해당 월만 추가해준다.
				c->month_use_mount[month-1]=month_use_mount; //전기사용량
				c->month_cost[month-1]=month_cost;//비용
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
	int serch=0;//찾으려는 단어가 있고 없을 나타낸다.
	double sum=0.0;
	while(ptr){
		if(ptr->year==year){
			for(int i=0;i<12;i++){sum+=ptr->month_cost[i];}
			printf("\n%d 년도의 총 전기료는 %lf입니다.",year,sum);
			serch++;
			break;
			}
		else if((ptr->year)>year){ptr=ptr->left_child;}
		else if((ptr->year)<year){ptr=ptr->right_child;}
	}
	if(serch==0){printf("해당년도가 없습니다.");}
	
}

void bi_serch_year_month(int year, int month){
	int serch=0;
	tree_pointer ptr;
	ptr=root;
	while(ptr){
		if(ptr->year==year){
			if((ptr->month_cost[month-1]==0)){break;}//처음에 이진트리에 불러올때 입력받지 않은 달은 0으로 초기화 시켜놨기에 쓸모가 없다.
			printf("\n%d년 %d월의 총 전기료는 %lf 이고 총 사용량은 %lf 입니다."
				,year,month,ptr->month_cost[month-1],ptr->month_use_mount[month-1]);
			serch++;
			break;}
		else if((ptr->year)>year){ptr=ptr->left_child;}
		else if((ptr->year)<year){ptr=ptr->right_child;}
	}
	if((serch==0)||(ptr->month_cost[month-1]==0)){printf("해당데이터가 존재하지 않습니다");}

}

double cost(double month_use_mount,int year,int month){
	double sum=0.0;
	//2016년 8월 7월 누진세 인하 예외처리 -50 인하
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
	//그외 나머지 부분은 동일하니 이렇게처리
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
		f=fopen(f_name,"a");//모드 a는 기존에 있던 데이터에 추가해서 입력하는것!
		for(int i=0;i<12;i++){
			fprintf(f,"%d,%d,%lf,%lf\n",ptr->year,i+1,ptr->month_cost[i],ptr->month_use_mount[i]);
		}
		fclose(f);
}

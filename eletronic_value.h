//년도수를 키로하는 이진트리의 노드
typedef struct node *tree_pointer;
typedef struct node{
	int year;                 //년도 
	double month_use_mount[12];  //월별 사용량
	double month_cost[12];       //월별 가격
	tree_pointer left_child;//처음들어온 년도보다 적은년도가 들어오는경우
	tree_pointer right_child;//처음들어온 년도보다 큰년도가 들어오는경우
}node;

tree_pointer root = NULL;             //root
int i=0;
int e_use[100];//키로와트수
double e_base_cost[100];//키로와트수당 기본요금
double e_add_cost[100];//키로와트수당 추가요금

//함수
void baseFile(char*); //전기사용량 기준파일을 열어서 기준 데이터를 저장시키는 함수
void file_bi(char*);  //파일속의 데이터를 사용할수 있게끔 이진트리로 전환해준다.
void insert_bt(int, int, double,double);//이진트리에 정보들을 삽입해준다(년도, 월, 전기료, 전기 사용량)순
void bi_serch_year(int); //'Y'명령어를 입력받으면 실행되는 함수 해당년도의 총합을 계산해서 보여준다.
void bi_serch_year_month(int, int);//'M'명령어를 입력받으면 실행되는 함수 해당되는 달의 전기료와 전기사용량 제시. 
double cost(double,int,int);//전기료의 비용을 계산하는 함수 (2016년 7,8월에는 예외처리해서 누진세 할인적용!!)
void bi_file(char*,tree_pointer);//'Q'명령어를 누르면 실행되서 중위 순환해서 이진트리의 데이터들을 넘겨준다.
void insert_file(char*,tree_pointer);//이진트리에서 중위 순환으로 넘겨받는 파라미터들을 파일의 형태로 저장해준다.

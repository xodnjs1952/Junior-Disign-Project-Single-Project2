//�⵵���� Ű���ϴ� ����Ʈ���� ���
typedef struct node *tree_pointer;
typedef struct node{
	int year;                 //�⵵ 
	double month_use_mount[12];  //���� ��뷮
	double month_cost[12];       //���� ����
	tree_pointer left_child;//ó������ �⵵���� �����⵵�� �����°��
	tree_pointer right_child;//ó������ �⵵���� ū�⵵�� �����°��
}node;

tree_pointer root = NULL;             //root
int i=0;
int e_use[100];//Ű�ο�Ʈ��
double e_base_cost[100];//Ű�ο�Ʈ���� �⺻���
double e_add_cost[100];//Ű�ο�Ʈ���� �߰����

//�Լ�
void baseFile(char*); //�����뷮 ���������� ��� ���� �����͸� �����Ű�� �Լ�
void file_bi(char*);  //���ϼ��� �����͸� ����Ҽ� �ְԲ� ����Ʈ���� ��ȯ���ش�.
void insert_bt(int, int, double,double);//����Ʈ���� �������� �������ش�(�⵵, ��, �����, ���� ��뷮)��
void bi_serch_year(int); //'Y'��ɾ �Է¹����� ����Ǵ� �Լ� �ش�⵵�� ������ ����ؼ� �����ش�.
void bi_serch_year_month(int, int);//'M'��ɾ �Է¹����� ����Ǵ� �Լ� �ش�Ǵ� ���� ������ �����뷮 ����. 
double cost(double,int,int);//������� ����� ����ϴ� �Լ� (2016�� 7,8������ ����ó���ؼ� ������ ��������!!)
void bi_file(char*,tree_pointer);//'Q'��ɾ ������ ����Ǽ� ���� ��ȯ�ؼ� ����Ʈ���� �����͵��� �Ѱ��ش�.
void insert_file(char*,tree_pointer);//����Ʈ������ ���� ��ȯ���� �Ѱܹ޴� �Ķ���͵��� ������ ���·� �������ش�.

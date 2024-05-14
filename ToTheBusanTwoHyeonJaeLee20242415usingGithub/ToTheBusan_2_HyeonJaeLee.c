//2-1 20�� �̳� �Լ��� �λ���(1) ���� 2-2 �Ķ���� ����
//---1�� 2������� ����---
// Sleep() ���� ������ �Է½ÿ��� ����, ������ �̵��߰�, 
//�ù�, ����, ������ ���� �ൿ, ��� ǥ��
//---���� �߰�---
//������ ü�� �߰�
//�ùξ�׷�, ������ ��׷� (���� �ൿ ����)
//---�Է°� ó��---
//��� �Է¿� ���� ��ȿ �� �Է� �� �� ���� �ٽ� �Է� �ޱ�
//�ݵ�� ���� 1���� �Էµȴٰ� ����
//�迭 ���������� ����
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//�Ķ����
#define LEN_MIN 15
#define LEN_MAX 50
#define STM_MIN 0
#define STM_MAX 5
#define PROB_MIN 10
#define PROB_MAX 90
#define AGGRO_MIN 0
#define AGGRO_MAX 5

// ������ �̵�����
#define MOVE_LEFT 1
#define MOVE_STAY 0

// ������ ���� ���
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// ������ �ൿ
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

// (�Է�,���� �����Լ�) ��Ʈ�� ����ϴ� �Լ�
void intro(void);
void spacing(void);
int get_train_length(void);
int get_probability(void);

void intro(void) {
	printf("==================================================\n");
	printf("[                 ^                              ]\n");
	printf("[                 *                      +       ]\n");
	printf("[       ***^***^*****^***^***            !       ]\n");
	printf("[              * * * *               $   +       ]\n");
	printf("[            &         &             $   !       ]\n");
	printf("[           *           *       @#@#@#   +       ]\n");
	printf("[            &         &             $   !       ]\n");
	printf("[              * * * *               $   +       ]\n");
	printf("[                                        !       ]\n");
	printf("[                                        +       ]\n");
	printf("[                        @ @ @ @                 ]\n");
	printf("[                      @         @               ]\n");
	printf("[                     @           @              ]\n");
	printf("[                      @         @               ]\n");
	printf("[                        @ @ @ @                 ]\n");
	printf("==================================================\n");
	printf("====�������� �����ؼ� ����κ��� �ù��� ���Ѷ�====\n");
	printf("====   �� ��Ʈ�ڽ� �����ε� �ϰ� �����ߴ�?    ====\n");
}
void spacing(void) {
	printf("\n");
}

int get_train_length(void) {
	int t_length;
	printf("train length(15~50)>> ");
	scanf_s("%d", &t_length);
	return t_length;
}

int get_probability(void){
	int p;
	printf("percentile probability 'p' (10~90)>> ");
	scanf_s("%d", &p);
	return p;
}


int main() {
	intro();
	spacing();
	int t_length = get_train_length();
	printf("%d", t_length);
	spacing();
	int p = get_probability();
	printf("%d", p);
	spacing();
	return 0;
}

// (�Է�,���� �����Լ�) ����Ű �Է����� ���� �������ϴ� �Լ�
// (�Է� ���� �Լ�)������ ���̸� �Է��ϴ� �Լ�
// (�Է� ���� �Լ�)Ȯ���� �Է��ϴ� �Լ�
// ---Ȯ���� ���� ���� �Է�---
// ���� ���� �� �Է½� ��ȿ�� �� �Է� �� ������ �ٽ� �Է��ϴ� �Լ�
// ��ȿ�� �Է� �ȳ��� �ٽ� �Է� ����
// ---���� �ʱ���� ���----
// ���� �ʱ� ���� ��� �Լ�
// ----�ù�, ���� �̵�---
// �ù� �̵� �����ϴ� �Լ�
// ���� �̵� �����ϴ� �Լ�
// ---��ȭ�� ���� ���� ���---
// ��ȭ�� ���� ���� ��� �Լ�
// ---�ù�, ���� �̵� ���� ���---
// �ù��� �̵� ���� ����ϴ� �Լ�
// ������ �̵� ���� ����ϴ� �Լ�
// ---���� �¸��� ���---
// �ù� �¸� ��� �Լ�
// ���� �¸� ��� �Լ�


//int main() {
// 
//	srand((unsigned int)time(NULL));
// 
//	{
//		//���� ���̿� Ȯ�� p(%) �Է¹ޱ� �߸��� �Է� -> ���α׷� ����
//		//int citizen, zombie, madongsuk;
//
//		if ((LEN_MIN <= t_length && t_length <= LEN_MAX) && (PROB_MIN <= p && p <= PROB_MAX))
//		{
//			//���� �ʱ� ���� ���
//			citizen = t_length - 6;
//			zombie = t_length - 3;
//			madongsuk = t_length - 2;
//
//			printf("\n");
//
//			for (int i = 0; i < t_length; i++) {
//				printf("#");
//			}
//
//			printf("\n");
//
//			for (int i = 0; i < t_length; i++) {
//
//				if (i == 0 || i == t_length - 1) {
//					printf("#");
//				}
//
//				else if (i == citizen) {
//					printf("C");
//				}
//				else if (i == zombie) {
//					printf("Z");
//				}
//				else if (i == madongsuk) {
//					printf("M");
//				}
//				else {
//					printf(" ");
//				}
//
//			}
//
//			printf("\n");
//
//			for (int i = 0; i < t_length; i++) {
//				printf("#");
//			}
//
//			printf("\n");
//
//			int after_citizen = citizen;
//			int after_zombie = zombie;
//
//			int turn = 1;
//
//			while (after_citizen + 1 != after_zombie && after_citizen != 1) {
//				int r = rand() % 100;
//				//�ù� �̵�	
//				int before_citizen = after_citizen;
//
//				if (r >= p) {
//					after_citizen = after_citizen - 1;
//				}
//				else {
//					after_citizen = after_citizen;
//				}
//				//���� �̵� 
//
//				int before_zombie = after_zombie;
//
//				if (turn % 2 == 1 && r < p) {
//					after_zombie = after_zombie - 1;
//				}
//				else if (turn % 2 == 1 && r >= p) {
//					after_zombie = after_zombie;
//				}
//				else {
//					after_zombie = after_zombie;
//				}
//
//
//				//���� ���� ���
//				printf("\n\n");
//
//				for (int i = 0; i < t_length; i++) {
//					printf("#");
//				}
//
//				printf("\n");
//
//				for (int i = 0; i < t_length; i++) {
//
//					if (i == 0 || i == t_length - 1) {
//						printf("#");
//					}
//
//					else if (i == after_citizen) {
//						printf("C");
//					}
//					else if (i == after_zombie) {
//						printf("Z");
//					}
//					else if (i == madongsuk) {
//						printf("M");
//					}
//					else {
//						printf(" ");
//					}
//
//				}
//
//				printf("\n");
//
//				for (int i = 0; i < t_length; i++) {
//					printf("#");
//				}
//
//				printf("\n\n");
//
//				//�ù�, ���� ���� ���
//				//�ù� ���� ���
//				if (before_citizen == after_citizen) {
//					printf("citizen: stay %d\n", before_citizen);
//				}
//				else {
//					printf("citizen: %d -> %d\n", before_citizen, after_citizen);
//				}
//				//���� ���� ���
//				if (turn % 2 == 1 && before_zombie == after_zombie) {
//					printf("zombie: stay %d\n", before_zombie);
//				}
//				else if (turn % 2 == 1 && before_zombie == after_zombie + 1) {
//					printf("zombie: %d -> %d\n", before_zombie, after_zombie);
//				}
//				else {
//					printf("zombie: stay %d (cannot move)\n", before_zombie);
//				}
//
//				turn++;
//				Sleep(4000);
//			}
//			// �ƿ�Ʈ�� 4���̳� ��������, ���� ���� ���(����, ����)
//			//�ù� �¸�
//			printf("\n");
//
//			if (after_citizen == 1) {
//				printf("SUCCESS!\n");
//				printf("citizen(s) escaped to the next train");
//			}
//			//���� �¸�
//			else if (after_citizen + 1 == after_zombie) {
//				printf("GAME OVER!\n");
//				printf("Citizen(s) has(have) ben attacked by a zombie");
//			}
//		}
//		//���� ���� �� �Է½� ���α׷� ����
//		else {
//			printf("<Notice>\n");
//			printf("Because of the wrong input values, the program is ended.\n");
//			printf("Please enter correct train length and percentile probability to start the program");
//		}
//
//	}
//	return 0;
//}
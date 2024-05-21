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
#include <Windows.h>
//�Ķ����
#define LEN_MIN 15 // ���� ����
#define LEN_MAX 50
#define STM_MIN 0 // ������ ü��
#define STM_MAX 5
#define PROB_MIN 10 // Ȯ��
#define PROB_MAX 90
#define AGGRO_MIN 0 // ��׷� ���� 
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

void intro(void);
int get_train_length(void);
int get_probability(void);
int get_random_number(void);

void first_train_state(int, int, int, int);

int calc_citizen_moving(int, int, int);
int calc_zombie_moving(int, int, int, int);

void after_train_state(int, int, int, int);

void print_citizen_state(int, int);
void print_zombie_state(int, int, int);

void victory_citizen(int);
void victory_zombie(int, int);

int t_length;
int p, r;
int first_citizen, first_zombie, first_madongsuk;
int turn;
int before_citizen, before_zombie, before_madongsuk;
int after_citizen, after_zombie, after_madongsuk;

// ��Ʈ�� �Լ�
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
// �ùٸ� ���� �� �ޱ�
int get_train_length(void) {
	int t_length;
	while (1) {
		printf("train length(15~50)>> ");
		scanf_s("%d", &t_length);
		if ((LEN_MIN <= t_length && t_length <= LEN_MAX)) {
			break;
		}
	}
	return t_length;
}
// �ùٸ� Ȯ�� �� �ޱ�
int get_probability(void){
	while (1) {
		printf("percentile probability 'p' (10~90)>> ");
		scanf_s("%d", &p);
		if (PROB_MIN <= p && p <= PROB_MAX) {
			return p;
			break;
		}
	}
}
// �ʱ� ���� ���� ��� �Լ�
void first_train_state(int t_length, int first_citizen, int first_zombie, int first_madongsuk) {

	for (int i = 0; i < t_length; i++) {
		printf("#");
	}
	
	printf("\n");

	for (int i = 0; i < t_length; i++) {

		if (i == 0 || i == t_length - 1) {
			printf("#");
		}
		else if (i == first_citizen) {
			printf("C");
		}
		else if (i == first_zombie) {
			printf("Z");
		}
		else if (i == first_madongsuk) {
			printf("M");
		}
		else {
			printf(" ");
		}

	}

	printf("\n");
	
	for (int i = 0; i < t_length; i++) {
		printf("#");
	}

	printf("\n");
}
// ���� �� ���� �Լ� 
int get_random_number(void) {
	srand((unsigned int)time(NULL));
	r = rand() % 100;
	return r;
}
// �ù� �̵� ��� �Լ�
int calc_citizen_moving(int r, int p, int after_citizen) {
	if (r >= p) {
		after_citizen = after_citizen - 1;
		
	}
	else if (r < p) {
		after_citizen = after_citizen;
	}
	return after_citizen;
}
// ���� �̵� ��� �Լ� 
int calc_zombie_moving(int turn, int r, int p, int after_zombie) {
	if (turn % 2 == 1 && r < p) {
		after_zombie = after_zombie - 1;
	}
	else if (turn % 2 == 1 && r >= p) {
		after_zombie = after_zombie;
	}
	else {
		after_zombie = after_zombie;
	}
	return after_zombie;
}

void after_train_state(int t_length, int after_citizen, int after_zombie, int first_madongsuk) {
	for (int i = 0; i < t_length; i++) {
		printf("#");
	}
	printf("\n");
	for (int i = 0; i < t_length; i++) {

		if (i == 0 || i == t_length - 1) {
			printf("#");
		}
		else if (i == after_citizen) {
			printf("C");
		}
		else if (i == after_zombie) {
			printf("Z");
		}
		else if (i == first_madongsuk) {
			printf("M");
		}
		else {
			printf(" ");
		}

	}
	printf("\n");
	for (int i = 0; i < t_length; i++) {
		printf("#");
	}
	printf("\n");	
}
//�ù� ���� ���
void print_citizen_state(int before_citizen, int after_citizen) {
	if (before_citizen == after_citizen) {
		printf("citizen: stay %d\n", before_citizen);
	}
	else {
		printf("citizen: %d -> %d\n", before_citizen, after_citizen);
	}
}
//���� ���� ���
void print_zombie_state(int turn, int before_zombie, int after_zombie) {
	if (turn % 2 == 1 && before_zombie == after_zombie) {
		printf("zombie: stay %d\n", before_zombie);
	}
	else if (turn % 2 == 1 && before_zombie == after_zombie + 1) {
		printf("zombie: %d -> %d\n", before_zombie, after_zombie);
	}
	else {
		printf("zombie: stay %d (cannot move)\n", before_zombie);
	}
}

//�ù� �¸� ���
void victory_citizen(int after_citizen) {
	if (after_citizen == 1) {
		printf("\n");
		printf("SUCCESS!\n");
		printf("citizen(s) escaped to the next train");
	}
}
//���� �¸� ���
void victory_zombie(int after_citizen, int after_zombie) {
	if (after_citizen + 1 == after_zombie) {
		printf("\n");
		printf("GAME OVER!\n");
		printf("Citizen(s) has(have) ben attacked by a zombie");
	}
	
}
// main �Լ�
int main() {
	// ��Ʈ��
	intro();
	// ���� , Ȯ�� �Է�
	t_length = get_train_length();//ok
	p = get_probability();
	//������ ����15�̸� �ù� �ʱ� ��ġ9 
	// �ù�, ����, ������ �ʱ� ��ġ
	first_citizen = t_length - 6;
	first_zombie = t_length - 3;
	first_madongsuk = t_length - 2;

	// ���� �ʱ� ���� ���
	first_train_state(t_length, first_citizen, first_zombie, first_madongsuk);

	turn = 1;
	
	after_citizen = first_citizen;
	after_zombie = first_zombie;

	while (after_citizen + 1 != after_zombie && after_citizen != 1) {
		 
		r = get_random_number();
		//�ù� �̵� ���
		before_citizen = after_citizen;
		after_citizen = calc_citizen_moving(r, p, after_citizen);
		
		//���� �̵� ���
		before_zombie = after_zombie;
		after_zombie = calc_zombie_moving(turn, r, p, after_zombie);
		
		printf("\n");
		//������ ���� �� ���� ����
		after_train_state(t_length, after_citizen, after_zombie, first_madongsuk);

		printf("\n\n");

		//������ ���� �� �ù� �̵� ���
		print_citizen_state(before_citizen, after_citizen);
		//������ ���� �� ���� �̵� ���
		print_zombie_state(turn, before_zombie, after_zombie);
		turn++;
		Sleep(4000);//for test
	}
	//�ù� �¸�
	victory_citizen(after_citizen);
	//���� �¸�
	victory_zombie(after_citizen, after_zombie);
	return 0;
}
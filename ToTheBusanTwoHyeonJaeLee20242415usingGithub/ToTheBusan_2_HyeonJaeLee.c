//2-2 Sleep()����
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//2-2 �Ķ���� ����
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

//2-1 �λ���(1)�ڵ带 20�� �̳� �Լ���� ���� (�迭�� ��������)
void intro(void);
int get_train_length(void);
int get_probability(void);
int get_random_number(void);
int get_madongsuk_stamina(void);


void first_train_state(int, int, int, int);

int calc_citizen_moving(int, int, int);
int calc_citizen_aggro(int, int, int);
int get_madongsuk_moving(void);

int calc_zombie_moving(int, int, int, int);

void after_train_state(int, int, int, int);

void print_citizen_state(int, int, int);
void print_zombie_state(int, int, int);

int calc_madongsuk_moving(int);
void print_madongsuk_state(int, int, int, int);
int calc_madongsuk_aggro(int, int);

void victory_citizen(int);
void victory_zombie(int, int);

int t_length, madongsuk_stamina;
int p, r;
int first_citizen, first_zombie, first_madongsuk;
int turn;
int before_citizen, before_zombie, before_madongsuk;
int after_citizen, after_zombie, after_madongsuk;
int citizen_aggro, madongsuk_aggro;
int madongsuk_moving;

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
	while (1) {
		printf("train length(15~50)>> ");
		scanf_s("%d", &t_length);
		if ((LEN_MIN <= t_length && t_length <= LEN_MAX)) {
			return t_length;
			break;
		}
	}
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
// ������ ���¹̳� �Է� �Լ�
int get_madongsuk_stamina(void) {
	while (1) {
		printf("madongsuk stamina(0~5)>> ");
		scanf_s("%d", &madongsuk_stamina);
		if ((STM_MIN <= madongsuk_stamina && madongsuk_stamina <= STM_MAX)) {
			return madongsuk_stamina;
			break;
		}
	}
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
// �ù� ��׷� ��� �Լ�
int calc_citizen_aggro(int r, int p, int citizen_aggro) {
	if (r >= p) {
		citizen_aggro++;
	}
	else {
		citizen_aggro--;
	}
	return citizen_aggro;
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

void after_train_state(int t_length, int after_citizen, int after_zombie, int after_madongsuk) {
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
		else if (i == after_madongsuk) {
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
void print_citizen_state(int before_citizen, int after_citizen, int citizen_aggro) {
	if (before_citizen == after_citizen) {
		printf("citizen: stay %d (aggro: %d)\n", before_citizen, citizen_aggro);
	}
	else {
		printf("citizen: %d -> %d (aggro: %d)\n", before_citizen, after_citizen, citizen_aggro);
	}
}

int get_madongsuk_moving(void) {
	while (1) {
		printf("madongsuk move(0:stay, 1:left)>> ");
		scanf_s("%d", &madongsuk_moving);
		if (madongsuk_moving == MOVE_STAY || madongsuk_moving == MOVE_LEFT) {
			return madongsuk_moving;
			break;
		}
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

int calc_madongsuk_moving(int madongsuk_moving) {
	if (madongsuk_moving == MOVE_STAY) {
		madongsuk_moving = madongsuk_moving;
	}
	else {
		madongsuk_moving = madongsuk_moving - 1;
	}
	return madongsuk_moving;
}

void print_madongsuk_state(int before_madongsuk, int after_madongsuk, int madongsuk_aggro, int madongsuk_stamina) {
	if (madongsuk_moving == MOVE_STAY) {
		printf("madongsuk : stay %d(aggro: %d, stamina: %d)", before_madongsuk, madongsuk_aggro, madongsuk_stamina);
	}
	else {
		printf("madongsuk:  %d -> %d(aggro: %d, stamina: %d)", before_madongsuk, after_madongsuk, madongsuk_aggro, madongsuk_stamina);
	}
	
}
// ������ ��׷� ���
int calc_madongsuk_aggro(int madongsuk_movinging, int madongsuk_aggro ) {
	if (madongsuk_moving == MOVE_STAY) {
		madongsuk_aggro--;
	}
	else {
		madongsuk_aggro++;
	}
	return madongsuk_aggro;
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
	//2-2 �Է°� ó��: �����Է�, ������ ü�� �Է�, Ȯ�� �Է�
	t_length = get_train_length();//ok
	madongsuk_stamina = get_madongsuk_stamina();
	p = get_probability();
	
	//2-2 �ʱ� ���� ���
	// �ù�, ����, ������ �ʱ� ��ġ
	first_citizen = t_length - 6;
	first_zombie = t_length - 3;
	first_madongsuk = t_length - 2;

	// ���� �ʱ� ���� ���
	first_train_state(t_length, first_citizen, first_zombie, first_madongsuk);

	turn = 1;
	
	after_citizen = first_citizen;
	after_zombie = first_zombie;
	after_madongsuk = first_madongsuk;

	//2-2 �ù�, ������ ��׷� �߰�
	citizen_aggro = 1;
	madongsuk_aggro = 1;

	while (after_citizen + 1 != after_zombie && after_citizen != 1) {
		 //2-2 �̵� ������
		r = get_random_number();
		//�ù� �̵� ���
		before_citizen = after_citizen;
		after_citizen = calc_citizen_moving(r, p, after_citizen);
		
		//���� �̵� ���
		before_zombie = after_zombie;
		after_zombie = calc_zombie_moving(turn, r, p, after_zombie);
		
		printf("\n");
		//������ ���� �� ���� ����
		after_train_state(t_length, after_citizen, after_zombie, after_madongsuk);

		printf("\n\n");

		//1������ ���� �� �ù� �̵� ���
		print_citizen_state(before_citizen, after_citizen, citizen_aggro);
		// �ù� ��׷� ���
		citizen_aggro = calc_citizen_aggro(r, p, citizen_aggro);

		//1������ ���� �� ���� �̵� ���
		print_zombie_state(turn, before_zombie, after_zombie);
		
		printf("\n\n");

		// ������ �̵� �Է�
		madongsuk_moving = get_madongsuk_moving();
		// ������ �̵� ���
		before_madongsuk = after_madongsuk;
		after_madongsuk = calc_madongsuk_moving(madongsuk_moving);
		// ������ �̵� �ݿ�
		after_train_state(t_length, after_citizen, after_zombie, after_madongsuk);

		printf("\n\n");

		//������ �̵� ���
		print_madongsuk_state(before_madongsuk, after_madongsuk, madongsuk_aggro, madongsuk_stamina);
		//������ ��׷� ���
		madongsuk_aggro = calc_madongsuk_aggro(after_madongsuk, madongsuk_aggro);
		
		printf("\n\n");

		//2-2 �ൿ ������

		turn++;		
	}
	//�ù� �¸�
	victory_citizen(after_citizen);
	//���� �¸�
	victory_zombie(after_citizen, after_zombie);
	return 0;
}
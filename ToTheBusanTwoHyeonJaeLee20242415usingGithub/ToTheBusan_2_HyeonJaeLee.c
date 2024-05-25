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
//�Լ� �����
void intro(void);
int get_train_length(void);
int get_madongsuk_stamina(void);
int get_probability(void);

int get_random_number(void);

void first_train_state(int, int, int, int);

int calc_citizen_moving(int, int, int);
int calc_after_citizen_aggro(int, int, int);
int calc_zombie_moving(int, int, int, int);

void after_train_state(int, int, int, int);

void print_citizen_state(int, int, int, int);
void print_zombie_state(int, int, int);

int get_madongsuk_moving(void);
int calc_madongsuk_moving(int);
int calc_madongsuk_aggro(int, int);

void print_madongsuk_state(int, int, int, int, int);

void citizen_acting(int);
int calc_madongsuk_stamina(int, int, int, int, int);
void zombie_acting(int, int, int, int, int, int, int);

//���� �����
int t_length, first_madongsuk_stamina;
int p;
int r;
int first_citizen, first_zombie, first_madongsuk;

int turn;

int after_citizen, after_zombie, after_madongsuk;
int before_citizen, before_zombie, before_madongsuk;

int first_citizen_aggro, first_madongsuk_aggro;
int after_citizen_aggro, after_madongsuk_aggro;
int before_citizen_aggro, before_madongsuk_aggro;

int madongsuk_moving;

int before_madongsuk_stamina;
int after_madongsuk_stamina;

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
// ������ ���¹̳� �Է� �Լ�
int get_madongsuk_stamina(void) {
	while (1) {
		printf("madongsuk stamina(0~5)>> ");
		scanf_s("%d", &first_madongsuk_stamina);
		if ((STM_MIN <= first_madongsuk_stamina && first_madongsuk_stamina <= STM_MAX)) {
			return first_madongsuk_stamina;
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

// �ù� �̵� ��� �Լ�
int calc_citizen_moving(int r, int p, int after_citizen) {
	if (r >= p) {
		after_citizen = after_citizen - 1;
		return after_citizen;
	}
	else if (r < p) {
		after_citizen = after_citizen;
		return after_citizen;
	}
}
// �ù� ��׷� ��� �Լ�
int calc_after_citizen_aggro(int r, int p, int after_citizen_aggro) {
	if (r >= p) {
		after_citizen_aggro++;
		if (after_citizen_aggro > AGGRO_MAX) {
			after_citizen_aggro--;
		}
	}
	else if (r < p) {
		after_citizen_aggro--;
		if (after_citizen_aggro < AGGRO_MIN) {
			after_citizen_aggro++;
		}
	}
	return after_citizen_aggro;
}
// ���� �̵� ��� �Լ� 
int calc_zombie_moving(int turn, int after_citizen_aggro, int after_madongsuk_aggro, int after_zombie) {
	if (turn % 2 == 1 && after_citizen_aggro >= after_madongsuk_aggro) {
		after_zombie = after_zombie - 1;
		return after_zombie;
	}
	else if (turn % 2 == 1 && after_citizen_aggro < after_madongsuk_aggro) {
		after_zombie = after_zombie + 1;
		return after_zombie;
	}
	else {
		after_zombie = after_zombie;
		return after_zombie;
	}
}
// �̵� �ݿ��� ���� ���� ��� �Լ�
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
void print_citizen_state(int before_citizen, int after_citizen, int before_citizen_aggro, int after_citizen_aggro) {
	if (before_citizen == after_citizen) {
		printf("citizen: stay %d (aggro: %d -> %d)\n", before_citizen, before_citizen_aggro, after_citizen_aggro);
	}
	else {
		printf("citizen: %d -> %d (aggro: %d -> %d)\n", before_citizen, after_citizen, before_citizen_aggro, after_citizen_aggro);
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
//������ �̵� �Է�
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
// ������ �̵� ���
int calc_madongsuk_moving(int madongsuk_moving) {
	if (madongsuk_moving == MOVE_STAY) {
		madongsuk_moving = madongsuk_moving;
		return madongsuk_moving;
	}
	else {
		madongsuk_moving = madongsuk_moving - 1;
		return madongsuk_moving;
	}
}
// ������ ��׷� ���
int calc_madongsuk_aggro(int madongsuk_movinging, int madongsuk_aggro) {
	if (madongsuk_moving == MOVE_STAY) {
		madongsuk_aggro--;
		if (madongsuk_aggro < AGGRO_MIN) {
			madongsuk_aggro++;
		}
		return madongsuk_aggro;
	}
	else {
		madongsuk_aggro++;
		if (madongsuk_aggro > AGGRO_MAX) {
			madongsuk_aggro--;
		}
		return madongsuk_aggro;
	}
}
// ������ �̵� ���
void print_madongsuk_state(int before_madongsuk, int after_madongsuk, int before_madongsuk_aggro, int after_madongsuk_aggro, int after_madongsuk_stamina) {
	if (madongsuk_moving == MOVE_STAY) {
		printf("madongsuk : stay %d(aggro:%d -> %d, stamina: %d)", before_madongsuk, before_madongsuk_aggro, after_madongsuk_aggro, after_madongsuk_stamina);
	}
	else {
		printf("madongsuk:  %d -> %d(aggro: %d -> %d, stamina: %d)", before_madongsuk, after_madongsuk, before_madongsuk_aggro, after_madongsuk_aggro, after_madongsuk_stamina);
	}
	
}

//�ù� �¸� ���
void citizen_acting(int after_citizen) {
	if (after_citizen == 1) {
		printf("YOU WIN! SUCCESS! citizen(s) escaped to the next train.\n");
	}
	else {
		printf("citizen does nothing.\n");
	}
}
//������ ü�� ���
int calc_madongsuk_stamina(int after_citizen, int after_zombie, int after_citizen_aggro, int after_madongsuk_aggro, int after_madongsuk_stamina ) {
	if (after_citizen + 1 == after_zombie && after_zombie + 1 == after_madongsuk) {
		if (after_citizen_aggro <= after_madongsuk_aggro) {
			after_madongsuk_stamina--;
			if (after_madongsuk_stamina < STM_MIN) {
				after_madongsuk_stamina++;
			}
		}
		else {
			after_madongsuk_stamina == after_madongsuk_stamina;
		}
	}
	else if (after_citizen + 1 != after_zombie && after_zombie + 1 == after_madongsuk) {
		after_madongsuk_stamina--;
		if (after_madongsuk_stamina < STM_MIN) {
			after_madongsuk_stamina++;
		}
	}
	return after_madongsuk_stamina;
}

//���� �ൿ ���
void zombie_acting(int after_citizen, int after_zombie, int after_madongsuk, int after_citizen_aggro, int after_madongsuk_aggro, 
	int before_madongsuk_stamina, int after_madongsuk_stamina) {
	if (after_citizen + 1 == after_zombie && after_zombie + 1 != after_madongsuk) {
		printf("GAME OVER! citzen dead...\n");
	}
	else if (after_citizen + 1 != after_zombie && after_zombie + 1 == after_madongsuk) {
		printf("Zombie attacked madongsuk(madongseok stamina: %d -> %d)\n", before_madongsuk_stamina, after_madongsuk_stamina);

		if (after_madongsuk_stamina == STM_MIN) {
				printf("GAME OVER! madongsuk dead");
		}

	}
	else if (after_citizen + 1 == after_zombie && after_zombie + 1 == after_madongsuk) {
		if (after_citizen_aggro <= after_madongsuk_aggro) {
			printf("Zombie attacked madongseok (aggro: %d vs %d, madongsuk stamina: %d -> %d)\n", after_citizen_aggro, after_madongsuk_aggro, before_madongsuk_stamina, after_madongsuk_stamina);
			if (after_madongsuk_stamina == STM_MIN) {
				printf("GAME OVER! madongsuk dead");
			}
		}
		else {
			printf("GAME OVER! citizen dead...\n");
		}
	}
	else {
		printf("zombie attacked nobody\n");
	}
}

// main �Լ�
int main() {
	
	// ��Ʈ��
	intro();
	//2-2 �Է°� ó��: �����Է�, ������ ü�� �Է�, Ȯ�� �Է�
	t_length = get_train_length();//ok
	first_madongsuk_stamina = get_madongsuk_stamina();
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
	first_citizen_aggro = 1;
	first_madongsuk_aggro = 1;

	after_citizen_aggro = first_citizen_aggro;
	after_madongsuk_aggro = first_madongsuk_aggro;
	
	after_madongsuk_stamina = first_madongsuk_stamina;

	while (after_citizen + 1 != after_zombie && after_citizen != 1 && after_madongsuk_stamina != STM_MIN) {
		//2-3 �̵� ������
		r = get_random_number();
		//2-3 �ù� �̵� ���
		before_citizen = after_citizen;
		after_citizen = calc_citizen_moving(r, p, after_citizen);
		
		// 2-3 �ù� ��׷� ���
		before_citizen_aggro = after_citizen_aggro;
		after_citizen_aggro = calc_after_citizen_aggro(r, p, after_citizen_aggro);

		//2-3 ���� �̵� ���
		before_zombie = after_zombie;
		after_zombie = calc_zombie_moving(turn, r, p, after_zombie);
		
		printf("\n");

		//2-3 ������ ���� �� ���� ����
		after_train_state(t_length, after_citizen, after_zombie, after_madongsuk);

		printf("\n\n");
	
		//2-3 �ù� �̵� ���
		print_citizen_state(before_citizen, after_citizen, before_citizen_aggro, after_citizen_aggro);
		

		//2-3 ���� �̵� ���
		print_zombie_state(turn, before_zombie, after_zombie);
		
		printf("\n\n");

		//2-3 ������ �̵� �Է�
		madongsuk_moving = get_madongsuk_moving();

		//2-3 ������ �̵� ���
		before_madongsuk = after_madongsuk;
		after_madongsuk = calc_madongsuk_moving(madongsuk_moving);

		//2-3 ������ ��׷� ���
		before_madongsuk_aggro = after_madongsuk_aggro;
		after_madongsuk_aggro = calc_madongsuk_aggro(after_madongsuk, after_madongsuk_aggro);

		//2-3 ������ �̵� �ݿ��� ���� ���� ���
		after_train_state(t_length, after_citizen, after_zombie, after_madongsuk);

		printf("\n\n");

		//������ �̵� ���
		print_madongsuk_state(before_madongsuk, after_madongsuk, before_madongsuk_aggro, after_madongsuk_aggro, after_madongsuk_stamina);
		
		printf("\n\n");

		//2-4 �ൿ ������
		// 2-4 �ù� �ൿ ���
		citizen_acting(after_citizen);
		// 2-4 ������ ü�� ���
		before_madongsuk_stamina = after_madongsuk_stamina;
		after_madongsuk_stamina = calc_madongsuk_stamina(after_citizen, after_zombie, after_citizen_aggro, after_madongsuk_aggro, after_madongsuk_stamina);
		// 2-4 ���� �ൿ ���
		zombie_acting(after_citizen, after_zombie, after_madongsuk, after_citizen_aggro, after_madongsuk_aggro, before_madongsuk_stamina,
			after_madongsuk_stamina);

		turn++;
	}
	return 0;
}
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

//2-1 �λ���(1)�ڵ带 20�� �̳� �Լ���� ����

//�Լ� �����
void intro(void);
int get_train_length(void);
int get_madongsuk_stamina(void);
int get_probability(void);

int get_random_number(void);

void first_train_state(int, int, int, int);

int calc_citizen_moving(int, int, int);
int calc_after_citizen_aggro(int, int, int);
int calc_zombie_moving(int, int, int, int, int, int, int, int);

void after_train_state(int, int, int, int);

void print_citizen_state(int, int, int, int);
void print_zombie_state(int, int, int, int, int);

int get_madongsuk_moving(int, int);
int calc_madongsuk_moving(int, int);
int calc_madongsuk_aggro(int, int);

void print_madongsuk_state(int, int, int, int, int);

void citizen_acting(int);
int calc_madongsuk_stamina(int, int, int, int, int, int);
int get_zombie_acting(int, int, int, int, int, int);
void print_zombie_acting(int, int, int , int, int, int, int, int);

int get_madongsuk_acting(int, int);
int madongsuk_acting_aggro_effect(int, int);
int madongsuk_acting_stamina_effect(int, int);

void print_madongsuk_acting(int, int, int);
void print_madongsuk_aggro_stamina(int, int, int, int, int, int);

int calc_zombie_control_counter(int, int, int, int);

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

int zombie_acting;
int zombie_actions[4] = { 0, 1, 2, 3 };
int madongsuk_acting;
int madongsuk_actions[3] = { 0, 1, 2 };

int before_zombie_control_counter;
int after_zombie_control_counter;

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
	}
	else if (r < p) {
		after_citizen = after_citizen;
	}
	return after_citizen;
}
// �ù� ��׷� ��� �Լ�
int calc_after_citizen_aggro(int r, int p, int after_citizen_aggro) {
	if (r >= p) {
		after_citizen_aggro++;
		if (after_citizen_aggro > AGGRO_MAX) {
			after_citizen_aggro = AGGRO_MAX;
		}
	}
	else if (r < p) {
		after_citizen_aggro--;
		if (after_citizen_aggro < AGGRO_MIN) {
			after_citizen_aggro = AGGRO_MIN;
		}
	}
	return after_citizen_aggro;
}
// ���� �̵� ��� �Լ�
int calc_zombie_moving(int turn, int after_citizen_aggro, int after_madongsuk_aggro,
					  int after_zombie, int after_citizen, int after_madongsuk,
					  int before_zombie_control_counter, int after_zombie_control_counter) {
	if (before_zombie_control_counter == after_zombie_control_counter) {
		if (turn % 2 == 1 && after_citizen_aggro >= after_madongsuk_aggro) {
			after_zombie = after_zombie - 1;
			if (after_zombie == after_citizen) {
				after_zombie++;
			}
		}

		else if (turn % 2 == 1 && after_citizen_aggro < after_madongsuk_aggro) {
			after_zombie = after_zombie + 1;
			if (after_zombie == after_madongsuk) {
				after_zombie--;
			}
		}

		else {
			after_zombie = after_zombie;
		}
	}
	else {
		after_zombie = after_zombie;
	}
	return after_zombie;
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
void print_zombie_state(int turn, int before_zombie, int after_zombie, 
						int before_zombie_control_counter, int after_zombie_control_counter) {
	if (before_zombie_control_counter == after_zombie_control_counter) {
		if (turn % 2 == 1 && before_zombie == after_zombie) {
			printf("zombie: stay %d\n", before_zombie);
		}
		else if (turn % 2 == 1 && before_zombie != after_zombie) {
			printf("zombie: %d -> %d\n", before_zombie, after_zombie);
		}
		else {
			printf("zombie: stay %d (cannot move)\n", before_zombie);
		}
	}
	else {
		printf("zombie: stay %d (madongsuk pulled zombie)\n", before_zombie);
	}
	
}
//������ �̵� �Է�
int get_madongsuk_moving(int after_zombie, int after_madongsuk) {
	while (1) {
		if (after_madongsuk == after_zombie + 1) {
			printf("madongsuk move(0:stay)>> ");
			scanf_s("%d", &madongsuk_moving);
			if (madongsuk_moving == MOVE_STAY) {
				return madongsuk_moving;
				break;
			}
		}
		else {
			printf("madongsuk move(0:stay, 1:left)>> ");
			scanf_s("%d", &madongsuk_moving);
			if (madongsuk_moving == MOVE_STAY || madongsuk_moving == MOVE_LEFT) {
				return madongsuk_moving;
				break;
			}
		}
	}
}
// ������ �̵� ���
int calc_madongsuk_moving(int madongsuk_moving, int after_madongsuk) {
	if (madongsuk_moving == MOVE_STAY) {
		after_madongsuk = after_madongsuk;
	}
	else {
		after_madongsuk = after_madongsuk - 1;
	}
	return after_madongsuk;
}
// ������ ��׷� ���
int calc_madongsuk_aggro(int madongsuk_moving, int after_madongsuk_aggro) {
	if (madongsuk_moving == MOVE_STAY) {
		after_madongsuk_aggro--;
		if (after_madongsuk_aggro < AGGRO_MIN) {
			after_madongsuk_aggro = AGGRO_MIN;
		}
		return after_madongsuk_aggro;
	}
	else {
		after_madongsuk_aggro++;
		if (after_madongsuk_aggro > AGGRO_MAX) {
			after_madongsuk_aggro = AGGRO_MAX;
		}
		return after_madongsuk_aggro;
	}
}
// ������ �̵� ���
void print_madongsuk_state(int before_madongsuk, int after_madongsuk, 
	                       int before_madongsuk_aggro, int after_madongsuk_aggro, int after_madongsuk_stamina) {
	if (madongsuk_moving == MOVE_STAY) {
		printf("madongsuk : stay %d(aggro:%d -> %d, stamina: %d)", before_madongsuk, before_madongsuk_aggro, 
			   after_madongsuk_aggro, after_madongsuk_stamina);
	}
	else {
		printf("madongsuk:  %d -> %d(aggro: %d -> %d, stamina: %d)", before_madongsuk, after_madongsuk, 
			    before_madongsuk_aggro, after_madongsuk_aggro, after_madongsuk_stamina);
	}
	
}

//�ù� �¸� ���
void citizen_acting(int after_citizen) {
	if (after_citizen == 1) {
		printf("YOU WIN! SUCCESS! citizen(s) escaped to the next train.\n");
		exit(0);
	}
	else {
		printf("citizen does nothing.\n");
	}
}
//������ ���� �������� ���� ü�� ���
int calc_madongsuk_stamina(int after_citizen, int after_zombie, int after_madongsuk,
	                       int after_citizen_aggro, int after_madongsuk_aggro, int after_madongsuk_stamina ) {
	if (after_citizen + 1 == after_zombie && after_zombie + 1 == after_madongsuk) {
		if (after_citizen_aggro <= after_madongsuk_aggro) {
			after_madongsuk_stamina--;
			if (after_madongsuk_stamina < STM_MIN) {
				after_madongsuk_stamina++;
			}
		}
		else {
			after_madongsuk_stamina = after_madongsuk_stamina;
		}
	}
	else if (after_citizen + 1 != after_zombie && after_zombie + 1 == after_madongsuk) {
		after_madongsuk_stamina--;
		if (after_madongsuk_stamina < STM_MIN) {
			after_madongsuk_stamina++;
		}
	}
	else {
		after_madongsuk_stamina = after_madongsuk_stamina;
	}
	return after_madongsuk_stamina;
}

//���� �ൿ ��� ��� 
int get_zombie_acting(int after_citizen, int after_zombie, int after_madongsuk, 
					  int after_citizen_aggro,
					  int after_madongsuk_aggro, int after_madongsuk_stamina) {

	if (after_citizen + 1 == after_zombie && after_zombie + 1 != after_madongsuk) {
		return ATK_CITIZEN;
	}

	else if (after_citizen + 1 != after_zombie && after_zombie + 1 == after_madongsuk) {
		
		if (after_madongsuk_stamina == STM_MIN) {
			return ATK_DONGSEOK;
		}
		return 3;
			
	}

	else if (after_citizen + 1 == after_zombie && after_zombie + 1 == after_madongsuk) {
		if (after_citizen_aggro <= after_madongsuk_aggro) {
			if (after_madongsuk_stamina == STM_MIN) {
				return ATK_DONGSEOK;
			}
			return 3;
		}
		else {
			return ATK_CITIZEN;
		}

	}

	else {
		return ATK_NONE;
	}
}

// ���� �ൿ ��� ���
void print_zombie_acting(int after_citizen, int after_zombie, int after_madongsuk, 
						int before_madongsuk_stamina, int after_madongsuk_stamina,
						int after_citizen_aggro, int after_madongsuk_aggro,	int zombie_acting) {
	
	if (zombie_actions[zombie_acting] == ATK_NONE) {
		printf("zombie attacked nobody\n");
	}

	else if (zombie_actions[zombie_acting] == ATK_CITIZEN) {
		printf("GAME OVER! citizen dead...\n");
		exit(0);
	}

	else if (after_citizen + 1 != after_zombie && after_zombie + 1 == after_madongsuk) {
		printf("Zombie attacked madongsuk(madongseok stamina: %d -> %d)\n", before_madongsuk_stamina, after_madongsuk_stamina);
		if (zombie_actions[zombie_acting] == ATK_DONGSEOK) {
			printf("GAME OVER! madongsuk dead\n");
			exit(0);
		}
	}

	else if (after_citizen + 1 == after_zombie && after_zombie + 1 == after_madongsuk) {
		if (after_citizen_aggro <= after_madongsuk_aggro) {
			printf("Zombie attacked madongseok (aggro: %d vs %d, madongsuk stamina: %d -> %d)\n", 
				after_citizen_aggro, after_madongsuk_aggro,
				before_madongsuk_stamina, after_madongsuk_stamina);

			if (zombie_actions[zombie_acting] == ATK_DONGSEOK) {
				printf("GAME OVER! madongsuk dead\n");
				exit(0);
			}
		}
	}
}

// ������ �ൿ �Է�
int get_madongsuk_acting(int after_madongsuk, int after_zombie) {
	while (1) {
		if (after_madongsuk != after_zombie + 1) {
			printf("madongsuk action(0.rest, 1.provoke)>> ");
			scanf_s("%d", &madongsuk_acting);
		}
		else if (after_madongsuk == after_zombie + 1) {
			printf("madongsuk action(0.rest, 1.provoke, 2.pull)>> ");
			scanf_s("%d", &madongsuk_acting);
		}

		if(madongsuk_acting == ACTION_REST || madongsuk_acting == ACTION_PROVOKE || madongsuk_acting == ACTION_PULL) {
			return madongsuk_acting;
			break;
		}
	}
}
//������ �ൿ���� ���� ��׷� ��ȭ ���
int madongsuk_acting_aggro_effect(int madongsuk_acting, int after_madongsuk_aggro) {
	if (madongsuk_actions[madongsuk_acting] == ACTION_REST ) {
		after_madongsuk_aggro--;
		if (after_madongsuk_aggro < AGGRO_MIN) {
			after_madongsuk_aggro++;
		}
	}
	else if (madongsuk_actions[madongsuk_acting] == ACTION_PROVOKE) {
		after_madongsuk_aggro = AGGRO_MAX;
	}
	else if (madongsuk_actions[madongsuk_acting] == ACTION_PULL) {
		after_madongsuk_aggro += 2;
		if (after_madongsuk_aggro > AGGRO_MAX) {
			after_madongsuk_aggro = AGGRO_MAX;
		}
	}
	return after_madongsuk_aggro;
}
//������ �ൿ���� ���� ü�� ��ȭ ���
int madongsuk_acting_stamina_effect(int madongsuk_acting, int after_madongsuk_stamina) {
	if (madongsuk_actions[madongsuk_acting] == ACTION_REST) {
		after_madongsuk_stamina++;
		if (after_madongsuk_stamina > STM_MAX) {
			after_madongsuk_stamina--;
		}
	}
	
	else if (madongsuk_actions[madongsuk_acting] == ACTION_PULL) {
		after_madongsuk_stamina--;
		if (after_madongsuk_stamina < STM_MIN) {
			after_madongsuk_stamina++;
		}
	}
	else {
		after_madongsuk_stamina = after_madongsuk_stamina;
	}
	return after_madongsuk_stamina; // �Ű����� 
}

//������ �ൿ ���
void print_madongsuk_acting(int madongsuk_acting, int r, int p)
{
	if (madongsuk_acting == 0) {
		printf("madongsuk rests...\n");
	}
	
	else if (madongsuk_acting == 1) {
		printf("madongsuk provoked zombie...\n");
	}

	else if (madongsuk_acting == 2) {
		if (r >= p) {
			printf("madongsuk pulled zombie... Next turn, it can't move\n");
		}
		else {
			printf("madongsuk failed to pull zombie\n");
		}
	}
}
// ������ �ൿ �� ��׷� ü�� ��ȭ ���
void print_madongsuk_aggro_stamina(int madongsuk_acting, int after_madongsuk, 
								   int before_madongsuk_aggro, int after_madongsuk_aggro, 
								   int before_madongsuk_stamina, int after_madongsuk_stamina) {

	if (madongsuk_acting == 0 || madongsuk_acting == 2) {
		printf("madongsuk: %d (aggro: %d -> %d, stamina: %d -> %d)\n", after_madongsuk,
			    before_madongsuk_aggro, after_madongsuk_aggro, before_madongsuk_stamina, after_madongsuk_stamina);
	}
	
	else {
		printf("madongsuk: %d (aggro: %d -> %d, stamina: %d)\n", after_madongsuk,
			    before_madongsuk_aggro, after_madongsuk_aggro, after_madongsuk_stamina);
	}

}

calc_zombie_control_counter(int madongsuk_acting, int after_zombie_control_counter, int r, int p) {
	if (madongsuk_acting == ACTION_PULL && r >= p) {
		after_zombie_control_counter++;
	}
	else {
		after_zombie_control_counter = after_zombie_control_counter;
	}
	return after_zombie_control_counter;
}

// main �Լ�
int main() {
	
	//2-1 ��Ʈ��
	intro();
	//2-2 �Է°� ó��: �����Է�, ������ ü�� �Է�, Ȯ�� �Է�
	t_length = get_train_length();
	first_madongsuk_stamina = get_madongsuk_stamina();
	p = get_probability();
	
	printf("\n\n");
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

	before_zombie_control_counter = 0;
	after_zombie_control_counter = 0;
	
	while (1) {
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
		after_zombie = calc_zombie_moving(turn, after_citizen_aggro, after_madongsuk_aggro,
					                      after_zombie, after_citizen, after_madongsuk,
					                      before_zombie_control_counter, after_zombie_control_counter);
		
		printf("\n\n");

		//2-3 ������ ���� �� ���� ����
		after_train_state(t_length, after_citizen, after_zombie, after_madongsuk);

		printf("\n\n");
	
		//2-3 �ù� �̵� ���
		print_citizen_state(before_citizen, after_citizen, before_citizen_aggro, after_citizen_aggro);
		

		//2-3 ���� �̵� ���
		print_zombie_state(turn, before_zombie, after_zombie,
						  before_zombie_control_counter, after_zombie_control_counter);
		
		printf("\n\n");

		//2-3 ������ �̵� �Է�
		madongsuk_moving = get_madongsuk_moving(after_zombie, after_madongsuk);

		//2-3 ������ �̵� ���
		before_madongsuk = after_madongsuk;
		after_madongsuk = calc_madongsuk_moving(madongsuk_moving, after_madongsuk);

		//2-3 ������ ��׷� ���
		before_madongsuk_aggro = after_madongsuk_aggro;
		after_madongsuk_aggro = calc_madongsuk_aggro(madongsuk_moving, after_madongsuk_aggro);

		//2-3 ������ �̵� �ݿ��� ���� ���� ���
		after_train_state(t_length, after_citizen, after_zombie, after_madongsuk);

		printf("\n\n");

		//2-3 ������ �̵� ���
		print_madongsuk_state(before_madongsuk, after_madongsuk,
			                  before_madongsuk_aggro, after_madongsuk_aggro, after_madongsuk_stamina);
		
		printf("\n\n\n");

		//2-4 �ൿ ������
		
		// 2-4 �ù� �ൿ ���
		citizen_acting(after_citizen);

		// 2-4 ������ ���� �������� ���� ü�� ���
		before_madongsuk_stamina = after_madongsuk_stamina;
		after_madongsuk_stamina = calc_madongsuk_stamina(after_citizen, after_zombie, after_madongsuk,
								  after_citizen_aggro, after_madongsuk_aggro, after_madongsuk_stamina);
		
		// 2-4 ���� �ൿ ��ȯ
		zombie_acting = get_zombie_acting(after_citizen, after_zombie, after_madongsuk,
										  after_citizen_aggro,
										  after_madongsuk_aggro, after_madongsuk_stamina);
		// 2-4 ���� �ൿ ���
		print_zombie_acting(after_citizen, after_zombie, after_madongsuk,
			                before_madongsuk_stamina, after_madongsuk_stamina,
			                after_citizen_aggro, after_madongsuk_aggro, zombie_acting);

		//2-4 ������ �ൿ �Է�
		madongsuk_acting = get_madongsuk_acting(after_madongsuk, after_zombie);
		
		printf("\n\n");
		
		// 2-4 ������ �ൿ���� ���� ��׷� ��ȭ ���
		before_madongsuk_aggro = after_madongsuk_aggro;
		after_madongsuk_aggro = madongsuk_acting_aggro_effect(madongsuk_acting, after_madongsuk_aggro);
		// 2-4 ������ �ൿ���� ���� ü�� ��ȭ ���
		before_madongsuk_stamina = after_madongsuk_stamina;
		after_madongsuk_stamina = madongsuk_acting_stamina_effect(madongsuk_acting, after_madongsuk_stamina);

		//2-4 ������ �ൿ ���
		print_madongsuk_acting(madongsuk_acting, r, p);
		print_madongsuk_aggro_stamina(madongsuk_acting, after_madongsuk,
									  before_madongsuk_aggro, after_madongsuk_aggro,
									  before_madongsuk_stamina, after_madongsuk_stamina);

		//2-4 ���� ���� �� �̵� ���� ���� ���
		before_zombie_control_counter = after_zombie_control_counter;
		after_zombie_control_counter = calc_zombie_control_counter(madongsuk_acting, after_zombie_control_counter, r, p);

		// ���� ������
		turn++;
	}
	return 0;
}



// ���� ���� ��� ��ũ�� Ȱ��



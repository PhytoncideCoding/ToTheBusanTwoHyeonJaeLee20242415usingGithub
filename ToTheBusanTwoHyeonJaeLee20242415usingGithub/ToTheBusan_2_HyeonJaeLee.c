//2-2 Sleep()삭제
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//2-2 파라미터 수정
#define LEN_MIN 15 // 기차 길이
#define LEN_MAX 50
#define STM_MIN 0 // 마동석 체력
#define STM_MAX 5
#define PROB_MIN 10 // 확률
#define PROB_MAX 90
#define AGGRO_MIN 0 // 어그로 범위 
#define AGGRO_MAX 5

// 마동석 이동방향
#define MOVE_LEFT 1
#define MOVE_STAY 0

// 좀비의 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// 마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

//2-1 부산헹(1)코드를 20줄 이내 함수들로 정리 (배열은 전역변수)
//함수 선언부
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

//변수 선언부
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

// 인트로 함수
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
	printf("====마동석에 빙의해서 좀비로부터 시민을 지켜라====\n");
	printf("====   내 아트박스 사장인데 니가 스포했니?    ====\n");
}
// 올바른 길이 값 받기
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
// 마동석 스태미나 입력 함수
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
// 올바른 확률 값 받기
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
// 초기 열차 상태 출력 함수
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
// 랜덤 수 리턴 함수 
int get_random_number(void) {
	srand((unsigned int)time(NULL));
	r = rand() % 100;
	return r;
}

// 시민 이동 계산 함수
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
// 시민 어그로 계산 함수
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
// 좀비 이동 계산 함수 
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
// 이동 반영한 열차 상태 출력 함수
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
//시민 상태 출력
void print_citizen_state(int before_citizen, int after_citizen, int before_citizen_aggro, int after_citizen_aggro) {
	if (before_citizen == after_citizen) {
		printf("citizen: stay %d (aggro: %d -> %d)\n", before_citizen, before_citizen_aggro, after_citizen_aggro);
	}
	else {
		printf("citizen: %d -> %d (aggro: %d -> %d)\n", before_citizen, after_citizen, before_citizen_aggro, after_citizen_aggro);
	}
}
//좀비 상태 출력
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
//마동석 이동 입력
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
// 마동석 이동 계산
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
// 마동석 어그로 계산
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
// 마동석 이동 출력
void print_madongsuk_state(int before_madongsuk, int after_madongsuk, int before_madongsuk_aggro, int after_madongsuk_aggro, int after_madongsuk_stamina) {
	if (madongsuk_moving == MOVE_STAY) {
		printf("madongsuk : stay %d(aggro:%d -> %d, stamina: %d)", before_madongsuk, before_madongsuk_aggro, after_madongsuk_aggro, after_madongsuk_stamina);
	}
	else {
		printf("madongsuk:  %d -> %d(aggro: %d -> %d, stamina: %d)", before_madongsuk, after_madongsuk, before_madongsuk_aggro, after_madongsuk_aggro, after_madongsuk_stamina);
	}
	
}

//시민 승리 출력
void citizen_acting(int after_citizen) {
	if (after_citizen == 1) {
		printf("YOU WIN! SUCCESS! citizen(s) escaped to the next train.\n");
	}
	else {
		printf("citizen does nothing.\n");
	}
}
//마동석 체력 계산
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

//좀비 행동 출력
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

// main 함수
int main() {
	
	// 인트로
	intro();
	//2-2 입력값 처리: 길이입력, 마동석 체력 입력, 확률 입력
	t_length = get_train_length();//ok
	first_madongsuk_stamina = get_madongsuk_stamina();
	p = get_probability();
	
	//2-2 초기 상태 출력
	// 시민, 좀비, 마동석 초기 위치
	first_citizen = t_length - 6;
	first_zombie = t_length - 3;
	first_madongsuk = t_length - 2;

	// 열차 초기 상태 출력
	first_train_state(t_length, first_citizen, first_zombie, first_madongsuk);

	turn = 1;
	
	after_citizen = first_citizen;
	after_zombie = first_zombie;
	after_madongsuk = first_madongsuk;

	//2-2 시민, 마동석 어그로 추가
	first_citizen_aggro = 1;
	first_madongsuk_aggro = 1;

	after_citizen_aggro = first_citizen_aggro;
	after_madongsuk_aggro = first_madongsuk_aggro;
	
	after_madongsuk_stamina = first_madongsuk_stamina;

	while (after_citizen + 1 != after_zombie && after_citizen != 1 && after_madongsuk_stamina != STM_MIN) {
		//2-3 이동 페이즈
		r = get_random_number();
		//2-3 시민 이동 계산
		before_citizen = after_citizen;
		after_citizen = calc_citizen_moving(r, p, after_citizen);
		
		// 2-3 시민 어그로 계산
		before_citizen_aggro = after_citizen_aggro;
		after_citizen_aggro = calc_after_citizen_aggro(r, p, after_citizen_aggro);

		//2-3 좀비 이동 계산
		before_zombie = after_zombie;
		after_zombie = calc_zombie_moving(turn, r, p, after_zombie);
		
		printf("\n");

		//2-3 페이즈 진행 후 열차 상태
		after_train_state(t_length, after_citizen, after_zombie, after_madongsuk);

		printf("\n\n");
	
		//2-3 시민 이동 출력
		print_citizen_state(before_citizen, after_citizen, before_citizen_aggro, after_citizen_aggro);
		

		//2-3 좀비 이동 출력
		print_zombie_state(turn, before_zombie, after_zombie);
		
		printf("\n\n");

		//2-3 마동석 이동 입력
		madongsuk_moving = get_madongsuk_moving();

		//2-3 마동석 이동 계산
		before_madongsuk = after_madongsuk;
		after_madongsuk = calc_madongsuk_moving(madongsuk_moving);

		//2-3 마동석 어그로 계산
		before_madongsuk_aggro = after_madongsuk_aggro;
		after_madongsuk_aggro = calc_madongsuk_aggro(after_madongsuk, after_madongsuk_aggro);

		//2-3 마동석 이동 반영한 열차 상태 출력
		after_train_state(t_length, after_citizen, after_zombie, after_madongsuk);

		printf("\n\n");

		//마동석 이동 출력
		print_madongsuk_state(before_madongsuk, after_madongsuk, before_madongsuk_aggro, after_madongsuk_aggro, after_madongsuk_stamina);
		
		printf("\n\n");

		//2-4 행동 페이즈
		// 2-4 시민 행동 출력
		citizen_acting(after_citizen);
		// 2-4 마동석 체력 계산
		before_madongsuk_stamina = after_madongsuk_stamina;
		after_madongsuk_stamina = calc_madongsuk_stamina(after_citizen, after_zombie, after_citizen_aggro, after_madongsuk_aggro, after_madongsuk_stamina);
		// 2-4 좀비 행동 출력
		zombie_acting(after_citizen, after_zombie, after_madongsuk, after_citizen_aggro, after_madongsuk_aggro, before_madongsuk_stamina,
			after_madongsuk_stamina);

		turn++;
	}
	return 0;
}
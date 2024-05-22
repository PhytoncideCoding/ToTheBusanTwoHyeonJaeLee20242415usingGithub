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
// 마동석 스태미나 입력 함수
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
// 시민 이동 계산 함수
int calc_citizen_moving(int r, int p, int after_citizen) {
	if (r >= p) {
		after_citizen = after_citizen - 1;
		
	}
	else if (r < p) {
		after_citizen = after_citizen;
	}
	return after_citizen;
}
// 시민 어그로 계산 함수
int calc_citizen_aggro(int r, int p, int citizen_aggro) {
	if (r >= p) {
		citizen_aggro++;
	}
	else {
		citizen_aggro--;
	}
	return citizen_aggro;
}
// 좀비 이동 계산 함수 
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
//시민 상태 출력
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
// 마동석 어그로 계산
int calc_madongsuk_aggro(int madongsuk_movinging, int madongsuk_aggro ) {
	if (madongsuk_moving == MOVE_STAY) {
		madongsuk_aggro--;
	}
	else {
		madongsuk_aggro++;
	}
	return madongsuk_aggro;
}
//시민 승리 출력
void victory_citizen(int after_citizen) {
	if (after_citizen == 1) {
		printf("\n");
		printf("SUCCESS!\n");
		printf("citizen(s) escaped to the next train");
	}
}
//좀비 승리 출력
void victory_zombie(int after_citizen, int after_zombie) {
	if (after_citizen + 1 == after_zombie) {
		printf("\n");
		printf("GAME OVER!\n");
		printf("Citizen(s) has(have) ben attacked by a zombie");
	}
	
}
// main 함수
int main() {
	
	// 인트로
	intro();
	//2-2 입력값 처리: 길이입력, 마동석 체력 입력, 확률 입력
	t_length = get_train_length();//ok
	madongsuk_stamina = get_madongsuk_stamina();
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
	citizen_aggro = 1;
	madongsuk_aggro = 1;

	while (after_citizen + 1 != after_zombie && after_citizen != 1) {
		 //2-2 이동 페이즈
		r = get_random_number();
		//시민 이동 계산
		before_citizen = after_citizen;
		after_citizen = calc_citizen_moving(r, p, after_citizen);
		
		//좀비 이동 계산
		before_zombie = after_zombie;
		after_zombie = calc_zombie_moving(turn, r, p, after_zombie);
		
		printf("\n");
		//페이즈 진행 후 열차 상태
		after_train_state(t_length, after_citizen, after_zombie, after_madongsuk);

		printf("\n\n");

		//1페이즈 진행 후 시민 이동 출력
		print_citizen_state(before_citizen, after_citizen, citizen_aggro);
		// 시민 어그로 계산
		citizen_aggro = calc_citizen_aggro(r, p, citizen_aggro);

		//1페이즈 진행 후 좀비 이동 출력
		print_zombie_state(turn, before_zombie, after_zombie);
		
		printf("\n\n");

		// 마동석 이동 입력
		madongsuk_moving = get_madongsuk_moving();
		// 마동석 이동 계산
		before_madongsuk = after_madongsuk;
		after_madongsuk = calc_madongsuk_moving(madongsuk_moving);
		// 마동석 이동 반영
		after_train_state(t_length, after_citizen, after_zombie, after_madongsuk);

		printf("\n\n");

		//마동석 이동 출력
		print_madongsuk_state(before_madongsuk, after_madongsuk, madongsuk_aggro, madongsuk_stamina);
		//마동석 어그로 계산
		madongsuk_aggro = calc_madongsuk_aggro(after_madongsuk, madongsuk_aggro);
		
		printf("\n\n");

		//2-2 행동 페이즈

		turn++;		
	}
	//시민 승리
	victory_citizen(after_citizen);
	//좀비 승리
	victory_zombie(after_citizen, after_zombie);
	return 0;
}
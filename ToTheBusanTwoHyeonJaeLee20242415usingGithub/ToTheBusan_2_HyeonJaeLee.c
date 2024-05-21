//2-1 20줄 이내 함수로 부산헹(1) 정리 2-2 파라미터 변경
//---1턴 2페이즈로 구성---
// Sleep() 삭제 마동석 입력시에만 정지, 마동석 이동추가, 
//시민, 좀비, 마동석 각각 행동, 결과 표시
//---스탯 추가---
//마동석 체력 추가
//시민어그로, 마동석 어그로 (좀비 행동 결정)
//---입력값 처리---
//모든 입력에 대해 유효 값 입력 될 때 까지 다시 입력 받기
//반드시 정수 1개만 입력된다고 가정
//배열 전역변수로 선언

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
//파라미터
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
		
	}
	else if (r < p) {
		after_citizen = after_citizen;
	}
	return after_citizen;
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
//시민 상태 출력
void print_citizen_state(int before_citizen, int after_citizen) {
	if (before_citizen == after_citizen) {
		printf("citizen: stay %d\n", before_citizen);
	}
	else {
		printf("citizen: %d -> %d\n", before_citizen, after_citizen);
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
	// 길이 , 확률 입력
	t_length = get_train_length();//ok
	p = get_probability();
	//열차의 길이15이면 시민 초기 위치9 
	// 시민, 좀비, 마동석 초기 위치
	first_citizen = t_length - 6;
	first_zombie = t_length - 3;
	first_madongsuk = t_length - 2;

	// 열차 초기 상태 출력
	first_train_state(t_length, first_citizen, first_zombie, first_madongsuk);

	turn = 1;
	
	after_citizen = first_citizen;
	after_zombie = first_zombie;

	while (after_citizen + 1 != after_zombie && after_citizen != 1) {
		 
		r = get_random_number();
		//시민 이동 계산
		before_citizen = after_citizen;
		after_citizen = calc_citizen_moving(r, p, after_citizen);
		
		//좀비 이동 계산
		before_zombie = after_zombie;
		after_zombie = calc_zombie_moving(turn, r, p, after_zombie);
		
		printf("\n");
		//페이즈 진행 후 열차 상태
		after_train_state(t_length, after_citizen, after_zombie, first_madongsuk);

		printf("\n\n");

		//페이즈 진행 후 시민 이동 출력
		print_citizen_state(before_citizen, after_citizen);
		//페이즈 진행 후 좀비 이동 출력
		print_zombie_state(turn, before_zombie, after_zombie);
		turn++;
		Sleep(4000);//for test
	}
	//시민 승리
	victory_citizen(after_citizen);
	//좀비 승리
	victory_zombie(after_citizen, after_zombie);
	return 0;
}
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

//파라미터
#define LEN_MIN 15
#define LEN_MAX 50
#define STM_MIN 0
#define STM_MAX 5
#define PROB_MIN 10
#define PROB_MAX 90
#define AGGRO_MIN 0
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

// 인트로 출력하는 함수
void intro(void);
void spacing(void);
void get_train_length(void);
void get_probability(void);
void basic_length_setting(void);
void first_train_state(void);

int t_length, p;
int citizen, zombie, madongsuk;


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
//줄 바꾸기
void spacing(void) {
	printf("\n");
}
// 올바른 길이 값 받기
void get_train_length(void) {
	while (1) {
		printf("train length(15~50)>> ");
		scanf_s("%d", &t_length);
		if ((LEN_MIN <= t_length && t_length <= LEN_MAX)) {
			break;
		}
	}
}
// 올바른 확률 값 받기
void get_probability(void){
	while (1) {
		printf("percentile probability 'p' (10~90)>> ");
		scanf_s("%d", &p);
		if (PROB_MIN <= p && p <= PROB_MAX) {
			break;
		}
	}
}
// t_length 에 따라 #출력하는 함수(반환값X)
void basic_length_setting(void) {
	for (int i = 0; i < t_length; i++) {
		printf("#");
	}
	printf("\n");
}

// 초기 열차 상태 출력 함수
void first_train_state(void) {
    citizen = t_length - 6;
	zombie = t_length - 3;
    madongsuk = t_length - 2;
	for (int i = 0; i < t_length; i++) {

		if (i == 0 || i == t_length - 1) {
			printf("#");
		}
		else if (i == citizen) {
			printf("C");
		}
		else if (i == zombie) {
			printf("Z");
		}
		else if (i == madongsuk) {
			printf("M");
		}
		else {
			printf(" ");
		}

	}
	printf("\n");
}
// main 실행 함수
int main() {
	intro();

	get_train_length();
	get_probability();

	spacing();
	
	basic_length_setting();
	first_train_state();
	basic_length_setting();

	spacing();

	return 0;
}

// ----시민, 좀비 이동---
// 시민 이동 정의하는 함수
// 좀비 이동 정의하는 함수
// ---변화된 열차 상태 출력---
// 변화된 열차 상태 출력 함수
// ---시민, 좀비 이동 정보 출력---
// 시민의 이동 정보 출력하는 함수
// 좀비의 이동 정보 출력하는 함수
// ---최종 승리자 출력---
// 시민 승리 출력 함수
// 좀비 승리 출력 함수


//int main() {
// 
//	srand((unsigned int)time(NULL));
// 
//	{
//
//			int after_citizen = citizen;
//			int after_zombie = zombie;
//
//			int turn = 1;
//
//			while (after_citizen + 1 != after_zombie && after_citizen != 1) {
//				int r = rand() % 100;
//				//시민 이동	
//				int before_citizen = after_citizen;
//
//				if (r >= p) {
//					after_citizen = after_citizen - 1;
//				}
//				else {
//					after_citizen = after_citizen;
//				}
//				//좀비 이동 
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
//				//열차 상태 출력
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
//				//시민, 좀비 상태 출력
//				//시민 상태 출력
//				if (before_citizen == after_citizen) {
//					printf("citizen: stay %d\n", before_citizen);
//				}
//				else {
//					printf("citizen: %d -> %d\n", before_citizen, after_citizen);
//				}
//				//좀비 상태 출력
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
//			// 아웃트로 4초이내 지나가기, 종료 상태 출력(성공, 실패)
//			//시민 승리
//			printf("\n");
//
//			if (after_citizen == 1) {
//				printf("SUCCESS!\n");
//				printf("citizen(s) escaped to the next train");
//			}
//			//좀비 승리
//			else if (after_citizen + 1 == after_zombie) {
//				printf("GAME OVER!\n");
//				printf("Citizen(s) has(have) ben attacked by a zombie");
//			}
//		}
//		//범위 밖의 값 입력시 프로그램 종료
//		else {
//			printf("<Notice>\n");
//			printf("Because of the wrong input values, the program is ended.\n");
//			printf("Please enter correct train length and percentile probability to start the program");
//		}
//
//	}
//	return 0;
//}
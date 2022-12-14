#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h> //system("cls"); 함수를 호출하기 위한 헤더파일. system("cls"); = 화면을 깨끗하게 지웁니다.
#include <stdlib.h>
#include <string.h>

struct Student { //구조체. 학생에 관한 정보 포함
	char name[13]; //이름 영어 12자, 한글 4자까지 넣을 수 있습니다.
	int grade; //학년
	char studentID[11]; //학번
	char phone[13]; //전화번호
	double scores[3]; //과목 수 0:출석 점수(10.0), 1:시험 성적(60.0), 2:과제물(30.0) 출석 점수는 기본적으로 10점임. 출결 기능에서 수정시마다 바뀜
	int attendance[15]; //0 결석, 1 출석, 2 지각. 한명 당 총 15주차까지 있음. 기본적으로 모두 출석으로 되어있음.
};

struct Student studentInfo[20]; //구조체 20개 생성. 학생 최대 20명까지 등록 가능. 전역 변수

int studentCount = 0; //등록된 학생의 숫자를 나타냄. 등록 된 학생 수 만큼 반복할 때도 유용함. 코딩 하실 때 활용하시라고 전역변수로 해두긴 했는데 현재 등록 되어있는 학생 수와 일치해야 합니다. 값이 틀리면 오류가 날 수 있으므로 함부로 값을 바꾸면 안됩니다.

//-----------------------------------------------------------------------------------파일 처리

void fileProcessing(); //파일처리 함수 원형
void fileSave(); //학생 정보를 저장하는 함수 원형
void fileLoad(); //학생 정보를 불러오는 함수 원형
void countSave(); //학생 숫자를 저장하는 함수 원형
void countLoad(); //학생 숫자를 불러오는 함수 원형

//-----------------------------------------------------------------------------------조대영 변수, 함수 원형

void studentInformation(void); //학생 인적사항 관리 함수 원형
void addInfo(); //학생 추가 시 사용하는 함수 원형
void inquiryInfo(); //학생 조회 시 사용하는 함수 원형
void deleteInfo(); //학생 정보 삭제 시 사용하는 함수 원형
void sort(); //학생 정보를 이름 순으로 정렬하는 함수 원형

//-----------------------------------------------------------------------------------정재헌 변수, 함수 원형

void attendance(void); //출결관리 함수 원형
void attendanceAdd(void); //학생 출석정보 수정
void attendanceSearch(); //학생 출석정보 출력

//-----------------------------------------------------------------------------------길민준 변수, 함수 원형

const char* stitles[3] = { "출석(10.0)","시험(60.0)","과제물(30.0)" };

void grade(void); //성적관리 함수 원형
void Run();
int SelectMenu();//메뉴 출력 및 선택
void AddStudent();//학생 데이터 입력
void RemoveStudent();//학생 데이터 삭제
void FindStudent();//학생 검색
void ListStudent();//목록 보기
int IsAvailNum(int num);//유효한 번호인지 판별
void ViewStuData(int n);

//-----------------------------------------------------------------------------------




int main(void) {
	system("mode con cols=150 lines=40");
	int select; //메뉴 선택 시 입력 값 저장 변수

	printf("********************\n학생 관리 앱\nMade By 조대영, 길민준, 정재헌, 조진욱\n"); //타이틀 출력

	while (1) {
		printf("********************\n\t-메뉴-\n1.학생 인적사항 관리\n2.출결 관리\n3.성적 관리\n4.학생 파일 저장/불러오기\n5.끝내기\n********************\n입력: "); //메뉴 출력
		scanf_s("%d", &select); //메뉴 선택

		switch (select) {
		case 1: //학생 인적사항 관리 함수 분기
			studentInformation();
			system("cls");
			break;
		case 2: //출결관리 함수 분기
			attendance();
			system("cls");
			break;
		case 3: //성적관리 함수 분기
			grade();
			system("cls");
			break;
		case 4:
			fileProcessing(); //파일 처리
			system("cls");
			break;
		case 5: //프로그램 종료
			printf("프로그램을 종료합니다.\n");
			return 0;
			break;
		default: //잘못 된 값 입력 시 다시 되돌아 감
			system("cls");
			printf("잘못된 입력입니다.\n");
			getchar();
			break;
		}
	}
	return 0;
}

//-----------------------------------------------------------------------------------파일 처리

void fileProcessing() {
	char select;
	system("cls");

	printf("********************\n파일 저장/불러오기 화면\n");

	while (1) {
		int select;

		printf("********************\n1.학생 데이터 저장\n2.학생 데이터 불러오기\n3.메인 화면으로\n********************\n입력: ");
		scanf_s("%d", &select); //메뉴 선택

		switch (select) {
		case 1: //학생 정보 파일로 저장
			printf("데이터 저장 시 기존 데이터를 덮어씁니다.\n그래도 저장하시겠습니까(y/n): ");
			scanf_s(" %c", &select);
			if ((select == 'y') || (select == 'Y')) {
				countSave(); //학생 숫자 저장
				fileSave(); //학생 정보 저장
			}
			else if ((select == 'n') || (select == 'N')) {
				system("cls");
				printf("---데이터를 저장하지 않고 선택 화면으로 돌아갑니다.---\n");
			}
			else {
				system("cls");
				printf("---잘못된 입력입니다.---\n");
			}
			break;
		case 2: //학생 정보 파일 불러오기
			printf("데이터 불러오기 시 현재 실행중인 내용이 지워집니다.\n그래도 불러오시겠습니까(y/n): ");
			scanf_s(" %c", &select);
			if ((select == 'y') || (select == 'Y')) {
				countLoad(); //학생 숫자 불러오기
				fileLoad(); //학생 정보 불러오기
			}
			else if((select == 'n') || (select == 'N')) {
				system("cls");
				printf("---데이터를 불러오지 않고 선택 화면으로 돌아갑니다.---\n");
			}
			else {
				system("cls");
				printf("---잘못된 입력입니다.---\n");
			}
			break;
		case 3:
			return;
			break;
		default:
			system("cls");
			printf("---잘못된 입력입니다.---\n");
			getchar();
			break;
		}
	}
}

void countSave() { //학생의 숫자(int studentCount)는 여기서 따로 저장됩니다.
	FILE* fp;
	fp = fopen("studentCount.txt", "w"); //파일 열기. (파일명, 쓰기 모드)

	if (fp == NULL) {
		system("cls");
		printf("---파일열기 실패---\n");
		return;
	}
	else {
		system("cls");
		printf("---파일열기 성공---\n");
	}

	fprintf(fp, "%d\n", studentCount);

	fclose(fp); //파일 닫기

	printf("---학생 수 저장 완료---\n");

	return;
}

void fileSave() { //학생 정보를 저장합니다. 학생 숫자만큼 반복하여 저장하는 방식입니다.
	FILE* fp;
	fp = fopen("studentData.txt", "w"); //파일 열기. (파일명, 쓰기 모드)

	if (fp == NULL) {
		printf("---파일열기 실패---\n");
		return;
	}
	else {
		printf("---파일열기 성공---\n");
	}

	for (int i = 0; i < studentCount; i++) {
		fprintf(fp, "%s %d %s %s ", studentInfo[i].name, studentInfo[i].grade, studentInfo[i].studentID, studentInfo[i].phone);
		for (int y = 0; y < 3; y++) {
			fprintf(fp, "%lf ", studentInfo[i].scores[y]);
		}
		for (int y = 0; y < 15; y++) {
			fprintf(fp, "%d ", studentInfo[i].attendance[y]);
		}
		fprintf(fp, "\n");
	}

	fclose(fp); //파일 닫기

	printf("---학생 정보 저장 완료---\n");

	return;
}

void countLoad() { //학생 숫자가 기록된 파일을 먼저 불러와 studentCount 전역변수에 집어넣습니다.
	FILE* fp;
	if ((fp = fopen("studentCount.txt", "r")) == NULL) { //파일 열기. (파일명, 읽기 모드)
		system("cls");
		printf("---파일열기 실패---\n");
		return;
	}
	else {
		system("cls");
		printf("---파일열기 성공---\n");
	}

	fscanf(fp, "%d", &studentCount);

	fclose(fp); //파일 닫기

	printf("---학생 수 불러오기 완료---\n");

	return;
}

void fileLoad() { //먼저 불러온 studentCount 값을 토대로 반복하여 파일의 학생 정보를 불러옵니다.
	FILE* fp;
	if ((fp = fopen("studentData.txt", "r")) == NULL) { //파일 열기. (파일명, 읽기 모드)
		printf("---파일열기 실패---\n");
		return;
	}
	else {
		printf("---파일열기 성공---\n");
	}

	fscanf(fp, "%d", &studentCount);

	for (int i = 0; i < studentCount; i++) {
		fscanf(fp, "%s", studentInfo[i].name);
		fscanf(fp, "%d", &studentInfo[i].grade);
		fscanf(fp, "%s", studentInfo[i].studentID);
		fscanf(fp, "%s", studentInfo[i].phone);
		for (int y = 0; y < 3; y++) {
			fscanf(fp, "%lf", &studentInfo[i].scores[y]);
		}
		for (int y = 0; y < 15; y++) {
			fscanf(fp, "%d", &studentInfo[i].attendance[y]);
		}
	}

	fclose(fp); //파일 닫기

	printf("---학생 정보 불러오기 완료---\n");

	return;
}

//-----------------------------------------------------------------------------------학생 추가 시 사용하는 함수. 조대영 담당


void studentInformation(void) { //학생 인적사항 관리 함수. 조대영 담당
	int select; //메뉴 선택 시 입력 값 저장 변수
	system("cls");

	printf("********************\n학생 인적사항 관리 화면\n");

	while (1) {
		printf("********************\n1.학생 추가\n2.학생 조회\n3.학생 정보 삭제\n4.학생 리스트 정렬\n5.메인 화면으로\n********************\n입력: ");
		scanf_s("%d", &select);

		switch (select) {
		case 1:
			addInfo(); //학생 추가 함수로 분기
			break;
		case 2:
			inquiryInfo(); //학생 조회 함수로 분기
			break;
		case 3:
			deleteInfo(); //학생 정보 삭제 함수로 분기
			break;
		case 4:
			sort();
			break;
		case 5:
			return;
			break;
		default: //잘못 된 값 입력 시 다시 되돌아 감
			system("cls");
			printf("---잘못된 입력입니다.---\n");
			getchar();
			break;
		}
	}
}

void addInfo() {
	if (studentCount >= 20) { //학생이 20명 등록되어 꽉 차게되면 더 이상 등록 불가능함을 알리고 false 리턴
		printf("더 이상 학생을 등록할 수 없습니다.");
		return;
	}
	printf("이름(최대 12Byte): ");
	scanf("%s", studentInfo[studentCount].name); //이름을 입력 받아 studentInfo 배열에 차례대로 집어넣음
	printf("학년: ");
	scanf_s(" %d", &studentInfo[studentCount].grade); //나이를 입력 받아 studentInfo 배열에 차례대로 집어넣음
	printf("학번: ");
	scanf("%s", studentInfo[studentCount].studentID);
	printf("휴대폰 번호('-'포함x): ");
	scanf("%s", studentInfo[studentCount].phone);
	for (int i = 0; i < 3; i++) { //성적 초기화
		studentInfo[studentCount].scores[i] = -1;
	}
	studentInfo[studentCount].scores[0] = 10;
	for (int i = 0; i < 15; i++) { //출석 초기화
		studentInfo[studentCount].attendance[i] = 1;
	}
	system("cls");
	printf("---추가 완료---\n");
	studentCount++; //정상적으로 학생 추가 시 학생 수 1 증가
}

void inquiryInfo() { //학생 조회 시 사용하는 함수 
	if (studentCount == 0) { //등록 된 학생이 한 명도 없으면 없음을 알리고 함수 종료
		system("cls");
		printf("---학생 정보가 없습니다.---\n");
		return;
	}
	system("cls");
	printf("---학생 정보 출력---\n********************************************************************************\n번호\t\t이름\t\t학년\t\t학번\t\t휴대폰 번호\t\t\n");
	for (int i = 0; i < studentCount; i++) {
		printf("%d\t\t%s\t\t%d\t\t%s\t%s\n", i, studentInfo[i].name, studentInfo[i].grade, studentInfo[i].studentID, studentInfo[i].phone);
	}
	printf("********************************************************************************\n총 %d명의 학생 정보가 있습니다.\n", studentCount);
}

void deleteInfo() { //학생 정보 삭제 시 사용하는 함수.
	int m; //몇 번째 학생을 삭제 할 지 번호를 받는 변수
	if (studentCount == 0) {
		system("cls");
		printf("---삭제 할 학생 정보가 없습니다.---\n");
		return;
	}
	inquiryInfo(studentCount);
	printf("삭제하고 싶은 학생 정보의 번호를 입력하세요.");
	scanf_s("%d", &m);
	if (m < 0 || m >= studentCount) { //없는 학생 번호 입력 시 오류 출력 및 함수 종료. false를 돌려 줌
		system("cls");
		printf("---잘못된 값입니다.---\n");
		getchar();
		return;
	}
	for (int i = m + 1; i < studentCount; i++) { //학생 정보 삭제 및 배열 뒷쪽의 학생 정보를 앞으로 당김.
		strcpy(studentInfo[i - 1].name, studentInfo[i].name);
		studentInfo[i - 1].grade = studentInfo[i].grade;
		strcpy(studentInfo[i - 1].studentID, studentInfo[i].studentID);
		strcpy(studentInfo[i - 1].phone, studentInfo[i].phone);
	}
	studentCount--; //정상적으로 학생 정보 삭제 완료 시 학생 수 1 감소
	system("cls");
	printf("---삭제 완료---\n");
}

int isEmpty() {
	if (studentCount == 0) {
		return 1;
	}
	else
	{
		return 0;
	}
}

void sort() { //학생을 이름 순으로 정렬하는 함수.
	struct Student v[20]; //임의의 Student 구조체 배열 v 선언
	struct Student n; //임시 기억 공간
	char c;

	if (studentCount == 0) { //등록 된 학생이 한 명도 없으면 없음을 알리고 함수 종료
		system("cls");
		printf("---학생 정보가 없습니다.---\n");
		return;
	}

	for (int i = 0; i < studentCount; i++) { //임의로 선언 된 구조체 배열 v에 학생 정보를 복사함.
		v[i] = studentInfo[i];
	}

	for (int i = 1; i < studentCount; i++) { //여기서 임의로 선언 된 구조체 배열 v의 학생 데이터가 정렬됨.
		for (int y = i; y > 0; y--) {
			if (strcmp(v[y].name, v[y - 1].name) < 0) {
				n = v[y];
				v[y] = v[y - 1];
				v[y - 1] = n;
			}
			else {
				break;
			}
		}
	}

	system("cls");
	printf("학생 정보 출력\n********************************************************************************\n번호\t\t이름\t\t학년\t\t학번\t\t휴대폰 번호\t\t\n");
	for (int i = 0; i < studentCount; i++) { //앞에서 정렬 된 v의 내용을 출력합니다.
		printf("%d\t\t%s\t\t%d\t\t%s\t%s\n", i, v[i].name, v[i].grade, v[i].studentID, v[i].phone);
	}
	printf("********************************************************************************\n정렬 완료. 총 %d명의 학생 정보가 있습니다.\n이대로 저장 하시겠습니까(y/n)? ", studentCount);
	scanf_s(" %c", &c);
	if ((c == 'y') || (c == 'Y')) { //입력에 따라 정렬된 v의 내용을 StudentInfo에 복사하거나 아니면 무효로 함.
		for (int i = 0; i < studentCount; i++) {
			studentInfo[i] = v[i];
		}
		system("cls");
		printf("---변경 사항 적용 완료!---\n");
	}
	else if((c == 'n') || (c == 'N')) {
		system("cls");
		printf("---변경 사항을 적용하지 않고 선택 화면으로 돌아갑니다.---\n");
	}
	else {
		system("cls");
		printf("---잘못된 입력입니다.---\n");
		printf("---변경 사항을 적용하지 않고 선택 화면으로 돌아갑니다.---\n");
	}
}


//-----------------------------------------------------------------------------------출결관리 함수. 정재헌 담당


void attendance(void) {
	int select;
	system("cls");
	printf("******************\n");
	printf("출결 관리 화면\n");

	while (1) {
		printf("******************\n");
		printf("1. 출결 관리\n2. 출결 현황 조회\n3. 메인 화면으로\n******************\n선택: ");
		scanf_s("%d", &select);

		switch (select) {
		case 1:
			attendanceAdd(); //학생의 출결정보를 수정하는 함수
			break;
		case 2:
			attendanceSearch(); //학생의 출결정보를 조회하는 함수
			break;
		case 3:
			return;
			break;
		default:
			system("cls");
			printf_s("---잘못된 입력---\n");
			getchar();
			break;
		}
	}
}

void attendanceAdd(void) { //학생의 출석 정보를 수정하는 함수
	int selectStudent, selectDay, selectAttendance;
	int n = 10;

	inquiryInfo(); //학생 리스트 출력
	if (isEmpty()) { //학생 정보가 없으면 빠져나감.
		return;
	}

	printf("학생 번호 선택: ");
	scanf_s("%d", &selectStudent);
	if ((selectStudent >= studentCount) || (selectStudent < 0)) { //출결정보를 수정 할 학생 번호 선택
		system("cls");
		printf("---잘못된 번호입니다.---\n");
		getchar();
		return; 
	}
	do {
		printf("주차 선택(1~15): ");
		scanf_s("%d", &selectDay); //몇주차 출결 정보를 수정할지 선택
		if ((selectDay > 15) || (selectDay < 1)) {
			printf("잘못된 값\n");
			getchar();
		}
	} while ((selectDay > 15) || (selectDay < 1));
	do
	{
		printf("1.출석 2.결석 3.지각\n선택: ");
		scanf_s("%d", &selectAttendance); //출석, 결석, 지각 선택
		if ((selectAttendance > 3) || (selectAttendance < 0)) {
			printf("잘못된 값\n");
			getchar();
		}
	} while ((selectAttendance > 3) || (selectAttendance < 0));

	system("cls");

	switch (selectAttendance) { //결과 화면 출력
	case 1:
		studentInfo[selectStudent].attendance[selectDay - 1] = 1;
		printf("%s학생 %d주차 출석 처리 완료\n", studentInfo[selectStudent].name, selectDay);
		break;
	case 2:
		studentInfo[selectStudent].attendance[selectDay - 1] = 0;
		printf("%s학생 %d주차 결석 처리 완료\n", studentInfo[selectStudent].name, selectDay);
		break;
	case 3:
		studentInfo[selectStudent].attendance[selectDay - 1] = 2;
		printf("%s학생 %d주차 지각 처리 완료\n", studentInfo[selectStudent].name, selectDay);
		break;
	default:
		break;
	}

	for (int i = 0; i < 15; i++) { //결과를 성적 기능의 출결 점수에 반영함.
		switch (studentInfo[selectStudent].attendance[i])
		{
		case 0:
			n -= 3;
			break;
		case 1:
			break;
		case 2:
			n -= 1;
			break;
		default:
			break;
		}
	}
	if (n < 0) {
		studentInfo[selectStudent].scores[0] = 0;
	}
	else {
		studentInfo[selectStudent].scores[0] = n;
	}
}

void attendanceSearch() { //학생들의 출석 정보를 출력하는 함수

	if (studentCount == 0) { //등록 된 학생이 한 명도 없으면 없음을 알리고 함수 종료
		system("cls");
		printf("---학생 정보가 없습니다.---\n");
		return;
	}
	system("cls");
	printf("학생 정보 출력\n***************************************************************************************************************************************\n번호\t이름\t1주차\t2주차\t3주차\t4주차\t5주차\t6주차\t7주차\t8주차\t9주차\t10주차\t11주차\t12주차\t13주차\t14주차\t15주차\n");
	for (int i = 0; i < studentCount; i++) {
		printf("%d\t%s\t", i, studentInfo[i].name);
		for (int y = 0; y < 15; y++) {
			switch (studentInfo[i].attendance[y]) {
			case 1:
				printf("출석\t");
				break;
			case 2:
				printf("지각\t");
				break;
			case 0:
				printf("결석\t");
				break;
			default:
				break;
			}
		}
		printf("\n");
	}
	printf("***************************************************************************************************************************************\n총 %d명의 학생 정보가 있습니다.\n", studentCount);
}


//-----------------------------------------------------------------------------------성적관리 함수. 길민준 담당


void grade(void) {
	int key = 0;
	system("cls");
	printf("*******************\n");
	printf("성적 관리 화면\n");

	while ((key = SelectMenu()) != 5)//선택한 메뉴가 0이 아니면 반복
	{
		switch (key)//선택한 키에 따라 기능 수행
		{
		case 1: AddStudent(); break;
		case 2: RemoveStudent(); break;
		case 3: FindStudent(); break;
		case 4: ListStudent(); break;
		default: 
			system("cls");
			printf("---잘못된 입력입니다.---\n");
			getchar();
			break;
		}
	}
	printf("프로그램 종료\n");
}

int SelectMenu()
{
	int key = 0;
	printf("*******************\n");
	printf("1. 학생 성적 입력\n2. 학생 성적 초기화\n3. 학생 검색\n4. 목록으로 보기\n5. 메인 화면으로 \n");
	printf("*******************\n입력: ");
	scanf_s("%d", &key);
	return key;
}

void AddStudent() { //학생 데이터 입력
	int num;
	double score;

	inquiryInfo(); //학생 정보 출력
	if (isEmpty()) { //학생 정보가 없으면 빠져나감
		return;
	}

	printf("점수 입력 할 학생 번호(0 ~ %d): ", studentCount - 1);
	scanf_s("%d", &num);

	if (IsAvailNum(num) == 0)//유효한 번호인지 판별하는 IsAvailNum() 함수 호출 후 유효한 번호가 아닐 때 메세지 출력 후 빠져나감.
	{
		system("cls");
		printf("---범위를 벗어난 학생 번호입니다.---\n");
		return;
	}

	printf("%s 학생의 성적을 입력합니다.\n", studentInfo[num].name);

	do
	{
		printf("시혐 점수(0.0~60.0): ");
		scanf_s("%lf", &score); //시험 점수를 입력 함.
		if ((score < 0.0) || (score > 60.0)) {
			printf("잘못된 범위입니다.\n");
			getchar();
		}
	} while ((score < 0.0) || (score > 60.0)); //시험 점수 입력 범위을 벗어난 숫자 입력 시 다시 입력하도록 함.
	studentInfo[num].scores[1] = score;

	do
	{
		printf("과제 점수(0.0~30.0): ");
		scanf_s("%lf", &score); //과제 점수를 입력 함.
		if ((score < 0.0) || (score > 30.0)) {
			printf("잘못된 범위입니다.\n");
			getchar();
		}
	} while ((score < 0.0) || (score > 30.0)); //과제 점수 입력 범위을 벗어난 숫자 입력 시 다시 입력하도록 함.
	studentInfo[num].scores[2] = score;

	system("cls");
	printf("---성적 입력 완료---\n");
}

void RemoveStudent() {//학생 데이터 삭제
	int num = -1;
	int s = 0;

	inquiryInfo(); //학생 정보 출력
	if (isEmpty()) { //학생 정보가 없으면 빠져나감
		return;
	}

	printf("성적 초기화 할 학생 번호(0~%d): ", studentCount - 1);
	scanf_s("%d", &num); //초기화 할 학생 번호 입력

	if (IsAvailNum(num) == 0)//유효한 번호인지 판별하는 IsAvailNum() 함수 호출 후 유효한 번호가 아닐 때 메세지 출력 후 빠져나감.
	{
		system("cls");
		printf("범위를 벗어난 학생 번호입니다.\n");
		return;
	}

	for (s = 1; s < 3; s++) //학생의 시험 성적과 과제 성적을 -1로 초기화 함.
	{
		studentInfo[num].scores[s] = -1;
	}

	printf("삭제하였습니다.\n");
}

void FindStudent() { //한 명의 학생 성적 검색
	int num = -1;
	int s = 0;

	inquiryInfo(); //학생 정보 출력
	if (isEmpty()) { //학생 정보가 없으면 빠져나감
		return;
	}

	printf("검색할 학생 번호(0~%d): ", studentCount - 1);
	scanf_s("%d", &num);

	if (IsAvailNum(num) == 0)//유효한 번호인지 판별하는 IsAvailNum() 함수 호출 후 유효한 번호가 아닐 때 메세지 출력 후 빠져나감.
	{
		system("cls");
		printf("---범위를 벗어난 학생 번호입니다.---\n");
		return;
	}

	system("cls");
	ViewStuData(num); //학생 한명의 성적 내역을 출력하는 ViewStuData() 함수 호출
}

void ListStudent() { //목록 보기
	if (isEmpty()) {
		system("cls");
		printf("---학생 정보가 없습니다.---\n");
		return;
	}

	system("cls");
	printf("학생 성적 출력(성적이 -1인 곳은 미입력)\n********************************************************************************************************\n번호\t\t이름\t\t%s\t\t%s\t\t%s\t\t총점\n", stitles[0], stitles[1], stitles[2]);
	for (int i = 0; i < studentCount; i++) {
		printf("%d\t\t%s\t\t%.1lf\t\t\t%.1lf\t\t\t%.1lf\t\t\t%.1lf\n", i, studentInfo[i].name, studentInfo[i].scores[0], studentInfo[i].scores[1], studentInfo[i].scores[2], studentInfo[i].scores[0] + studentInfo[i].scores[1] + studentInfo[i].scores[2]);
	}
	printf("********************************************************************************************************\n총 %d명의 성적 정보가 있습니다.\n\n\n", studentCount);
}
int IsAvailNum(int num) { //유효한 번호인지 판별하여 리턴함.
	return (num >= 0) && (num <= studentCount - 1);
}

void ViewStuData(int n) { //학생 한명의 성적 내역을 출력하는 함수
	int i = 0;
	int s = 0;

	printf("---%s 학생 점수 조회---\n%s: %.1lf점\n%s: %.1lf점\n%s: %.1lf점\n총점: %.1lf점\n", studentInfo[n].name, stitles[0], studentInfo[n].scores[0], stitles[1], studentInfo[n].scores[1], stitles[2], studentInfo[n].scores[2], studentInfo[n].scores[0] + studentInfo[n].scores[1] + studentInfo[n].scores[2]);
}
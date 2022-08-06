#include <stdio.h>
#include <list>
#include <algorithm>

using namespace std;

char map[20][21];
int result = 0;
int n;

void swipe(char board[][21], int count, int dir) {
	if (count > 5) {
		return;
	}

	int max_result = 0;
	bool changed = false;
	list<int> lt;


	// 위로 스와이프
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] != '0') {
				if (lt.empty()) {
					lt.push_back(board[i][j] - '0');
				}
				else if (lt.back() == board[i][j] - '0') {
					int last_elem = lt.back();
					lt.pop_back();
					last_elem *= 2;
					changed = true;
					lt.push_back(last_elem);
					max_result = max(last_elem, max_result);
				}
				else {
					lt.push_back(board[i][j] - '0');
					max_result = max(board[i][j] - '0', max_result);
				}
			}
		}

		for (int w = 0; w < n; w++) {
			if (lt.empty()) {
				board[i][w] = '0';
			}
			else {
				board[i][w] = lt.front() + '0';
			}
		}
	}

	result = max(result, max_result);

	if (changed) {
		swipe(board, count + 1, 0);
		swipe(board, count + 1, 1);
		swipe(board, count + 1, 2);
		swipe(board, count + 1, 3);
	}
	else {
		return;
	}
	

	if (max_result == 0) {
		return;
	}
}

int main() {

	// 입력받기
	scanf("%d", &n);

	// 상하좌우 스와이프

	// 더 이상 스와이프가 불가능하면 return
	swipe(map, 1, 0);

	// 백 조건
	// 1. 더 이상 스와이프가 불가능하다
	// 2. 스와이프 횟수가 5번이 넘었다


	// 결과 출력
	printf("%d", result);

	return 0;
}

#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

struct INFO {
	int rx, ry, bx, by, count;
};

INFO start;
char board[10][11];
int h, w;
int dir_x[4] = { 0, 0, -1, 1 };
int dir_y[4] = { -1, 1, 0, 0 };

int bfs() {
	int visited[10][10][10][10];

	queue<INFO> q;

	q.push(start);

	visited[start.rx][start.ry][start.bx][start.by] = 1;

	while (!q.empty()) {
		struct INFO front = q.front();
		q.pop();

		if (front.count >= 10) {
			return -1;
		}

		for (int i = 0; i < 4; i++) {
			int next_rx = front.rx;
			int next_ry = front.ry;
			int next_bx = front.bx;
			int next_by = front.by;

			bool failed = false;

			while (true) {
				if (board[next_by][next_bx] == 'O') {
					failed = true;
					break;
				}

				if (board[next_by][next_bx] != '#') {
					next_bx += dir_x[i];
					next_by += dir_y[i];
				}
				else {
					next_bx -= dir_x[i];
					next_by -= dir_y[i];

					break;
				}
			}

			if (failed) {
				continue;
			}

			while (true) {
				if (board[next_ry][next_rx] == 'O') {
					return front.count + 1;
				}

				if (board[next_ry][next_rx] != '#') {
					next_rx += dir_x[i];
					next_ry += dir_y[i];
				} else {
					next_rx -= dir_x[i];
					next_ry -= dir_y[i];

					break;
				}
			}

			if (next_rx == next_bx && next_ry == next_by) {
				int r_dist = abs(next_rx - front.rx) + abs(next_ry - front.ry);
				int b_dist = abs(next_bx - front.bx) + abs(next_by - front.by);

				if (r_dist > b_dist) {
					next_rx -= dir_x[i];
					next_ry -= dir_y[i];
				} else {
					next_bx -= dir_x[i];
					next_by -= dir_y[i];
				}
			}

			if (visited[next_rx][next_ry][next_bx][next_by] != 1) {
				struct INFO next;
				next.rx = next_rx;
				next.ry = next_ry;
				next.bx = next_bx;
				next.by = next_by;
				next.count = front.count + 1;

				q.push(next);

				visited[next_rx][next_ry][next_bx][next_by] = 1;
			}
			
		}
	}

	return -1;
}

int main()
{
	scanf("%d %d\n", &h, &w);
	
	for (int i = 0; i < h; i++) {
		scanf("%s", board[i]);
	}

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (board[y][x] == 'R') {
				start.rx = x;
				start.ry = y;
			}
			if (board[y][x] == 'B') {
				start.bx = x;
				start.by = y;
			}
		}
	}

	start.count = 0;

	int result = bfs();

	printf("%d", result);

	return 0;
}

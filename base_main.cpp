#include <iostream>
#include <vector>
using namespace std;

#define WITH_ENEMY_PUSH true
const int maxn = 239;
const int resure = 3;

#ifdef WITH_ENEMY_PUSH
const vector<int> enemy_push = {10, 20, 40, 60, 100, 150, 200, 239, 350};
#endif

int random(int min, int max) {
	srand(time(NULL));
	int num = min + rand() % (max - min + 1);
	return num;
}

int x = 0, y = 0, pref = 1;
bool game_over = false;
vector<vector<int>> pole;

bool check_win() {
	for (int now_x = 0; now_x < maxn; ++now_x) {
		for (int now_y = 0; now_y < maxn; ++now_y) {
			if (pole[now_x][now_y]) {
				return false;
			}
		}
	}
	return true;
}

void get_knife() {
	if (pref == 1) {
		for (int now_y = y; now_y < maxn; ++now_y) {
			if (pole[x][now_y] > 0) {
				--pole[x][now_y];
			}
		}
	} else if (pref == 2) {
		for (int now_y = 0; now_y <= y; ++now_y) {
			if (pole[x][now_y] > 0) {
				--pole[x][now_y];
			}
		}
	} else if (pref == 3) {
		for (int now_x = x; now_x < maxn; ++now_x) {
			if (pole[now_x][y] > 0) {
				--pole[now_x][y];
			}
		}
	} else {
		for (int now_x = 0; now_x <= x; ++now_x) {
			if (pole[now_x][y] > 0) {
				--pole[now_x][y];
			}
		}
	}
}

void push_step(char step) {
	if (step == 'Q') {
		game_over = true;
	} else if (step == 'W') {
		++y;
		pref = 1;
	} else if (step == 'X') {
		--y;
		pref = 2;
	} else if (step == 'A') {
		--x;
		pref = 3;
	} else if (step == 'D') {
		++x;
		pref = 4;
	} else if (step == 'S') {
		cout << "You are lose, try again...\n";
		exit(0);
	} else if (step == 'P') {
		get_knife();
	}
}

void step_order() {
	for (int now_x = 0; now_x < maxn; ++now_x) {
		for (int now_y = 0; now_y < maxn; ++now_y) {
			if (pole[now_x][now_y]) {
				int go = random(1, 4);
				if (go == 1) {
					if (now_y != maxn - 1) {
						--pole[now_x][now_y];
						++pole[now_x][now_y + 1];
					}
				} else if (go == 2) {
					if (now_y != 0) {
						--pole[now_x][now_y];
						++pole[now_x][now_y - 1];
					}
				} else if (go == 3) {
					if (now_x != maxn - 1) {
						--pole[now_x][now_y];
						++pole[now_x + 1][now_y];
					}
				} else {
					if (now_x != 0) {
						--pole[now_x][now_y];
						++pole[now_x - 1][now_y];
					}
				}
			}
		}
	}
}

void get_enemy_push() {
	for (int now_x = random(0, resure); now_x < maxn; now_x += resure) {
		for (int now_y = random(0, resure); now_y < maxn; now_y += resure) {
			++pole[now_x][now_y];
		}
	}
}

#define FAST_IO true
#define FILE true

int main() { // or signed
	// if your need faster code;
#ifdef FAST_IO
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
#endif
	// push in freopen your files;
	// or comment it if you don't need files;
#ifdef FILE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	cout << "Time to new project\n";
	cout << "Game rules :\n";
	// TODO: Game rules;
	pole.resize(maxn, vector<int>(maxn, 0));
	for (int now_x = 0; now_x < maxn; ++now_x) {
		for (int now_y = 0; now_y < maxn; ++now_y) {
			pole[now_x][now_y] = random(0, 1);
		}
	}
	int cnt_steps = 0;
	while (!game_over) {
#ifdef WITH_ENEMY_PUSH
		for (int id = 0; id < enemy_push.size(); ++id) {
			if (enemy_push[id] == cnt_steps) {
				get_enemy_push();
			}
		}
#endif
		step_order();
		// TODO: Clear file output.txt;
		cout << "Now pole of game is :\n";
		for (int now_x = 0; now_x < maxn; ++now_x) {
			for (int now_y = 0; now_y < maxn; ++now_y) {
				cout << pole[now_x][now_y] << ' ';
			}
			cout << '\n';
		}
		if (check_win()) {
			cout << "You are win, good job!\n";
			return 0;
		}
		cout << "Please choose your step :\n";
		char step;
		cin >> step;
		push_step(step);
#ifdef WITH_ENEMY_PUSH
		++cnt_steps;
#endif
	}
	// TODO: Push project to github;
	return 0;
}
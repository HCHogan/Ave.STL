#include <iostream>

const int N = 10010;

struct node {
	int s[2];	// child
	int p;		// parent
	int v;		// value
	int cnt, size;
	void init(int p1, int v1) {
		p = p1, v = v1;
		cnt = size = 1;
	}
} tr[N];

void rotate(int x) {
	int y = tr[x].p, z = tr[y].p;

}

#pragma once
#include <algorithm>
#include <utility>

using namespace std;

#define inf32 1000000000

class MyPriorityQueue {
public:
	MyPriorityQueue(int n) {

        V = new pair<int, int>[n];
		index = new int[n];
		this->n = n;

		for (int i = 0; i < n; i++)
			V[i] = { i, inf32 };

		for (int i = 0; i < n; i++)
			index[i] = i;
	}

	pair<int, int> Top() {
		return V[0];
	}

    bool Empty(){
        return n==0;
    }

	void Pop() {
		swap(V[0], V[n - 1]);
		swap(index[V[0].first], index[V[n - 1].first]);

		n--;

		Heapfy(0);
	}

	void Heapfy(int at)
	{
		int p1 = at * 2 + 1;
		int p2 = at * 2 + 2;

		int pos = at;
		if (p1 < n && V[p1].second < V[pos].second)
			pos = p1;
		if (p2 < n && V[p2].second < V[pos].second)
			pos = p2;

		if (at != pos)
		{
			swap(V[at], V[pos]);
			swap(index[V[at].first], index[V[pos].first]);

			Heapfy(pos);
		}
	}

	void Alterar(int vertex, int value)
	{
		int at = index[vertex];

		V[at].second = value;

		while (at != 0 && V[(at - 1) / 2].second > V[at].second) {
			swap(V[(at - 1) / 2], V[at]);
			swap(index[V[(at - 1) / 2].first], index[V[at].first]);

			at = (at - 1) / 2;
		}
	}

private:
	pair<int, int>* V;
	int* index;
	int n;
};

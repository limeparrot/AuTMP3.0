// Вариант 82
#include <iostream>
#include <iomanip>
#define N 10 
#define count 0
#define lc 1
#define rs 2
#define size 3

int o = 0;

using namespace std;

struct Tree
{
	int mas[N][4] = { 0 };
	int n = 0; // Kol-vo elementov v dereve
	int root;	
};

void aroot(Tree* a, int k)
{
		a->mas[a->n][count] = k;
		a->mas[a->n][lc] = 0;
		a->mas[a->n][rs] = 0;
		a->mas[a->n][size] = 1;
		(a->n)++;
}


int add(Tree* a, int k)
{
	if (a->n == 0) { aroot(a, k); 
	}
	else {
		a->mas[a->n][count] = k;
		a->mas[a->n][lc] = 0;
		a->mas[a->n][rs] = 0;
		a->mas[a->n][size] = 0;
		(a->n)++;
	}
	return a->mas[(a->n)-1][count];
}

int f(Tree* t,int k)
{
	int u = 0;
	for (u=0; u < N; u++)
	{
		if (t->mas[u][count] == k) break; 
	}
	return u;
}



int getsize(Tree* t, int num) // обертка для поля size, работает с пустыми деревьями (t=null)
{
	num = f(t, num);
	if (!(t->mas[num][size])) return 0;
	return t->mas[num][size];
}
void fixsize(Tree* t, int n) // установление корректного размера дерева
{
	int i = N-1;
	int num;
	while(i>-1)
	{
		if(t->mas[i][count]){
		num = i;
		t->mas[num][size] = getsize(t, t->mas[num][lc]) + getsize(t, t->mas[f(t, (t->mas[num][lc]))][rs]) + 1; }
		i--; 
	}
}

int rotateright(Tree* t, int num) // правый поворот вокруг узла p...передаётся номер в массиве
{
	int q = f(t, t->mas[num][lc]); // q - адрес левого узла
	if (!t->mas[q][count]) return t->mas[num][count];
	if (num == 0) t->root = q;
	t->mas[num][lc] = t->mas[f(t, (t->mas[q][lc]))][rs];
	t->mas[f(t, (t->mas[q][lc]))][rs] = t->mas[num][count];
	t->mas[q][size] = t->mas[num][size];
	fixsize(t, num);
	return t->mas[q][count];
}

int rotateleft(Tree* t, int num) // левый поворот вокруг узла p...передаётся номер в массиве
{
	int p = f(t, t->mas[f(t,t->mas[num][lc])][rs]); // q - адрес левого узла
	if (!t->mas[p][count]) return t->mas[num][count];
	if (num == 0) t->root = p;
	t->mas[f(t,t->mas[num][lc])][rs] = t->mas[p][lc];
	t->mas[p][lc] = t->mas[num][count];
	t->mas[p][size] = t->mas[num][size];
	fixsize(t, num);
	return t->mas[p][count];
}

int insertroot(Tree* t, int num, int k) // вставка нового узла с ключом k в корень дерева t
{
	if(num != 0) num = f(t, num);
	if (!t->mas[num][count]) return add(t, k);
	if (k < t->mas[num][count])
	{
		t->mas[num][lc] = insertroot(t, t->mas[num][lc], k); cout << "ERR";
		return rotateright(t, num);
	}
	else
	{
		cout << "ER66R";
		t->mas[f(t, t->mas[num][lc])][rs] = insertroot(t, t->mas[f(t, t->mas[num][lc])][rs], k);
		return rotateleft(t, num);
	}
}


void insert(Tree* t, int num, int k)
{
	bool e = true;
	if (!(t->n)) { add(t, k); 	e = false; }
	int i = 0; int h;
	if (rand() % (t->mas[num][size] + 1) == 0 &&0) { //рандомизированная вставка
	insertroot(t, num, k); e = false;}
	while (e)
	{
		if ((t->mas[num][count] > k && i == 0) || (t->mas[f(t, num)][count] > k && i != 0))
		{
			if (i == 0)
			{
				num = t->mas[num][lc];
				if (num == 0) { t->mas[num][lc] = add(t, k); e = false; }
				else
				{
					i++; continue;
				}
			}
			else {
				h = num;
				num = t->mas[f(t, num)][lc];
				if (num == 0) { t->mas[f(t, h)][lc] = add(t, k); e = false; }
				else
				{
					i++; continue;
				}
			}
		}
		else
		{
			if (i == 0)
			{
				num = t->mas[f(t,(t->mas[num][lc]))][rs];
				if (num == 0) { t->mas[f(t,(t->mas[num][lc]))][rs] = add(t, k); e = false; }
				else
				{
					i++; continue;
				}
			}
			else 
			{
				h = num;
				num = t->mas[f(t,(t->mas[f(t, h)][lc]))][rs];
				if (num == 0) { t->mas[f(t, (t->mas[f(t, h)][lc]))][rs] = add(t, k);    e = false; }
				else
				{
					i++; continue;
				}
			}
		} 
	}

	fixsize(t, num);
}

void pr(Tree* t, int num)// А - прямой 
{
	cout << t->mas[num][count] << "->";

	if (t->mas[num][lc] != 0) 
	{
		pr(t, f(t, t->mas[num][lc])); 
	}

	if (t->mas[f(t, t->mas[num][lc])][rs] != 0)
	{
		pr(t, f(t, t->mas[f(t, t->mas[num][lc])][rs]));
	}
}

void sem(Tree* t, int num)// В - симметричный
{
	

	if (t->mas[num][lc] != 0)
	{
		pr(t, f(t, t->mas[num][lc]));
	}
	cout << t->mas[num][count] << "->";
	if (t->mas[f(t, t->mas[num][lc])][rs] != 0)
	{
		pr(t, f(t, t->mas[f(t, t->mas[num][lc])][rs]));
	}

}

int join(Tree* p, Tree* q) // объединение двух деревьев, обход А , B - обртаный.
{
	if (!p->mas[p->root][count]) return 0;
	if (!q->mas[q->root][count]) return 0;
	int a[N] = { 0 }; int z = 1000; int v = 0; a[0] = q->mas[0][count];
	for (int i = 1; i < q->n; i++)
		a[i]  = q->mas[i][count]; 
	for (int i = 1; i < q->n; i++)
		for (int j = i; j < q->n; j++)
			if (a[i] > a[j]){
				int r = a[j];
				a[j] = a[i];
				a[i] = r;
			}
	for(int i = 1; i < q->n; i++)
		insert(p, 0, a[i]);
	insert(p, 0, a[0]);

}

int remove(Tree* t, int k, int numb) // удаление из дерева t первого найденного узла с ключом k 
{
	if (!t->n) return 0;
	if (t->mas[f(t, k)][count] == k)
	{
		int q = join(t, t);
		t->mas[f(t, k)][count] = 0; 
		return t->mas[q][count];
	}
	else if (k < t->mas[f(t, k)][count])
			t->mas[f(t, k)][lc] = remove(t, t->mas[f(t, k)][lc], k);
	else
			t->mas[f(t, t->mas[f(t, k)][lc])][rs] = remove(t, t->mas[f(t, k)][lc], k);
	return t->mas[f(t, k)][count];
}

void main()
{
	Tree a;

	a.root = 0;
	insert(&a, a.root, 5);
	insert(&a, a.root, 7); 
	insert(&a, a.root, 3);
	insert(&a, a.root, 8);
	cout << "Tree A(direct output): "; pr(&a, 0); cout << endl;

	
	Tree b; 

	b.root = 0;
	insert(&b, b.root, 2);
	insert(&b, b.root, 1);
	insert(&b, b.root, 6);
	cout << "Tree B(symmetric output): "; sem(&b, 0); cout << endl;
	
	join(&a, &b);
	cout << endl << "Tree A + B(direct output): "; pr(&a, 0);
}
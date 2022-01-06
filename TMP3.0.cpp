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
		//a->root = 
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
	if (rand() % (t->mas[num][size] + 1) == 0 &&!e) { //рандомизированная вставка
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
				if (num == 0) { t->mas[f(t, (t->mas[f(t, h)][lc]))][rs] = add(t, k); cout << t->mas[f(t, (t->mas[f(t, h)][lc]))][rs];   e = false; }
				else
				{
					i++; continue;
				}
			}
		} 
	}

	fixsize(t, num);
}


//node* join(node* p, node* q) // объединение двух деревьев
//{
//	if (!p) return q;
//	if (!q) return p;
//	if (rand() % (p->size + q->size) < p->size)
//	{
//		p->right = join(p->right, q);
//		fixsize(p);
//		return p;
//	}
//	else
//	{
//		q->left = join(p, q->left);
//		fixsize(q);
//		return q;
//	}
//}

/*
node* remove(node* p, int k) // удаление из дерева p первого найденного узла с ключом k 
{
	if (!p) return p;
	if (p->key == k)
	{
		node* q = join(p->left, p->right);
		delete p;
		return q;
	}
	else if (k < p->key)
		p->left = remove(p->left, k);
	else
		p->right = remove(p->right, k);
	return p;
}
*/





void main()
{
	Tree a;

	a.root = 0;
	insert(&a, a.root, 5);
	insert(&a, a.root, 2); 
	insert(&a, a.root, 7);
	insert(&a, a.root, 6);

	/*
	Tree b;

	b.root = 0;
	insert(&b, b.root, 5);
	insert(&b, b.root, 2);
	insert(&b, b.root, 7);
	insert(&b, b.root, 6);
*/
	//cout <<endl << a.mas[1][0] << a.mas[0][0];
	//cout << a.mas[1][lc]<< endl;


	cout << endl; cout << "count" << "lc  " << "rs   " << "size" ; for (int i = 0; i < N; i++) { cout << endl; for (int j = 0; j < 4; j++) cout << a.mas[i][j] << "    "; }
	//cout << endl; cout << "count" << "lc  " << "rs   " << "size"; for (int i = 0; i < N; i++) { cout << endl; for (int j = 0; j < 4; j++) cout << b.mas[i][j] << "    "; }
}
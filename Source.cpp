struct node // ��������� ��� ������������� ����� ������
{
	int count;
	int size;
	node* left;
	node* right;
	node(int k) { count = k; left = right = 0; size = 1; }
};

int getsize(node* p) // ������� ��� ���� size, �������� � ������� ��������� (t=NULL)
{
	if (!p) return 0;
	return p->size;
}

void fixsize(node* p) // ������������ ����������� ������� ������
{
	p->size = getsize(p->left) + getsize(p->right) + 1;
}

node* join(node* p, node* q) // ����������� ���� ��������
{
	if (!p) return q;
	if (!q) return p;
	if (rand() % (p->size + q->size) < p->size)
	{
		p->right = join(p->right, q);
		fixsize(p);
		return p;
	}
	else
	{
		q->left = join(p, q->left);
		fixsize(q);
		return q;
	}
}

node* remove(node* p, int k) // �������� �� ������ p ������� ���������� ���� � ������ k 
{
	if (!p) return p;
	if (p->count == k)
	{
		node* q = join(p->left, p->right);
		delete p;
		return q;
	}
	else if (k < p->count)
		p->left = remove(p->left, k);
	else
		p->right = remove(p->right, k);
	return p;
}




node* find(node* p, int k) // ����� ����� k � ������ p
{
	if (!p) return 0; // � ������ ������ ����� �� ������
	if (k == p->count)
		return p;
	if (k < p->count)
		return find(p->left, k);
	else
		return find(p->right, k);
}

node* rotateright(node* p) // ������ ������� ������ ���� p
{
	node* q = p->left;
	if (!q) return p;
	p->left = q->right;
	q->right = p;
	q->size = p->size;
	fixsize(p);
	return q;
}

node* rotateleft(node* q) // ����� ������� ������ ���� q
{
	node* p = q->right;
	if (!p) return q;
	q->right = p->left;
	p->left = q;
	p->size = q->size;
	fixsize(q);
	return p;
}

node* insertroot(node* p, int k) // ������� ������ ���� � ������ k � ������ ������ p 
{
	if (!p) return new node(k);
	if (k < p->count)
	{
		p->left = insertroot(p->left, k);
		return rotateright(p);
	}
	else
	{
		p->right = insertroot(p->right, k);
		return rotateleft(p);
	}
}

node* insert(node* p, int k) // ����������������� ������� ������ ���� � ������ k � ������ p
{
	if (!p) return new node(k);
	if (rand() % (p->size + 1) == 0)
		return insertroot(p, k);
	if (p->count > k)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	fixsize(p);
	return p;
}





int main()
{
	node* a[4] = { 0 };
	node* b[4] = { 0 };
	//node tree(1);
	node* tree = insertroot(nullptr, 2); //insert(&tree, 3); insert(&tree, 4);
	insert(tree, 4);
	//node b = *(find(&a, 1)); 
	cout << tree->count << endl;
	cout << find(tree, 4) << endl;
}
*/

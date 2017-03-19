#include <iostream> 
using namespace std;

struct node
{
	int pageNo;
	node *next, *prev;
};

class Hash
{
public:
	Hash(int _capacity){
		int iter;
		capacity = _capacity;
		array = new node* [capacity];
		for (int iter = 0; iter < capacity; ++iter)
		{
			array[iter] = NULL;
		}
	}

	void insertPage(node *candidate){
		array[candidate->pageNo] = candidate;
	}

	node* searchPage(int pageNo){
		return array[pageNo];
	}

	void deletePage(int pageNo){
		array[pageNo] = NULL;
	}

	~Hash();
	
private:
	int capacity;
	node **array;
};

class Queue
{
public:
	Queue(int _size, int _hashCapacity){
		maxSize = _size;
		hashCapacity = _hashCapacity;
		initialize();
	}

	void accessPage(int pageNo){
		node *curr;
		curr = hash->searchPage(pageNo);
		if (curr == NULL)
		{
			curr = new node;
			curr->pageNo = pageNo;
		}
		else{
			detachCurr(curr);
			size--;
		}
		attachToFront(curr);
	}

	void getTable(){
		if(head == NULL){
			cout<<"Empty\n";
			return;
		}
		node *p;
		p = head;
		while(p != tail){
			cout<<p->pageNo<<" -> ";
			p = p->next;
		}
		cout<<p->pageNo<<endl;
	}

	~Queue(){}
private:
	int maxSize;
	int size;
	int hashCapacity;
	node *head;
	node *tail;
	Hash *hash;

	void initialize(){
		head = NULL;
		tail = NULL;
		size = 0;
		hash = new Hash(hashCapacity);
	}

	void detachCurr(node *curr){
		hash->deletePage(curr->pageNo);
		if(curr == head && curr == tail){
			head = NULL;
			tail = NULL;
			return;
		}
		if(curr == head){
			head = head->next;
		}
		else{
			curr->prev->next = curr->next;
		}
		if(curr == tail){
			tail = tail->prev;
		}
		else{
			curr->next->prev = curr->prev;
		}
	}

	void attachToFront(node *curr){
		if (size == maxSize)
		{
			node *p = tail;
			detachCurr(p);
			delete p;
			size--;
		}
		hash->insertPage(curr);
		curr->prev = NULL;
		curr->next = head;
		head = curr;
		if (curr->next == NULL)
		{
			tail = curr;
		}
		else{
			curr->next->prev = curr;
		}
		size++;
	}
	
};

Queue LRUtable(4, 10);

int main(int argc, char const *argv[])
{
	LRUtable.accessPage(1);LRUtable.getTable();
	LRUtable.accessPage(2);LRUtable.getTable();
	LRUtable.accessPage(3);LRUtable.getTable();
	LRUtable.accessPage(2);LRUtable.getTable();
	LRUtable.accessPage(4);LRUtable.getTable();
	LRUtable.accessPage(5);LRUtable.getTable();
	return 0;
}
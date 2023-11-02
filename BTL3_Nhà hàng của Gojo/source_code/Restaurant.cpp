#include "main.h"
class table{
public:
	Restaurant::customer* posX;
	int size;
	table() {
		posX = nullptr;
		size = 0;
	}
	~table() {
		posX->prev->next = nullptr;
		posX->prev = nullptr;
		for (int i = 0; i < size; i++) {
			Restaurant::customer* tem = posX;
			posX = posX->next;
			delete tem;
		}
		size = 0;
	}
	void add(Restaurant::customer* cus) {
		if (!posX) {
			posX = cus;
			posX->next = posX;
			posX->prev = posX;
			size = 1;
		}
		else if (size >= MAXSIZE / 2) {
			int RES = -1;
			int tem = -1;
			Restaurant::customer* cur = posX;
			Restaurant::customer* bestSpot = posX;

			for(int i = 0; i < size; i++){
				int each = cus->energy - cur->energy;
				if (tem < abs(each)) {
					bestSpot = cur;
					RES = each;
					tem = abs(each);
				}
				cur = cur->next;
			}

			if (bestSpot) {
				if (RES >= 0) {
					cus->next = bestSpot->next;
					cus->prev = bestSpot;
					bestSpot->next->prev = cus;
					bestSpot->next = cus;
				}
				else {
					cus->prev = bestSpot->prev;
					cus->next = bestSpot;
					bestSpot->prev->next = cus;
					bestSpot->prev = cus;
				}
				posX = cus;
				size++;
			}
		}
		else {
			if (posX->energy <= cus->energy) {
				cus->next = posX->next;
				cus->prev = posX;
				posX->next->prev = cus;
				posX->next = cus;
			}
			else {
				cus->prev = posX->prev;
				cus->next = posX;
				posX->prev->next = cus;
				posX->prev = cus;
			}
			posX = cus;
			size++;
		}
	}
	bool removeCus(string name) {
		Restaurant::customer* cur = posX;

		for (int i = 0; i < size; i++) {
			if (name == cur->name) {
				break;
			}
			cur = cur->next;
		}

		if (cur->name == name) {
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			if (cur->energy > 0) {
				posX = cur->next;
			}
			else {
				posX = cur->prev;
			}
			if (size == 1) {
				posX = nullptr;
			}
			size--;
			delete cur;
			return true;
		}
		return false;
	}
	bool isin(string name) {
		Restaurant::customer* cur = posX;
		for (int i = 0; i < size; i++) {
			if (cur->name == name) return true;
			cur = cur->next;
		}
		return false;
	}
	Restaurant::customer* getCus(string name) {
		Restaurant::customer* cur = posX;
		for(int i = 0; i < size; i++) {
			if (cur->name == name) return cur;
			cur = cur->next;
		}
		return nullptr;
	}
};

class waitingLine {
public:
	Restaurant::customer* head;
	Restaurant::customer* tail;
	int size;
	waitingLine() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	~waitingLine() {
		size = 0;
		tail = nullptr;
		for (int i = 0; i < size; i++) {
			Restaurant::customer* tem = head;
			head = head->next;
			delete tem;
		}
	}
	void add(Restaurant::customer* cus) {
		if (!head) {
			head = cus;
			tail = head;
			size = 1;
		}
		else {
			tail->next = cus;
			cus->prev = tail;
			tail = cus;
			size++;
		}
	}
	Restaurant::customer* removeFirst() {// remove the old head return it
		if (!head) return nullptr;
		Restaurant::customer* cus = head;
		head = head->next;
		size--;
		if (!head) tail = nullptr;
		return cus;
	}
	bool removeName(string name) {
		if (size == 0) {
			return false;
		}
		Restaurant::customer* curr = head;
		while (curr && curr->name != name) {
			curr = curr->next;
		}
		if (!curr) return false;
		if (curr == head) {
			head = head->next;
			if (head) head->prev = nullptr;
			if (!head) tail = nullptr;
		}
		else if (curr == tail) {
			tail = tail->prev;
			if(tail) tail->next = nullptr;
		}
		else {
			curr->next->prev = curr->prev;
			curr->prev->next = curr->next;
		}
		delete curr;
		size--;
		return true;
	}
};
class Ticket {
public:
	Restaurant::customer* data;
	Ticket* next;
	Ticket* prev;

	Ticket(Restaurant::customer* d) : data(d), next(nullptr), prev(nullptr) {}
	~Ticket() {}
};

class TicketQueue {
public:
	Ticket* front;
	Ticket* rear;

	TicketQueue() : front(nullptr), rear(nullptr) {}
	~TicketQueue() {
		rear = nullptr;
		while (front) {
			Ticket* tem = front;
			front = front->next;
			delete tem;
		}
	}
	bool isEmpty() {
		return front == nullptr;
	}
	void enqueue(Restaurant::customer* data) {
		Ticket* newTicket = new Ticket(data);
		if (rear == nullptr) {
			front = rear = newTicket;
		}
		else {
			rear->next = newTicket;
			newTicket->prev = rear;
			rear = newTicket;
		}
	}
	void dequeue() {
		if (isEmpty()) {
			return;
		}

		Ticket* temp = front;
		front = front->next;
		front->prev = nullptr;

		if (front == nullptr) {
			rear = nullptr;
		}

		delete temp;
	}
	string peek(int n = 0) {
		if (n == 0) {
			if (isEmpty()) {
				return "";
			}
			return front->data->name;
		}
		Ticket* curr = front;
		for (int i = 0; i < n && curr; i++) {
			curr = curr->next;
		}

		if (curr) return curr->data->name;
		return "";
	}
	bool removeName(string name) {
		if (isEmpty()) {
			return false;
		}

		Ticket* curr = front;
		while (curr) {
			if (curr->data->name == name) {
				if (curr == front) {
					front = front->next;
					if (!front) rear = nullptr;
					if (front) front->prev = nullptr;
				}
				else if (curr == rear) {
					rear = rear->prev;
					rear->next = nullptr;
				}
				else {
					curr->prev->next = curr->next;
					curr->next->prev = curr->prev;
				}
				delete curr;
				return true;
			}
			curr = curr->next;
		}
		return false;
	}
	int getOrder(Restaurant::customer* tk) {
		Ticket* cur = front;
		int i = 0;
		while (cur && cur->data != tk) {
			i++;
			cur = cur->next;
		}
		if (cur) return i;
		return -1;
	}
};

class imp_res : public Restaurant
{
public:
	table* tb;
	waitingLine* wl;
	TicketQueue* tq;
	imp_res() {
		tb = new table();
		wl = new waitingLine();
		tq = new TicketQueue();
	};
	~imp_res() {
		delete tb;
		delete wl;
		delete tq;
	};

	void swapCus(customer* a, customer* b) {
		string tempName = a->name;
		int tempEnergy = a->energy;
		a->name = b->name;
		a->energy = b->energy;
		b->name = tempName;
		b->energy = tempEnergy;
	}
	customer* getCus(customer* head, int n) { //for shellsort
		if (!head) return nullptr;
		customer* rs = head;
		while (n--) {
			rs = rs->next;
		}
		return rs;
	}
	int inssort2(customer* head, int n, int incr) {
		int rs = 0;
		for (int i = incr; i < n; i += incr) {
			for (int k = i; k >= incr; k -= incr) {
				int en1 = abs(getCus(head, k)->energy);
				int en2 = abs(getCus(head, k - incr)->energy);
				if (en1 < en2) break;
				if ((en1 == en2)
					&& tq->getOrder(getCus(head, k)) > tq->getOrder(getCus(head, k - incr))) {
					break;
				}
				swapCus(getCus(head, k), getCus(head, k - incr));
				rs++;
			}
		}
		return rs;
	}
	int shellsort(customer* head, int n) {    // Shellsort referenced by Clifford A. Shaffer
		int rs = 0;
		for (int i = n / 2; i > 2; i /= 2) {
			for (int j = 0; j < i; j++) {
				rs += inssort2(head, n - j, i);
			}
		}
		rs += inssort2(head, n, 1);
		//cout << "Swap: " << rs << endl;
		return rs;
	}
	void RED(string name, int energy) // add new customer
	{
		//cout << name << ": " << energy << endl;
		if (!energy) return;
		customer* tem = tb->posX; // In heaven (above the sky), in the world (under the sky), I am the one and only.
		for(int i = 0; i < tb->size; i++) {
			if (tem->name == name) return;
			tem = tem->next;
		}
		tem = wl->head;
		for (int i = 0; i < wl->size; i++) {
			if (tem->name == name) return;
			tem = tem->next;
		}

		customer* cus = new customer(name, energy, nullptr, nullptr);
		if (tb->size < MAXSIZE) {
			tb->add(cus);
		}
		else if (wl->size < MAXSIZE) {
			wl->add(cus);
		}
		else return;
		tq->enqueue(cus);
	}
	void BLUE(int num) //delete first num customers
	{
		//cout << "blue " << num << endl;
		if (num == 0) return;
		if (num >= tb->size) num = tb->size;

		int t = 0;
		for (int i = 0; i < num; i++) {
			string name = tq->peek(t);
			if (tb->isin(name)) {
				tq->removeName(name);
				tb->removeCus(name);
			}
			else t++;
		}
		while (tb->size < MAXSIZE && wl->size > 0) {// add customer from waiting line to table
			customer* cus = wl->removeFirst();
			tb->add(cus);
		}
	}
	void PURPLE() // shellsort
	{
		//cout << "purple" << endl;
		if (!wl->head) return;
		customer* maxEner = wl->head;
		customer* cur = wl->head;
		int n = 0, rs = 0;
		while (cur) {
			if (abs(maxEner->energy) <= abs(cur->energy)) {
				if (abs(maxEner->energy) == abs(cur->energy)) {
					if (!(tq->getOrder(maxEner) < tq->getOrder(cur))) {
						n++;
						cur = cur->next;
						continue;
					}
				}
				maxEner = cur;
				rs = n;
			}
			n++;
			cur = cur->next;
		}
		int num = shellsort(wl->head, rs + 1) % MAXSIZE; //return swap times
		BLUE(num);
	}
	void REVERSAL() //reversal
	{
		//cout << "reversal" << endl;

		if (tb->size <= 1) {
			return;
		}
		waitingLine* wlpos = new waitingLine;// create positive list
		waitingLine* wlneg = new waitingLine;// create negative list

		customer* tail = tb->posX;

		string posXname = tb->posX->name;
		customer* cur = tb->posX;

		for(int i = 0; i < tb->size; i++) {
			if (cur->energy > 0) {
				wlpos->add(new customer(cur->name, cur->energy, nullptr, nullptr));
			}
			else {
				wlneg->add(new customer(cur->name, cur->energy, nullptr, nullptr));
			}
			cur = cur->prev;
		}

		customer* cusneg = wlneg->tail;
		customer* cuspos = wlpos->tail;
		cur = tb->posX;

		cusneg = wlneg->tail;
		cuspos = wlpos->tail;
		for (int i = 0; i < tb->size; i++) {// reversal
			if (cur->energy > 0) {
				swapCus(cur, cuspos);
				cuspos = cuspos->prev;
			}
			else {
				swapCus(cur, cusneg);
				cusneg = cusneg->prev;
			}
			cur = cur->prev;
		}

		delete wlpos;
		delete wlneg;

		cur = tb->posX;
		for (int i = 0; i < tb->size; i++) {
			if (cur->name == posXname) {
				tb->posX = cur;
				break;
			}
			cur = cur->next;
		}
	}
	void UNLIMITED_VOID() //print sublist that have minimum energy (the negative?) ¯\_(ツ)_/¯
	{// minimum energy then maximum length sublist
		//cout << "unlimited_void" << endl;
		if (tb->size < 4) return;
		else {
			int rs = 2147483647;
			int cursum = 0, length = 4;
			customer* start = tb->posX, * curr = tb->posX;

			customer* rsl = getCus(tb->posX, 0), * rsr = getCus(tb->posX, 3);

			for (int i = 4; i < tb->size; i++) {
				cursum = 0;
				for (int k = 0; k < i; k++) {
					cursum += getCus(start, k)->energy;
				}
				if (cursum <= rs) {
					rs = cursum;
					rsl = start;
					rsr = getCus(start, i - 1);
					length = i;
				}
				for (int k = i; k < tb->size + i; k++) {
					customer* cus1 = getCus(start, k);
					customer* cus2 = getCus(start, k - i);
					cursum += cus1->energy - cus2->energy;
					if (cursum < rs || (cursum == rs && i >= length)) {
						rs = cursum;
						rsl = cus2->next;
						rsr = cus1;
						length = i;
					}
				}
			}

			waitingLine* rslist = new waitingLine();
			int minimum = 2147483647;

			for(int i = 0; i < length; i++) {
				rslist->add(new customer(rsl->name, rsl->energy, nullptr, nullptr));
				if (minimum > rsl->energy) {
					minimum = rsl->energy;
				}
				rsl = rsl->next;
			}

			customer* cur = rslist->head;
			rslist->tail->next = rslist->head;
			rslist->head->prev = rslist->tail;

			while (cur->energy != minimum) {
				cur = cur->next;
			}

			for (int i = 0; i < length; i++) {
				cur->print();
				cur = cur->next;
			}
			delete rslist;
		}
	}
	void DOMAIN_EXPANSION() //kick the customers with greater energy sum
	{
		//cout << "domain_expansion" << endl;
		if (tb->size + wl->size <= 1) return;
		int sum = 0;

		customer* cur = tb->posX;
		for (int i = 0; i < tb->size; i++) {
			sum += cur->energy;
			cur = cur->next;
		}

		cur = wl->head;
		for (int i = 0; i < wl->size; i++) {
			sum += cur->energy;
			cur = cur->next;
		}

		bool pos = (sum >= 0);
		Ticket* tic = tq->rear;
		while (tic) { //print deleted customers
			if (tic->data->energy < 0 && pos) {
				tic->data->print();
			}
			else if (tic->data->energy > 0 && !pos) {
				tic->data->print();
			}
			tic = tic->prev;
		}
		tic = tq->front;
		while (tic) {// delete customers
			string name = tic->data->name;
			Ticket*tn = tic->next;
			if (tic->data->energy < 0 && pos) {
				tq->removeName(name);
				tb->removeCus(name);
				wl->removeName(name);
			}
			else if (tic->data->energy > 0 && !pos) {
				tq->removeName(name);
				tb->removeCus(name);
				wl->removeName(name);
			}
			tic = tn;
		}
		while (tb->size < MAXSIZE && wl->size > 0) {// add customer from waiting line to table
			customer* cus = wl->removeFirst();
			tb->add(cus);
		}
	}
	void LIGHT(int num) // print
	{
		//cout << "light " << num << endl;
		if (num == 0) { // print waiting line
			if (wl->size == 0) return;
			customer* cur = wl->head;

			while (cur) {
				cur->print();
				cur = cur->next;
			}
		}
		else {
			if (tb->size == 0) return;
			customer* cur = tb->posX;

			if (num > 0) {
				for (int i = 0; i < tb->size; i++) {
					cur->print();
					cur = cur->next;
				}
			}
			else if (num < 0) {
				for (int i = 0; i < tb->size; i++) {
					cur->print();
					cur = cur->prev;
				}
			}
		}
	}
};

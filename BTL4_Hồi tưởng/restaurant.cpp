#include "main.h"

//Le Vo Dang Khoa 2211606

int ms = 0;
int mod = 1e9+7;
int leak = 2;
bool checkleak = false;
bool inkoku = false;
bool inres = !false;

class Node{
public:
    bool isLeaf;
    int val;
    char ch;
    Node* left;
    Node* right;
    Node(char c, int freq){
        isLeaf = true;
        ch = c;
        val = freq;
        left = right = nullptr;
    }
    Node(int freq, Node* l, Node* r){
        isLeaf = false;
        ch = '\0';
        val = freq;
        left = l;
        right = r;
    }
};
class huffman{
public:
    Node* root = nullptr;
	huffman(string str){
	}
	~huffman(){
		deletehm(root);
	}
	void deletehm(Node* node){
		if(!node) return;

		deletehm(node->left);
		deletehm(node->right);

		
		if(checkleak) {
			cout << "Del node: " << --leak << endl;
		}

		delete node;
	}
	void sorthm(vector<Node*> &hn){
		int i = hn.size() - 1;
		while(i > 0 && hn[i]->val < hn[i - 1]->val){
			swap(hn[i], hn[i - 1]);
			i--;
		}
	}
	void deleteNode(vector<Node*> &vec, int in){ // xoa 2 node tai in
		for(size_t i = in; i < vec.size() - 2; i++){
			vec[i] = vec[i + 2];
		}
		vec.pop_back();
		vec.pop_back();
	}
    int getHeight(Node* node) {
		if (node == nullptr) return 0;
		int left = getHeight(node->left);
		int right = getHeight(node->right);
		return max(left, right) + 1;
	}
	Node* rotateLL(Node* root) {
		Node* newRoot = root->left;
		root->left = newRoot->right;
		newRoot->right = root;
		return newRoot;
	}
	Node* rotateRR(Node* root) {
		Node* newRoot = root->right;
		root->right = newRoot->left;
		newRoot->left = root;
		return newRoot;
	}
	Node* rotateLR(Node* root) {
		root->left = rotateRR(root->left);
		return rotateLL(root);
	}
	Node* rotateRL(Node* root) {
		root->right = rotateLL(root->right);
		return rotateRR(root);
	}
	Node* Rotate3times(Node* root, int &count, bool &check){
		if (root == nullptr || count >= 3 || check)
			return root;

		int balanceFactor = getHeight(root->left) - getHeight(root->right);

		if (balanceFactor > 1) {
			if (getHeight(root->left->left) >= getHeight(root->left->right))
				root = rotateLL(root);
			else
				root = rotateLR(root);
			count++;
			check = true;
			
			cout << "====================================\nRotate:\n";
			print_tree(root);
		} 
		else if (balanceFactor < -1) {
			if (getHeight(root->right->right) >= getHeight(root->right->left))
				root = rotateRR(root);
			else
				root = rotateRL(root);
			count++;
			check = true;
			cout << "====================================\nRotate:\n";
			print_tree(root);
		}

		root->left = Rotate3times(root->left, count, check);
		root->right = Rotate3times(root->right, count, check);

		return root;
	}
	bool build(vector<pair<char, int>> vec){ // trong cay huffman
		if(vec.size() == 0) return false;
		bool in = !false; // temp

        vector<Node*> huffnode;
        for(size_t i = 0; i < vec.size(); i++){
            Node* hn = new Node(vec[i].first, vec[i].second);
			if(checkleak) cout << "Node leaf: " << ++leak << endl;
            huffnode.push_back(hn);
        }

        while(huffnode.size() > 1){
			sorthm(huffnode);
			if(in){
				cout << "====================================\n";
				for(size_t i = 0; i < huffnode.size(); i++){
					if(huffnode[i]->left || huffnode[i]->right){
						print_tree(huffnode[i]);
					}
					else {
						if(huffnode[i]->isLeaf) cout << huffnode[i]->ch << " ";
						cout << huffnode[i]->val << endl;
					}
				}
			}
			
            Node* n1 = huffnode[0];
            Node* n2 = huffnode[1];
            deleteNode(huffnode, 0);
			Node* nR = new Node(n1->val + n2->val, n1, n2);
			int t = 0;
			bool f = true;
			for(int i = 0; i < 3; i++){
				if(f){
					f = false;
					nR = Rotate3times(nR, t, f);
				}
			}

            huffnode.push_back(nR);
			if(checkleak) cout << "Node: " << ++leak << endl;

        }
        root = huffnode[0];
		if(root->isLeaf && (root->left || root->right)) return false;
		if(in){
			cout << "====================================\n";
			print_tree();
		}
		return true;
	}
	void InCay(Node* root, int depth = 0) { //print_tree helper
		if (root == nullptr) return;

		const int khoangCach = 5;

		InCay(root->right, depth + 1);

		for (int i = 0; i < depth * khoangCach; i++) {
			cout << " ";
		}

		if(root->isLeaf) cout << root->ch << " " << root->val << endl;
		else cout << root->val << endl;

		InCay(root->left, depth + 1);
	}  
	void print_tree(Node* root = nullptr){ // temp
		if(root) InCay(root);
		else InCay(this->root);
	}
	string gc(Node* node, char ch, string rs){ // get_code helper
		if(!node) return "";
		if(node->isLeaf){
			if(ch == node->ch){
				return rs;
			}
		}

		string left_search = gc(node->left, ch, rs + "0");
		if(left_search != "") return left_search;

		string right_search = gc(node->right, ch, rs + "1");
		if(right_search != "") return right_search;

		return "";
	}
	string get_code(string name){ // lay ma nhi phan cua string
		string rs = "";
		bool encode = false;
		for(int i = 0; i < int(name.length()); i++){
			rs += gc(this->root, name[i], "");
			if(encode) cout << name[i] << " " << gc(this->root, name[i], "") << endl;
		}
		if(rs == "") return "0";
		return rs;
	}
	void in_order(Node* root){ // hand
		if(!root) return;

		in_order(root->left);
		if(root->isLeaf) cout << root->ch << endl;
		else cout << root->val << endl;
		in_order(root->right);
	}
};             

class customer{
public:
	string name;
	huffman* Xtree;
	int result;
	int ID;
	customer* left;
	customer* right;
	customer(){
		left = nullptr;
		right = nullptr;
		Xtree = new huffman("");
	}
	~customer(){
		if(checkleak) cout << "Del huffman " << --leak << endl;
		delete Xtree;
	}
	customer(string n, huffman* h, string dc){
		name = n;
		Xtree = h;
		left = nullptr;
		right = nullptr;
		cout << dc << endl;

		string full_dc_name = Xtree->get_code(dc);
		string dc_name = "";
		for(int i = full_dc_name.length() - 1; i >= 0 && full_dc_name.length() - i <= 10; i--){
			dc_name += full_dc_name[i];
		}
		h->print_tree();
		result = bina_to_decimal(dc_name);
		cout << dc_name << endl;
		ID = result % ms + 1;
	}
	int bina_to_decimal(string bina){
		int n = bina.size();
		int rs = 0;
		for(int i = 0; i < n; i++){
			rs += (bina[n - i - 1] == '1'? pow(2, i): 0);
		}
		return rs;
	}
};
class areaG{
public:
	int ID;
	customer* root;
	queue<customer*> time_in;
	areaG(){
		ID = -1;
		root = nullptr;
	}
	areaG(customer* cus){
		ID = cus->ID;
		root = cus;
		time_in.push(cus);
	}
	~areaG(){
		while(!time_in.empty()){
			time_in.pop();
		}
		deletetree(this->root);
	}
	void deletetree(customer* node){
		if(!node) return;

		deletetree(node->left);
		deletetree(node->right);

		if(checkleak) cout << "Del cus: " << --leak << endl;
		delete node;
	}
	void add(customer* cus) {
        root = insertNode(root, cus);
		time_in.push(cus);
    }
    customer* insertNode(customer* root, customer* newCustomer) { // add helper
        if (!root) {
            return newCustomer;
        }
        if (newCustomer->result < root->result) {
            root->left = insertNode(root->left, newCustomer);
        }
        else if (newCustomer->result >= root->result) {
            root->right = insertNode(root->right, newCustomer);
        }

        return root;
    }
	customer* deleteNode(customer* root, int res) { // remove helper
        if (root == nullptr) {
            return root;
        }

        if (res < root->result) {
            root->left = deleteNode(root->left, res);
        }
        else if (res > root->result) {
            root->right = deleteNode(root->right, res);
        }
        else {
            if (root->left == nullptr) {
                customer* temp = root->right;
				if(checkleak) cout << "Del koku " << --leak << endl;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                customer* temp = root->left;
				if(checkleak) cout << "Del koku " << --leak << endl;
                delete root;
                return temp;
            }
            customer* temp = findMinRight(root->right);
            root->result = temp->result;
			root->ID = temp->ID;
			root->name = temp->name;

			huffman* temtree = root->Xtree;
			root->Xtree = temp->Xtree;
			temp->Xtree = temtree;

            root->right = deleteNode(root->right, temp->result);
        }
        return root;
    }
    customer* findMinRight(customer* node) { // remove helper
        customer* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    void remove(int res) {
        this->root = deleteNode(this->root, res);
    }
	void postorderTraversal(customer* root, vector<int>& result) { // kokusen helper
		if (root == nullptr) return;

		postorderTraversal(root->left, result);
		postorderTraversal(root->right, result);
		result.push_back(root->result);
	}
	
	vector<vector<long long>> table; // kokusen helper
	long long dfs(vector<int>&nums) { // kokusen helper
		long long n = nums.size();
		if (n <= 2) return 1;
		vector<int> left, right;
		for (long long i = 1; i < int(nums.size()); i++)
		{
			if (nums[i] > nums[0]) left.push_back(nums[i]);
			else right.push_back(nums[i]);
		}
		long long lans = dfs(left);
		long long rans = dfs(right);
		long long llen = left.size();
		return ((((table[n - 1][llen] * lans) % mod) * rans) % mod);
	}
    int numOfWays(vector<int>& nums) { // kokusen helper
        long long n = nums.size();
        table.resize(n + 1);
        for (long long i = 0; i <= n; i++)
        {
            table[i].resize(i + 1, 1);
            for (long long j = 1; j < i; j++)
            {
                table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % mod;
            }
        }
        return dfs(nums);
    }
	void koku(){ // kokusen
		vector<int> nums;
		postorderTraversal(this->root, nums);
		int Y = numOfWays(nums) % ms;
		for(int i = 0; i < Y && !time_in.empty(); i++){
			customer* tem = time_in.front();
			time_in.pop();
			if(inkoku) cout << "Res bị xóa: " << tem->result << endl;
			remove(tem->result);
		}
	}
};
class resG{ //Vo luong khong xu
public:
	vector<areaG*> root;
	resG(){
		root = {};
	}
	~resG(){
		if(checkleak) cout << "Del resG: " << --leak << endl;
		for(size_t i = 0; i < root.size(); i++){
			if(checkleak) cout << "Del areaG: " << --leak << endl;
			areaG* tem = root[i];
			delete tem;
		}
	}
	void add(customer* cus){
		if(root.size() == 0){
			root.push_back(new areaG(cus));
			if(checkleak) cout << "AreaG: " << ++leak << endl;
		}
		else{
			for(size_t i = 0; i < root.size(); i++){
				if(root[i]->ID == cus->ID){
					root[i]->add(cus);
					return;
				}
			}
			root.push_back(new areaG(cus));
			if(checkleak) cout << "AreaG : " << ++leak << endl;
		}
	}
	void print_tree(int num){ // limitless
		for(size_t i = 0; i < root.size(); i++){
			if(root[i]->ID == num){
				in_order(root[i]->root);
				return;
			}
		}
	}
	void in_order(customer* root){ // limitless
		if(!root) return;

		in_order(root->left);
		cout << root->result << endl;
		in_order(root->right);
	}
	void delnum0area(){
		for (auto it = root.begin(); it != root.end();) {
			if ((*it)->time_in.size() == 0) {
				delete *it;
				if(checkleak) cout << "Del areaG " << leak-- << endl;
				it = root.erase(it);
			} else {
				++it;
			}
    	}
	}
	void koku(){
		for(size_t i = 0; i < root.size(); i++){
			root[i]->koku();
			delnum0area();
		}
	}	
};

class areaS{
public:
	int ID;
    int Num;
	vector<customer*> cus_in;

    areaS(customer* cus) {
		cus_in ={cus};
		ID = cus->ID;
		Num = 1;
    }
	~areaS(){
		for(size_t i = 0; i < cus_in.size(); i++){
			customer* tem = cus_in[i];
			if(checkleak) cout << "Del cus: " << --leak << endl;
			delete tem;
		}
	}
	void add(customer* cus){
		cus_in.push_back(cus);
		Num++;
	}
	void del() {
		if (!cus_in.empty()) { 
			customer* cus = cus_in[0];
			for(size_t i = 0; i < cus_in.size() - 1; i++){
				cus_in[i] = cus_in[i + 1];
			}
			cus_in.pop_back();
			Num--;
			delete cus;
		}
	}
	void print_cus(){
		for(size_t i = 0; i < this->cus_in.size(); i++){
			cout << cus_in[i]->result << " ";
		}
		cout << endl;
	}
};
class resS{ //Phuc ma ngu chua
public:
	vector<areaS*> minHeap;
	vector<int> diary;
	//vector<areaS*> time_area;
    resS() {}
	~resS(){
		if(checkleak) cout << "Del resS: " << --leak << endl;
		for(size_t i = 0; i < minHeap.size(); i++){
			areaS* tem = minHeap[i];
			if(checkleak) cout << "Del areaS: " << --leak << endl;
			delete tem;
		}
	}

	bool sooner(areaS* a, areaS* b){ // tra ve khu vuc a lon hon b
		for(int i = diary.size() - 1; i >= 0; i--){
			if(diary[i] == a->ID) return true;
			if(diary[i] == b->ID) return false;
		}
		return false;
	}

	void reheapup(int index) {
        int parent = (index - 1) / 2;

        while (index > 0 && 
		((minHeap[index]->Num < minHeap[parent]->Num) || 
		(minHeap[index]->Num == minHeap[parent]->Num && sooner(minHeap[parent], minHeap[index])
		))) {
            swap(minHeap[index], minHeap[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }
	void reheapdown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
		int n = minHeap.size();
        int smallest = index;

        if (leftChild < n && minHeap[leftChild]->Num < minHeap[smallest]->Num) {
			smallest = leftChild;
		} 
		else if (leftChild < n && minHeap[leftChild]->Num == minHeap[smallest]->Num) {
			if (sooner(minHeap[smallest], minHeap[leftChild])) {
				smallest = leftChild;
			}
		}

		if (rightChild < n && minHeap[rightChild]->Num < minHeap[smallest]->Num) {
			smallest = rightChild;
		} 
		else if (rightChild < n && minHeap[rightChild]->Num == minHeap[smallest]->Num) {
			if (sooner(minHeap[smallest], minHeap[rightChild])) {
				smallest = rightChild;
			}
		}
        if (smallest != index) {
            swap(minHeap[index], minHeap[smallest]);
            reheapdown(smallest);
        }
    }
	void add(customer* cus) {
		diary.push_back(cus->ID);
        for (size_t i = 0; i < minHeap.size(); ++i) {
            if (minHeap[i]->ID == cus->ID) {
                minHeap[i]->add(cus);
                reheapdown(i);
                return;
            }
        }

		areaS* newArea = new areaS(cus);
		if(checkleak) cout << "AreaS: " << ++leak << endl;
		minHeap.push_back(newArea);
		diary.push_back(newArea->ID);
		reheapup(minHeap.size() - 1);
    }
	void removeEmptyAreas() {
		for (auto it = minHeap.begin(); it != minHeap.end();) {
            if ((*it)->Num == 0) {
                delete *it;
                it = minHeap.erase(it);
            } else {
                ++it;
            }
        }
		for (int i = (minHeap.size() - 1) / 2; i >= 0; --i) {
			reheapdown(i);
		}
	}
	void print_full(int index, int num){ // cleave preorder LIFO
		int si = minHeap.size();
		if (index >= si)
			return;

		int n = minHeap[index]->cus_in.size();
		for(int i = n - 1; i >= 0 && n - num <= i; i--){
        	cout << minHeap[index]->cus_in[i]->ID << "-" << minHeap[index]->cus_in[i]->result << endl;
		}

        print_full(2 * index + 1, num);
        print_full(2 * index + 2, num);
	}
	static bool incre(areaS* a, areaS* b, const vector<int>& di) { // sort helper
		if(a->Num == b->Num){
			for(int i = di.size() - 1; i >= 0; i--){
				if(di[i] == a->ID) return false;
				if(di[i] == b->ID) return true;
			}
			return false;
		}
		else return a->Num < b->Num;
	}
	void print_heap(vector<areaS*> a){ // temp
		for(size_t i = 0; i < a.size(); i++){
			cout << a[i]->ID << " ";
		}
		cout << endl;
	}
	void print_vec(vector<customer*> a){ // temp
		for(size_t i = 0; i < a.size(); i++){
			cout << a[i]->result << " ";
		}
		cout << endl;
	}
	void print_res(){ // temp
		for(size_t i = 0; i < minHeap.size(); i++){
			cout << minHeap[i]->ID << " Num: " << minHeap[i]->Num << " ";
			for(size_t k = 0; k < minHeap[i]->cus_in.size(); k++){
				cout << minHeap[i]->cus_in[k]->result << " ";
			}
			cout << endl;
		}
	}
	void delete_first_min(int num){ // keiteiken
		vector<areaS*> ar = minHeap; // sort minheap
        sort(ar.begin(), ar.end(), [this](areaS* a, areaS* b) { return incre(a, b, this->diary); });

    	for(int i = 0; i < num && i < int(minHeap.size()); i++){
			for(int k = 0; int(ar[i]->cus_in.size()) > 0 && k < num; k++){
				cout << ar[i]->cus_in[0]->result << "-" << ar[i]->ID << endl; 
				diary.push_back(ar[i]->ID);
				if(checkleak) cout << "Del keitei: " << --leak << endl;
				ar[i]->del();
			}
		}
		removeEmptyAreas();
		for(size_t k = 0; k < minHeap.size(); k++){
			reheapup(k);
		}
	}
};

bool compare(pair<char, int> &a, pair<char, int> &b){
	if(a.second != b.second){
		return a.second < b.second;
	}
	if((islower(a.first) && islower(b.first))||(isupper(a.first) && isupper(b.first))){
		return a.first < b.first;
	}
	return a.first > b.first;
}
char decode_Upper(char c, int s){
	s %= 26;
	if(c + s <= 'Z'){
		return char(c + s);
	}
	else{
		int t =  s - ('Z' - c) - 1;
		return char('A' + t);
	}
}
char decode_Lower(char c, int s){
	s %= 26;
	if(c + s <= 'z'){
		return char(c + s);
	}
	else{
		int t =  s - ('z' - c) - 1;
		return char('a' + t);
	}
}
vector<pair<char, int>> frequent(string name){
	unordered_map<char, int> rs;
	for(int i = 0; i < int(name.length()); i++){
        rs[name[i]]++;
	}
	vector<pair<char, int>> tem(rs.begin(), rs.end());
	reverse(tem.begin(), tem. end());
	return tem;
}
vector<pair<char, int>> decode_caesar(vector<pair<char, int>> freq, string &dc_name){
	vector<pair<char, int>> tem = freq;
	for(size_t i = 0; i < tem.size(); i++){
		if(isupper(tem[i].first)){
			tem[i].first = decode_Upper(tem[i].first, tem[i].second);
		} 
		else{
			tem[i].first = decode_Lower(tem[i].first, tem[i].second);
		}
	}
	unordered_map<char, char> ex;
	for(size_t i = 0; i < tem.size(); i++){
		ex[freq[i].first] = tem[i].first;
	}
	for(int i = 0; i < int(dc_name.length()); i++){
		dc_name[i] = ex[dc_name[i]];
	}
	return tem;
}
void print_vec(vector<pair<char, int>> freq){ // temp
	for(size_t i = 0; i < freq.size(); i++){
		cout << freq[i].first << " " << freq[i].second << endl;
	}
}
vector<pair<char, int>> accumulate(vector<pair<char, int>> freq){
	vector<pair<char, int>> rs;
	for(size_t i = 0; i < freq.size(); i++){
		char c = freq[i].first;
		if(c == '@') continue;
		int s = 0;
		for(size_t k = i; k < freq.size(); k++){
			if(freq[k].first == c){
				s += freq[k].second;
				freq[k].first = '@';
			}
		}
		rs.push_back({c, s});
	}
	return rs;
}

resG* rG = new resG();
resS* rS = new resS();

string last_cus = "";
customer* t = nullptr;

void lapse(string name){ // them khach vao nha hang
	//cout << "LAPSE " << name << endl;
	if(name[0] <= '9' && name[0] >= '0'){
		customer *cus = new customer();
		cus->name = "";
		cus->result = stoi(name);
		cus->ID = cus->result % ms + 1;
		last_cus = cus->name;
		
		if(cus->result % 2){
			rG->add(cus);
		}
		else{
			rS->add(cus);
		}
		return;
	}
	if(name.length() < 3) return;
	string dc_name = name;
	vector<pair<char, int>> freq = frequent(name);
	if(freq.size() < 3) return;

	freq = decode_caesar(freq, dc_name);
	freq = accumulate(freq);
	sort(freq.begin(), freq.end(), compare);
	
	huffman* hm = new huffman(dc_name);
	if(checkleak) cout << "Huffman " << ++leak << endl;
	
	if(!hm->build(freq)){
		cout << "NO";
		delete hm;
		return;
	}

	customer *cus = new customer(name, hm, dc_name);
	if(checkleak) cout << "Customer: " << ++leak << endl;

	last_cus = cus->name;
	t = cus;

	//cout << cus->name << endl << dc_name << endl;
	
	if(inres) cout << cus->result << endl;

	if(cus->ID > ms){
		delete cus;
		return;
	}
	if(cus->result % 2){
		rG->add(cus);
	}
	else{
		rS->add(cus);
	}
}
void kokusen(){ //kick G
	//cout << "KOKUSEN\n";
	rG->koku();
}
void keiteiken(int num){ //kick S
	//cout << "KEITEIKEN " << num << endl;
	rS->delete_first_min(num);
}
void hand(){ // in cay huffman ong khach gan nhat
	//cout << "HAND\n";

	//t->Xtree->print_tree();
	string name = last_cus;
	string dc_name = name;
	vector<pair<char, int>> freq = frequent(name);

	freq = decode_caesar(freq, dc_name);
	freq = accumulate(freq);
	sort(freq.begin(), freq.end(), compare);
	
	huffman* hm = new huffman(dc_name);
	if(checkleak) cout << "Huffman " << ++leak << endl;
	hm->build(freq);

	hm->in_order(hm->root);
	delete hm;
}
void limitless(int num){ // in nha G
	//cout << "LIMITLESS " << num << endl ;
	rG->print_tree(num);
}
void cleave(int num){ // in nha S
	//cout << "CLEAVE " << num << endl;
	rS->print_full(0, num);
}

void simulate(string filename)
{
	ifstream ifs(filename);
	string tem = "";
	string name = "";

	while (ifs >> tem){
		if(tem == "LAPSE"){ // them khach
			ifs >> name;
			lapse(name);
		}
		else if(tem == "KOKUSEN"){ // xoa G
			kokusen();
		}
		else if(tem == "KEITEIKEN"){ // xoa S
			ifs >> name;
			keiteiken(stoi(name));
		}
		else if(tem == "HAND"){ // in cay huffman khach gan nhat
			hand();
		}
		else if(tem == "LIMITLESS"){ // in inorder G tai khu vuc num
			ifs >> name;
			limitless(stoi(name));
		}
		else if(tem == "CLEAVE"){ // in preorder S theo LIFO
			ifs >> name;
			cleave(stoi(name));
		}
		else if(tem == "MAXSIZE"){ // cap nhat maxsize
			ifs >> name;
			ms = stoi(name);
		}
		else if(tem == "E") {
			cout << "End\n";
			break;
		}
	}
	// giai phong bo nho
	delete rG;
	delete rS;
	if(checkleak) cout << leak << endl;
	return;
}
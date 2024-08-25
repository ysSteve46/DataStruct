#include <iostream>
#include <algorithm>

using namespace std;
class Polynomial; //forward declaration
template <class T> class circularList;

//Circular list w/Header
template <class T>
class chainNode {
	friend class circularList<T>;
private:
	T data;
	chainNode<T>* link;
public:
	chainNode() { link = nullptr; }
	chainNode(const T& d) { data = d; link = nullptr; }
	chainNode(const T& d, chainNode<T>* next) { data = d; link = next; }
};

template <class T>
class circularList {
public:
	circularList() { //constructor
		head = new chainNode<T>();
		head->link = head;
		last = head;
		av = new chainNode<T>();
	}
	~circularList();
	//forward iterator
	class chainIterator {
	public:
		//typedefs
		//constructor
		chainIterator(chainNode<T>* startNode = 0) {
			current = startNode;
		}
		//dereferencing operators * and ->
		T& operator *() const { return current->data; }
		T* operator ->() const { return &current->data; }

		//increment
		chainIterator& operator ++() {//preincrement
			current = current->link; return *this;
		}
		chainIterator operator ++(int) {//postincrement
			chainIterator old = *this;
			current = current->link;
			return old;
		}
		
		//equality testing
		bool operator!=(const chainIterator right)const {
			return current != right.current;
		}
		bool operator==(const chainIterator right)const {
			return current == right.current;
		}
	private:
		chainNode<T>* current;
	};
	chainIterator header() const { return chainIterator(head); }
	chainIterator begin() const { return chainIterator(head->link); }
	chainIterator end() const { return chainIterator(last); }
	//chain manipulation
	void insertBack(const T& e);
	void insertFront(const T& e);
	//void reverse();
private:
	chainNode<T>* head; //header node
	//chainNode<T>* first;
	chainNode<T>* last;
	chainNode<T>* av;
};

template <class T>
circularList<T>::~circularList() {
	if (last) {
		chainNode<T>* f = last->link;
		last->link = av;
		av = f;
		last = head;
	}
}

template <class T>
void circularList<T>::insertBack(const T& e) {
	//inserting at back
	chainNode<T>* newNode = new chainNode<T>(e);
	newNode->link = head;
	last->link = newNode;
	last = newNode;
}

template<class T>
void circularList<T>::insertFront(const T& e) {
	//insert element at the 'front' of the circular list
	//*this, where last points to the last node in the list
	chainNode<T>* newNode = new chainNode<T>(e);
	if (last) { //non empty list
		newNode->link = last->link;
		last->link = newNode;
	}
	else { //empty list
		last = newNode;
		newNode->link = newNode;
	}
}

/*
template <class T>
void circularList<T>::reverse() {
	chainNode<T>* current = head->link,
		* previous = 0; //trails current
	while (current) {
		chainNode<T>* r = previous;
		previous = current;
		current = current->link;
		previous->link = r;
	}
	head->link = previous;
}
*/

//Polynomial
struct term {
	float coef = 0;
	int exp = 0;
	term set(float c, int e) { coef = c; exp = e; return *this; };
};

class Polynomial {
public:
	Polynomial();
	Polynomial(const Polynomial& a); //copy constructor
	~Polynomial();
	friend istream& operator>>(istream& in, Polynomial& x);
	friend ostream& operator<<(ostream& out, Polynomial& x);
	const Polynomial& operator=(const Polynomial& a);
	Polynomial operator+(const Polynomial& b) const;
	Polynomial operator-(const Polynomial& b) const;
	Polynomial operator*(const Polynomial& b) const;
	float Eval(float x) const;
private:
	circularList<term> poly;
};

Polynomial::Polynomial() {
	poly.header()->exp = -1;
}

Polynomial::Polynomial(const Polynomial& a) {
	poly.header()->exp = -1;
	term temp;
	circularList<term>::chainIterator ai = a.poly.begin();
	while (ai->exp!=-1) {
		poly.insertBack(temp.set(ai->coef, ai->exp));
		ai++;
	}
}

Polynomial::~Polynomial() {
	//Destructor. Return all nodes of Polynomial *this and return
	//to the available space list
	poly.~circularList();
}

istream& operator>>(istream& in, Polynomial& x){
	//Read in an input polynomial and convert it to circular list
	term t;
	in >> t.coef >> t.exp;
	x.poly.insertBack(t);
	return in;
}

ostream& operator<<(ostream& out, Polynomial& x) {
	//Convert x from its linked list representation to its
	//external expression and output it
	circularList<term>::chainIterator a = x.poly.begin();
	while (1) {
		if (a->exp == -1) { return out; }
		if (a->exp > 1 || a->exp < 0) {
			out << a->coef << "x^" << a->exp;
		}
		else if(a->exp == 1) {
			out << a->coef << "x";
		}
		else {
			out << a->coef;
		}
		a++;
		if (a->coef > 0 && a->exp != -1) {
			//output "+" if the term after first one is > 0
			out << "+";
		}
	}
}

const Polynomial& Polynomial::operator=(const Polynomial& a) {
	//assign polynomial a to *this
	if (poly.end()!=nullptr) {
		this->Polynomial::~Polynomial();
	}
	term temp;
	circularList<term>::chainIterator ai = a.poly.begin();
	while (1) {
		if (ai->exp == -1) return *this;
		poly.insertBack(temp.set(ai->coef, ai->exp));
		ai++;
	}
}

Polynomial Polynomial::operator+(const Polynomial& b) const {
	//add *this (a) and b and the sum returned
	term temp;
	circularList<term>::chainIterator ai = poly.begin(),
		bi = b.poly.begin();
	Polynomial c;
	while (1) {
		if (ai->exp == bi->exp) {
			if (ai->exp == -1) return c;
			float sum = ai->coef + bi->coef;
			if (sum) c.poly.insertBack(temp.set(sum, ai->exp));
			ai++; bi++; //advance to next erm
		}
		else if (ai->exp < bi->exp) {
			c.poly.insertBack(temp.set(bi->coef, bi->exp));
			bi++; //next term of b
		}
		else {
			c.poly.insertBack(temp.set(ai->coef, ai->exp));
			ai++; //next term of a
		}
	}
}

Polynomial Polynomial::operator-(const Polynomial& b) const{
	//subtract *this (a) and b and the sum returned
	term temp;
	circularList<term>::chainIterator ai = poly.begin(),
		bi = b.poly.begin();
	Polynomial c;
	while (1) {
		if (ai->exp == bi->exp) {
			if (ai->exp == -1) return c;
			float sum = ai->coef - bi->coef;
			if (sum!=0) c.poly.insertBack(temp.set(sum, ai->exp));
			ai++; bi++; //advance to next erm
		}
		else if (ai->exp < bi->exp) {
			//0 - bi->coef
			c.poly.insertBack(temp.set(bi->coef*-1, bi->exp));
			bi++; //next term of b
		}
		else {
			c.poly.insertBack(temp.set(ai->coef, ai->exp));
			ai++; //next term of a
		}
	}
}

Polynomial Polynomial::operator*(const Polynomial& b) const {
	//multiply *this (a) and b
	term temp;
	circularList<term>::chainIterator ai = poly.begin(),
		bi = b.poly.begin(), ci;
	Polynomial c;
	while (1) {
		if (ai->exp == -1) return c;
		while (bi->exp != -1) {
			bool added = false; //check if the term for c is added
			float theCoeff = ai->coef * bi->coef;
			int theExp = ai->exp + bi->exp;
			if (theExp) {
				//Run down the existing nodes of C to check if there 
				//is an element that has the same exponent as theCoeff
				ci = c.poly.begin();
				while (ci->exp != -1) {
					if (ci->exp == theExp) {
						ci->coef += theCoeff;
						added = true;
					}
					ci++;
				}
				//Insert the term if the current term isn't added
				if (added == false) 
					c.poly.insertBack(temp.set(theCoeff, theExp));
			}
			else {
				c.poly.insertBack(temp.set(theCoeff, 0));
			}
			bi++;
		}
		bi = b.poly.begin();
		ai++;
	}
}

float Polynomial::Eval(float x) const {
	circularList<term>::chainIterator e = poly.begin();
	float sum = 0;
	while (e->exp!=-1) {
		sum += e->coef * (float)pow(x, e->exp);
		e++;
	}
	return sum;
}

int main() {
	Polynomial A;
	Polynomial B;
	int m, n;
	cout << "Enter terms of A, B: ";
	cin >> m >> n;
	cout << "Enter coefficients, exponents of A:\n";
	for (int i = 0; i < m; i++) {
		cin >> A;
	}
	cout << "Enter coefficients, exponents of B:\n";
	for (int j = 0; j < n; j++) {
		cin >> B;
	}
	//Output A and B
	cout << "A = " << A << '\n';
	cout << "B = " << B << '\n';
	//Addition
	Polynomial C  = A + B;
	cout << "C = A + B = " << C << '\n';
	//Subtraction
	Polynomial D = A - B;
	cout << "D = A - B = " << D << '\n';
	//Multiplication
	Polynomial E = C; //Assign polynomial C to E
	E = E * B;
	cout << "E = C * B = " << E << '\n';
	//Evaluate the polynomial C = A+B with user input
	float ex;
	cout << "Input a number to evaluate C: ";
	cin >> ex;
	cout << "The result after evaluating C = " << C.Eval(ex) << '\n';

	system("pause");
	return 0;
}
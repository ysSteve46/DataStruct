#include <iostream>
#include <algorithm>

using namespace std;

class polynomial; //forward decleartion

class Term{
	friend polynomial;
private:
	float coef;
	int exp;
public:
	Term(float co = 0, int ex = 0):exp(ex), coef(co){}
};

class polynomial {
private:
	Term* termArray;
	int capacity;
	int terms;
public:
	polynomial():termArray(new Term[2]),capacity(2),terms(0) {}
	//forward decleartions
	polynomial Add(polynomial b);
	polynomial Mult(polynomial b);
	float Eval(float f);
	void NewTerm(const float theCoeff, const int theExp);
	void display();
};

polynomial polynomial::Add(polynomial b) {
	polynomial c;
	int aPos = 0, bPos = 0;
	while((aPos<terms)&&(bPos<b.terms))
		if(termArray[aPos].exp==b.termArray[bPos].exp){
			float t = termArray[aPos].coef + b.termArray[bPos].coef;
			if (t)c.NewTerm(t, termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if (termArray[aPos].exp < b.termArray[bPos].exp) {
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else {
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	for (; aPos < terms; aPos++)
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos < b.terms; bPos++)
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	return c;
}

polynomial polynomial::Mult(polynomial b) {
	polynomial c;
	float* prods = new float[terms + b.terms + 1];
	fill(prods, prods + terms + b.terms + 1, 0); //initialize
	for (int i = 0; i < terms; i++) {
		for (int j = 0; j < b.terms; j++) {
			//Multiply the term of polynomial A to
			//every term of polynomial B
			float t = termArray[i].coef * b.termArray[j].coef;
			int e = termArray[i].exp + b.termArray[j].exp;
			prods[e] += t;
		}
	}
	//Add terms to polynomial c if the element of prods array is > 0
	for (int k = (terms + b.terms); k >= 0; k--) {
		if (prods[k] != 0)
			c.NewTerm(prods[k], k);
	}
	return c;
}

float polynomial::Eval(float f) {
	float result = 0;
	for (int i = 0; i < terms; i++) {
		result += termArray[i].coef * pow(f, termArray[i].exp);
	}
	return result;
}

void polynomial::NewTerm(const float theCoeff, const int theExp) {
	if (terms == capacity) {
		capacity *= 2;
		Term* temp = new Term[capacity];
		copy(termArray, termArray + terms, temp);
		delete[] termArray;
		termArray = temp;
	}
	termArray[terms].coef = theCoeff;
	termArray[terms++].exp = theExp;
}

void polynomial::display() {
	int i;
	for (i = 0; i < terms; i++) {
		if (termArray[i].exp > 1) {
			cout << termArray[i].coef << "x^" << termArray[i].exp;
		}
		else if (termArray[i].exp == 1) {
			cout << termArray[i].coef << "x";
		}
		else {
			cout << termArray[i].coef;
		}
		if(i<terms-1){ cout << "+"; }
	}
	cout << '\n';
}

int main() {
	int numTerms;
	polynomial a, b;
	cout << "Enter terms of A(x): \n";
	cin >> numTerms;
	cout << "Enter polynomial A coefficients, exponents:\n";
	for(int i = 0; i < numTerms; i++){
		float coA;
		int exA;
		cin >> coA >> exA;
		a.NewTerm(coA, exA);
	}
	cout << "Enter terms of B(x): \n";
	cin >> numTerms;
	cout << "Enter polynomial B coefficients, exponents:\n";
	for (int i = 0; i < numTerms; i++) {
		float coB;
		int exB;
		cin >> coB >> exB;
		b.NewTerm(coB, exB);
	}
	polynomial C;
	C = a.Add(b); //Add
	//C = a.Mult(b); //Mult
	cout << "C(x) = A(x) + B(x) = ";
	//cout << "C(x) = A(x) * B(x) = ";
	C.display();
	//cout << C.Eval(2) << '\n'; //Eval

	system("pause");
	return 0;
}
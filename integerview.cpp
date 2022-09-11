#include <iostream>
using namespace std;

class IntegerViewImplementation {
public:
	virtual void view() = 0;
	virtual void binView() = 0;
	virtual ~IntegerViewImplementation() = default;
};

class ConcreteIntegerView: public IntegerViewImplementation {
	int i;
	void binPrint(int t) {
		if (!t)
			return;
		binPrint(t >> 1);
		if (t & 1)
			cout << '1';
		else
			cout << '0';
	}
public:
	ConcreteIntegerView(int i) :
			i { i } {

	}
	void view() override {
		cout << i << endl;
	}
	void binView() override {
		this->binPrint(this->i);
		cout << endl;
	}
};

class IntegerViewAbstraction {
protected:
	IntegerViewImplementation *implementation;
public:
	IntegerViewAbstraction(IntegerViewImplementation *_implementation) :
			implementation(_implementation) {

	}
	virtual void view() const {
		this->implementation->view();
	}
	virtual ~IntegerViewAbstraction() {
	}
};

class IntegerViewAbstractionBinary: public IntegerViewAbstraction {
public:
	IntegerViewAbstractionBinary(IntegerViewImplementation *_implementation) :
			IntegerViewAbstraction(_implementation) {

	}
	void view() const override {
		this->implementation->binView();
	}
};

int main() {
	int i { };
	cout << "Enter an integer" << endl;
	cin >> i;
	IntegerViewImplementation *imp = new ConcreteIntegerView(i);
	IntegerViewAbstraction *dec = new IntegerViewAbstraction(imp);
	IntegerViewAbstraction *bin = new IntegerViewAbstractionBinary(imp);
	cout << "Decimal integer: ";
	dec->view();
	cout << endl;
	cout << "Binary integer: ";
	bin->view();
	cout << endl;
	return 0;
}

///Demos use of lambda functions in C++
#include <iostream>
#include <list>
#include <vector>
#include <functional>
#include <regex>

using namespace std;
void demoLambdaFunctions();
void demoLambdaFunctionAsParameterToAFunction1();
void demoLambdaFunctionAsParameterToAFunction2();

class Vehicle {
private:
	string make, model;
	double price;
public:
	Vehicle(string make, string model, double price) : make(make), model(model), price(price) {};
	double getPrice() const { return this->price; };
	string getModel() const { return this->model; };
	friend ostream& operator<<(ostream& os, const Vehicle& v) {
		os << v.make << "," << v.model << "," << v.price;
		return os;
	}
};

Vehicle* getBestForCustomer(Vehicle* pA, Vehicle* pB) {

	bool bModelMatchA = std::regex_match(pA->getModel(), std::regex("s[0-9]"));
	bool bModelMatchB = std::regex_match(pB->getModel(), std::regex("s[0-9]"));

	if (bModelMatchA && bModelMatchB){
		return pA->getPrice() < pB->getPrice() ? pA : pB;
	}
	else if (!bModelMatchA && !bModelMatchB) {
		return nullptr;
	}
	else {
		if (bModelMatchA)
			return pA;
		else
			return pB;
	}
}

int main()
{

	//cout << endl << "****************** demoLambdaFunctions ******************" << endl;
	//demoLambdaFunctions();

	//cout << endl << "****************** demoLambdaFunctionAsParameterToAFunction1 ******************" << endl;
	//demoLambdaFunctionAsParameterToAFunction1();

	//cout << endl << "****************** demoLambdaFunctionAsParameterToAFunction2 ******************" << endl;
	//demoLambdaFunctionAsParameterToAFunction2();
}

int add(int x, int y) {
	return x + y;
}
int max(int x, int y) {
	return x > y ? x : y; //ternary operator (3 operands)
}
bool isInRange(int x) {
	return x > 0 && x < 100 ? true : false;
}

/// @brief Function to accept a list of integers and a predicate and return the first value which matches the predicate
/// @param list A list of integers
/// @param predicate A predicate which accepts an integer and returns true or false if the integer matches the predicate logic
/// @return First integer matching the predicate
int findFirstBy(list<int> list, std::function<bool(int)> predicate) {
	for (int n : list) {
		if (predicate(n))
			return n;
	}

	return -1;
}

/// @brief Demos how to define a lambda function
void demoLambdaFunctions()
{
	//what is a lambda function? Function that we can write "in-place" in the code
	//auto func = [/*empty*/](/*params*/) { /*code*/};

	/// @brief A simple lambda
	auto maxFunc = [/*empty*/](int x, int y) { return x > y ? x : y; };
	cout << maxFunc(374, 89) << endl;

	int lo = 0, hi = 500;
	/// @brief A lambda function which accept input parameters (lo, hi) to use in the threshold
	auto inRangeFunc = [lo, hi](int value) { return value > lo && value < hi ? true : false; };
	cout << inRangeFunc(89) << endl;
	cout << inRangeFunc(374) << endl;

	string strPrompt = "Age:";
	auto print = [strPrompt](int x) { cout << strPrompt << x << endl; };
	print(43);

}

void demoLambdaFunctionAsParameterToAFunction1()
{
	list<int> nums = { 17, 3, 8, 21, 89, -23, 56 };
	int multipleOf = 3;
	int min = 10, max = 100;

	/// @brief A lambda function which accept input parameters (multipleOf, min, max) to match a number which is a multiple of 3 and between 10 and 100
	auto func = [multipleOf, min, max](int n) { return (n % multipleOf == 0 && n >= min && n <= max); };

	int number = findFirstBy(nums, func);
	cout << "The first number to satisfy the lambda function in the list is " << number << endl;

}

void demoLambdaFunctionAsParameterToAFunction2() {
	vector<Vehicle*> vehicleVec;
	vehicleVec.emplace_back(new Vehicle("tesla", "x1", 10000));
	vehicleVec.emplace_back(new Vehicle("tesla", "v3", 65000));
	vehicleVec.emplace_back(new Vehicle("tesla", "x5", 80000));

	auto print = [](Vehicle* v) {
		if (v != nullptr)
			cout << *v << endl;
		else
			cout << "No valid object to print!" << endl;
	};

	Vehicle* pBest = getBestForCustomer(vehicleVec.at(0), (vehicleVec.at(1)));
	print(pBest);
}

///Demos use of lambda functions in C++
#include <iostream>
#include <list>
#include <vector>
#include <functional>
#include <regex>

using namespace std;
void demoLambdaFunctions();
void demoLambdaFunctionAsParameterToAFunction();

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

	bool bMatchA = std::regex_match(pA->getModel(), std::regex("s[0-9]"));

	if (bMatchA && std::regex_match(pB->getModel(), std::regex("s[0-9]"))){
		return pA->getPrice() < pB->getPrice() ? pA : pB;
	}
	else if (!bMatchA && !std::regex_match(pB->getModel(), std::regex("s[0-9]"))) {
		return nullptr;
	}
	//else {
		//mix ("s1", "x5")
		return pA; //to do...
	//}
}

int main()
{
	vector<Vehicle*> vehicleVec;
	vehicleVec.emplace_back(new Vehicle("tesla", "x1", 10000));
	vehicleVec.emplace_back(new Vehicle("tesla", "x3", 65000));
	vehicleVec.emplace_back(new Vehicle("tesla", "x5", 80000));
	auto print = [](Vehicle* v) { 
		if(v != nullptr)
			cout << *v << endl; 
	};
	//print(vehicleVec.at(0));

	Vehicle *pBest = getBestForCustomer(vehicleVec.at(0), (vehicleVec.at(1)));
	print(pBest);







	//cout << endl << "****************** demoLambdaFunctions ******************" << endl;
	//demoLambdaFunctions();

	//cout << endl << "****************** demoLambdaFunctionAsParameterToAFunction ******************" << endl;
	//demoLambdaFunctionAsParameterToAFunction();
}

int add(int x, int y) {
	return x + y;
}
int max(int x, int y) {
	return x > y ? x : y; //ternary operator (3 operands)
}

const int maxRange = 100;

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

void demoLambdaFunctionAsParameterToAFunction()
{
	list<int> nums = { 17, 3, 8, 21, 89, -23, 56 };
	int multipleOf = 3;
	int min = 10, max = 100;

	/// @brief A lambda function which accept input parameters (multipleOf, min, max) to match a number which is a multiple of 3 and between 10 and 100
	auto func = [multipleOf, min, max](int n) { return (n % multipleOf == 0 && n >= min && n <= max); };

	int number = findFirstBy(nums, func);
	cout << "The first number to satisfy the lambda function in the list is " << number << endl;

}

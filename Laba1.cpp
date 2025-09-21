
#include <iostream>
#include <limits>
using namespace std;

int main()
{
	short h, osn1, osn2; // потому что нужен тип данных для числа с самым узким диапазоном значений 
	cin >> h;
	cin >> osn1;
	cin >> osn2;
	float s; // потому что площадь может получиться дробной
	s = (osn1 + osn2) * h / 2.0; // делим на 2.0 чтобы значение не округлялось
	cout << "Ploshad " << s << endl;

	cout << "short" << endl;
	short maxshort = numeric_limits<short>::max();
	cout << "max short " << maxshort << endl;
	short minshort = numeric_limits<short>::min();
	cout << "min short " << minshort << endl;
	short bitsshort = sizeof(short) * 8;
	cout << "bits in short " << bitsshort << endl;

	cout << "float" << endl;
	float maxfloat = numeric_limits<float>::max();
	cout << "max float " << maxfloat << endl;
	float minfloat = numeric_limits<float>::min();
	cout << "min float " << minfloat << endl;
	short bitsfloat = sizeof(float) * 8;
	cout << "bits in float " << bitsfloat << endl;


	
	return 0;
}

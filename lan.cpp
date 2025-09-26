#include <iostream>
#include <limits>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	short h, osn1, osn2; // потому что нужен тип данных для числа с самым узким диапазоном значений 
	cout << "Высота" << endl;
	cin >> h;
	cout << "Первое основание" << endl;
	cin >> osn1;
	cout << "Второе основание" << endl;
	cin >> osn2;
	float s; // потому что площадь может получиться дробной
	s = (osn1 + osn2) * h / 2.0; // делим на 2.0 чтобы значение не округлялось
	cout << "Площадь трапеции = " << s << endl;

	cout << "short" << endl;
	short maxshort = numeric_limits<short>::max();
	cout << "max short " << maxshort << endl;
	short minshort = numeric_limits<short>::lowest();
	cout << "min short " << minshort << endl;
	short bitsshort = sizeof(short) * 8;
	cout << "bits in short " << bitsshort << endl;

	cout << "float" << endl;
	float maxfloat = numeric_limits<float>::max();
	cout << "max float " << maxfloat << endl;
	float minfloat = numeric_limits<float>::lowest();
	cout << "min float " << minfloat << endl;
	short bitsfloat = sizeof(float) * 8;
	cout << "bits in float " << bitsfloat << endl;



	return 0;
}
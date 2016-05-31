#include <iostream>
#include <bitset>

using namespace std;

struct registers {
	struct {
		union {
			struct {
				unsigned char f;
				unsigned char a;
			};
			unsigned short af;
		};
	};

	struct {
		union {
			struct {
				unsigned char c;
				unsigned char b;
			};
			unsigned short bc;
		};
	};

	struct {
		union {
			struct {
				unsigned char e;
				unsigned char d;
			};
			unsigned short de;
		};
	};

	struct {
		union {
			struct {
				unsigned char l;
				unsigned char h;
			};
			unsigned short hl;
		};
	};

	unsigned short sp;
	unsigned short pc;
};


int main() {
	registers a;

	a.a = 211;
	cout << a.a << endl;
	bitset<8> x(a.a);
	cout << x << endl << endl;

	a.f = 111;
	bitset<8> y(a.f);
	cout << a.f << endl;
	cout << y << endl << endl;

	bitset<16> z(a.af);
	cout << a.af << endl;
	cout << z;
	return 0;
}


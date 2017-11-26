#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <cmath>

typedef unsigned long long LL;
using namespace std;

bool Miller_Rabin(LL n);

int main()
{
  int t;
  LL p;
  cin >> t;
  while (t--) {
	cin >> p;
	if (Miller_Rabin(p))
		cout << "Yes\n";
	else
		cout << "No\n";
  }
  return 0;
}

static LL modular_multi(LL x, LL y, LL mo)
{
	LL t;
	x %= mo;
	for (t = 0; y; x = (x << 1)%mo, y>>=1)
		if (y&1)
			t = (t+x)%mo;
	return t;
}

static LL modular_exp(LL num, LL t, LL mo)
{
	LL ret = 1, temp = num % mo;
	for (;t;t>>=1, temp = modular_multi(temp, temp, mo))
		if (t&1)
			ret = modular_multi(ret, temp, mo);
	return ret;
}

bool Miller_Rabin(LL n)
{
	int i, s;
	LL a, u, x, y, z;
	s = 10;
	if (n <= 2)
		if (n == 2)
			return true;
		else
			return false;

	if (n == 3)
		return true;

	if (n % 2 == 0)
		return false;

	u = n - 1;
	while (u % 2 == 0)
		u = u / 2;
	srand(time(0));
	for (i = 0; i < s; i++) {
		z = u;
		a = (rand() % (n - 3)) + 2;
		x = modular_exp(a, z, n);
		while (z < n) {
			y = modular_multi(x, x, n);
			if (y == 1 && x != 1 && x != n - 1)
				return false;

			x = y;
			z = z * 2;
		}

		if (x != 1)
			return false;
	}

	return true;
}

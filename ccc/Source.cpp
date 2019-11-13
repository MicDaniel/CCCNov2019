#include<iostream>
#include<fstream>
#include<math.h>
#include<cmath>

using namespace std;

ifstream in("level3_4.in");
ofstream out("level3_4.out");

int mat[1000][1000];
int country[1000][1000];
int w[1000][1000];

int getMax(int n, int m) {
	int max = INT_MIN;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mat[i][j] > max) {
				max = mat[i][j];
			}
		}
	}

	return max;
}
int getMin(int n, int m) {
	int min = INT_MAX;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (w[i][j] < min) {
				min = w[i][j];
			}
		}
	}
	return min;
}

long long getAverage(int n, int m) {
	double mean = 0;
	long long sum = 0;
	int counter = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			sum += mat[i][j];
			counter++;
		}
	}

	mean = sum / counter;
	return floor(mean);
}

bool checkBorder(int n, int m, int i, int j) {
	if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
		return true;
	}

	
	if (i - 1 >= 0) {
		if (country[i][j] != country[i - 1][j]) {
			return true;
		}
	}
	if (j+1<m) {
		if (country[i][j] != country[i][j + 1]) {
			return true;
		}
	}
	if (i + 1 < n) {
		if (country[i][j] != country[i + 1][j]) {
			return true;
		}
	}
	if (j - 1 >= 0) {
		if (country[i][j] != country[i][j - 1]) {
			return true;
		}
	}
	return false;
}

int eucl(int i1, int i2, int j1, int j2) {
	return floor(sqrt((i1 - i2) * (i1 - i2) + (j1 - j2) * (j1 - j2)));
}

void calcualteEuc(int n, int m, int ci, int cj) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i == ci && j == cj)
				w[i][j] = INT_MAX;
			else
				w[i][j] = eucl(ci, i, cj, j);
		}
	}
}

void centerOfMass(int tara, int n, int m, int &centerOfMassI, int &centerOfMassJ) {

	int sumI = 0;
	int sumJ = 0;
	int counter = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (country[i][j] == tara) {
				sumI += i;
				sumJ += j;
				counter++;
			}
		}
	}
	centerOfMassI =floor(sumI / counter);
	centerOfMassJ = floor(sumJ / counter);
}

int countIMin(int n, int m, int min) {
	int iMin = INT_MAX;
	int counter = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (w[i][j] == min) {
				if (i < iMin) {
					iMin = i;
					counter = 0;
				}
				else if (i == iMin) {
					counter++;
				}
			}
		}
	}
	return counter;
}

int iMin(int n, int m, int min) {
	int iMin = INT_MAX;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (w[i][j] == min) {
				if (i < iMin) {
					iMin = i;
				}
			}
		}
	}
	return iMin;
}

int jMin(int n, int m, int min, int ci) {
	int jMin = INT_MAX;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (w[i][j] = min && i == ci) {
				if (j < jMin) {
					jMin = j;
				}
			}
		}
	}

	return jMin;
}

void change(int n, int m, int minimum) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (w[i][j] == minimum) {
				w[i][j] = INT_MAX;
			}
		}
	}
}

void changeI(int n, int m, int minimum, int imin) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (w[i][j] == minimum && imin == i) {
				w[i][j] = INT_MAX;
			}
		}
	}
}

int frecventaTari[1000];
int matrice[1000][1000];
int main() {

	int n, m;
	int counterTari = 0;
	int centerOfMassI = 0;
	int centerOfMassJ = 0;

	in >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			in >> mat[i][j];
			in >> country[i][j];
			if (country[i][j] > counterTari)
				counterTari = country[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (checkBorder(n, m, i, j) == true) {
				frecventaTari[country[i][j]]++;
				matrice[i][j] = 1;
			}
		}
	}

	int tara = 0;
	while (tara <= counterTari) {
		centerOfMass(tara, n, m, centerOfMassI, centerOfMassJ);
		if (country[centerOfMassI][centerOfMassJ] == tara
			&& checkBorder(n,m,centerOfMassI,centerOfMassJ)==false) {
			out << centerOfMassJ << ' ' << centerOfMassI<<'\n';
		}
		else {
			bool ok = true;
			calcualteEuc(n, m, centerOfMassI, centerOfMassJ);
			while (ok) {
				int min = getMin(n, m);
				int imin = iMin(n, m, min);
				for (int k = 0; k < m; k++) {
					if (checkBorder(n, m, imin, k) == false) {
						if (w[imin][k] == min) {
							out << k << ' ' << imin << '\n';
							ok = false;
							break;
						}
					}
				}
				changeI(n, m, min, imin);
			}
		}
		tara++;
	}
	return 0;
}
// BIO_Lab3_2.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool InitWorld(int *mas, int tap, int m)
{
	int j = m - 1;
	while (j >= 0 && mas[j] == tap) j--;
	if (j < 0) return false;
	if (mas[j] >= tap)
		j--;
	mas[j]++;
	if (j == m - 1) return true;
	for (int k = j + 1; k < m; k++)
		mas[k] = 1;
	return true;
}

int Sravn(string text, string pat)
{
	int count = 0;
	for (int i = 0;i < pat.length();i++)
	{
		if (text.substr(i, 1) != pat.substr(i, 1)) count++;
	}
	return count;
}

int TotalDistance(string str, string motiv)
{
	int min = INT_MAX;
	for (int i = 0; i < str.size() - motiv.size() + 1; i++)
	{
		int count = Sravn(str.substr(i, motiv.size()), motiv);
		if (count < min)
		{
			min = count;
		}
	}
	return min;
}

int TotalDistance(string* DNA, string motiv, int t)
{
	int min = INT_MAX;
	int sum = 0;
	for (int i = 0; i < t;i++)
	{
		int tmp = TotalDistance(DNA[i], motiv);
		sum = sum + tmp;
	}
	return sum;
}

int NextVertex(int* s, int i, int L, int k)
{
	if (i < L)
	{
		s[i + 1] = 1;
		return i + 1;
	}
	else
	{
		for (int j = L - 1; j >= 0; j--)
		{
			if (s[j] < k)
			{
				s[j] = s[j] + 1;
				return j;
			}
		}
	}
	return -1;
}

int ByPass(int* s, int i, int L, int k)
{
	for (int j = i - 1; j >= 0; j--)
	{
		if (s[j] < k)
		{
			s[j] = s[j] + 1;
			return j;
		}
	}
	return -1;
}

string BranchAndMedianSearch(string* DNA, int t, int l, int* s)
{
	char *symbol = new char[4];
	symbol[0] = 'A';
	symbol[1] = 'C';
	symbol[2] = 'G';
	symbol[3] = 'T';
	int bestDistance = INT_MAX;
	int optimisticDistance = 0;
	string prefix;
	string word;
	string bestW;
	int i = 0;
	while (i > -1)
	{
		if (i < l)
		{
			prefix.clear();
			for (int j = 0; j < i;j++)
			{
				prefix = prefix + symbol[s[j] - 1];
			}
			optimisticDistance = TotalDistance(DNA, prefix, t);
			if (optimisticDistance > bestDistance)
			{
				i = ByPass(s, i, l, 4);
			}
			else
			{
				i = NextVertex(s, i, l, 4);
			}
		}
		else
		{
			word.clear();
			for (int j = 0; j < l;j++)
			{
				word = word + symbol[s[j] - 1];
			}
			if (TotalDistance(DNA, word, t) < bestDistance)
			{
				bestDistance = TotalDistance(DNA, word, t);
				bestW = word;
			}
			i = NextVertex(s, i, l, 4);
		}
	}
	delete[] symbol;
	return bestW;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	ifstream fin("input.txt");
	ifstream fin2("input.txt");
	ofstream fout("output.txt");
	if (!fin.is_open()) // если файл не открыт
		cout << "Файл не может быть открыт!\n"; // сообщить об этом
	else
	{
		string lc;
		string temp;
		int t = 0;
		while (fin)
		{
			getline(fin, temp);
			t++;
		}
		t = t - 2;
		fin.close();

		getline(fin2, lc, '\n');
		int l = atoi(lc.c_str());	// размер шаблона
		cout << "Размер шаблона = " << l << endl;
		cout << "Число строк    = " << t << endl;
		string* DNA = new string[t];
		for (int i = 0; i < t; i++)
		{
			getline(fin2, DNA[i]);
			cout << DNA[i] << endl;
		}
		int *num = new int[l];
		for (int i = 0;i < l;i++)
		{
			num[i] = 1;
		}
		string bestW = BranchAndMedianSearch(DNA, t, l, num);
		cout << "Лучшее слово: " << bestW << endl;
		fout << bestW << endl;
		delete[] DNA;
	}
	fout.close();
	return 0;
}


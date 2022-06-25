#pragma once
#include"pole.h"
#include<queue>
#include<iostream>
#include<vector>
class algorytm
{
public:
	int m;
	int n;
	int odlegloscMinimalna(std::vector<std::vector<int>> plansza);
	void rec(std::vector<std::vector<int>>& plansza, int optymalneKroki);
};


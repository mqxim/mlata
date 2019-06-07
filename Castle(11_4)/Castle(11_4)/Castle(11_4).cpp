#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>
#include <cmath>

// Ильин М., ПС-21

//11.4.Стена(6)

//Жил - был жадный Король.Он приказал своему главному Архитектору построить стену вокруг
//его замка.Король был таким жадным, что не послушал предложение Архитектора построить
//красивую кирпичную стену совершенной формы с изящными высокими башнями.Вместо этого
//он приказал построить стену вокруг всего замка, используя минимальное количество камня, но
//потребовал, чтобы стена не подходила к замку ближе некоторого расстояния.Если Король узнает,
//что Архитектор использовал больше ресурсов для постройки стены, чем было абсолютно
//необходимо для удовлетворения требований, Архитектор лишится головы.Более того, Архитектор
//должен представить проект стены, где указано точное количество ресурсов.

//Ваша задача - помочь Архитектору сохранить голову, написав программу, определяющую
//минимальную длину стены, которую можно построить вокруг замка, удовлетворив требования
//Короля.
//Задача слегка упрощается тем, что замок Короля представляет собой многоугольник и
//расположен на плоской поверхности.Архитектор уже сопоставил замку прямоугольную декартову
//систему координат и точно определил координаты каждого угла замка в футах.
//Ввод из файла INPUT.TXT.Первая строка содержит два целых числа N и L, разделённых
//пробелом : N - число углов в замке Короля, а L - минимальное число футов, на которое Король
//разрешил приблизить стену к замку.
//Следующие N строк описывают координаты углов замка в порядке обхода по часовой стрелке.
//Каждая строка содержит два целых числа x i и y i, разделённых пробелом и представляющих собой
//координаты i - го угла в футах.Все углы имеют различные координаты, и стены замка не
//пересекаются иначе как в углах.
//Ограничения : 3 ≤ N ≤ 1000, 1 ≤ L ≤ 1000, -10000 ≤ x i, y i  ≤ 10000, время 2 с.
//Вывод в файл OUTPUT.TXT.Выводится единственное число - минимальная длина стены в
//футах, которая может быть построена вокруг замка согласно требованиям Короля с точностью до
//фута.

using namespace std;

const double pi = 3.141592653;

struct Point
{
	int x, y;

	double distTo(Point p)
	{
		return hypot(p.x - x, p.y - y);
	}

	double angleTo(Point p)
	{
		double angle = atan2(p.y - y, p.x - x);

		if (angle <= 0)
		{
			angle += 2 * pi;
		}

		return angle;
	}
};

int Next(int i, int n)
{
	return (i + 1) % n;
}

bool PointsAreClockwise(Point a, Point b, Point c)
{
	return (b.x - a.x) * (b.y + a.y) + (c.x - b.x) * (c.y + b.y) + (a.x - c.x) * (a.y + c.y) > 0;
}

bool StackTopIsClockwise(const list<Point>& stack)
{
	return PointsAreClockwise(
		*prev(prev(prev(stack.end()))),
		*prev(prev(stack.end())),
		*prev(stack.end())
	);
}

int main()
{
	ifstream fin("input.txt");

	ofstream fout("output.txt");

	int n, l;

	vector<Point> points;

	fin >> n >> l;

	points.reserve(n);

	for (int i = 0; i < n; i++)
	{
		Point p;

		fin >> p.x >> p.y;

		points.push_back(p);
	}

	auto startPointIter = min_element(points.begin(), points.end(), [](Point a, Point b) {
		return (a.y > b.y) || (a.y == b.y && a.x < b.x);
	});

	int startPointIndex = distance(points.begin(), startPointIter);

	Point startPoint = points[startPointIndex];

	sort(points.begin(), points.end(), [&](Point a, Point b) {
		return startPoint.angleTo(a) > startPoint.angleTo(b);
	});

	startPointIter = min_element(points.begin(), points.end(), [](Point a, Point b) {
		return (a.y > b.y) || (a.y == b.y && a.x < b.x);
	});

	startPointIndex = distance(points.begin(), startPointIter);

	startPoint = points[startPointIndex];

	list<Point> stack;

	bool first = true;

	for (int index = startPointIndex; index != startPointIndex || first; index = Next(index, n))
	{
		stack.push_back(points[index]);

		while (stack.size() > 2 && !StackTopIsClockwise(stack))
		{
			stack.erase(prev(prev(stack.end())));
		}

		first = false;
	}

	stack.push_back(startPoint);

	double len = 0;

	for (auto i = stack.begin(); next(i) != stack.end(); i++)
	{
		len += i->distTo(*next(i));
	}

	len += 2 * pi * l;

	fout << round(len) << endl;

	return 0;
}
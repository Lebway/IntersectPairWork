﻿#ifndef LINE__H
#define LINE__H

#include "intersect.h"
#include <vector>

class Line
{
public:
	Line(long long x1, long long y1, long long x2, long long y2);
	void lineIntersect(Line&, vector<struct Position>&);
	long long a, b, c;
	long long x1, y1, x2, y2;
};

class rayLine : public Line
{
public:
	rayLine(long long, long long, long long, long long);
	void lineIntersect(Line&, vector<struct Position>&);
	void rayLineIntersect(rayLine&, vector<struct Position>&);
	inline bool outRangeX(long long x);
	inline bool outRangeY(long long y);
	long long x_end1, y_end1;
	int x_forward, y_forward;
};

class segLine : public Line
{
public:
	segLine(long long, long long, long long, long long);
	void lineIntersect(Line&, vector<struct Position>&);
	void rayLineIntersect(rayLine&, vector<struct Position>&);
	void segLineIntersect(segLine&, vector<struct Position>&);
	inline bool outRangeX(long long x);
	inline bool outRangeY(long long y);
	long long x_endLeft, y_endLeft, x_endRight, y_endRight;
	bool vertical;
};



#endif // !LINE__H

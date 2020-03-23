#include<iostream>
#include<fstream>
#include<regex>
#include<sstream>
#include"errorhandler.h"

std::string ErrorOutput[20] = { "��ȷ��", "�����в�����������ȷ��", "�����в�����ʽ����ȷ��","�����ļ������ڣ�",
								"�����ļ�Ϊ�գ�", "n������Χ��", "n����Ϊ���֣�",
								"ͼ�β���������Χ��", "�������غϣ�", "����ͼ�θ�ʽ����", "��(ֱ�ߡ����ߡ��߶�)֮���غ�", "Բ�غ�" };

ErrorType CommandError(int argc, char* argv[]) {
	if (argc != 5) {
		return ErrorType::CommandNum;
	}
	else {
		std::string i = argv[1];
		std::string o = argv[3];
		if (i != "-i" || o != "-o") {
			return ErrorType::CommandFormat;
		}
		else {
			struct stat buffer;
			if (stat(argv[2], &buffer) != 0) {
				return ErrorType::FileNotExist;
			}
			else {
				return ErrorType::NoError;
			}
		}
	}
}

ErrorType EmptyFileError(std::ifstream &ifile) {
	ifile.seekg(0, std::ios::end);
	if (int(ifile.tellg()) == 0) {
		return ErrorType::EmptyFile;
	}
	ifile.seekg(0, std::ios::beg);
	return ErrorType::NoError;
}

ErrorType NumError(std::string ntmp) {
	std::regex partten("-?[0-9]+");
	if (std::regex_match(ntmp, partten)) {
		int n;
		n = atoi(ntmp.c_str());
		if (n <= 0 || n > 500000) {
			return ErrorType::NumOutOfRange;
		}
		else {
			return ErrorType::NoError;
		}
	}
	else {
		return ErrorType::AssertNum;
	}
}

ErrorType BondError(long long num, int low, int high) {
	if (num > high || num < low) {
		return ErrorType::FigureOutOfRange;
	}
	else {
		return ErrorType::NoError;
	}
}

ErrorType OverlapError(long long a, long long b, long long c, long long d) {
	if (a == c && b == d) {
		return ErrorType::LinePointOverlap;
	}
	else {
		return ErrorType::NoError;
	}
}

CorrectFigure FigureError(std::string figuretmp) {
	CorrectFigure figure;
	std::regex partten("(L -?[0-9]+ -?[0-9]+ -?[0-9]+ -?[0-9]+)|(R -?[0-9]+ -?[0-9]+ -?[0-9]+ -?[0-9]+)|(S -?[0-9]+ -?[0-9]+ -?[0-9]+ -?[0-9]+)|(C -?[0-9]+ -?[0-9]+ -?[0-9]+)");
	if (std::regex_match(figuretmp, partten)) {
		std::stringstream ss(figuretmp);
		std::string shape;
		long long a;
		long long b;
		long long c;
		long long d;
		ss >> shape;
		if (shape == "L" || shape == "R" || shape == "S") {
			ss >> a >> b >> c >> d;
			BondError(a, -100000, 100000);
			BondError(b, -100000, 100000);
			BondError(c, -100000, 100000);
			BondError(d, -100000, 100000);
			OverlapError(a, b, c, d);
			figure.shape = shape[0];
			figure.a = a;
			figure.b = b;
			figure.c = c;
			figure.d = d;
		}
		else {
			ss >> a >> b >> c;
			BondError(a, -100000, 100000);
			BondError(b, -100000, 100000);
			BondError(c, 1, 100000);
			figure.shape = shape[0];
			figure.a = a;
			figure.b = b;
			figure.c = c;
		}
		figure.errortype = ErrorType::NoError;
		return figure;
	}
	else {
		figure.errortype = ErrorType::FigureFormat;
		return figure;
	}
}

void HandleError(ErrorType errortype) {
	if (errortype == ErrorType::NoError) {
		return;
	}
	else {
		std::cout << ErrorOutput[static_cast<int>(errortype)];
		exit(0);
	}
}
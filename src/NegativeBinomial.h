#pragma once
#include <vector>
#include "logFactorial.h"
#include "basicFunctions.h"
#include <iostream>
#include "Distributor.h"
#include <algorithm>

class Distributor;

class NegativeBinomial
{
	private:
		double Sigma;
		int Kmax;
		LogFactorial LogFac;
		int Resolution;
	public:
		double dMu;
		double muMax;
		std::vector<std::vector<double>> PureData;
		
		NegativeBinomial(int kMax, int resolution,double maxMu);
		void Populate(double sigma);
		// ~NegativeBinomial();
};

class TruncatedGaussian
{
	private:
	public:
		int Truncator;
		std::vector<std::vector<double>> PureData;
		TruncatedGaussian(int kMax, int bounder,double gamma);
};

struct EB_Bracket
{
	std::vector<int> Top;
	std::vector<int> Bottom;
	std::vector<double> Interpolate;	
	EB_Bracket(int q)
	{
		Top.resize(q);
		Bottom.resize(q);
		Interpolate.resize(q);
	}
};

extern int nWorkers;
class ErroredBinomial
{
	private:
		int nWorkers;
		TruncatedGaussian TG;
		EB_Bracket CurrentBracket;
		
		int Kmax;
		int Bounder;
		
		
		// void Worker(int id);
		// std::vector<int> WorkerStatus;
		// std::vector<std::thread> Threads;
		int masterStart = 0;
	public:
		std::vector<std::vector<double>> Data;
		NegativeBinomial NB;
		int Resolution;
		double Sigma;
		int qMax;
		
		ErroredBinomial(int kMax, int res, int bounder, double gamma, int qMax,double muMax, int nWorkers);
		// void CloseThreads();
		void PopulateChunk(int resMin, int resMax);
		void Populate(double sigma, Distributor & dist);

		void SetBracket(double nu);

		double GetProb(int q, int k);
};


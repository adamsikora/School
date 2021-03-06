#include <limits>
#include <iostream>
#include <bitset>

#include "MatlabEngine.h"

#include "Stopwatch.h"

#include "Encoding.h"

#include "LearningEvolution.h"
#include "Curver.h"
#include "Bandit.h"
#include "Salesman.h"

int main()
{
	utils::StopWatch sw(true);

	//std::function<double(double)> func = [](double var) {return var*var+sin(10*var); };
	//CurveValue nc(0.05, 0ui64, std::pair<double, double>(-10.0, 10.0), func);
	//
	//Species<CurveValue> news(nc, 10000, 100);

	//uint64_t size = 1000;
	//std::vector<uint64_t> items;
	//items.reserve(size);
	//uint64_t total = 0;
	//for (uint64_t i = 0; i < size; ++i) {
	//	total += 100 + i;
	//	items.push_back(100 + i);
	//}
	//
	//std::vector<uint64_t> init;
	//init.reserve(size);
	//for (uint64_t i = 0; i < size; ++i) {
	//	init.push_back(mersenneTwister() % 10);
	//}
	//
	//Bandit nb(0.002, init, 10, std::make_shared<Items>(items, total));
	//Species<Bandit> news(nb, 1000, 20, 50, 0.5, 0.02);
	//news.evolve();

	//uint64_t size = 16;
	//double pi = atan(1) * 4;
	//std::vector<std::pair<double, double>> items;
	//items.reserve(size);
	//for (uint64_t i = 0; i < size; ++i) {
	//	double pos = 2 * static_cast<double>(i) / static_cast<double>(size)*pi;
	//	items.emplace_back(sin(pos), cos(pos));
	//}
	//std::vector<uint64_t> init;
	//init.reserve(size);
	//for (uint64_t i = 0; i < size / 2; ++i) {
	//	init.push_back(2*i);
	//}
	//for (uint64_t i = 0; i < size / 2; ++i) {
	//	init.push_back(2*i + 1);
	//}
	//Salesman ns(0.05, init, std::make_shared<CityPositions>(items));
	//BlindEvolution<Salesman> s(ns, 100000, 2*pi, 20, 3, 1.0, 0.0);
	//s.evolve();

	//std::function<double(double)> func = [](double var) {return var*var + sin(10 * var); };
	//
	//for (uint64_t i = 0; i < 10; ++i) {
	//	LearningEvolution news(0, 0.05, 100, 1000, 3, std::pair<double, double>(-10.0, 10.0), func);
	//	news.evolve();
	//}

	//std::vector<std::pair<double, double>> data;
	//for (double i = 0; i < 100; ++i) {
	//	data.emplace_back(i, i*i);
	//}
	//
	//utils::matlab::plot(data);
	uint64_t x = 5, y = 3;
	std::vector<double> img;
	for (double i = 0; i < x*y; ++i) {
		img.emplace_back(i);
	}
	
	utils::matlab::draw(img, std::pair<uint64_t, uint64_t>(x, y), "jet");

	sw.stop();
	std::cout << sw.getLastElapsed();
	std::cin.ignore();

	//evolve(nc);

	//std::cout << std::numeric_limits<uint64_t>::max();

	/*for (int64_t i = 0; i < 100; ++i) {
		std::cout << grayToBin((binToGray(i))) << std::endl;
	}
	std::cout << "pokus";
	std::cin.ignore();*/

	return 0;
}

//#define  BUFSIZE 256
//
//int main()
//
//{
//	Engine *ep;
//	mxArray *T = NULL, *result = NULL;
//	char buffer[BUFSIZE + 1];
//	double time[10] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
//
//	/*
//	* Call engOpen with a NULL string. This starts a MATLAB process
//	* on the current host using the command "matlab".
//	*/
//	if (!(ep = engOpen(""))) {
//		fprintf(stderr, "\nCan't start MATLAB engine\n");
//		return EXIT_FAILURE;
//	}
//
//	/*
//	* PART I
//	*
//	* For the first half of this demonstration, we will send data
//	* to MATLAB, analyze the data, and plot the result.
//	*/
//
//	/*
//	* Create a variable for our data
//	*/
//	T = mxCreateDoubleMatrix(1, 10, mxREAL);
//	memcpy((void *)mxGetPr(T), (void *)time, sizeof(time));
//	/*
//	* Place the variable T into the MATLAB workspace
//	*/
//	engPutVariable(ep, "T", T);
//
//	/*
//	* Evaluate a function of time, distance = (1/2)g.*t.^2
//	* (g is the acceleration due to gravity)
//	*/
//	engEvalString(ep, "D = .5.*(-9.8).*T.^2;");
//
//	/*
//	* Plot the result
//	*/
//	engEvalString(ep, "plot(T,D);");
//	engEvalString(ep, "title('Position vs. Time for a falling object');");
//	engEvalString(ep, "xlabel('Time (seconds)');");
//	engEvalString(ep, "ylabel('Position (meters)');");
//
//	/*
//	* use fgetc() to make sure that we pause long enough to be
//	* able to see the plot
//	*/
//	printf("Hit return to continue\n\n");
//	fgetc(stdin);
//	/*
//	* We're done for Part I! Free memory, close MATLAB figure.
//	*/
//	printf("Done for Part I.\n");
//	mxDestroyArray(T);
//	engEvalString(ep, "close;");
//
//
//	/*
//	* PART II
//	*
//	* For the second half of this demonstration, we will request
//	* a MATLAB string, which should define a variable X.  MATLAB
//	* will evaluate the string and create the variable.  We
//	* will then recover the variable, and determine its type.
//	*/
//
//	/*
//	* Use engOutputBuffer to capture MATLAB output, so we can
//	* echo it back.  Ensure first that the buffer is always NULL
//	* terminated.
//	*/
//
//	buffer[BUFSIZE] = '\0';
//	engOutputBuffer(ep, buffer, BUFSIZE);
//	while (result == NULL) {
//		char str[BUFSIZE + 1];
//		/*
//		* Get a string input from the user
//		*/
//		printf("Enter a MATLAB command to evaluate.  This command should\n");
//		printf("create a variable X.  This program will then determine\n");
//		printf("what kind of variable you created.\n");
//		printf("For example: X = 1:5\n");
//		printf(">> ");
//
//		fgets(str, BUFSIZE, stdin);
//
//		/*
//		* Evaluate input with engEvalString
//		*/
//		engEvalString(ep, str);
//
//		/*
//		* Echo the output from the command.
//		*/
//		printf("%s", buffer);
//
//		/*
//		* Get result of computation
//		*/
//		printf("\nRetrieving X...\n");
//		if ((result = engGetVariable(ep, "X")) == NULL)
//			printf("Oops! You didn't create a variable X.\n\n");
//		else {
//			printf("X is class %s\t\n", mxGetClassName(result));
//		}
//	}
//
//	/*
//	* We're done! Free memory, close MATLAB engine and exit.
//	*/
//	printf("Done!\n");
//	mxDestroyArray(result);
//	engClose(ep);
//
//	return EXIT_SUCCESS;
//}
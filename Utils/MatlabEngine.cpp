
#include "MatlabEngine.h"
#include "engine.h"

namespace utils
{
	namespace matlab
	{
		namespace {
			const uint64_t bufferSize = 256;
			Engine *ep = nullptr;

			void engineInit()
			{
				if (ep == nullptr) {
					if (!(ep = engOpen(""))) {
						fprintf(stderr, "\nCan't start MATLAB engine\n");
					}
				}
			}
		}

		void plot(const std::vector<std::pair<double, double>>& data)
		{
			engineInit();

			const uint64_t size = data.size();
			double *x = new double[size], *y = new double[size];

			for (uint64_t i = 0; i < size; ++i) {
				x[i] = data[i].first;
				y[i] = data[i].second;
			}

			mxArray *matlabX = mxCreateDoubleMatrix(1, size, mxREAL);
			mxArray *matlabY = mxCreateDoubleMatrix(1, size, mxREAL);

			memcpy((void *)mxGetPr(matlabX), (void *)x, sizeof(x)*size);
			memcpy((void *)mxGetPr(matlabY), (void *)y, sizeof(y)*size);

			engPutVariable(ep, "X", matlabX);
			engPutVariable(ep, "Y", matlabY);

			engEvalString(ep, "plot(X,Y);");

			engEvalString(ep, "title('Position vs. Time for a falling object');");
			engEvalString(ep, "xlabel('Time (seconds)');");
			engEvalString(ep, "ylabel('Position (meters)');");

			mxDestroyArray(matlabX);
			mxDestroyArray(matlabY);

			//mxArray *T = NULL, *result = NULL;
			//double time[10] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
			//
			//T = mxCreateDoubleMatrix(1, 10, mxREAL);
			//memcpy((void *)mxGetPr(T), (void *)time, sizeof(time));
			//
			//engPutVariable(ep, "T", T);
			//
			//engEvalString(ep, "D = .5.*(-9.8).*T.^2;");
			//
			//engEvalString(ep, "plot(T,D);");
			//engEvalString(ep, "title('Position vs. Time for a falling object');");
			//engEvalString(ep, "xlabel('Time (seconds)');");
			//engEvalString(ep, "ylabel('Position (meters)');");
			//
			//mxDestroyArray(T);
			//engEvalString(ep, "close;");
		}
	}
}
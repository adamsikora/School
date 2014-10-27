
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

			void drawInternal(double *img, uint64_t size, std::pair<uint64_t, uint64_t> range, std::string colormap)
			{
				engineInit();

				mxArray *matlabImg = mxCreateDoubleMatrix(range.second, range.first, mxREAL);
				memcpy((void *)mxGetPr(matlabImg), (void *)img, sizeof(img)*size);

				engPutVariable(ep, "img", matlabImg);

				engEvalString(ep, "imagesc(img);");
				engEvalString(ep, std::string("colormap(" + colormap + ");").c_str());

				mxDestroyArray(matlabImg);
			}
		}

		void evaluate(std::string command)
		{
			engineInit();

			engEvalString(ep, command.c_str());
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

			//engEvalString(ep, "title('Position vs. Time for a falling object');");
			//engEvalString(ep, "xlabel('Time (seconds)');");
			//engEvalString(ep, "ylabel('Position (meters)');");

			mxDestroyArray(matlabX);
			mxDestroyArray(matlabY);
		}

		void draw(const std::vector<double>& data, std::pair<uint64_t, uint64_t> range, std::string colormap)
		{
			const uint64_t size = data.size();
			double *img = new double[size];

			for (uint64_t i = 0; i < range.first; ++i) {
				for (uint64_t j = 0; j < range.second; ++j) {
					img[j + range.second*i] = data[i + range.first*j];
				}
			}

			drawInternal(img, size, range, colormap);
		}

		void draw(const std::vector<uint64_t>& data, std::pair<uint64_t, uint64_t> range, std::string colormap)
		{
			const uint64_t size = data.size();
			double *img = new double[size];

			for (uint64_t i = 0; i < range.first; ++i) {
				for (uint64_t j = 0; j < range.second; ++j) {
					img[j + range.second*i] = static_cast<double>(data[i + range.first*j]);
				}
			}

			drawInternal(img, size, range, colormap);
		}
	}
}
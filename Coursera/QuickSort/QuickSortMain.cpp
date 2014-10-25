#include "StlBase.h"

#include "StopWatch.h"

typedef std::vector<int64_t>::iterator vectIt;

std::random_device rd;
std::mt19937_64 mt(rd());

vectIt choosePivot(vectIt begin, vectIt end)
{
	return begin + (mt() % (end - begin));
	//vectIt vecIts[3] = {begin, begin + (end - begin - 1) / 2, end - 1};
	/*vectIt middle = begin + (--end - begin) / 2;

	vectIt result;

	if (*begin < *middle) {
		if (*middle < *end) {
			result = middle;
		}
		else {
			result = (*begin < *end ? end : begin);
		}
	}
	else {
		if (*begin < *end) {
			result = begin;
		}
		else {
			result = (*middle < *end ? end : middle);
		}
	}

	return result;*/
}

void quickSort(vectIt begin, vectIt end)
{
	if (end - begin > 1) {
		if (end - begin == 2) {
			if (*begin > *(begin + 1)) {
				std::swap(*begin, *(begin + 1));
			}
		}
		else {
			vectIt pivot = choosePivot(begin, end);
			std::swap(*begin, *pivot);
			pivot = begin;

			vectIt it = begin + 1;
			for (vectIt jt = begin + 1; jt < end; ++jt) {
				if (*jt < *pivot) {
					std::swap(*it, *jt);
					++it;
				}
			}
			std::swap(*pivot, *(it - 1));
			quickSort(begin, it - 1);
			quickSort(it, end);
		}
	}
}

bool isSorted(vectIt begin, vectIt end)
{
	bool sorted = true;

	for (vectIt it = begin; it < end - 1; ++it) {
		if (*it > *(it + 1)) {
			return false;
		}
	}
	return true;
}

int main()
{
	/*std::ifstream input("QuickSort.txt");

	std::vector<int64_t> in;
	in.reserve(10000);
	for (int64_t i = 0; i < 10000; ++i) {
		int64_t next;
		input >> next;
		in.push_back(next);
	}
	std::vector<int64_t> in2 = { 8, 2, 4, 5, 7, 1 };

	quickSort(in2.begin(), in2.end());*/

	std::vector<int64_t> in;
	int64_t reserve = 1i64 << 28i64;
	in.reserve(reserve);
	for (int64_t i = 0; i < reserve; ++i) {
		in.push_back(mt());
	}
	StopWatch sw;
	sw.start();

	quickSort(in.begin(), in.end());

	sw.stop();
	std::cout << "It took: " << sw.getTotalElapsed() << std::endl;

	std::cout << isSorted(in.begin(), in.end()) << std::endl;

	std::cin.ignore();

	return 0;
}
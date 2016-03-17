#ifndef __re_util_algorithm_stagedalgorithm_hpp_defined
#define __re_util_algorithm_stagedalgorithm_hpp_defined

#include "../Delegate.hpp"

namespace re
{
	namespace util
	{
		namespace algorithm
		{
			template<class InputArg, class Accumulator>
			class StagedAlgorithm : Delegate<void (*)(InputArg, Accumulator&)>
			{
				Accumulator acc;
			public:
				StagedAlgorithm(void (*function)(InputArg, Accumulator&), Accumulator && initial) : acc(std::move(initial)) {
					(*this) += function;
				}
				StagedAlgorithm(void (*function)(InputArg, Accumulator&), const Accumulator & initial) : acc(initial) {
					(*this) += function;
				}

				void stage(InputArg arg) {
					(*this)(arg, acc);
				}

				Accumulator & accumulator() { return acc; }
				const Accumulator& accumulator() const { return acc; }
			};

		}
	}
}

#endif
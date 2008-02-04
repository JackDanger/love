%{#include "Timer.h"%}

namespace love
{
	class Timer : public Device
	{
	public:
		virtual void startBenchmark() = 0;
		virtual float endBenchmark() = 0;
		float getFps() const;
	};
}

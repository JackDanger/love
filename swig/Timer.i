%{#include "Timer.h"%}

namespace love
{
	class Timer : public Device
	{
	public:
		virtual float getDelta() = 0;
		virtual void startBenchmark() = 0;
		virtual float endBenchmark() = 0;
		float getFps() const;
	};
}

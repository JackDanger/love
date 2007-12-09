namespace love
{
	class FrameAnimation : public Sprite
	{
	public:

		void addFrame(float x, float y, float width, float height, float post_delay);
		void addFrames(int sizex, int sizey, float width, float height, float post_delay);

		void start();
		void stop();
		void delay(float t);
	};

	typedef boost::shared_ptr<FrameAnimation> pFrameAnimation;

}// love

%template(SmartFrameAnimation) boost::shared_ptr<love::FrameAnimation>;
namespace love
{
	class Keyboard : public AbstractDevice, public KeyListener
	{
	public:
		bool isDown(int key);
	};

}

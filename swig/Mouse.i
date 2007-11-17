namespace love
{
	class Mouse : public AbstractDevice, public MouseListener, public MouseMotionListener
	{
	public:

		int getButtons() const;
		float getX() const;
		float getY() const;
		void setVisible(bool visible);
		bool isVisible() const;
		bool isDown(int button) const;


	};

}

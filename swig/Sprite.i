namespace love
{
	class Sprite : public AbstractEntity, public Loadable
	{
	public:
		float getWidth() const;
		float getHeight() const;
	};
}
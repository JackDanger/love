namespace love
{
	class Sprite : public AbstractEntity, public Loadable
	{
	public:
	float getWidth() const;
	float getHeight() const;
	};
	
	typedef boost::shared_ptr<Sprite> pSprite;
}

%template(SmartSprite) boost::shared_ptr<love::Sprite>;
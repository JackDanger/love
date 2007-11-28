namespace love
{
	class Sprite : public AbstractEntity, public Loadable
	{
	public:
		virtual void update(float dt);
		float getWidth() const;
		float getHeight() const;
	};
}

%template(SmartSprite) boost::shared_ptr<love::Sprite>;
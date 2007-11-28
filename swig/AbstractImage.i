
namespace love
{
	class AbstractImage : public Sprite
	{
	public:
	virtual void update(float dt);
	};
}

%template(SmartAbstractImage) boost::shared_ptr<love::AbstractImage>;
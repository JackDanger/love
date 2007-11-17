
namespace love
{
	class AbstractImage : public Sprite
	{
	};
}

%template(SmartAbstractImage) boost::shared_ptr<love::AbstractImage>;
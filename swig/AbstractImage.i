namespace love
{
	class AbstractImage : public Sprite
	{
	};

	typedef boost::shared_ptr<AbstractImage> pAbstractImage;
}

%template(SmartImage) boost::shared_ptr<love::AbstractImage>;
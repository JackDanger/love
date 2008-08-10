%{#include "Contact.h"%}

namespace love_box2d
{
	class Contact
	{
	public:
		float getSeparation() const;
		float getFriction() const;
		float getRestitution() const;
	};
	
	typedef boost::shared_ptr<Contact> pContact;
}

%template(SmartContact) boost::shared_ptr<love_box2d::Contact>;

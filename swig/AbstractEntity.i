
namespace love
{

	class AbstractEntity : public Object, public Renderable, public Updateable, public Scriptable
	{
	private:
	public:
		virtual void update(float dt);
	};
}

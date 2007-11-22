
namespace love
{

	class AbstractGraphics : public AbstractDevice
	{
	protected:	
	public:
	
		AbstractGraphics();
		virtual ~AbstractGraphics();
		
		void setColor(int r, int g, int b, int a = 255);
		void setColor(int code, int a = 255);
		void setBackgroundColor(int r, int g, int b);
		void setBackgroundColor(int code);

		pAbstractColor getColor();
		pAbstractColor getBackgroundColor();
		pAbstractFont getFont();

		virtual void translate(float x, float y) const = 0;
		virtual void rotate(float a) const = 0;
		virtual void scale(float s) const = 0;
		virtual void scale(float sx, float sy) const = 0;

		virtual void drawLine(float x1, float y1, float x2, float y2, float rotation = 0, float lineWidth = 1) const = 0;
		virtual void drawTriangle(float x, float y, float width, float height, float rotation = 0, float lineWidth = 1) const = 0;
		virtual void fillTriangle(float x, float y, float width, float height, float rotation = 0) const = 0;
		virtual void drawRectangle(float x, float y, float width, float height, float rotation = 0, float lineWidth = 1) const = 0;
		virtual void fillRectangle(float x, float y, float width, float height, float rotation = 0) const = 0;
		virtual void drawCircle(float x, float y, float radius, int points = 10, float rotation = 0, float lineWidth = 1) const = 0;
		virtual void fillCircle(float x, float y, float radius, int points = 10, float rotation = 0) const = 0;

		virtual void identity() const = 0;
		virtual void push() const = 0;
		virtual void pop() const = 0; 
		virtual void clear() const = 0;
				
	}; // AbstractGraphics
	
	typedef boost::shared_ptr<AbstractGraphics> pAbstractGraphics;
	
} 


// Extensions
%extend love::AbstractGraphics {
	
	void setColor(const pAbstractColor * color)
	{
		self->setColor(*color);
	}
	void setBackgroundColor(const pAbstractColor * color)
	{
		self->setBackgroundColor(*color);
	}
	void setFont(const pAbstractFont * font)
	{
		self->setFont(*font);
	}
	
	void draw(const pAbstractImage * sprite, float x = 0, float y = 0) const
	{
		self->draw((pSprite)*sprite, x, y);
	}
	void draw(const pAbstractImage * sprite, float x, float y, float width, float height) const
	{
		self->draw((pSprite)*sprite, x, y, width, height);
	}
	void draw(const pFrameAnimation * sprite, float x = 0, float y = 0) const
	{
		self->draw((pSprite)*sprite, x, y);
	}
	void draw(const pFrameAnimation * sprite, float x, float y, float width, float height) const
	{
		self->draw((pSprite)*sprite, x, y, width, height);
	}
	void draw(const pParticleSystem * particleSystem, float x = 0, float y = 0) const
	{
		self->draw(*particleSystem, x, y);
	}
	virtual void draw(const char * str, float x = 0, float y = 0, float limit = 0, int align = 1) const
	{
		self->draw(str, x, y, limit, align);
	}

};
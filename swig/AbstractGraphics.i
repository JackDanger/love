
namespace love
{

	class AbstractGraphics : public AbstractDevice
	{
	protected:

		pAbstractColor color;
		pAbstractColor background;
		pAbstractFont font;
		pAbstractFont defaultFont;
	
	public:
	
		AbstractGraphics();
		virtual ~AbstractGraphics();
		
		void setColor(const pAbstractColor * color);
		void setColor(int r, int g, int b, int a = 255);
		void setColor(int code, int a = 255);
		void setBackground(const pAbstractColor * color);
		void setBackground(int r, int g, int b);
		void setBackground(int code);
		
		void setFont(const pAbstractFont * font);
		void setFont(pAbstractFont font);

		pAbstractColor getColor();
		pAbstractColor getBackground();

		pAbstractFont getFont();

		// hide all of this
		//virtual void drawSprite(const pAbstractImage * sprite) const;
		//virtual void drawSprite(const pAbstractImage * sprite, float x, float y) const;
		//virtual void drawSprite(const pAbstractImage * sprite, float x, float y, float width, float height) const;
		//virtual void drawSprite(const pAbstractImage * sprite, float x, float y, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) const;
		//virtual void drawSubSprite(const pAbstractImage * sprite, float x, float y, float width, float height) const;
		//virtual void drawSprite(const pFrameAnimation * sprite) const;
		//virtual void drawSprite(const pFrameAnimation * sprite, float x, float y) const;
		//virtual void drawSprite(const pFrameAnimation * sprite, float x, float y, float width, float height) const;
		//virtual void drawSprite(const pFrameAnimation * sprite, float x, float y, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) const;
		//virtual void drawSubSprite(const pFrameAnimation * sprite, float x, float y, float width, float height) const;
		//virtual void drawSprite(const pSprite & sprite) const = 0;
		//virtual void drawSprite(const pSprite & sprite, float x, float y) const = 0;
		//virtual void drawSprite(const pSprite & sprite, float x, float y, float width, float height) const = 0;
		//virtual void drawSprite(const pSprite & sprite, float x, float y, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) const = 0;
		//virtual void drawSubSprite(const pSprite & sprite, float x, float y, float width, float height) const = 0;
		//virtual void drawParticleSystem(const pParticleSystem * particleSystem) const = 0;
		//virtual void drawParticleSystem(const pParticleSystem * particleSystem, float x, float y) const = 0;
		//virtual void drawBezier(const pBezier * bezier, float x, float y, int precision = 20, float lineWidth = 2.0f) const = 0;
		//virtual void drawString(const char * str, float x, float y) const = 0;
		//virtual void drawText(const char * str, float x, float y, float limit = 0, int align = 1) const = 0;

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

		// draw functions
		//virtual void draw(pSprite sprite, float x = 0, float y = 0) const;
		//virtual void draw(pSprite sprite, float x, float y, float width, float height) const;
		//virtual void draw(pParticleSystem particleSystem, float x = 0, float y = 0) const;		
		virtual void draw(const char * str, float x = 0, float y = 0, float limit = 0, int align = 1) const;

		virtual void identity() const = 0;
		virtual void push() const = 0;
		virtual void pop() const = 0; 
		virtual void clear() const = 0;
				
	}; // AbstractGraphics
	
	typedef boost::shared_ptr<AbstractGraphics> pAbstractGraphics;
	
} 


// Extensions
%extend love::AbstractGraphics {
	
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

};
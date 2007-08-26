#include "GUIText.h"

namespace love
{
	GUIText::GUIText(love::Font * font, AbstractColor * color)
	{
		this->font = font;
		this->color = color;
	}
       
	GUIText::~GUIText()
	{
	}

	int GUIText::getWidth(unsigned char glyph) const
	{
		if(font == 0)
			return 0;
		return font->width[glyph];
	}

    int GUIText::getWidth(const std::string& text) const
	{
		if(font == 0)
			return 0;

		int fist = (int)font->getLineWidth(text.c_str());

		return fist;
	}
        
	int GUIText::getHeight() const
	{
		if(font == 0)
			return 0;
		return (int)(font->getLineHeight() * 1.1);
		//return (int)(font->getLineHeight());
	}

	void GUIText::setColor(gcn::Color color)
	{
		this->color->setColor(color.r, color.g, color.b, color.a);
	}

	love::Font * GUIText::getFont()
	{
		return font;
	}

	void GUIText::setFont(love::Font * font)
	{
		this->font = font;
	}

	AbstractColor * GUIText::getColor()
	{
		return color;
	}

	void GUIText::setColor(AbstractColor * color)
	{
		this->color = color;
	}

	void GUIText::drawString(gcn::Graphics* graphics, const std::string& text, int x, int y)
	{
		
		gcn::OpenGLGraphics* glGraphics = (gcn::OpenGLGraphics*) graphics;
	
		if(glGraphics == NULL)
		{
			return;
			//should throw exception
		}

	
		if(font != NULL)
		{
			
			gcn::Rectangle rect = glGraphics->getCurrentClipArea();
			
			// Store current color etc
			glPushAttrib(GL_CURRENT_BIT);

			// Fix some of the shit that GuiChan messes up.
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			// Enable texturing (simple)
			glEnable(GL_TEXTURE_2D);

			// Enable blending (thank you for disabling that, GuiChan)
			glEnable(GL_BLEND);
			
			// Set leet color
			//glColor4ub(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha());
			
			glPushMatrix(); //-2 because of some tweaking shit
			glRasterPos2i(rect.x + x,  rect.y + y + (GLint)font->getLineHeight() - 2);
			glTranslatef((GLfloat)rect.x + x, rect.y + y + font->getLineHeight() - 2, 0.0f);

			font->print(text);

			glPopMatrix();

			// Restore GuiChan style color material gl ultra shit
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

			// Restore color etc
			glPopAttrib();
			
			// Balance plzx
			glDisable(GL_TEXTURE_2D);
			
		}
	}	
}
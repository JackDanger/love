#include "GUIText.h"

namespace love
{
	GUIText::GUIText(pAbstractFont font, pAbstractColor color)
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

		int temp = (int)font->getLineWidth(text.c_str());

		return temp;
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

	pAbstractFont GUIText::getFont()
	{
		return font;
	}

	void GUIText::setFont(AbstractFont * font)
	{
		this->font.reset<AbstractFont>(font);
	}

	void GUIText::setFont(pAbstractFont font)
	{
		this->font = font;
	}

	pAbstractColor GUIText::getColor()
	{
		return color;
	}

	void GUIText::setColor(pAbstractColor color)
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

		/*gcn::Rectangle rect = glGraphics->getCurrentClipArea();

		//glRasterPos2i(rect.x + x,  rect.y + y + (GLint)font->getLineHeight() - 2);
		//glTranslatef((GLfloat)rect.x + x, rect.y + y + font->getLineHeight() - 2, 0.0f);
		glTranslatef(x,y,0.0f);

		int bgf = getWidth(text);
		bgf = bgf;

		glPushMatrix();
		glBegin(GL_QUADS);
			glVertex2f(0,0);
			glVertex2f(font->getLineWidth(text.c_str()),0);
			glVertex2f(font->getLineWidth(text.c_str()),font->getLineHeight());
			glVertex2f(0,font->getLineHeight());
		glEnd();
		glPopMatrix();*/
	
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

#include "GUIDynamicBackground.h"

using std::vector;

namespace love
{

	GUIDynamicBackground::GUIDynamicBackground()
	{
		precision = 3;
		center.setX(800);
		center.setY(350);

		vel.setX((float)(rand()%50 + 100));
		vel.setY((float)(rand()%50 + 100));
		line = true;
	}

	GUIDynamicBackground::GUIDynamicBackground(float width, float height) : width(width), height(height)
	{
	}

	GUIDynamicBackground::~GUIDynamicBackground()
	{
	}

	void GUIDynamicBackground::render()
	{
		glDisable(GL_TEXTURE_2D);
		//glPolygonMode(GL_FRONT ,GL_LINE);
		
		//glLineWidth(1.0);
		

		glBegin(GL_QUADS);

		/**
		glVertex2f(0, 0);  //A
		glVertex2f(0, 50); //B
		glVertex2f(50, 0); //C

		glVertex2f(50, 50); //D
		**/


		for(int j=0;j<precision;j++)
		{
			for(int i=0;i<precision;i++)
			{

				Color clr0 = getColor(i*triangleWidth, j*triangleHeight);
				Color clr1 = getColor(i*triangleWidth, j*triangleHeight + triangleHeight);
				Color clr2 = getColor(i*triangleWidth + triangleWidth, j*triangleHeight + triangleHeight);
				Color clr3 = getColor(i*triangleWidth + triangleWidth, j*triangleHeight);


				glColor3ub(clr0.getRed(), clr0.getGreen(), clr0.getBlue());
				glVertex2f(i*triangleWidth, j*triangleHeight);


				glColor3ub(clr1.getRed(), clr1.getGreen(), clr1.getBlue());
				glVertex2f(i*triangleWidth, (j+1)*triangleHeight);

				glColor3ub(clr2.getRed(), clr2.getGreen(), clr2.getBlue());
				glVertex2f((i+1)*triangleWidth, (j+1)*triangleHeight);

				glColor3ub(clr3.getRed(), clr3.getGreen(), clr3.getBlue());
				glVertex2f((i+1)*triangleWidth, j*triangleHeight);
			}
		}



		glEnd();


		if(line)
		{

		float h = 170/2;
		float m = height/2;

		glColor4ub(255, 255, 255, 30);

		glBegin(GL_QUADS);
			glVertex2f(0, m - h);
			glVertex2f(0, m + h);
			glVertex2f(width, m + h);
			glVertex2f(width, m - h);
		glEnd();
		
		}

	}

	Vector GUIDynamicBackground::getPosition(int i, int j)
	{
		return Vector((float)(i*precision), (float)(j*precision));
	}

	Color GUIDynamicBackground::getColor(float x, float y)
	{
		// Distance to center
		float d = (center - Vector(x, y)).getLength();

		float pos = 1 - (d/700);

		if(pos < 0) pos = 0;
		if(pos > 1) pos = 1;

		pAbstractColor temp = colors[0]->getGradient(&colors[1], pos);

		return Color(temp->getCode());
	}

	void GUIDynamicBackground::update(float dt)
	{

		for(unsigned int i=0;i<colors.size(); i++)
			colors[i]->update(dt);

		float speed = 100;
			
		if(center.getX() < 0)
		{
			center.setX(0);
			vel.setX(speed);
		}

		if(center.getX() > width)
		{
			center.setX(width);
			vel.setX(-speed);
		}

		if(center.getY() < 0)
		{
			center.setY(0);
			vel.setY(speed);
		}

		if(center.getY() > height)
		{
			center.setY(height);
			vel.setY(-speed);
		}

		center += vel * dt;
	}

	void GUIDynamicBackground::setSize(float width, float height)
	{

		colors.clear();

		this->width = width;
		this->height = height;
		this->triangleWidth = width / precision;
		this->triangleHeight = height / precision;


		// Main bgcolor
		pSmoothAnimatedColor c(new SmoothAnimatedColor(0));
		pAbstractColor clr(new Color(0x3b90c8));
		c->addColor(&clr, 5);
		//c->addColor(new Color(0x2facfd), 5);
		//c->addColor(new Color(0xf24023), 5);
		//c->play();
		c->setMode(AnimatedColor::LOVE_ANIMATED_COLOR_LOOP);
		colors.push_back(c);

		// Specular
		pSmoothAnimatedColor c1(new SmoothAnimatedColor(0));
 		pAbstractColor clr2(new Color(0xa6d5f3));
		c1->addColor(&clr2, 2);
		//c1->addColor(new Color(0x2ca9fa), 2);
		//c1->play();
		c1->setMode(AnimatedColor::LOVE_ANIMATED_COLOR_LOOP);
		colors.push_back(c1);

	}

	void GUIDynamicBackground::setLine(bool line)
	{
		this->line = line;
	}

}// love

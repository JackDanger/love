#include "LoveMenu.h"
#include "Core.h"

#include <cmath>

using namespace std;

namespace love
{

	LoveMenu::LoveMenu()
	{
		setTitle("zzZzz LOVE Menu ...");
		games = 0;

	}

	LoveMenu::LoveMenu(Container<Game> * games)
	{
		this->games = games;
	}

	LoveMenu::~LoveMenu()
	{
	}



	void LoveMenu::init()
	{
	

		//display->queueMode(800, 600, 32, false);

		glClearColor(1, 1, 1, 1);
		setTitle("ZzzZzz LOVE Menu ...");


		mouseDown = false;
		xpos = 0;
		ypos = 0;
		

		defaultThumb.reset<ImageFromFile>(new ImageFromFile(LoveFile("data","thumb-std.png")));
		defaultThumbDither.reset<ImageFromFile>(new ImageFromFile(LoveFile("data","thumb-ds-std.png")));
		loveBottomRight.reset<ImageFromFile>(new ImageFromFile(LoveFile("data","love-could-bottom-right.png")));

		font.reset<Font>(new Font(LoveFile("data/fonts", "FreeSans.ttf"), 14));		


		Container<Game> games = *this->games;

		W = (int)ceil((float)sqrt((float)games.size()));

		worldWidth = (float)(W * (X_PAD + T_WIDTH));
		worldHeight = (ceil((float)games.size()/(float)W)) * (Y_PAD + T_HEIGHT);

		for(games.begin(); !games.end(); games.next())
		{

			printf("LOVEMENU DETECTS [%s] ... ", games.key().c_str());

			if(games.value()->getThumb() != 0)
			{
				printf("With image!");
			}
			else
			{
				//printf("Without image!");
			}

			printf("\n");
		}

		

		load();
		setInited(true);

		
	}

	void LoveMenu::renderText(const string & s, float x, float y, int alpha)
	{
		glColor4ub(89, 187, 250, alpha);
		glPushMatrix();
		glTranslatef(x, y, 0);
		font->print(s);
		glPopMatrix();
	}

	void LoveMenu::renderThumb(const pAbstractImage & img, float x, float y, int alpha)
	{
		glColor4ub(255, 255, 255, alpha);
		glPushMatrix();
		glTranslatef(x, y, 0);
		defaultThumbDither->render();
		glTranslatef(8, 8, 0);
		img->render();
		glPopMatrix();
	}

	void LoveMenu::mousePressed(float x, float y, int button)
	{
		if(button == LOVE_MOUSE_RIGHT)
		{
			xLastMouseDown = x;
			yLastMouseDown = y;
			mouseDown = true;
		}
		else if(button == LOVE_MOUSE_LEFT)
		{
			float x = X_PAD;
			float y = Y_PAD;
			int w = W;

			Container<Game> games = *this->games;
					
			for(games.begin(); !games.end(); games.next())
			{

				if(xMouseWorld >= x && xMouseWorld <= x + T_WIDTH
					&& yMouseWorld >= y && yMouseWorld <= y + T_HEIGHT)
				{
					printf("Clicked game: %s\n", games.key().c_str());
					Core::changeGame(games.key());
					break;
				}

				if(w <= 1)
				{
					x = X_PAD;
					y += T_HEIGHT + Y_PAD;
					w = W;
				}
				else
				{
					x += T_WIDTH + X_PAD;
					w--;
				}
			}
		}
	}

	void LoveMenu::mouseReleased(float x, float y, int button)
	{
		if(button == LOVE_MOUSE_RIGHT)
		{
			mouseDown = false;
		}

	}

	void LoveMenu::render()
	{

		glLoadIdentity();
		glTranslatef(xpos, ypos, 0);

		Container<Game> games = *this->games;

		float x = X_PAD;
		float y = Y_PAD;

		int w = W;


		for(games.begin(); !games.end(); games.next())
		{

			
			// Calculate alpha
			float xCenter = x + X_PAD + (T_WIDTH/2);
			float yCenter = y + Y_PAD + (T_HEIGHT/2);

			int alpha = 128;

			float a = (xCenter - xMouseWorld);
			float b = (yCenter - yMouseWorld);
			float c = sqrt(a*a+b*b);

			alpha = (int)(255 - c);

			if(c < 75) alpha = 255;

			if(alpha < 100) alpha = 100;
			if(alpha > 255) alpha = 255;
			

			if(games.value()->getThumb() == 0)
			{
				// Render generic
				renderThumb(defaultThumb, x, y, alpha);

				int maxchar = 15;

				string title = games.value()->getTitle();

				if(title.size() > (unsigned int)maxchar)
					title = title.substr(0, maxchar) + " ...";


				renderText(title, x + X_TEXT_PAD, y + Y_TEXT_PAD, alpha);
			}
			else
			{	
				renderThumb(games.value()->getThumb(), x, y, alpha);
			}

			if(w <= 1)
			{
				x = X_PAD;
				y += T_HEIGHT + Y_PAD;
				w = W;
			}
			else
			{
				x += T_WIDTH + X_PAD;
				w--;
			}

		}


		//renderText("(Right-click-and-drag to move around ^^)", 150, displayHeight - 20, 100);

		glLoadIdentity();
		glColor4ub(255, 255, 255, 255);
		glTranslatef((GLfloat)(displayWidth - 256), (GLfloat)(displayHeight - 256), 0.0f);
		loveBottomRight->render();



	}

	void LoveMenu::update(float dt)
	{
		xMouse = Core::getMouse()->getX();
		yMouse = Core::getMouse()->getY();

		xMouseWorld = xMouse - xpos;
		yMouseWorld = yMouse - ypos;

		if(mouseDown)
		{

			const float factor = 2.0f;

			float xdir = xMouse - xLastMouseDown;
			float ydir = yMouse - yLastMouseDown;

			xpos += (-xdir * factor) * dt;
			ypos += (-ydir * factor) * dt;

		}

		if(worldHeight > 0 && worldWidth > 0)
		{
			float xposMin = displayWidth - worldWidth;

			float yposMin = displayHeight - worldHeight - 10;

			if(xpos < xposMin) xpos = xposMin;
			if(xpos > 0) xpos = 0;

			if(ypos < yposMin) ypos = yposMin;
			if(ypos > 0) ypos = 0;
		}

	
	}

	void LoveMenu::load()
	{
		Game::load();
		
		defaultThumb->load();
		defaultThumbDither->load();
		loveBottomRight->load();
		font->load();

		displayWidth = Core::getDisplayMode()->getWidth();
		displayHeight = Core::getDisplayMode()->getHeight();
		
	}

	void LoveMenu::unload()
	{
		Game::unload();
		
		defaultThumb->unload();
		defaultThumbDither->unload();
		loveBottomRight->unload();
		font->unload();

	}

	void LoveMenu::resume()
	{
		Game::resume();
		glClearColor(1, 1, 1, 1);
		displayWidth = Core::getDisplayMode()->getWidth();
		displayHeight = Core::getDisplayMode()->getHeight();
	}

	void LoveMenu::reloadGraphics()
	{
		Game::reloadGraphics();

		defaultThumb->load();
		defaultThumbDither->load();
		loveBottomRight->load();
		font->load();

		Container<Game> games = *this->games;

		for(games.begin(); !games.end(); games.next())
		{
			if(games.value()->getThumb()!=0)
				games.value()->getThumb()->load();
		}

	}

}// love

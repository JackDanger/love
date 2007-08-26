#include "SelectGame.h"
#include "Core.h"

namespace love
{

	SelectGame::SelectGame()
	{
		setTitle("Game Selector (This menu)");
	}

	SelectGame::~SelectGame()
	{
	}

	void SelectGame::init()
	{

		display->queueMode(1024, 768, 32, false);
		display->queueMode(1024, 768, 16, false);
		display->queueMode(800, 600, 32, false);
		display->queueMode(800, 600, 16, false);

		text.reset<Text>(new Text());
		gameFont.reset<Font>(new Font("Arial.ttf", 12));
		gameFont->load();

		gameColor.reset<Color>(new Color(0,0,0,0));

		black.reset<Color>(new Color(0x000000));

		setInited(true);

		// Get list of games
		love::Container<love::Game> & games = love::Core::getGames();
		games.begin();

		int listStartX = 80;
		int listStartY = 150;

		int listSpaceY = 25;

		while(!games.end())
		{
			gameListElement gle;
			gle.x = 80;
			gle.y = (int)(listStartY + gameList.size() * listSpaceY);
			gle.running = games.value()->isInited() ? true : false;
			gle.str += games.value()->getTitle();
			gle.gameName = games.key();


			gameList.push_back(gle);

			games.next();
		}
	}

	void SelectGame::render()
	{

		glColor4ub(255,255,255,255);

		// Render white bg
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
		glBegin(GL_QUADS);
			glVertex2f(0,0);
			glVertex2f(0,2000);
			glVertex2f(2000,2000);
			glVertex2f(2000,0);
		glEnd();
		glPopMatrix();

		// Render LOVE logo.
		glEnable(GL_TEXTURE_2D);
		//loveLogo->render(50,20);

		//hidoi->render(350,60);

		glTranslatef(80.0f,130.0f, 0.0f);
		renderGameList();


	}

	void SelectGame::renderGameList()
	{

		Mouse * mouse = Core::getMouse();
		float my = mouse->getY();
		float mx = mouse->getY();

		

		// Render list of available games.
		
		for (int i=0;i<(int)gameList.size();i++)
		{

			gameListElement gle = gameList[i];

			

			unsigned int distance = abs( (gle.y - 7) - (int)my);
			distance = distance == 0 ? 1 : distance;

			int color = (int)((float)2000 / (float)distance);
				
			if(color > 255) color = 255;
			if(color < 64) color = 64;

			//glColor4ub(0,0,0,color);
			gameColor->setAlpha(color);


			glLoadIdentity();
			glTranslatef((float)gameList[i].x,(float)gameList[i].y, 0);
			text->print(gameFont.get(), gameColor.get(), gameList[i].str.c_str());
		}



		
	}

	void SelectGame::update(float dt)
	{
	}

	void SelectGame::mousePressed(float x, float y, int button)
	{
		for (int i=0;i<(int)gameList.size();i++)
		{

			gameListElement gle = gameList[i];

			if(y > gle.y - 20 && y < gle.y + 5)
				love::Core::changeGame(gle.gameName);
		}

		
	}

	void SelectGame::resume()
	{
		Game::resume();
		glClearColor(1, 1, 1, 1);
	}

	void SelectGame::reloadGraphics()
	{
		gameFont->load();
	}


}// love

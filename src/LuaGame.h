/**
* @file LuaGame.h
* @author Anders Ruud
* @date 2006-11-06
* @brief Contains definition for class LuaGame.
**/

#ifndef LOVE_LUAGAME_H
#define LOVE_LUAGAME_H

#include <math.h>
// LOVE
#include "Game.h"
#include "Container.h"
#include "Loadable.h"
#include "Text.h"
#include "Font.h"
#include "Event.h"
#include "Sound.h"
#include "Music.h"
#include "Color.h"
#include "LuaGL.h"
#include "FrameAnimation.h"
#include "Actor.h"
#include "ParticleEmitter.h"

#include "GameObjectContainer.h"

#include "LuaGameState.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>


// Lua
extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}


namespace love
{

	/**
	* @class LuaGame
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-11-06
	* @brief 
	**/
	class LuaGame : public Game
	{
	private:

		lua_State * L;

		pVextor pvex;


		// GL Wrapper
		pLuaGL gl;

		// Text
		pText text;

		// This objects holds all object containers. (PLZ)
		GameObjectContainer obj;

		// A record of included files. (Prevents 
		// re-inclusion)
		map<string, bool> included;

		Container<GameState> gameStates;

		// The game's source relative to execution directory.
		// May be directory or archive file.
		string source;

		GameState * currentGameState;

		Font * currentFont;

		// Text and primitives will be rendered with this color.
		Color * currentColor;
		Color * backgroundColor;

		// Defaults
		pColor defaultCurrentColor;
		pColor defaultBackgroundColor;
		//pFont defaultFont;

		//the global rotation
		float rotation;
		

		/**
		* @brief Gets path to a certain file.
		* @param s The filename only.
		* @return The path to the file.
		**/
		string getPath(const char * s) const;


	public:

		/**
		* @brief Contructs an empty LuaGame.
		* @param source The source for the game. Can be directory or archive file. (.love only)
		**/
		LuaGame(const string & source);

		virtual ~LuaGame();

		/**
		* @brief Initializes the game.
		**/
		int init();

		/**
		* @brief zomg
		**/
		int load();
		void unload();

		/**
		* @brief Renders the entire game once.
		**/
		void render();

		/**
		* @brief Updates the entire game.
		* @param dt The time since last frame (in seconds).
		**/
		void update(float dt);

		void suspend();
		void resume();
		void reloadGraphics();



		bool fileExists(const string & file);

		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(float x, float y, int button);
		void mouseReleased(float x, float y, int button);

		void say(const char * str);

		void eventFired(pEvent e);

		Vextor * createVextor(const char * str, float x, float y);


		bool luaIsFunction(const string & tablename, const string & functionname);
		void luaCheckErr(int status);

		// File methods
		void addFile(const char * filename);

		
		/**
		* @brief Reads and parses a Lua-file.
		* This method checks if the file already is included, and
		* does not include if it is.
		* 
		* @param filename The filname and path to the file.
		**/
		void include(const char * filename);

		//State methods
		void addState(const char * key);
		void removeState(const char * key);
		void setState(const char * key);

		// Image methods
		AbstractImage * addImage(const char * key, const char * filename);

		pAbstractImage addImage(const char * filename);

		AbstractImage * getImage(const char * key);
		void removeImage(const char * key);
		//void delImage(const char * key);
		bool isImage(const char * key);
		void listImages();

		// FrameAnimations
		FrameAnimation * addFrameAnimation(const char * key, const char * image);
		FrameAnimation * addFrameAnimation(const char * key, AbstractImage * image);
		FrameAnimation * getFrameAnimation(const char * key);
		void removeFrameAnimation(const char * key);
		bool isFrameAnimation(const char * key);

		//Actor * addActor(const char * key);
		Actor * addActor(const char * key, const char * scriptname = "");
		Actor * getActor(const char * key);
		void removeActor(const char * key);
		bool isActor(const char * key);

		ParticleEmitter * addParticleEmitter(const char * key, float delay = 0, int mode = 1);

		// Color methods
		Color * addColor(const char * key, int r, int g, int b, int a = 255);
		//Color * addColor(const char * key, int r, int g, int b);
		Color * addColor(const char * key, int hex);
		Color * getColor(const char * key);
		void setColor(Color * color);
		void setColor(const char * key);
		void setBackground(Color * color);
		void setBackground(const char * key);

		// Text
		Font * addFont(const char * key, int size);
		Font * addFont(const char * key, const char * fontfile, int size);
		Font * getFont(const char * key);
		void drawString(int x, int y, const char * str);

		void setFont(const char * key);
		void setFont(Font * font);

		void print(float x, float y, const char * c);
		//void drawString(const char * str, float x, float y);

		void setRotation(float rotation);
		float getRotation();

		// Basic Shapes
		void drawLine(float x1, float y1, float x2, float y2, float lineWidth = 1);
		void drawTriangle(float x, float y, float width, float height, float lineWidth = 1);
		void fillTriangle(float x, float y, float width, float height);
		void drawRect(float x, float y, float width, float height, float lineWidth = 1);
		void fillRect(float x, float y, float width, float height);
		void drawCircle(float x, float y, float radius, int points = 10, float lineWidth = 1);
		void fillCircle(float x, float y, float radius, int points = 10);

		// Sounds
		AbstractSound * addSound(const char * key, const char * filename);
		AbstractSound * getSound(const char * key);
		void stopAllSounds(float seconds = 0.0f);
		void pauseAllSounds();
		void resumeAllSounds();

		// Music
		AbstractMusic * addMusic(const char * key, const char * filename);
		AbstractMusic * getMusic(const char * key);

	};

	typedef boost::shared_ptr<LuaGame> pLuaGame;

} // love

#endif

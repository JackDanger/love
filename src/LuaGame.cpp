#include "LuaGame.h"
#include "Core.h"
#include "MessageEvent.h"

#include "lualove.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "AbstractFileSystem.h"
#include "AbstractSoundDevice.h"
#include "AbstractImageDevice.h"
#include "AbstractSound.h"
#include "AbstractMusic.h"
#include "GameConfigurationLoader.h"

#include <fstream>

#include "love.h"

using std::fstream;
using std::ios;

using boost::dynamic_pointer_cast;

#ifdef __cplusplus
extern "C" 
{
	int extern Love_Init(lua_State * L);
}
#endif


namespace love
{
	LuaGame::LuaGame(const string & source)
	{
		setScript("main");
		setType(LOVE_TYPE_LUA_GAME);

		this->source = source;

		// Init OpenGL wrapper
		gl.reset<LuaGL>(new LuaGL());

		// Defaults
		defaultCurrentColor.reset<Color>(new Color(0xffffff));
		defaultBackgroundColor.reset<Color>(new Color(0));
		//defaultFont.reset<Font>(new Font("FreeSans.ttf", 14));

		rotation = 0.0f;
		gui = 0;
	}

	LuaGame::~LuaGame()
	{
		//unload();
		if(gui != 0) delete gui;
	}

	string LuaGame::getPath(const char * s) const
	{
		return string(s);
	}


	int LuaGame::init()
	{

		config = new GameConfigurationLoader(source);
		config->load();

		inited = true;

		//pMessageEvent pme2(new MessageEvent("Init completed: " + getTitle() + "\n"));
		//Core::eventFired(pme2);

		/** This code sets "r" as a member of "defimage" (for great reference)
		lua_getglobal(L, "defimage");	// Pushes defimage on stack
		lua_pushstring(L, "r");
		lua_pushnumber(L, 255);
		lua_settable(L, -3);
		lua_pop(L, 1);
		**/

		gui = new gcn::Container();
		gui->setDimension(gcn::Rectangle(0, 0, core->getDisplayMode().getWidth(), core->getDisplayMode().getHeight()));
		gui->setOpaque(false);
		
		return LOVE_OK;

	}

	int LuaGame::load()
	{
		// Assign default obj.colors
		backgroundColor = defaultBackgroundColor.get();
		currentColor = defaultCurrentColor.get();

		//Sound::initFMOD();

		// The table name to look for in the lua chunk
		

		//pMessageEvent pme(new MessageEvent("Init started: " + getTitle() + "\n"));
		//Core::eventFired(pme);

		//printf("Right before loading font ... ^-^\n");

		addFont("love_system_font", 20);
		setFont("love_system_font");	

		//text.reset<Text>(new Text(&obj.fonts, &obj.colors));
		text.reset<Text>(new Text());
		//text->setFont("love_system_font"); //no need
		text->load();

		//init gui
		core->gui->add(gui);

		// Init lua
		L = lua_open();
		luaL_openlibs(L);
		Love_Init(L);

		lualove_init(L); // @todo find out why this cannot init L.

		// Push game
		lualove_push_global_pointer(L, (void*)this, "game", this->getType());
		
		// Keyboard
		lualove_push_global_pointer(L, (void*)core->keyboard, "keyboard", core->keyboard->getType());

		// Mouse
		lualove_push_global_pointer(L, (void*)core->mouse, "mouse", core->mouse->getType());

		// GL Wrapper
		lualove_push_global_pointer(L, (void*)gl.get(), "gl", gl->getType());

		// Text
		lualove_push_global_pointer(L, (void*)text.get(), "text", text->getType());

		// @todo Push mouse, keyboard, timer

		// Push globals
		//lualove_create_table(L, "key");
		lualove_push_all_globals(L);

		// Load test stuff from zip file
		//lualove_load(L, core->filesystem->getFile("data/test.zip", "global.lua"));

		// Load entry file
		//lualove_load(L, "data/games/"+dir+"/entry.lua");
		//lualove_load(L, "data/games/"+dir+"/bullet.lua");
		lualove_load(L, core->filesystem->getFile(source, "entry.lua"));
	

		// Add default Game State
		gameStates.create("sys_gs_main", new LuaGameState(L, "main"));
		currentGameState = gameStates["sys_gs_main"].get();

		// Check which functions are available
		// @todo Make simpler constants.
		currentGameState->init();

		//lualove_check_functions(L, this, LOVE_METHOD_ALL);

		// Call init
		//if(isAvailable(LOVE_METHOD_INIT))
		//	lualove_call_init_noarg(L, this);

		// Init all states
		for(gameStates.begin(); !gameStates.end(); gameStates.next())
		{
			if(gameStates.key() != "sys_gs_main")
				gameStates.value()->init();
		}

		// Init ALL Actors
		for(obj.actors.begin(); !obj.actors.end(); obj.actors.next())
			obj.actors.value()->init();

		loaded = true;

		return LOVE_OK;
	}

	void LuaGame::unload()
	{
		// End Lua-state
		lua_close(L);
		lualove_close(L);

		// Remove elements.
		obj.loadables.clear();

		//files.clear();
		obj.abstractImages.clear();
		obj.sprites.clear();
		//sounds.clear();
		obj.fonts.clear();
		obj.colors.clear();
		obj.frameAnimations.clear();
		included.clear();
		gameStates.clear();

		// clear color data
		core->graphics->setBackground(0,0,0);
		core->graphics->setColor(255,255,255);
		// set the font as default
		pFont defaultFont(new Font(core->filesystem->getBaseFile("data/fonts/FreeSans.ttf"), 14));
		defaultFont->load();
		core->graphics->setFont(defaultFont);

		//remove gui items
		core->gui->remove(gui);

		loaded = false;
	}

	void LuaGame::render()
	{
		glEnable(GL_TEXTURE_2D);
		glPushAttrib(GL_CURRENT_BIT);
		glColor3ub(255,255,255);

		// Render ALL Actors
		for(obj.actors.begin(); !obj.actors.end(); obj.actors.next())
			obj.actors.value()->render();


		// Render ALL Particles
		for(obj.particleEmitters.begin(); !obj.particleEmitters.end(); obj.particleEmitters.next())
			obj.particleEmitters.value()->render();


		//if(isAvailable(LOVE_METHOD_RENDER))
		//lualove_call_render_noarg(L, this);
		currentGameState->render();

		glPopAttrib();
		
		//zimg->render();

	}

	void LuaGame::update(float dt)
	{

		// Update ALL Actors
		for(obj.actors.begin(); !obj.actors.end(); obj.actors.next())
			obj.actors.value()->update(dt);

		// Update ALL Particles
		for(obj.particleEmitters.begin(); !obj.particleEmitters.end(); obj.particleEmitters.next())
			obj.particleEmitters.value()->update(dt);

		// Update ALL FrameAnimations
		for(obj.frameAnimations.begin(); !obj.frameAnimations.end(); obj.frameAnimations.next())
			obj.frameAnimations.value()->update(dt);

		// Call update
		//if(isAvailable(LOVE_METHOD_UPDATE))
		//	lualove_call_update_noarg(L, this, dt);
		currentGameState->update(dt);



	}

	void LuaGame::suspend()
	{
		// Stop all playing audio
		core->audio->stop();
		Game::suspend();
	}

	void LuaGame::resume()
	{
		Game::resume();
		// this is removed because it conflicts with the recent changes
		//glClearColor((float)core->graphics->background->getRed()/255.0f, (float)core->graphics->background->getGreen()/255.0f, (float)core->graphics->background->getBlue()/255.0f, 1.0f);
	}

	void LuaGame::reloadGraphics()
	{

		for(obj.abstractImages.begin(); !obj.abstractImages.end(); obj.abstractImages.next())
			obj.abstractImages.value()->load();

		for(obj.fonts.begin(); !obj.fonts.end(); obj.fonts.next())
			obj.fonts.value()->load();
	}

	bool LuaGame::fileExists(const string & file)
	{
		bool flag = false;
	
		fstream fin;
		fin.open(file.c_str(),ios::in);

		if(fin.is_open())
			flag=true;

		fin.close();

		return flag;
	}

	void LuaGame::keyPressed(int key)
	{
		//if(isAvailable(LOVE_METHOD_KEYPRESSED))
		//	lualove_call_keypressed_noarg(L, this, key);
		currentGameState->keyPressed(key);
	}

	void LuaGame::keyReleased(int key)
	{
		//if(isAvailable(LOVE_METHOD_KEYRELEASED))
		//	lualove_call_keyreleased_noarg(L, this, key);
		currentGameState->keyReleased(key);
	}

	void LuaGame::mousePressed(float x, float y, int button)
	{
		//if(isAvailable(LOVE_METHOD_MOUSEPRESSED))
		//	lualove_call_mousepressed_noarg(L, this, x, y, button);
		currentGameState->mousePressed(x, y, button);
	}

	void LuaGame::mouseReleased(float x, float y, int button)
	{
		//if(isAvailable(LOVE_METHOD_MOUSERELEASED))
		//	lualove_call_mousereleased_noarg(L, this, x, y, button);
		currentGameState->mouseReleased(x, y, button);
	}

	void LuaGame::eventFired(pEvent e)
	{
		switch(e->getType())
		{
		case EventListener::LOVE_EVENT_MESSAGE:
			pMessageEvent pme = dynamic_pointer_cast<MessageEvent, Event>(e);
			printf("Event: %s\n", pme->getMessage().c_str());
			break;
		}

		// Must pass this on to Lua, like this:
		// luaPushPointer(L, (void*)e.get(), script_types_lookup[e.getType()], 0);
		// global_script->eventFired(L, (void*)e.get(), e.getType());
	}

	void LuaGame::say(const char * str)
	{
		printf(str);
	}

	Vector * LuaGame::createVector(const char * str, float x, float y)
	{
		pvex.reset<Vector>(new Vector(x, y));
		printf("\nCreated vextor: %s(%f, %f)\n", str, x, y);
		return pvex.get();
	}

	bool LuaGame::luaIsFunction(const string & tablename, const string & functionname)
	{

		bool result = false;

		lua_pushstring(L, tablename.c_str());
		lua_rawget(L, LUA_GLOBALSINDEX);

		if(lua_istable(L, -1))
		{
			lua_pushstring(L, functionname.c_str());
			lua_rawget(L, -2);
			result = lua_isfunction(L, -1);
			lua_pop(L, 2);
		}else
		{
			lua_pop(L, 1);
		}

		return result;
	}

	void LuaGame::luaCheckErr(int status)
	{
		if(status != 0)
		{
			printf("\nLua error: %s\n", lua_tostring(L, -1));
			lua_pop(L, 1); // remove error message
		}
	}

	

	void LuaGame::addFile(const char * filename)
	{
		//string fn = "data/games/" + this->dir + "/" + string(filename);
		
		//if(fileExists(fn))
		//{
			printf("Adding file: %s\n", filename);
			//files.create(fn, new LuaFile(fn));
			//lualove_load(L, fn);
			lualove_load(L, core->filesystem->getFile(source, string(filename)));
		//}

	}

	void LuaGame::include(const char * filename)
	{
		string key = getPath(filename);

		// If file already is included, return
		if(included.find(key) != included.end())
			return;

		// File is not already included. Include.
		//lualove_load(L, key);
		lualove_load(L, core->filesystem->getFile(source, string(filename)));

		// Mark as included
		included[key] = true;

	}

	void LuaGame::addState(const char * key)
	{
		gameStates.create(string(key), new LuaGameState(this->L, string(key)));
	}

	void LuaGame::removeState(const char * key)
	{
		gameStates.erase(string(key));
	}

	void LuaGame::setState(const char * key)
	{
		currentGameState = gameStates[key].get();
	}

	/**
	* Image methods
	**/

	AbstractImage * LuaGame::addImage(const char * key, const char * filename)
	{

		// Get new file from filesystem
		AbstractFile * file = core->filesystem->getFile(source, string(filename));

		// Create new image file
		AbstractImage * img = core->imaging->getImage(file);

		pAbstractImage i(img);
		i->load();

		obj.abstractImages[key] = i;
		obj.sprites[key] = i;

		return i.get();
	}

	pAbstractImage LuaGame::addImage(const char * filename)
	{

		// Get new file from filesystem
		AbstractFile * file = core->filesystem->getFile(source, string(filename));

		// Create new image file
		AbstractImage * img = core->imaging->getImage(file);
		pAbstractImage p(img);

		return p;
	}

	AbstractImage * LuaGame::getImage(const char * key)
	{
		return obj.abstractImages[key].get();
	}

	void LuaGame::removeImage(const char * key)
	{
		obj.abstractImages.erase(key);
	}

	/*void LuaGame::delImage(const char * key)
	{
		obj.abstractImages.erase(key);
	}*/

	bool LuaGame::isImage(const char * key)
	{
		return obj.abstractImages.contains(key);
	}

	void LuaGame::listImages()
	{
		printf("Images: \n");

		for(obj.abstractImages.begin() ; !obj.abstractImages.end() ; obj.abstractImages.next())
		{
			printf("%s \n", obj.abstractImages.key().c_str());
		}
	}

	void LuaGame::drawSprite(const pAbstractImage & sprite, float x, float y) const
	{
		glPushMatrix();
		glTranslatef(x, y, 0);
		sprite->render();
		glPopMatrix();
	}

	void LuaGame::drawSprite(const pAbstractImage & sprite) const
	{
		sprite->render();
	}

	/**
	* Frame animation methods
	

	FrameAnimation * LuaGame::addFrameAnimation(const char * key, const char * image)
	{
		// Verify that image exists.
		if(!isImage(image))
			return 0;

		// Create new object
		pFrameAnimation f(new FrameAnimation(getImage(image)));

		obj.frameAnimations[key] = f;
		return f.get();
	}

	FrameAnimation * LuaGame::addFrameAnimation(const char * key, AbstractImage * image)
	{
		// Verify that image exists.
		if(image == 0)
			return 0;

		// Create new object
		pFrameAnimation f(new FrameAnimation(image));

		obj.frameAnimations[key] = f;
		return f.get();
	}

	FrameAnimation * LuaGame::getFrameAnimation(const char * key)
	{
		return obj.frameAnimations[key].get();
	}

	void LuaGame::removeFrameAnimation(const char * key)
	{
		obj.frameAnimations.erase(key);
	}

	bool LuaGame::isFrameAnimation(const char * key)
	{
		return obj.frameAnimations.contains(key);
	}

	**/

	/*Actor * LuaGame::addActor(const char * key)
	{
		pActor f(new Actor(L, &obj.sprites));
		obj.actors[key] = f;
		return f.get();
	}*/

	Actor * LuaGame::addActor(const char * key, const char * scriptname)
	{
		pActor f(new Actor(L, &obj.sprites, scriptname));
		obj.actors[key] = f;
		return f.get();
	}

	Actor * LuaGame::getActor(const char * key)
	{
		return obj.actors[key].get();
	}

	void LuaGame::removeActor(const char * key)
	{
		obj.actors.erase(key);
	}

	bool LuaGame::isActor(const char * key)
	{
		return obj.actors.contains(key);
	}

	ParticleEmitter * LuaGame::addParticleEmitter(const char * key, float delay, int mode)
	{
		pParticleEmitter f(new ParticleEmitter(L, &obj.sprites));
		f->setDelay(delay);
		f->setMode(mode);
		obj.particleEmitters[key] = f;
		return f.get();
	}

	/**
	* Color methods
	**/

	Color * LuaGame::addColor(const char * key, int r, int g, int b, int a)
	{
		obj.colors[key].reset<Color>(new Color(r, g, b, a));
		return obj.colors[key].get();
	}

	/*Color * LuaGame::addColor(const char * key, int r, int g, int b)
	{
		obj.colors[key].reset<Color>(new Color(r, g, b));
		return obj.colors[key].get();
	}*/

	Color * LuaGame::addColor(const char * key, int hex)
	{
		obj.colors[key].reset<Color>(new Color(hex));
		return obj.colors[key].get();
	}

	Color * LuaGame::getColor(const char * key)
	{
		return obj.colors[key].get();
	}

	void LuaGame::setColor(Color * color)
	{
		this->currentColor = color;
	}

	void LuaGame::setColor(const char * key)
	{
		this->currentColor = obj.colors[key].get();
	}

	void LuaGame::setBackground(Color * color)
	{
		backgroundColor = color;
		glClearColor((float)backgroundColor->getRed()/255.0f, (float)backgroundColor->getGreen()/255.0f, (float)backgroundColor->getBlue()/255.0f, 1.0f);
	}

	void LuaGame::setBackground(const char * key)
	{
		Color * color = obj.colors[key].get();
		backgroundColor = color;
		glClearColor((float)backgroundColor->getRed()/255.0f, (float)backgroundColor->getGreen()/255.0f, (float)backgroundColor->getBlue()/255.0f, 1.0f);
	}


	/**
	* Text methods
	**/

	void LuaGame::print(float x, float y, const char * c)
	{
		glPushAttrib(GL_CURRENT_BIT);

		glColor3ub(currentColor->getRed(), currentColor->getGreen(), currentColor->getBlue());
		glTranslatef(x, y, 0);
		currentFont->print(c);
		glTranslatef(-x, -y, 0);

		glPopAttrib();
		glEnable(GL_TEXTURE_2D);
	}

	Font * LuaGame::addFont(const char * key, int size)
	{
		obj.fonts[key].reset<Font>(new Font(core->filesystem->getBaseFile("data/fonts/FreeSans.ttf"), size));
		obj.fonts[key].get()->load();
		return obj.fonts[key].get();
	}

	Font * LuaGame::addFont(const char * key, const char * fontfile, int size)
	{
		obj.fonts[key].reset<Font>(new Font(core->filesystem->getFile(source, string(fontfile)), size));
		obj.fonts[key].get()->load();
		return obj.fonts[key].get();
	}

	Font * LuaGame::getFont(const char * key)
	{
		return obj.fonts[key].get();
	}

	void LuaGame::drawString(int x, int y, const char * str)
	{
		glPushAttrib(GL_CURRENT_BIT);

		glColor3ub(currentColor->getRed(), currentColor->getGreen(), currentColor->getBlue());
		glTranslatef((float)x, (float)y, 0);
		currentFont->print(str);
		glTranslatef(-(float)x, -(float)y, 0);

		glPopAttrib();
		glEnable(GL_TEXTURE_2D);
	}

	void LuaGame::setFont(const char * key)
	{
		currentFont = obj.fonts[key].get();
	}

	void LuaGame::setFont(Font * font)
	{
		currentFont = font;
	}

	void LuaGame::setRotation(float rotation)
	{
		this->rotation = rotation;
	}

	float LuaGame::getRotation()
	{
		return rotation;
	}

	// Basic Shapes
	void LuaGame::drawLine(float x1, float y1, float x2, float y2, float lineWidth)
	{
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_MULTISAMPLE);

		glColor4ub(currentColor->getRed(), currentColor->getGreen(), currentColor->getBlue(), currentColor->getAlpha());
		glLineWidth(lineWidth);
		
		glTranslatef((x1+x2)/2, (y1+y2)/2, 0.0f);
		glRotatef(rotation,0.0f,0.0f,1.0f);
		glTranslatef(-(x1+x2)/2, -(y1+y2)/2, 0.0f);

		glBegin(GL_LINES);
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
		glEnd();

		glDisable(GL_MULTISAMPLE);
		//glEnable(GL_TEXTURE_2D); //enabled elsewhere
		glPopAttrib();
		glPopMatrix();
	}

	void LuaGame::drawTriangle(float x, float y, float width, float height, float lineWidth)
	{
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_MULTISAMPLE);

		glColor4ub(currentColor->getRed(), currentColor->getGreen(), currentColor->getBlue(), currentColor->getAlpha());
		glLineWidth(lineWidth);
		glTranslatef(x,y,0.0f);
		glRotatef(rotation,0.0f,0.0f,1.0f);
		glBegin(GL_LINE_LOOP);
			glVertex2f(-(width/2),(height/2));
			glVertex2f(0,-(height/2));
			glVertex2f((width/2),(height/2));
		glEnd();

		glDisable(GL_MULTISAMPLE);
		//glEnable(GL_TEXTURE_2D); //enabled elsewhere
		glPopAttrib();
		glPopMatrix();
	}

	void LuaGame::fillTriangle(float x, float y, float width, float height)
	{
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_MULTISAMPLE);

		glColor4ub(currentColor->getRed(), currentColor->getGreen(), currentColor->getBlue(), currentColor->getAlpha());
		//glLineWidth(lineWidth);
		glTranslatef(x,y,0.0f);
		glRotatef(rotation,0.0f,0.0f,1.0f);
		glBegin(GL_TRIANGLES);
			glVertex2f(-(width/2),(height/2));
			glVertex2f((width/2),(height/2));
			glVertex2f(0,-(height/2));
		glEnd();

		glDisable(GL_MULTISAMPLE);
		//glEnable(GL_TEXTURE_2D); //enabled elsewhere
		glPopAttrib();
		glPopMatrix();
	}

	void LuaGame::drawRect(float x, float y, float width, float height, float lineWidth)
	{
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_MULTISAMPLE);

		glColor4ub(currentColor->getRed(), currentColor->getGreen(), currentColor->getBlue(), currentColor->getAlpha());
		glLineWidth(lineWidth);
		glTranslatef(x,y,0.0f);
		glRotatef(rotation,0.0f,0.0f,1.0f);
		glBegin(GL_LINE_LOOP);
			glVertex2f(-(width/2),-(height/2));
			glVertex2f(-(width/2),(height/2));
			glVertex2f((width/2),(height/2));
			glVertex2f((width/2),-(height/2));
		glEnd();

		glDisable(GL_MULTISAMPLE);
		//glEnable(GL_TEXTURE_2D); //enabled elsewhere
		glPopAttrib();
		glPopMatrix();
	}

	void LuaGame::fillRect(float x, float y, float width, float height)
	{
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_MULTISAMPLE);

		glColor4ub(currentColor->getRed(), currentColor->getGreen(), currentColor->getBlue(), currentColor->getAlpha());
		//glLineWidth(lineWidth);
		glTranslatef(x,y,0.0f);
		glRotatef(rotation,0.0f,0.0f,1.0f);
		glBegin(GL_QUADS);
			glVertex2f(-(width/2),-(height/2));
			glVertex2f(-(width/2),(height/2));
			glVertex2f((width/2),(height/2));
			glVertex2f((width/2),-(height/2));
		glEnd();

		glDisable(GL_MULTISAMPLE);
		//glEnable(GL_TEXTURE_2D); //enabled elsewhere
		glPopAttrib();
		glPopMatrix();
	}

	void LuaGame::drawCircle(float x, float y, float radius, int points, float lineWidth)
	{
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_MULTISAMPLE);

		glColor4ub(currentColor->getRed(), currentColor->getGreen(), currentColor->getBlue(), currentColor->getAlpha());
		glLineWidth(lineWidth);
		glTranslatef(x,y,0.0f);
		glRotatef(rotation,0.0f,0.0f,1.0f);

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i != points; i++)
		{
			float degInRad = (float)(i * (3.14159/(points / 2)));
			glVertex2f(cos(degInRad)*radius, sin(degInRad)*radius);
		}
		glEnd();

		glDisable(GL_MULTISAMPLE);
		//glEnable(GL_TEXTURE_2D); //enabled elsewhere
		glPopAttrib();
		glPopMatrix();
	}

	void LuaGame::fillCircle(float x, float y, float radius, int points)
	{
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_MULTISAMPLE);

		glColor4ub(currentColor->getRed(), currentColor->getGreen(), currentColor->getBlue(), currentColor->getAlpha());
		glTranslatef(x,y,0.0f);
		glRotatef(rotation,0.0f,0.0f,1.0f);

		float x1 = 0;
		float y1 = 0;
		float x2 = 0;
		float y2 = 0;
 
		glBegin(GL_TRIANGLES);
		for (int i = 0; i <= points; i++)
		{
			float degInRad = (float)(i * (3.14159/(points / 2)));
			x2 = cos(degInRad)*radius;
			y2 = sin(degInRad)*radius;
			glVertex2f(0.0f,0.0f);
			glVertex2f(x2,y2);
			glVertex2f(x1,y1);
			x1 = x2;
			y1 = y2;
		}
		glEnd();

		glDisable(GL_MULTISAMPLE);
		//glEnable(GL_TEXTURE_2D); //enabled elsewhere
		glPopAttrib();
		glPopMatrix();
	}

	/**
	 * Sounds
	 **/

	AbstractSound * LuaGame::addSound(const char * key, const char * filename)
	{

		// Get new file from filesystem
		AbstractFile * file = core->filesystem->getFile(source, string(filename));

		// Get new sound from audio device.
		AbstractSound * sound = core->audio->getSound(file);

		obj.sounds[key].reset<AbstractSound>(sound);
		obj.sounds[key].get()->load();
		return obj.sounds[key].get();
	}

	AbstractSound * LuaGame::getSound(const char * key)
	{
		return obj.sounds[key].get();
	}

	void LuaGame::stopAllSounds(float seconds)
	{
		//Mix_HaltChannel(-1);
		Mix_FadeOutChannel(-1, (int)(seconds * 1000));
	}

	void LuaGame::pauseAllSounds()
	{
		Mix_Pause(-1);
	}

	void LuaGame::resumeAllSounds()
	{
		Mix_Resume(-1);
	}

	/**
	 * Music
	 **/

	AbstractMusic * LuaGame::addMusic(const char * key, const char * filename)
	{

		// Get new file from filesystem
		AbstractFile * file = core->filesystem->getFile(source, string(filename));

		// Get new music from audio device.
		AbstractMusic * music = core->audio->getMusic(file);

		obj.music[key].reset<AbstractMusic>(music);
		obj.music[key].get()->load();
		return obj.music[key].get();
	}

	AbstractMusic * LuaGame::getMusic(const char * key)
	{
		return obj.music[key].get();
	}



}// love

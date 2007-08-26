
#ifndef FONT_TEX_GAME_PONG_GAME_H
#define FONT_TEX_GAME_PONG_GAME_H


// LOVE
#include "Game.h"
#include "Font.h"
#include "Text.h"
#include "SmoothAnimatedColor.h"
#include "ImageFromFile.h"
#include "FrameAnimation.h"
#include "Loader.h"
#include "LoadListener.h"
#include "ConfigLoader.h"
#include "Actor.h"
#include "Particle.h"
#include "ParticleEmitter.h"

#include "Sound.h"
#include "Music.h"

#include "AnimatedColor.h"

#include "GUIText.h"
#include "Menu.h"

#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <guichan/opengl.hpp>
#include <guichan/opengl/openglsdlimageloader.hpp>

// STL
#include <string>
#include <map>
#include <vector>

using std::map;
using std::vector;
using std::string;

using namespace love;

/**
* @brief FontTexGame 
* @version 1.0
* @since 1.0
* @author Anders Ruud
* @date 2006-09-01
* @brief 
**/
class FontTexGame : public love::Game
{
private:

gcn::OpenGLGraphics* graphics;           // Graphics driver
gcn::OpenGLSDLImageLoader* imageLoader;  // For loading images

/*
 * Guichan stuff we need
 */
gcn::Gui* gui;            // A Gui object - binds it all together
gcn::Font* font;     // A font
gcn::SDLInput* input;

/*
 * All of the default widgets
 */

//Menu * top;
Menu *menu;
Label *lovelabel;
AnimatedColor * shiny;
AnimatedColor * alsoshiny;
gcn::Container* top;                 // A top container
gcn::Label* label;                   // A label
gcn::Icon* icon;                     // An icon (image)
gcn::Button* button;                 // A button
gcn::TextField* textField;           // One-line text field
gcn::TextBox* textBox;               // Multi-line text box
gcn::ScrollArea* textBoxScrollArea;  // Scroll area for the text box
gcn::ListBox* listBox;               // A list box
gcn::DropDown* dropDown;             // Drop down
gcn::CheckBox* checkBox1;            // Two checkboxes
gcn::CheckBox* checkBox2;
gcn::RadioButton* radioButton1;      // Three radio buttons
gcn::RadioButton* radioButton2;
gcn::RadioButton* radioButton3;
gcn::Slider* slider;                 // A slider
gcn::Image *image;                   // An image for the icon
gcn::Window *window;
gcn::Image *darkbitsImage;
gcn::Icon* darkbitsIcon;
gcn::ScrollArea* nestedScrollArea;
gcn::Container* nestedContainer;
gcn::Slider* nestedSlider;

love::Font * lovefont;
Color * lovecolor;

//sounds shit
public:


	/**
	* @brief Creates a new FontTexGame object.
	**/
	FontTexGame();

	~FontTexGame();

	/**
	* @brief Initializes the game.
	**/
	int init();

	/**
	* @brief Renders the entire game once.
	**/
	void render();

	/**
	* @brief Updates the entire game.
	* @param dt The time since last frame (in seconds).
	**/
	void update(float dt);

	int load();
	void unload();

	/**
	* @brief Called when a key is pressed.
	* @param key The ASCII key code.
	**/
	void keyPressed(int key);

	void reloadGraphics();

};

#endif

/**
* @file GUIGameList2.h
* @author Anders Ruud
* @date 2007-05-14
* @brief Contains definition for class GUIGameList2.
**/

#ifndef LOVE_GUI_GAME_LIST_2_H
#define LOVE_GUI_GAME_LIST_2_H

// LOVE
#include "GUIEntity.h"
#include "GUIGameListElement.h"
#include "Vector.h"


// STL
#include <vector>

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	class Game;
	class EventListener;

	/**
	* @class GUIGameList2
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-05-14
	* @brief 
	**/

	class GUIGameList2 : public GUIEntity
	{
	private:


		/**
		* @brief Scale function.
		**/
		float scale(float t);


		int viewport_size;

		// Position function
		Vector position(float t);

		// Alpha function
		float buttonalpha(float t);
		float alpha(float t);


		float getT(int i);

		float center_t;

		float viewport_max;
		float viewport_min;



	public:

		float viewport;
		float space_t;
		int size;


		// Seeking
		bool seeking;
		bool seekDeltaReached;
		float seekSrc;
		float seekDest;
		float seekDelta;
		float seekDeltaMid;
		float seekAcc;

		float d1;
		float d2;
		int speedFlip;

		float radius;

		float seekTime;
		float seekMax;

		// Current game index
		int ci;


		// games
		std::vector<GUIGameListElement> gameListElements;

		float step;



		/**
		* @brief Contructs an empty GUIGameList2.
		**/
		GUIGameList2();
		virtual ~GUIGameList2();

		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(float x, float y, int button);

		/**
		* @brief Gets games.
		* @return games.
		**/
		std::vector<GUIGameListElement> & getGameListElements();


		void addGameListElement(GUIGameListElement e);

		void next(float speed = 0.2f);
		void previous(float speed = 0.2f);

		int sign(float n);
		float shortest(float a1, float a2);


		void seek(float t, float time = 0.5f);
		bool seekGame(const std::string & game, float time = 0.5f);
		float getCurrentPosition();

		float reverse(float angle);

		float clampa(float angle);

		float angleFunc(float t);

		void setViewport(float t);


		/**
		* @brief Speed function
		* @param t 0 = start, 1 = end
		**/
		float speedFunc(float t);


		void setSpeed(float speed);
		float getSpeed() const;

		void update(float dt);
		void render();

		float getStep() const;

		int load();
		void unload();
		void setSpacing(float st);

	};

	typedef boost::shared_ptr<GUIGameList2> pGUIGameList2;

} // love

#endif


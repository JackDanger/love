/**
* @file GUIGameList.h
* @author Anders Ruud
* @date 2007-05-14
* @brief Contains definition for class GUIGameList.
**/

#ifndef LOVE_GUIGAMELIST_H
#define LOVE_GUIGAMELIST_H

// LOVE
#include "GUIEntity.h"
#include "GUIGameListElement.h"


// STL
#include <vector>

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	class Game;
	class EventListener;

	/**
	* @class GUIGameList
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-05-14
	* @brief 
	**/

	class GUIGameList : public GUIEntity
	{
	private:


		/**
		* @brief Scale function.
		**/
		float scale(float angle);



	public:


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
		* @brief Contructs an empty GUIGameList.
		**/
		GUIGameList();
		virtual ~GUIGameList();

		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(float x, float y, int button);

		/**
		* @brief Gets games.
		* @return games.
		**/
		std::vector<GUIGameListElement> & getGameListElements();


		void addGameListElement(GUIGameListElement e);

		void next();
		void previous();

		int sign(float n);
		float shortest(float a1, float a2);


		void seek(float angle, float seekMax = 0.5f);
		float reverse(float angle);

		

		float clampa(float angle);

		float angleFunc(float t);


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

	};

	typedef boost::shared_ptr<GUIGameList> pGUIGameList;

} // love

#endif


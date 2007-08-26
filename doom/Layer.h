/**
* @file Layer.h
* @author Anders Ruud
* @date 2006-02-07
* @brief Contains definition for class Layer.
**/

#ifndef LOVE_LAYER_H
#define LOVE_LAYER_H

#include "Entity.h"

namespace love
{


	/**
	* @class Layer
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-02-07
	* @brief The top superclass of all Layer types in the engine.
	* 
	* Every element in the engine that are considered to be a 
	* layer inherits from this class. Note that the class is abstract
	* and contains code that apply to <i>all</i> layers only. 
	**/
	class Layer : public Entity
	{

	private:
	protected:

		// Where the rendering should start.
		float xOffset;
		float yOffset;

		// On which axis the layer should repeat it's rendering.
		bool xRepeat;
		bool yRepeat;

	public:
		/**
		* @brief Creates a new Layer object.
		**/
		Layer();

		virtual ~Layer();

		/**
		* @brief Renders the Layer once.
		**/
		virtual void render();

		/**
		* @brief Updates the Layer.
		**/
		virtual void update(float dt);

		/**
		* @fn getOffsetX()
		* @brief Checks the offset on the y-axis.
		* @return Offset on the x-axis.
		**/
		float getOffsetX();

		/**
		* @fn getOffsetY()
		* @brief Checks the offset on the y-axis.
		* @return Offset on the y-axis.
		**/
		float getOffsetY();

		/**
		* @fn isRepeatingX()
		* @brief Checks if a Layer is currently repeating.
		* @return Whether or not this Layer is repeating it's
		* rendering along the x-axis.
		**/
		bool isRepeatingX();

		/**
		* @fn isRepeatingY()
		* @brief Checks if a Layer is currently repeating.
		* @return Whether or not this Layer is repeating it's
		* rendering along the y-axis.
		**/
		bool isRepeatingY();

		};

	typedef boost::shared_ptr<Layer> pLayer;
}// love

#endif
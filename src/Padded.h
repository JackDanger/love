#ifndef LOVE_PADDED_H
#define LOVE_PADDED_H

namespace love
{
	/**
	 * @class Padded
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2007-08-16
	 * @brief A class used heavily by GUI items as it handles the concept of padding. Padding is used
	 *        between the edge of the menu item and the content.
	 **/
	class Padded
	{
	private:
		int top;
		int bottom;
		int right;
		int left;

	public:
		/**
		 * @brief Default constructor. Initializes the values as 0.
		 **/
		Padded();

		/**
		 * @brief Default deconstructor. Does nothing.
		 **/
		virtual ~Padded();

		/**
		 * @param top Padding on the top side.
		 * @param right Padding on the right side.
		 * @param bottom Padding on the bottom side.
		 * @param left Padding on the left side.
		 * @brief Sets the padding of all the sides separately.
		 **/
		virtual void setPadding(int top, int right, int bottom, int left);

		/**
		 * @param horizontal Padding on the horizontal sides (top and bottom).
		 * @param vertical Padding on the vertical sides (left and right).
		 * @brief Sets the padding on the sets of sides.
		 **/
		virtual void setPadding(int horizontal, int vertical);

		/**
		 * @param padding Padding on all the sides.
		 * @brief Sets the padding on all the sides.
		 **/
		virtual void setPadding(int padding);

		/**
		 * @param top Padding on the top side.
		 * @brief Sets the padding on the top side.
		 **/
		virtual void setPaddingTop(int top);

		/**
		 * @param right Padding on the right side.
		 * @brief Sets the padding on the right side.
		 **/
		virtual void setPaddingRight(int right);

		/**
		 * @param bottom Padding on the bottom side.
		 * @brief Sets the padding on the bottom side.
		 **/
		virtual void setPaddingBottom(int bottom);

		/**
		 * @param left Padding on the left side.
		 * @brief Sets the padding on the left side.
		 **/
		virtual void setPaddingLeft(int left);

		/**
		 * @return The amount of padding.
		 * @brief Gets the padding on the top side.
		 **/
		virtual int getPaddingTop();

		/**
		 * @return The amount of padding.
		 * @brief Gets the padding on the right side.
		 **/
		virtual int getPaddingRight();

		/**
		 * @return The amount of padding.
		 * @brief Gets the padding on the bottom side.
		 **/
		virtual int getPaddingBottom();

		/**
		 * @return The amount of padding.
		 * @brief Gets the padding on the left side.
		 **/
		virtual int getPaddingLeft();
	};

	//typedef boost::shared_ptr<Padded> pPadded; //not really needed, eh?
}

#endif
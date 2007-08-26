
#ifndef LOVE_INDENTIFIABLE_H
#define LOVE_INDENTIFIABLE_H

namespace love
{
	/**
	* @class Identifiable
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-08-05
	* @brief
	**/
	class Identifiable
	{

	private:
		static int nextId;
	protected:
		
		// The id of the object.
		int id;

		// The id of the class.
		int type;

		/**
		* @brief Get the next available id.
		* @return The next id.
		**/
		static int getNextId();

	public:		
		
		Identifiable();
		virtual ~Identifiable();

		int getId() const;


	};

}

#endif

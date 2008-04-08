/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_OPENGL_CONSOLE_H
#define LOVE_OPENGL_CONSOLE_H

#include <vector>
#include "Image.h"

namespace love_opengl
{
	class Console;

	class ConsoleElement
	{
		friend class Console;
	protected:
		std::vector<ConsoleElement *> children;
	public:
		virtual ~ConsoleElement();
		virtual int getHeight() const = 0;
		virtual bool draw(int x, int y, int level, Console * c) const = 0;
		void add(ConsoleElement * e);
		bool outside(int y, Console * c) const;
	};

	class ConsoleRoot : public ConsoleElement
	{
		friend class Console;
	public:
		int getHeight() const;
		bool draw(int x, int y, int level, Console * c) const;
	};

	class ConsoleString : public ConsoleElement
	{
	private:
		std::string str;
	public:
		ConsoleString(std::string str);
		int getHeight() const;
		bool draw(int x, int y, int level, Console * c) const;
	};

	class ConsoleBox : public ConsoleElement
	{
	public:
		static const int PADDING = 5;
		int getHeight() const;
		bool draw(int x, int y, int level, Console * c) const;
		virtual void setColor() const;
	};

	class ConsoleError : public ConsoleBox
	{
	public:
		void setColor() const;
	};

	class ConsoleImage : public ConsoleElement
	{
	private:
		pImage image;
	public:
		ConsoleImage(pImage image);
		int getHeight() const;
		bool draw(int x, int y, int level, Console * c) const;
	};

	class Console
	{
	private:
		
		// List of ConsoleElements currently in the console.
		ConsoleRoot * root;

		int width, height;

		// The current-parent stack. Whatever back() returns should
		// get the children.
		std::vector<ConsoleElement *> current_parent;

	public:

		static const int LINE_HEIGHT = 12;

		Console(int width, int height);
		~Console();

		void resize(int width, int height);

		int getWidth() const;
		int getHeight() const;

		void push_error();
		void push_box();
		void push(ConsoleElement * e);
		void pop();

		void add(const std::string & str);
		void add(pImage image);
		void add(ConsoleElement * e);
		void draw(int x, int y);
	};

} // love_opengl

#endif

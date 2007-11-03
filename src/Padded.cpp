#include "Padded.h"

namespace love
{
	Padded::Padded()
	{
		top = 0;
		right = 0;
		bottom = 0;
		left = 0;
	}

	Padded::~Padded()
	{ }

	void Padded::setPadding(int top, int right, int bottom, int left)
	{
		this->top = top;
		this->right = right;
		this->bottom = bottom;
		this->left = left;
	}

	void Padded::setPadding(int horizontal, int vertical)
	{
		this->top = horizontal;
		this->bottom = horizontal;
		this->right = vertical;
		this->left = vertical;
	}

	void Padded::setPadding(int padding)
	{
		this->top = padding;
		this->right = padding;
		this->bottom = padding;
		this->left = padding;
	}

	void Padded::setPaddingTop(int top)
	{
		this->top = top;
	}

	void Padded::setPaddingRight(int right)
	{
		this->right = right;
	}

	void Padded::setPaddingBottom(int bottom)
	{
		this->bottom = bottom;
	}

	void Padded::setPaddingLeft(int left)
	{
		this->left = left;
	}

	int Padded::getPaddingTop()
	{
		return top;
	}

	int Padded::getPaddingRight()
	{
		return right;
	}

	int Padded::getPaddingBottom()
	{
		return bottom;
	}

	int Padded::getPaddingLeft()
	{
		return left;
	}
}

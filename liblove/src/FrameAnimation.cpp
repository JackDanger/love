#include "FrameAnimation.h"
#include "love.h"

namespace love
{


	FrameAnimation::FrameAnimation() : timeBuffer(0), cfi(0), running(false)
	{
		setType(LOVE_TYPE_FRAME_ANIMATION);
	}

	FrameAnimation::FrameAnimation(AbstractImage * image) : image(image), timeBuffer(0), cfi(0), running(false)
	{
		setType(LOVE_TYPE_FRAME_ANIMATION);
	}

	FrameAnimation::~FrameAnimation()
	{

	}

	void FrameAnimation::addFrame(float x, float y, float width, float height, float post_delay)
	{
		frame f;
		f.x				= x;
		f.y				= y;
		f.width			= width;
		f.height		= height;
		f.post_delay	= post_delay;

		frames.push_back(f);
	}

	void FrameAnimation::addFrames(int sizex, int sizey, float width, float height, float post_delay)
	{

		for(int i = 0;i<sizey;i++)
		{
			for(int j=0;j<sizex;j++)
			{
				frame f;
				f.x				= width * j;
				f.y				= height * i;
				f.width			= width;
				f.height		= height;
				f.post_delay	= post_delay;

				frames.push_back(f);
			}
		}
	}


	void FrameAnimation::start()
	{
		running = true;
	}

	void FrameAnimation::stop()
	{
		running = false;
	}

	void FrameAnimation::delay(float t)
	{
		this->timeBuffer -= t;
	}

	void FrameAnimation::bind()
	{
	}

	void FrameAnimation::beginRender()
	{
		image->beginRender();
	}

	void FrameAnimation::sendVertices()
	{
		if(frames.size() <= 0)
			return;

		frame f = frames[cfi];
		image->sendVertices(f.x, f.y, f.width, f.height);
	}

	void FrameAnimation::endRender()
	{
		image->endRender();
	}

	renderinfo FrameAnimation::getRenderInfo()
	{
		if(frames.size() <= 0)
		{
			renderinfo r;
			r.wTex = 0;
			r.hTex = 0;
			r.xTex = 0;
			r.yTex = 0;
			r.width = 0;
			r.height = 0;
			return r;
		}

		frame f = frames[cfi];
		return image->getRenderInfo(f.x, f.y, f.width, f.height);
	}

	renderinfo FrameAnimation::getRenderInfo(float x, float y, float width, float height)
	{
		if(frames.size() <= 0)
		{
			renderinfo r;
			r.wTex = 0;
			r.hTex = 0;
			r.xTex = 0;
			r.yTex = 0;
			r.width = 0;
			r.height = 0;
			return r;
		}

		frame f = frames[cfi];
		return image->getRenderInfo(f.x + x, f.y + y, width, height);
	}

	void FrameAnimation::render()
	{
		
		if(frames.size() <= 0)
			return;

		frame f = frames[cfi];
		image->render(f.x, f.y, f.width, f.height);
	}

	void FrameAnimation::render(float x, float y)
	{
		
		if(frames.size() <= 0)
			return;

		glTranslatef(x, y, 0);
		render();
		glTranslatef(-x, -y, 0);
	}

	void FrameAnimation::render(float x, float y, float width, float height)
	{
		if(frames.size() <= 0)
			return;

		frame f = frames[cfi];
		image->render(f.x + x, f.y + y, width, height);
	}

	void FrameAnimation::renderQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
	{
	}

	void FrameAnimation::update(float dt)
	{
		if(!running)
			return;

		if(frames.size() <= 0)
			return;

		// More time get.
		timeBuffer += dt;

		// Next frame index
		unsigned int nfi = cfi;

		nfi = cfi;

		// While we still have more "spare time"
		while(timeBuffer >= frames[nfi].post_delay)
		{
			timeBuffer -= frames[nfi].post_delay;

			// Goto next frame
			nfi = (nfi + 1) >= frames.size() ? 0 : (nfi + 1);
		}

		// Next frame is now in nfi
		cfi = nfi;

		// Update dimensions
		frame f = frames[cfi];
		this->width = f.width;
		this->height = f.height;

	}

	int FrameAnimation::load()
	{
		if(!image || !image->load())
			return LOVE_ERROR;
		return LOVE_OK;
	}

	void FrameAnimation::unload()
	{
		if(image != 0)
			image->unload();
	}


}// love
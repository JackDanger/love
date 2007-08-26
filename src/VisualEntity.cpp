#include "VisualEntity.h"
#include "love.h"

namespace love
{
	VisualEntity::VisualEntity()
	{
		setType(LOVE_TYPE_VISUAL_ENTITY);
	}

	VisualEntity::~VisualEntity()
	{
	}

	void VisualEntity::init()
	{
	}

	Sprite* VisualEntity::getSprite()
	{
		return sprite;
	}

	void VisualEntity::setSprite(Sprite * sprite)
	{
		this->sprite = sprite;
	}

	void VisualEntity::update(float dt)
	{
		if(sprite != 0)
			sprite->update(dt);
		velocity += acceleration * dt;
		position += velocity * dt;
	}

	void VisualEntity::render()
	{
		if(sprite == 0 || !visible) return;

		glPushMatrix();
			glTranslatef(position.getX(), position.getY(), 0.0f);
			glRotatef(orientation, 0.0f, 0.0f, 1.0f);
			glTranslatef(-(sprite->getWidth() / 2),-(sprite->getHeight() / 2), z);
			glColor4ub(255,255,255,opacity);
			sprite->render();
			glColor4ub(255,255,255,255); //to reset the color
		glPopMatrix();
	}

	int VisualEntity::load()
	{
		sprite = 0;
		color = 0;
		opacity = 255;
		Entity::load();

		return LOVE_OK;
	}

	void VisualEntity::unload()
	{
	}
}
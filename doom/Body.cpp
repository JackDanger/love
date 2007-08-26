#include "Body.h"
#include "Grid.h"

namespace love 
{



	Body::Body() : VERY_SMALL(0.0001f)
	{

	}

	Body::Body(Vextor position, vector<Vextor> vertices, float mass)
	{

		// Physics
		setMass(mass);
		setFriction(0.0f);
		setRestitution(0.001f);
		setGlue(0.0f);

		// PointMass
		setAngularVelocity(0.0f);
		setAngle(0.0f);
		setOrientation(Matrix(0.0f));
		setVertices(vertices);

		// Entity
		setPosition(position);
		setDisplacement(Vextor(0,0));

		computeRadius();

	}

	Body::~Body()
	{
	}

	void Body::addImpulse(const Vextor & f, float dt)
	{
		if(!isMovable())
			return;

		// Update displacement
		setDisplacement( getDisplacement() + f * getInverseMass() * dt * dt );

	}

	void Body::render()
	{

		const vector<Vextor> & vertices = getVertices();

			glPushMatrix();

				glTranslatef(getX(), getY(), 0.0f);

				glColor4ub(255,255,255,180);

				if(vertices.size() > 2)
				{
					glBegin(GL_POLYGON);
						
						for(unsigned int i = 0;i<vertices.size();i++)
						{
							Vextor t = vertices[i] * getOrientation();
							glVertex2f(t.getX(), t.getY());
						}

					glEnd();
				}else if(vertices.size() == 2)
				{
					glBegin(GL_LINES);
						
						for(unsigned int i = 0;i<2;i++)
						{
							Vextor t = vertices[i] * getOrientation();
							glVertex2f(t.getX(), t.getY());
						}

					glEnd();
				}else if(vertices.size() == 1)
				{
					
					glPointSize(3.0f);

					glBegin(GL_POINTS);
							Vextor t = vertices[0];
							glVertex2f(t.getX(), t.getY());
					glEnd();
				}

			/**
			int precision = 20;
			float step = (float)((2*3.14159)/precision);

			// Render bounding stuff here.
			
			glBegin(GL_LINE_LOOP);
			
				for(int i = 0;i<precision;i++)
				{
					float xp = radius * cos(step*i);
					float yp = radius * sin(step*i);
					glVertex2f(xp, yp);
				}

			glEnd();

			glBegin(GL_LINE_LOOP);
				glVertex2f(-radius, -radius);
				glVertex2f(-radius, radius);
				glVertex2f(radius, radius);
				glVertex2f(radius, -radius);
			glEnd();
			**/


			glPopMatrix();


		/**
		Vextor disp_temp = displacement;
		disp_temp.normalize();
		disp_temp *= 50;

		glColor4ub(255,0,0,100);
		renderVextor(disp_temp);
		**/

		


	}

	void Body::renderVextor(const Vextor & v)
	{

		glLineWidth(2.0f);

		/***
		* Render arrow
		**/

		// Main line
		glPushMatrix();

			glTranslatef(getX(), getY(), 0);

			glBegin(GL_QUADS);
				glVertex2f(-1,-1);
				glVertex2f(-1,1);
				glVertex2f(1,1);
				glVertex2f(1,-1);
			glEnd();

			glBegin(GL_LINES);
				
				
				glVertex2f(0,0);
				glVertex2f(v.getX(), v.getY());					

			glEnd();

		glPopMatrix();


		// First arrow arm
		glPushMatrix();

			glTranslatef(getX()+v.getX(), getY()+v.getY(), 0);
			glRotatef(30, 0, 0, 1.0);

			glBegin(GL_LINES);			
				
				glVertex2f(0,0);
				glVertex2f(-(v.getX()/4), -(v.getY())/4);
			glEnd();

		glPopMatrix();

		// Second arrow arm
		glPushMatrix();

			glTranslatef(getX()+v.getX(), getY()+v.getY(), 0);
			glRotatef(-30, 0, 0, 1.0);

			glBegin(GL_LINES);			
				
				glVertex2f(0,0);
				glVertex2f(-v.getX()/4, -v.getY()/4);
			glEnd();

		glPopMatrix();
	}

	void Body::update(float dt)
	{
		if(!isMovable())
		{
			setDisplacement(Vextor(0,0));
			setOrientation(Matrix(0));//might not be needed
			return;
		}

		move(displacement);

		// Update angle
		setAngle( getAngle() + getAngularVelocity() * dt );
		setOrientation(Matrix(getAngle()));
	}


} // love
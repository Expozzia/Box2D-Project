#include "sprite_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <maths/math_utils.h>
#include <input/sony_controller_input_manager.h>
#include <system/debug_log.h>
#include <math.h>



SpriteApp::SpriteApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	input_manager_(NULL),
	font_(NULL)
{
}

void SpriteApp::Init()
{
	// create a sprite renderer to draw your sprites
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	InitFont();

	my_sprite_.set_position(platform_.width()*0.5f, platform_.height()*0.5f, 0.0f);
	my_sprite_.set_width(32.0f);
	my_sprite_.set_height(32.0f);

	input_manager_ = gef::InputManager::Create(platform_);

	speed = 10;

}

void SpriteApp::CleanUp()
{
	CleanUpFont();

	delete input_manager_;
	input_manager_ = NULL;

	// destroy sprite renderer once you've finished using it
	delete sprite_renderer_;
	sprite_renderer_ = NULL;
}

bool SpriteApp::Update(float frame_time)
{
	// frame rate = 1 second / frame_delta_time
	fps_ = 1.0f / frame_time;

	// Get latest data from input devices
	if (input_manager_)
	{
		input_manager_->Update();

		// Get controller input data for all controllers
		gef::SonyControllerInputManager* controller_input = input_manager_->controller_input();
		if (controller_input)
		{
			// Read controller data for controller 0
			const gef::SonyController* controller = controller_input->GetController(0);

			if (controller)
			{
				// Displays what button is pressed
				//gef::DebugOut("%f has been pressed", controller->buttons_pressed());

				
				// Testing for x axis on left analog stick
				float left_x_axis = controller->left_stick_x_axis();
				// Output the value along the X-axis (-1 to 1)
				//gef::DebugOut("x: %f\n", left_x_axis);


				// Testing for y axis on right analog stick
				float right_y_axis = controller->right_stick_y_axis();
				//gef::DebugOut("y: %f\n", right_y_axis);

				// Testing for x axis on right analog stick
				float right_x_axis = controller->right_stick_x_axis();
				// Output the value along the X-axis (-1 to 1)
				//gef::DebugOut("X: %f\n", right_x_axis);
				
				
				
				// Analog stick
				// -------------

				// Calculating angle of analog stick
				deltaX = right_x_axis;
				deltaY = -right_y_axis;

				// If the analog stick isn't being moved
				if (deltaX == 0 && deltaY == 0)
				{
					// Set the angle to 0 degrees
					angle = 0;
				}
				else
				{
					rad = atan2(deltaX, deltaY); // In radians

					// Converts answer to degrees
					angle = rad * 180 / pi;

					// If the angle is negative
					if (angle < 0)
					{
						// Adjust the angle to go full 360 degrees
						angle = 360 + angle;
					}
				}
				
				// Outputs the current angle
				gef::DebugOut("Angle is: %f\n", angle);
				// -------------

				// Rotating sprite with right analog stick
				//-------------

				// Converting angle to radian for the rotation value
				float rotation = (angle * pi) / 180;

				// Updates the sprite rotation
				my_sprite_.set_rotation(rotation);

				//-------------


				// Move the sprite based on DPAD controls ----------

				if (controller->buttons_down() & gef_SONY_CTRL_RIGHT)
				{
					// get a copy of the current position of the sprite
					gef::Vector4 sprite_position = my_sprite_.position();

					// update the x-axis on the COPY of the current position
					sprite_position.set_x(sprite_position.x() + speed);

					// update the sprite with the new position
					my_sprite_.set_position(sprite_position);
				}
				else if (controller->buttons_down() & gef_SONY_CTRL_LEFT)
				{
					// get a copy of the current position of the sprite
					gef::Vector4 sprite_position = my_sprite_.position();

					// update the x-axis on the COPY of the current position
					sprite_position.set_x(sprite_position.x() - speed);

					// update the sprite with the new position
					my_sprite_.set_position(sprite_position);
				}
				else if (controller->buttons_down() & gef_SONY_CTRL_UP)
				{

					// get a copy of the current position of the sprite
					gef::Vector4 sprite_position = my_sprite_.position();

					// update the x-axis on the COPY of the current position
					sprite_position.set_y(sprite_position.y() - speed);

					// update the sprite with the new position
					my_sprite_.set_position(sprite_position);

				}
				else if (controller->buttons_down() & gef_SONY_CTRL_DOWN)
				{
					// get a copy of the current position of the sprite
					gef::Vector4 sprite_position = my_sprite_.position();

					// update the x-axis on the COPY of the current position
					sprite_position.set_y(sprite_position.y() + speed);

					// update the sprite with the new position
					my_sprite_.set_position(sprite_position);
				}
				if (controller->buttons_pressed() & gef_SONY_CTRL_TRIANGLE)
				{
					my_sprite_.set_position(platform_.width()*0.5f, platform_.height()*0.5f, 0.0f);
				}

			

				// If Start and select are held down together
				if ((controller->buttons_down() & (gef_SONY_CTRL_START | gef_SONY_CTRL_SELECT)) == (gef_SONY_CTRL_START | gef_SONY_CTRL_SELECT))
				{
					// Exit the program
					return 0;
				}
			}

		}

	}
	
	
	return true;                                
}

void SpriteApp::Render()
{
	// draw all sprites between the Begin() and End() calls
	sprite_renderer_->Begin();

	// draw my sprite here
	sprite_renderer_->DrawSprite(my_sprite_);

	DrawHUD();
	sprite_renderer_->End();
}


void SpriteApp::InitFont()
{
	// create a Font object and load in the comic_sans font data
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}

void SpriteApp::CleanUpFont()
{
	// destroy the Font object
	delete font_;
	font_ = NULL;
}

void SpriteApp::DrawHUD()
{
	if(font_)
	{
		// display frame rate
		font_->RenderText(
			sprite_renderer_,						// sprite renderer to draw the letters
			gef::Vector4(650.0f, 510.0f, -0.9f),	// position on screen
			1.0f,									// scale
			0xffffffff,								// colour ABGR
			gef::TJ_LEFT,							// justification
			"FPS: %.1f xpos: %.1f",							// string of text to render
			fps_,									// any variables used in formatted text string http://www.cplusplus.com/reference/cstdio/printf/
			my_sprite_.position().x()
			);
	}
}


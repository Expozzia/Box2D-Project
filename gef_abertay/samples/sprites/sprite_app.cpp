#include "sprite_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/texture.h>
#include <graphics/mesh.h>
#include <graphics/primitive.h>
#include <assets/png_loader.h>
#include <graphics/image_data.h>
#include <graphics/font.h>
#include <input/touch_input_manager.h>
#include <maths/vector2.h>
#include <input/sony_controller_input_manager.h>
#include <maths/math_utils.h>


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

	time = 0;
	counter = 0;
	

	for (int i = 0; i < 10; i++)
	{
		float offset = i * 50.0f;

		arrSprite[i].set_position(250.0f + offset, 300.0f, 0.0f);
		arrSprite[i].set_width(30.0f);
		arrSprite[i].set_height(120.0f);

	}


	/*
	// Sets the position and size of the sprite
	my_sprite.set_position(450.0f, 300.0f, 0.0f);
	my_sprite.set_width(30.0f);
	my_sprite.set_height(120.0f);
	

	// Sets the position and size of the sprite
	my_sprite2.set_position(450.0f, 300.0f, 0.0f);
	my_sprite2.set_width(30.0f);
	my_sprite2.set_height(120.0f);
	*/
}

void SpriteApp::CleanUp()
{
	CleanUpFont();

	// destroy sprite renderer once you've finished using it
	delete sprite_renderer_;
	sprite_renderer_ = NULL;
}

bool SpriteApp::Update(float frame_time)
{
	// frame rate = 1 second / frame_delta_time
	fps_ = 1.0f / frame_time;

	// Movement of the sprite
	hSpeed = 1.0f;
	vSpeed = 1.0f;
	rotSpeed = 0.1f;


	/*

	// 1ST SPRITE

	// get current position of the sprite
	gef::Vector4 sprite_position = my_sprite.position();

	// Changes the position (increments X)
	sprite_position.set_x(sprite_position.x() - hSpeed);

	// Changes the position (increments Y)
	sprite_position.set_y(sprite_position.y() - vSpeed);

	// Set the position to the new one stored in temp variable
	my_sprite.set_position(sprite_position);

	// Rotation
	// Creates temp variable to store rotation
	sprite_rotation = my_sprite.rotation();

	// Changes the rotation of the sprite
	my_sprite.set_rotation(sprite_rotation - rotSpeed);
	

	// 2ND SPRITE

	// Creates temp variable to store position
	gef::Vector4 sprite_position2 = my_sprite2.position();

	// Changes the position (increments X)
	sprite_position2.set_x(sprite_position2.x() + hSpeed);

	// Changes the position (increments Y)
	sprite_position2.set_y(sprite_position2.y() + vSpeed);

	// Set the position to the new one stored in temp variable
	my_sprite2.set_position(sprite_position2);

	// Rotation
	// Creates temp variable to store rotation
	sprite_rotation2 = my_sprite2.rotation();
	
	// Changes the rotation of the sprite
	my_sprite2.set_rotation(sprite_rotation2 + rotSpeed);

	*/

	// Increments every time update is called
	counter++;

	// If the counter is greater than the fps
	if (counter > fps_)
	{
		// A second has passed
		time++;
	}

	// If 10 seconds have passed
	if (time > 10)
	{
		// Clean up
		CleanUp();
	}


	return true;
}

void SpriteApp::Render()
{
	// draw all sprites between the Begin() and End() calls
	sprite_renderer_->Begin();

	if (time < 10)
	{
		for (int i = 0; i < 10; i++)
		{
			sprite_renderer_->DrawSprite(arrSprite[i]);
		}
	}

	/*
	// draw my sprite here
	sprite_renderer_->DrawSprite(my_sprite);
	sprite_renderer_->DrawSprite(my_sprite2);
	*/

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
		// Display frame rate
		font_->RenderText(
			sprite_renderer_,						// sprite renderer to draw the letters
			gef::Vector4(850.0f, 510.0f, -0.9f),	// position on screen
			1.0f,									// scale
			0xffffffff,								// colour ABGR
			gef::TJ_LEFT,							// justification
			"FPS: %.1f",							// string of text to render
			fps_									// any variables used in formatted text string http://www.cplusplus.com/reference/cstdio/printf/
			);

		// Display position of the sprite
		font_->RenderText(
			sprite_renderer_,						// sprite renderer to draw the letters
			gef::Vector4(5.0f, 510.0f, -0.9f),	// position on screen
			1.0f,									// scale
			0xffffffff,								// colour ABGR
			gef::TJ_LEFT,							// justification
			"Position: %.0f %.0f",					// string of text to render
			my_sprite2.position().x(),				// any variables used in formatted text string http://www.cplusplus.com/reference/cstdio/printf/
			my_sprite2.position().y()
			);

	}
}


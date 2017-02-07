#ifndef _sprite_app_H
#define _sprite_app_H

#include <system/application.h>
#include <graphics/sprite.h>
#include <maths/vector2.h>
#include <maths/vector4.h>
#include <vector>
#include <graphics/mesh_instance.h>
#include <graphics/material.h>
#include <input/input_manager.h>

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class Renderer3D;
	class Mesh;
}

class SpriteApp : public gef::Application
{
public:
	SpriteApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();
private:
	void InitFont();
	void CleanUpFont();
	void DrawHUD();


	gef::SpriteRenderer* sprite_renderer_;
	gef::InputManager* input_manager_;
	gef::Font* font_;

	float fps_;

	// Creates a sprite object

	gef::Sprite my_sprite;
	gef::Sprite my_sprite2;

	// Speed variables
	float hSpeed;
	float vSpeed;
	float rotSpeed;

	float hSpeed2;
	float vSpeed2;
	float rotSpeed2;

	// Temp rotation variables
	float sprite_rotation;
	float sprite_rotation2;

	// Array of sprites
	gef::Sprite arrSprite[10];

	// Can't get vectors to work
	std::vector<gef::Sprite> vecSprites;

	float time;
	float counter;

};

#endif // _sprite_app_H

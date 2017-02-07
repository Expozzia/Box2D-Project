#ifndef _sprite_app_H
#define _sprite_app_H

#include <system/application.h>
#include <graphics/sprite.h>
#include <maths/vector4.h>
#include <vector>
#include <input\input_manager.h>

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
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
	gef::Font* font_;

	float fps_;
	gef::Sprite my_sprite_;

	// Input manager object
	gef::InputManager* input_manager_;

	// Speed of the sprite movement
	float speed;

	// Value of pi
	const float pi = 3.1415926535897;


	// Analog stick
	// -------------
	float deltaX;
	float deltaY;
	float rad; // In radians
	float angle; // degrees
	// -------------


};

#endif // _sprite_app_H

#ifndef _SCENE_APP_H
#define _SCENE_APP_H

#include <system/application.h>
#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
}

class SceneApp : public gef::Application
{
public:
	SceneApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();
private:
	void InitFont();
	void CleanUpFont();
	void DrawHUD();
	void SetupLights();


    
	gef::SpriteRenderer* sprite_renderer_;
	gef::Font* font_;
	gef::Renderer3D* renderer_3d_;

	// Input manager object
	gef::InputManager* input_manager_;

	PrimitiveBuilder* primitive_builder_;

	gef::MeshInstance player_;
	gef::Vector4 player_position_;

	float fps_;

	// Value of pi
	const float pi = 3.1415926535897;

	float speed;

	// Analog stick
	// -------------
	float lDeltaX;
	float lDeltaY;

	float rDeltaX;
	float rDeltaY;

	float leftRad; // In radians
	float leftAngle; // degrees

	float rightRad; // In radians
	float rightAngle; // degrees

	// -------------

};

#endif // _SCENE_APP_H

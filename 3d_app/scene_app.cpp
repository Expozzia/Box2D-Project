#include "scene_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <maths/math_utils.h>
#include <input\input_manager.h>
#include <input\sony_controller_input_manager.h>
#include <math.h>


SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	renderer_3d_(NULL),
	primitive_builder_(NULL),
	font_(NULL),
	input_manager_(NULL)
{
}

void SceneApp::Init()
{
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	// create the renderer for draw 3D geometry
	renderer_3d_ = gef::Renderer3D::Create(platform_);

	// initialise primitive builder to make create some 3D geometry easier
	primitive_builder_ = new PrimitiveBuilder(platform_);

	input_manager_ = gef::InputManager::Create(platform_);

	// Set mesh for the player
	player_.set_mesh(primitive_builder_->GetDefaultCubeMesh());

	player_position_.set_value(0.0f, 0.0f, 0.0f);

	speed = 3.0f;

	InitFont();
	SetupLights();
}

void SceneApp::CleanUp()
{
	CleanUpFont();

	delete primitive_builder_;
	primitive_builder_ = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;

	delete sprite_renderer_;
	sprite_renderer_ = NULL;
}

bool SceneApp::Update(float frame_time)
{
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

				// Testing for y axis on left analog stick 
				float left_y_axis = controller->left_stick_y_axis();


				// Testing for y axis on right analog stick 
				float right_y_axis = controller->right_stick_y_axis();

				// Testing for x axis on right analog stick
				float right_x_axis = controller->right_stick_x_axis();


				// Left Analog stick
				// -------------

				// Calculating angle of analog stick
				lDeltaX = left_x_axis;
				lDeltaY = -left_y_axis;

				// If the analog stick isn't being moved
				if (lDeltaX == 0 && lDeltaY == 0)
				{
					// Set the angle to 0 degrees
					leftAngle = 0;
				}
				else
				{
					leftRad = atan2(lDeltaX, lDeltaY); // In radians

					// Converts answer to degrees
					leftAngle = leftRad * 180 / pi;

					// If the angle is negative
					if (leftAngle < 0)
					{
						// Adjust the angle to go full 360 degrees
						leftAngle = 360 + leftAngle;
					}
				}


				// Right Analog stick
				// -------------

				// Calculating angle of analog stick
				rDeltaX = right_x_axis;
				rDeltaY = -right_y_axis;

				// If the analog stick isn't being moved
				if (rDeltaX == 0 && rDeltaY == 0)
				{
					// Set the angle to 0 degrees
					rightAngle = 0;
				}
				else
				{
					rightRad = atan2(rDeltaX, rDeltaY); // In radians

												 // Converts answer to degrees
					rightAngle = rightRad * 180 / pi;

					// If the angle is negative
					if (rightAngle < 0)
					{
						// Adjust the angle to go full 360 degrees
						rightAngle = 360 + rightAngle;
					}
				}


				// Outputs the current angle
				gef::DebugOut("Left angle is: %f\n", leftAngle);
				gef::DebugOut("Right angle is: %f\n", rightAngle);
				// -------------


				// If Start and select are held down together
				if ((controller->buttons_down() & (gef_SONY_CTRL_START | gef_SONY_CTRL_SELECT)) == (gef_SONY_CTRL_START | gef_SONY_CTRL_SELECT))
				{
					// Exit the program
					return 0;
				}
			}

		}

	}


	gef::Matrix44 player_transform;

	gef::Matrix44 player_scale_matrix;
	gef::Matrix44 player_rotateX_matrix;
	gef::Matrix44 player_rotateY_matrix;
	gef::Matrix44 player_rotateZ_matrix;

	gef::Matrix44 player_translation;

	// Scale
	player_scale_matrix.Scale(gef::Vector4(1.0f, 1.0f, 1.0f));

	// Rotation

	// Rotates the player object by degrees (after convertion)
	player_rotateX_matrix.RotationX(gef::DegToRad(0.0f));

	// Multiple matrixes of scale and rotation (x rotation)
	player_transform = player_scale_matrix * player_rotateX_matrix;

	// Translation
	
	// Takes the x and y axis input, divides by fps and multiples by speed
	player_position_ += gef::Vector4((lDeltaX / fps_) * speed, (lDeltaY / fps_) * speed, 0.0f);

	// Sets the translation to the player object
	player_transform.SetTranslation(player_position_);

	// Does the entire transformation
	player_.set_transform(player_transform);

	return true;
}

void SceneApp::Render()
{
	// Set up camera

	// Projection

	gef::Matrix44 projection_matrix;

	float fov = gef::DegToRad(45.0f);
	float aspect_ratio = (float)platform_.width() / (float)platform_.height();
	projection_matrix = platform_.PerspectiveProjectionFov(fov, aspect_ratio, 0.1f, 100.0f);
	renderer_3d_->set_projection_matrix(projection_matrix);

	// View matrix
	gef::Vector4 camera_eye(0.0f, 0.0f, 5.0f);
	gef::Vector4 camera_lookat(0.0f, 0.0f, 0.0f);
	gef::Vector4 camera_up(0.0f, 1.0f, 0.0f);

	gef::Matrix44 view_matrix;
	view_matrix.LookAt(camera_eye, camera_lookat, camera_up);
	renderer_3d_->set_view_matrix(view_matrix);



	// draw 3d geometry
	renderer_3d_->Begin();

	// Changes the material colour
	renderer_3d_->set_override_material(&primitive_builder_->red_material());

	// Renders the player (cube in this case)
	renderer_3d_->DrawMesh(player_);

	renderer_3d_->End();

	// start drawing sprites, but don't clear the frame buffer
	sprite_renderer_->Begin(false);
	DrawHUD();
	sprite_renderer_->End();
}
void SceneApp::InitFont()
{
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}

void SceneApp::CleanUpFont()
{
	delete font_;
	font_ = NULL;
}

void SceneApp::DrawHUD()
{
	if(font_)
	{
		// display frame rate
		font_->RenderText(sprite_renderer_, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f", fps_);
	}
}

void SceneApp::SetupLights()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = renderer_3d_->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.25f, 0.25f, 0.25f, 1.0f));

	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(default_point_light);
}

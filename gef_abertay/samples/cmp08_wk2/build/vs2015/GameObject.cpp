#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}


void GameObject::spriteMovement()
{
	
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
}

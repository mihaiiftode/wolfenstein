//
// Created by Morten Nobel-Jørgensen on 29/09/2017.
//

#include <glm/gtx/rotate_vector.hpp>
#include "FirstPersonController.hpp"
#include <iostream>

using namespace sre;
using namespace glm;


FirstPersonController::FirstPersonController(sre::Camera* camera)
	: camera(camera)
{
	camera->setPerspectiveProjection(45, 0.1f, 1000);
	camera->lookAt(vec3{0,0,0}, vec3{0,0,-1}, vec3{0,1,0});
	position = vec3(0, 0, 0);
}


void FirstPersonController::update(float deltaTime)
{
	vec3 direction(cos(radians(rotation)), 0, sin(radians(rotation)));
	rightVector = vec3(cos(radians(rotation + 90)), 0, sin(radians(rotation + 90)));
	std::cout << "forward: " << forward << "right: " << right << std::endl;

	if (forward)
		position += direction * deltaTime * speed;
	if (back)
		position -= direction * deltaTime * speed;
	if (left)
		position -= rightVector * deltaTime * speed;
	if (right)
		position += rightVector * deltaTime * speed;

	auto view = lookAt(position, position + direction, {0, 1, 0});
	camera->setViewTransform(view);
}

void FirstPersonController::onKey(SDL_Event& event)
{
	if (event.key.keysym.sym == SDLK_w)
	{
		if (event.type == SDL_KEYDOWN)
			forward = true;
		else if (event.type == SDL_KEYUP)
			forward = false;
	}
	if (event.key.keysym.sym == SDLK_s)
	{
		if (event.type == SDL_KEYDOWN)
			back = true;
		else if (event.type == SDL_KEYUP)
			back = false;
	}
	if (event.key.keysym.sym == SDLK_a)
	{
		if (event.type == SDL_KEYDOWN)
			left = true;
		else if (event.type == SDL_KEYUP)
			left = false;
	}
	if (event.key.keysym.sym == SDLK_d)
	{
		if (event.type == SDL_KEYDOWN)
			right = true;
		else if (event.type == SDL_KEYUP)
			right = false;
	}
}

float deltaY = 0;

void FirstPersonController::onMouse(SDL_Event& event)
{
	if (event.type != SDL_MOUSEMOTION) return;
	if (event.motion.xrel < 0)
		deltaY -= 1;
	else if (event.motion.xrel > 0)
		deltaY += 1;

	rotation = deltaY * 0.5;
}

void FirstPersonController::setInitialPosition(glm::vec2 position, float rotation)
{
	this->position = glm::vec3(position.x, 0, position.y);
	this->rotation = rotation;
}

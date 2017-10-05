//
// Created by Morten Nobel-Jørgensen on 29/09/2017.
//

#include <glm/gtx/rotate_vector.hpp>
#include "FirstPersonController.hpp"

using namespace sre;
using namespace glm;


FirstPersonController::FirstPersonController(sre::Camera* camera)
	: camera(camera)
{
	camera->setPerspectiveProjection(45, 0.1f, 1000);
	position = vec3(0, 0, 0);
}


void FirstPersonController::update(float deltaTime)
{
	camera->lookAt(vec3(position.x, 0, position.z), rotateY(position, radians(rotation)) , vec3{ 0,1,0 });
}

void FirstPersonController::onKey(SDL_Event& event)
{
}

void FirstPersonController::onMouse(SDL_Event& event)
{
	rotation += event.motion.yrel;
}

void FirstPersonController::setInitialPosition(glm::vec2 position, float rotation)
{
	this->position = glm::vec3(position.x, 0, position.y);
	this->rotation = rotation;
	oldRotation = rotation;
}

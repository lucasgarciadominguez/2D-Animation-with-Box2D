#pragma once
#include "Kernel.h"
//#include "EntitySystem.h"
#include "Renderer.h"
//#include "InputSystem.h"
//#include "MessageSystem.h"

namespace animationPractice
{
	Kernel::Kernel(EntitySystem* _entitySystem, Renderer* _renderSystem, InputSystem* _inputSystem, MessageSystem* _messageSystem)
		: entitySystem(_entitySystem), renderSystem(_renderSystem), inputSystem(_inputSystem), messageSystem(_messageSystem) {}

	void Kernel::Update()
	{
		//inputSystem->Update();
		//entitySystem->Update();

		//messageSystem->SendToListeners();

		//renderSystem->Update();
	}
}
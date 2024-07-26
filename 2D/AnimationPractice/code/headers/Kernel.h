#pragma once
namespace animationPractice
{
	class EntitySystem;
	class RenderSystem;
	class InputSystem;
	class MessageSystem;

	///
	/// Class in charge of managing all the tasks
	///
	class Kernel
	{
	private:

		EntitySystem* entitySystem;
		Renderer* renderSystem;
		InputSystem* inputSystem;
		MessageSystem* messageSystem;

	public:

		Kernel(EntitySystem* _entitySystem, Renderer* _renderSystem, InputSystem* _inputSystem, MessageSystem* _messageSystem);
		void Update();

	};
}

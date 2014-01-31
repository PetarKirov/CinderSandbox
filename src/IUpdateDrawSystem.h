#pragma once;

namespace zlx
{
	class IUpdateDrawSystem
	{
	public:
		virtual void update() = 0;
		virtual void draw() = 0;
	};
}
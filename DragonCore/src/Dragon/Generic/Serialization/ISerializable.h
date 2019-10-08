#pragma once

namespace dragon
{

	class ISerializable
	{
	public:
		virtual void Serialize(class OutStream& out) = 0;
		virtual void Deserialize(class InStream& in) = 0;
	};

}
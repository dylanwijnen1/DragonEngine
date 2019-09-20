#pragma once

class ISerializable
{
public:
	virtual void Serialize(class OutStream& out) = 0;
	virtual void Deserialize(class InStream& in) = 0;
};
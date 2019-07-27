#pragma once

class OutStream;
class InStream;

class ISerializable
{
public:
	virtual void Serialize(OutStream& out) = 0;
	virtual void Deserialize(InStream& in) = 0;
};
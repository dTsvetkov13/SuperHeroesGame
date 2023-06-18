#pragma once

#include "SharedPtr.hpp";

template<typename T>
class RequestReturnModel
{
public:
	bool isAccepted;
	SharedPtr<T> data;
	
	RequestReturnModel<T>(bool isAccepted, const SharedPtr<T>& ptr)
	{
		this->isAccepted = isAccepted;
		data = ptr;
	}

	RequestReturnModel<T>(bool isAccepted, const SharedPtr<T>&& ptr)
	{
		this->isAccepted = isAccepted;
		data = std::move(ptr);
	}
};


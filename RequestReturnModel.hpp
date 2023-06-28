#pragma once

#include "SharedPtr.hpp";

template<typename T>
class RequestReturnModel
{
public:
	bool isAccepted;
	SharedPtr<T> data;
	
	RequestReturnModel<T>(bool isAccepted, T ptr)
	{
		this->isAccepted = isAccepted;
		data = SharedPtr<T>(new T(ptr));
	}

	/*RequestReturnModel<T>(bool isAccepted, T&& ptr)
	{
		this->isAccepted = isAccepted;
		data = SharedPtr<T>(std::move(ptr));
	}*/
};


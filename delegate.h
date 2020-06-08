#ifndef DELEGATE_H
#define DELEGATE_H

#include <vector>
#include <functional>

/*
//Weston McNamara 2020, Made With Love In Canada
//Licensed Under MIT https://mit-license.org/
//https://github.com/westonmcnamara/delegate-cpp
 
//Delegate C++ is a single header, lightweight and easy to use abstraction for storing functions and callbacks.
//Delegate C++ currently cannot accept any functions with parameters. This is subject to change.

	EXAMPLE:
	
	#include <iostream>
	#include "delegate.h"

	//Any function
	void YourFunction() { std::cout << "Your Function Was Invoked!" << std::endl; }
	void YourFunction2() { std::cout << "Your Function 2 Was Invoked!" << std::endl; }

	int main()
	{
		//Create a delegate
		Delegate _delegate;

		_delegate += YourFunction;
		_delegate += YourFunction2;

		//Invoke functions added to the delegate.
		_delegate();
	}

	
	OUTPUT:
	Your Function Was Invoked!
	Your Function 2 Was Invoked!
*/
class Delegate
{
	public:
		//Creates a delegate and initializes it with a single handler.
		Delegate(std::function<void()> func) { m_handlers.push_back(func); }

		//Copy Constructor
		Delegate(const Delegate &delegate) : m_handlers(delegate.m_handlers) {}

		//Creates a delegate with no Functions
		Delegate() {}

		//Invokes each function added to this delegate. 
		//If no handlers exist, it throws std::runtime_error.
		void Invoke();

		//Adds a single DelFunction to the delegate.
		void AddHandler(std::function<void()> func) { m_handlers.push_back(func); }

		//Removes every function added to this delegate.
		void RemoveAllHandlers() { m_handlers.clear(); }

		//Invokes each handler added to this delegate.
		void operator() () { Invoke(); }

		//Adds a function to the delegate.
		void operator+= (std::function<void()> func) { AddHandler(func); }

	private:
		//This is where handlers/functions are stored.
		std::vector<std::function<void()>> m_handlers;
};

void Delegate::Invoke()
{
	if (m_handlers.empty()) { throw std::runtime_error("Empty delegate cannot be invoked."); }

	//Iterate through the vector, and invoke each function.
	for (int i = 0; i != m_handlers.size(); i++)
	{
		m_handlers[i]();
	}
}
#endif
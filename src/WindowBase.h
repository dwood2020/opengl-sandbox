#pragma once
#include <string>


class WindowBase {
protected:
	int width;
	int height;
	std::string title;

public:
	WindowBase(int width, int height, const std::string& title);
	virtual ~WindowBase();

};
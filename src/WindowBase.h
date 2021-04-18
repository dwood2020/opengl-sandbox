#pragma once
#include <string>


class WindowBase {
protected:
	int width;
	int height;
	std::string title;
	bool windowShouldClose;

public:
	WindowBase(int width, int height, const std::string& title);
	virtual ~WindowBase();

	bool GetWindowShouldClose(void) const;

};
#pragma once
#include <string>
#include <functional>


class WindowBase {
protected:
	int width;
	int height;
	std::string title;
	bool windowShouldClose;

	std::function<void(int,int)> onResize;
	std::function<void(void)> onClose;

public:
	WindowBase(int width, int height, const std::string& title);
	virtual ~WindowBase();
	
	virtual void SwapBuffers(void) = 0;
	virtual void DoFrame(void) = 0;
	virtual void MakeContextCurrent(void) = 0;
	virtual void GetWindowRect(int& width, int& height) = 0;
	bool GetWindowShouldClose(void) const;

	void SetOnResize(std::function<void(int, int)> f);
	void SetOnClose(std::function<void(void)> f);

};
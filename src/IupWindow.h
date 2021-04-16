#pragma once
#include <string>
#include "WindowBase.h"
#include <iup/iup.h>
#include <iup/iupgl.h>


class IupWindow : public WindowBase {
protected:

	Ihandle* canvas;
	Ihandle* dlg;

public:
	IupWindow(int width, int height, const std::string& title);
	virtual ~IupWindow();

	virtual void Init(int argc, char** argv);
	void MakeContextCurrent(void);


};

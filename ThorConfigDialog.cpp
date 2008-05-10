// ThorConfigDialog.cpp: implementation of the ThorConfigDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "ThorConfigDialog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ThorConfigDialog::ThorConfigDialog(ThorConfig *_config, Component *content) : DialogWindow (T("Options"), Colours::white, true, true)
{
	config = _config;
	if (content)
	{
		setContentComponent (content);
		setName (content->getName());
	}
	else
		setContentComponent (configComponent = new ThorConfigComponent(config));

	setTitleBarHeight (16);
	enterModalState (true);
	setVisible (true);
	setAlwaysOnTop(true);
}

ThorConfigDialog::~ThorConfigDialog()
{
}

void ThorConfigDialog::closeButtonPressed()
{
	delete this;
}
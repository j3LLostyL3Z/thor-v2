// ThorConfigDialog.h: interface for the ThorConfigDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THORCONFIGDIALOG_H__E11F5A37_C876_4D14_B59D_1B28022DA4B9__INCLUDED_)
#define AFX_THORCONFIGDIALOG_H__E11F5A37_C876_4D14_B59D_1B28022DA4B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <juce.h>
#include "ThorConfigComponent.h"
#include "ThorConfig.h"

class ThorConfigDialog : public DialogWindow  
{
	public:
		ThorConfigDialog(ThorConfig *_config, Component *content=0);
		virtual ~ThorConfigDialog();
		void closeButtonPressed();
	private:
		ThorConfig *config;
		ThorConfigComponent *configComponent;
};

#endif // !defined(AFX_THORCONFIGDIALOG_H__E11F5A37_C876_4D14_B59D_1B28022DA4B9__INCLUDED_)

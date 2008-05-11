#include <juce.h>
#include "ThorMainComponent.h"
#include "ThorConfig.h"

class wnd  : public DocumentWindow
{
public:
	ThorConfig config;
    //==============================================================================
    wnd()
        : DocumentWindow (T("Thor v2"),
                          Colours::white, 
                          DocumentWindow::allButtons, 
                          true)
    {
		setTitleBarHeight (0);
        setVisible (true);
		setAlwaysOnTop(true);
        // centre the window on the desktop with this size
        setBounds (config.getRect());

		if (config.getWindowAlpha())
		{
			setBackgroundColour (Colours::white.withAlpha ((float)config.getWindowAlpha()));
		}
		
		setContentComponent (new ThorMainComponent(&config));
    }

    ~wnd()
    {
		config.setRect (getBounds());
    }
    //==============================================================================
    void closeButtonPressed()
    {
        JUCEApplication::quit();
    }
};


//==============================================================================
/** This is the application object that is started up when Juce starts. It handles
    the initialisation and shutdown of the whole application.
*/
class JUCEThor : public JUCEApplication
{
    wnd *hWnd;

public:
    //==============================================================================
    JUCEThor()
        : hWnd (0)
    {
    }

    ~JUCEThor()
    {
    }

    //==============================================================================
    void initialise (const String& commandLine)
    {
        // just create the main window...
        hWnd = new wnd();

        /*  ..and now return, which will fall into to the main event
            dispatch loop, and this will run until something calls
            JUCEAppliction::quit().

            In this case, JUCEAppliction::quit() will be called by the
            hello world window being clicked.
        */
    }

    void shutdown()
    {
        // clear up..

        if (hWnd != 0)
            delete hWnd;
    }

    //==============================================================================
    const String getApplicationName()
    {
        return T("Thor");
    }

    const String getApplicationVersion()
    {
        return T("1.0");
    }

    bool moreThanOneInstanceAllowed()
    {
        return true;
    }

    void anotherInstanceStarted (const String& commandLine)
    {
    }
};


//==============================================================================
// This macro creates the application's main() function..
START_JUCE_APPLICATION (JUCEThor)

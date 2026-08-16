/*
  ==============================================================================

    Main.h
    Created: 25 Oct 2016 11:16:59pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once
#pragma warning(disable:4244 4100 4305 26451 26495)

#include "MainIncludes.h"

//==============================================================================
class ChataigneApplication : public OrganicApplication
                         , public ParameterListener
{
public:
	//============================================================================== 
	ChataigneApplication();

	//---- GLOBAL SETTINGS CHATAIGNE SPECIFIC
	BoolParameter * enableSendAnalytics;
	EnumParameter * interfaceLanguage;
    bool crashSent;
	//

	void initialiseInternal(const String& /*commandLine*/) override;
	void afterSettingsLoaded() override;
	void afterInit() override;
	void parameterValueChanged(Parameter*) override;

	void shutdown() override;

	void handleCrashed() override;
};

START_JUCE_APPLICATION(ChataigneApplication)

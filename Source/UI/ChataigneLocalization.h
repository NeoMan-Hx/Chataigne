/*
  Chataigne interface localisation.

  The translation is deliberately kept outside the model layer.  Control
  addresses, script names, project data, and user-created names remain in
  their original form; only strings presented by the UI are translated.
*/

#pragma once

class ChataigneLocalization
{
public:
	static const juce::String englishLanguageId;
	static const juce::String simplifiedChineseLanguageId;
	static const juce::String bilingualChineseLanguageId;

	static void setLanguage(const juce::String& languageId, bool refreshExistingComponents = true);
	static juce::String translateForDisplay(const juce::String& text);
	static juce::String translateCommandLabel(const juce::String& text);
	static juce::String sourceText(const juce::String& text);
	static bool isSimplifiedChinese();
	static bool isBilingual();
	static void refreshAllComponents();
};

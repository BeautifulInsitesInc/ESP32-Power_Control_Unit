#ifndef SAVE_SETTINGS_H
#define SAVE_SETTINGS_H

#include <Preferences.h>

Preferences preferences;

void savePreferences()
{
    preferences.begin("settings", false);

    preferences.putString("elementStatus1", elementStatus1);
    preferences.putString("elementStatus2", elementStatus2);
    preferences.putString("elementStatus3", elementStatus3);
    preferences.putString("elementStatus4", elementStatus4);
    preferences.putString("elementStatus5", elementStatus1);
    preferences.putString("elementStatus6", elementStatus1);
    preferences.putString("elementStatus7", elementStatus1);
    preferences.putString("elementStatus8", elementStatus1);
    // Trigger Values
    preferences.putString("triggerSelection1", triggerSelection1);
    tout(" Just ran save values - triggerSelction1 saved as :"); toutln(triggerSelection1);
    preferences.putString("triggerSelection2", triggerSelection2);
    preferences.putString("triggerSelection3", triggerSelection3);
    preferences.putString("triggerSelection4", triggerSelection4);
    preferences.putString("triggerSelection5", triggerSelection5);
    preferences.putString("triggerSelection6", triggerSelection6);
    preferences.putString("triggerSelection7", triggerSelection7);
    preferences.putString("triggerSelection8", triggerSelection8);
    // SLIDER VALUE
    preferences.putString("sliderValue5", sliderValue5);
    preferences.putString("sliderValue6", sliderValue6);
    preferences.putString("sliderValue7", sliderValue7);
    preferences.putString("sliderValue8", sliderValue8);
    // CYCLE TIMER TRIGGER
    preferences.putInt("cycleOn1", cycleOn1); preferences.putInt("cycleOff1", cycleOff1);
    preferences.putInt("cycleOn2", cycleOn2); preferences.putInt("cycleOff2", cycleOff2);
    preferences.putInt("cycleOn3", cycleOn3); preferences.putInt("cycleOff3", cycleOff3);
    preferences.putInt("cycleOn4", cycleOn4); preferences.putInt("cycleOff4", cycleOff4);
    preferences.putInt("cycleOn5", cycleOn5); preferences.putInt("cycleOff5", cycleOff5);
    preferences.putInt("cycleOn6", cycleOn6); preferences.putInt("cycleOff6", cycleOff6);
    preferences.putInt("cycleOn7", cycleOn7); preferences.putInt("cycleOff7", cycleOff7);
    preferences.putInt("cycleOn8", cycleOn8); preferences.putInt("cycleOff8", cycleOff8);

    preferences.end();
}

void loadPreferences()
{
    preferences.begin("settings", true);
    elementStatus1 = preferences.getString("elementStatus1", "off");
    elementStatus2 = preferences.getString("elementStatus2", "off");
    elementStatus3 = preferences.getString("elementStatus3", "off");
    elementStatus4 = preferences.getString("elementStatus4", "off");
    elementStatus5 = preferences.getString("elementStatus5", "off");
    elementStatus6 = preferences.getString("elementStatus6", "off");
    elementStatus7 = preferences.getString("elementStatus7", "off");
    elementStatus8 = preferences.getString("elementStatus8", "off");

    // Trigger Values
    triggerSelection1 = preferences.getString("triggerSelection1", "manual0");
    tout(" Just loaded valuess values - triggerSelction1 loaded as :"); toutln(triggerSelection1);

    triggerSelection2 = preferences.getString("triggerSelection2", "manual0");
    triggerSelection3 = preferences.getString("triggerSelection3", "manual0");
    triggerSelection4 = preferences.getString("triggerSelection4", "manual0");
    triggerSelection5 = preferences.getString("triggerSelection5", "manual0");
    triggerSelection6 = preferences.getString("triggerSelection6", "manual0");
    triggerSelection7 = preferences.getString("triggerSelection7", "manual0");
    triggerSelection8 = preferences.getString("triggerSelection8", "manual0");

    sliderValue5 = preferences.getString("sliderValue5", "0");
    sliderValue6 = preferences.getString("sliderValue6", "0");
    sliderValue7 = preferences.getString("sliderValue7", "0");
    sliderValue8 = preferences.getString("sliderValue8", "0");

    cycleOn1 = preferences.getInt("cycleOn1", 0); cycleOff1 = preferences.getInt("cycleOff1",0);
    cycleOn2 = preferences.getInt("cycleOn2", 0); cycleOff2 = preferences.getInt("cycleOff2",0);
    cycleOn3 = preferences.getInt("cycleOn3", 0); cycleOff3 = preferences.getInt("cycleOff3",0);
    cycleOn4 = preferences.getInt("cycleOn4", 0); cycleOff4 = preferences.getInt("cycleOff4",0);
    cycleOn5 = preferences.getInt("cycleOn5", 0); cycleOff5 = preferences.getInt("cycleOff5",0);
    cycleOn6 = preferences.getInt("cycleOn6", 0); cycleOff6 = preferences.getInt("cycleOff6",0);
    cycleOn7 = preferences.getInt("cycleOn7", 0); cycleOff7 = preferences.getInt("cycleOff7",0);
    cycleOn8 = preferences.getInt("cycleOn8", 0); cycleOff8 = preferences.getInt("cycleOff8",0);

    preferences.end();
}

#endif
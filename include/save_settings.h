#ifndef SAVE_SETTINGS_H
#define SAVE_SETTINGS_H

#include <Preferences.h>

Preferences preferences;

void savePreferences(){
    preferences.begin("settings", false);

    preferences.putString("elementStatus1", elementStatus1);
    preferences.putString("elementStatus2", elementStatus2); 
    preferences.putString("elementStatus3", elementStatus3); 
    preferences.putString("elementStatus4", elementStatus4); 
    preferences.putString("elementStatus5", elementStatus1);
    preferences.putString("elementStatus6", elementStatus1);
    preferences.putString("elementStatus7", elementStatus1);
    preferences.putString("elementStatus8", elementStatus1);

    //Trigger Values
    preferences.putString("triggerSelection1", triggerSelection1);
    preferences.putString("triggerSelection2", triggerSelection2);
    preferences.putString("triggerSelection3", triggerSelection3);
    preferences.putString("triggerSelection4", triggerSelection4);
    preferences.putString("triggerSelection5", triggerSelection5);
    preferences.putString("triggerSelection6", triggerSelection6);
    preferences.putString("triggerSelection7", triggerSelection7);
    preferences.putString("triggerSelection8", triggerSelection8);


    preferences.putString("sliderValue5", sliderValue5);
    preferences.putString("sliderValue6", sliderValue6);
    preferences.putString("sliderValue7", sliderValue7);
    preferences.putString("sliderValue8", sliderValue8);

    preferences.end();

}

void loadPreferences(){
    preferences.begin("settings", true);
    elementStatus1 = preferences.getString("elementStatus1", "off");
    elementStatus2 = preferences.getString("elementStatus2", "off");
    elementStatus3 = preferences.getString("elementStatus3", "off");
    elementStatus4 = preferences.getString("elementStatus4", "off"); 
    elementStatus5 = preferences.getString("elementStatus5", "off"); 
    elementStatus6 = preferences.getString("elementStatus6", "off"); 
    elementStatus7 = preferences.getString("elementStatus7", "off"); 
    elementStatus8 = preferences.getString("elementStatus8", "off"); 

    //Trigger Values
    triggerSelection1 = preferences.getString("triggerSelection1", "manual0");
    triggerSelection2 = preferences.getString("triggerSelection2", "manual0");
    triggerSelection3 = preferences.getString("triggerSelection3", "manual0");
    triggerSelection4 = preferences.getString("triggerSelection4", "manual0");
    triggerSelection5 = preferences.getString("triggerSelection5", "manual0");
    triggerSelection6 = preferences.getString("triggerSelection6", "manual0");
    triggerSelection7 = preferences.getString("triggerSelection7", "manual0");
    triggerSelection8 = preferences.getString("triggerSelection8", "manual0");

    sliderValue5 = preferences.getString("sliderValue5","0");
    sliderValue6 = preferences.getString("sliderValue6","0");
    sliderValue7 = preferences.getString("sliderValue7","0");
    sliderValue8 = preferences.getString("sliderValue8","0");

 

    preferences.end();
}



#endif
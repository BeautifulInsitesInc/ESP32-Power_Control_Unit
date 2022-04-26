#ifndef SAVE_SETTINGS_H
#define SAVE_SETTINGS_H

#include <Preferences.h>

Preferences preferences;

void savePreferences(){
    preferences.begin("settings", false);
    //AC plug status
    preferences.putString("plugStatus1", plugStatus1);
    preferences.putString("plugStatus2", plugStatus2); 
    preferences.putString("plugStatus3", plugStatus3); 
    preferences.putString("plugStatus4", plugStatus4); 
    //DC slide values
    int duty_cycle1 = dutyCycle1;
    preferences.putString("sliderValue1", sliderValue1);
    preferences.putString("sliderValue2", sliderValue2);
    preferences.putString("sliderValue3", sliderValue3);
    preferences.putString("sliderValue4", sliderValue4);

    preferences.end();
    toutln("Preferences Saved");
    tout("Saved plugStatus2 : "); toutln(plugStatus2);
    tout("duty1 :"); toutln(dutyCycle1);
    tout("duty2 :"); toutln(dutyCycle2);
    tout("sliderValue1 : "); toutln(sliderValue1);

}

void loadPreferences(){
    preferences.begin("settings", true);
    //AC plug status
    plugStatus1 = preferences.getString("plugStatus1", "off");
    plugStatus2 = preferences.getString("plugStatus2", "off");
    plugStatus3 = preferences.getString("plugStatus3", "off");
    plugStatus4 = preferences.getString("plugStatus4", "off"); 
    //DC slide Values
    sliderValue1 = preferences.getString("sliderValue1","0");
    sliderValue2 = preferences.getString("sliderValue2","0");
    sliderValue3 = preferences.getString("sliderValue3","0");
    sliderValue4 = preferences.getString("sliderValue4","0");

    preferences.end();
    toutln("preferences Loaded: ");
    tout("plugstatus2 :");tout(plugStatus2);
    tout("duty1 :"); toutln(dutyCycle1);
    tout("duty2 :"); toutln(dutyCycle2);
    tout("sliderValue1 : "); toutln(sliderValue1);
}



#endif
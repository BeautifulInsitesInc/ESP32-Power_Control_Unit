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
    //Trigger Values
    preferences.putString("triggerPlug1", triggerPlug1);
    preferences.putString("triggerPlug2", triggerPlug2);
    preferences.putString("triggerPlug3", triggerPlug3);
    preferences.putString("triggerPlug4", triggerPlug4);
    preferences.putString("triggerAC1", triggerAC1);
    preferences.putString("triggerAC2", triggerAC2);
    preferences.putString("triggerAC3", triggerAC3);
    preferences.putString("triggerAC4", triggerAC4);
    

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
    //Trigger Values
    triggerPlug1 = preferences.getString("triggerPlug1", "manual");
    triggerPlug2 = preferences.getString("triggerPlug2", "manual");
    triggerPlug3 = preferences.getString("triggerPlug3", "manual");
    triggerPlug4 = preferences.getString("triggerPlug4", "manual");

    triggerAC1 = preferences.getString("triggerAC1", "manual");
    triggerAC2 = preferences.getString("triggerAC2", "manual");
    triggerAC3 = preferences.getString("triggerAC3", "manual");
    triggerAC4 = preferences.getString("triggerAC4", "manual");

    preferences.end();
    toutln("preferences Loaded: ");
    tout("plugstatus2 :");tout(plugStatus2);
    tout("duty1 :"); toutln(dutyCycle1);
    tout("duty2 :"); toutln(dutyCycle2);
    tout("sliderValue1 : "); toutln(sliderValue1);
}



#endif
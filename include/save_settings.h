#ifndef SAVE_SETTINGS_H
#define SAVE_SETTINGS_H

#include <Preferences.h>

Preferences preferences;

void savePreferences(){
    preferences.begin("settings", false);
    //AC plug status
    preferences.putString("elementStatus1", elementStatus1);
    preferences.putString("elementStatus2", elementStatus2); 
    preferences.putString("elementStatus3", elementStatus3); 
    preferences.putString("elementStatus4", elementStatus4); 
    //DC slide values
    int duty_cycle1 = dutyCycle1;
    preferences.putString("elementStatus5", elementStatus1);
    preferences.putString("elementStatus6", elementStatus1);
    preferences.putString("elementStatus7", elementStatus1);
    preferences.putString("elementStatus8", elementStatus1);

    //Trigger Values
    preferences.putString("triggerStatus1", triggerStatus1);
    preferences.putString("triggerStatus2", triggerStatus2);
    preferences.putString("triggerStatus3", triggerStatus3);
    preferences.putString("triggerStatus4", triggerStatus4);
    preferences.putString("triggerStatus5", triggerStatus5);
    preferences.putString("triggerStatus6", triggerStatus6);
    preferences.putString("triggerStatus7", triggerStatus7);
    preferences.putString("triggerStatus8", triggerStatus8);


    preferences.putString("sliderValue1", sliderValue1);
    preferences.putString("sliderValue2", sliderValue2);
    preferences.putString("sliderValue3", sliderValue3);
    preferences.putString("sliderValue4", sliderValue4);

   
    

    preferences.end();
    toutln("Preferences Saved");
    tout("Saved elementStatus2 : "); toutln(elementStatus2);
    tout("duty1 :"); toutln(dutyCycle1);
    tout("duty2 :"); toutln(dutyCycle2);
    tout("sliderValue1 : "); toutln(sliderValue1);

}

void loadPreferences(){
    preferences.begin("settings", true);
    //AC plug status
    elementStatus1 = preferences.getString("elementStatus1", "off");
    elementStatus2 = preferences.getString("elementStatus2", "off");
    elementStatus3 = preferences.getString("elementStatus3", "off");
    elementStatus4 = preferences.getString("elementStatus4", "off"); 
    //DC slide Values
    elementStatus5 = preferences.getString("elementStatus5", "off"); 
    elementStatus6 = preferences.getString("elementStatus6", "off"); 
    elementStatus7 = preferences.getString("elementStatus7", "off"); 
    elementStatus8 = preferences.getString("elementStatus8", "off"); 

    //Trigger Values
    triggerStatus1 = preferences.getString("triggerStatus1", "manual");
    triggerStatus2 = preferences.getString("triggerStatus2", "manual");
    triggerStatus3 = preferences.getString("triggerStatus3", "manual");
    triggerStatus4 = preferences.getString("triggerStatus4", "manual");

    triggerStatus5 = preferences.getString("triggerStatus5", "manual");
    triggerStatus6 = preferences.getString("triggerStatus6", "manual");
    triggerStatus7 = preferences.getString("triggerStatus7", "manual");
    triggerStatus8 = preferences.getString("triggerStatus8", "manual");


    sliderValue1 = preferences.getString("sliderValue1","0");
    sliderValue2 = preferences.getString("sliderValue2","0");
    sliderValue3 = preferences.getString("sliderValue3","0");
    sliderValue4 = preferences.getString("sliderValue4","0");

 

    preferences.end();
    toutln("preferences Loaded: ");
    tout("plugstatus2 :");tout(elementStatus2);
    tout("duty1 :"); toutln(dutyCycle1);
    tout("duty2 :"); toutln(dutyCycle2);
    tout("sliderValue1 : "); toutln(sliderValue1);
}



#endif
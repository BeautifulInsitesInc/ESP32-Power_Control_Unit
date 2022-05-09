var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

// INITIALIZTION
window.addEventListener('load', onLoad);

function onLoad(event) {initWebSocket();}
function getValues(){websocket.send("getValues");}

function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage;
}

function onOpen(event) {console.log('Connection opened'); getValues();}
function onClose(event) {console.log('Connection closed'); setTimeout(initWebSocket, 2000);} 
function saveSettings(){console.log("Save Button was pressed");websocket.send("saveSettings");}
function loadSettings(){console.log("Load Settings Button was pressed"); websocket.send("loadSettings");}


// ===================== SEND STATUS CHANGES =========================
/* html ids
    Main switch on/off  - element itself : element1
                        - State : elementStatus1
    Trigger section     - trigger selection : triggerSelection1
                            Selection Indexes: manual0, alwaysON1, timeClock2, timeCycle3, sensor4, linked5
        timeclock section   timeclockID : clockTime1
                            button : clockTimeButton1
        timecycle section   timecycleID: cycleTime1
                            Button: cycleTimeButton1
    Sliders             - element itself: slider1
                        - Speed: sliderValue1
*/

// ON/OFF STATUS CHANGE
function updateStatus(element) {  
    var elementNumber = element.id.charAt(element.id.length-1);
    if (element.checked){
        document.getElementById("elementStatus"+elementNumber).innerHTML = "ON!";
        elementStatus = "on";
        // Disable the slider
        if (elementNumber>4) {
            document.getElementById("slider"+elementNumber).removeAttribute('disabled');
            var sliderValue = document.getElementById("slider"+elementNumber).value;
        }
    }
    else {
        document.getElementById("elementStatus"+elementNumber).innerHTML = "OFF";
        elementStatus = "off";
        // Enable the slider
        if (elementNumber>4) document.getElementById("slider"+elementNumber).setAttribute("disabled","true"); 
    }
    // Send S1on = "Status", Element 1, on/off
    var statusUpdate = "S" + elementNumber + elementStatus;
    websocket.send(statusUpdate);
    if (elementNumber>4) {websocket.send("M"+elementNumber+sliderValue.toString());}
}
// SLIDER VALUE CHANGE
function updateSliderPWM(element) {  
    var elementNumber = element.id.charAt(element.id.length-1);
    var sliderValue = document.getElementById(element.id).value;
    document.getElementById("sliderValue"+elementNumber).innerHTML = sliderValue;
    websocket.send("M"+elementNumber+sliderValue.toString());
}
// TRIGGER CHANGE
function triggerChange(element){
    var elementNumber = element.id.charAt(element.id.length-1);
    var triggerSelection = element.value;
    var triggerSelectionIndex = element.value.charAt(element.value.length-1);
    console.log("recieved trigger from plugNumber: "+ elementNumber +" triggerSelection : " + triggerSelection+" index number: "+triggerSelectionIndex);
    websocket.send("T"+elementNumber+triggerSelectionIndex);
}
// =========== END SEND STATUS CHANGES =================


// SETUP TIME CYCLE
function setCycleTime(element){
    var elementNumber = element.id.charAt(element.id.length-1);
    var cycleTimeOn = document.getElementById("cycleTimeOn"+elementNumber).value;
    var cycleTimeOff = document.getElementById("cycleTimeOff"+elementNumber).value;
    console.log("elementNumber :"+elementNumber+" cycletimeONe: "+cycleTimeOn);
    websocket.send("cycle-"+elementNumber+"-"+cycleTimeOn+"-"+cycleTimeOff);
}

function onMessage(event) {
    console.log("Recieved message : ");
    console.log(event.data);
    var myObj = JSON.parse(event.data);
    var keys = Object.keys(myObj)

    for (var i = 0; i < keys.length; i++){
        var key = keys[i];
        var itemType = key.substring(0,4); //  e = element on/off s= slider t = trigger
        var elementNumber = key.charAt(key.length-1);
        var keyValue = myObj[key];
        var triggerValueIndex = keyValue.charAt(keyValue.length-1); // if its a trigger get the idex from the last characture
        console.log("Counter:" + i + " Item:" + itemType + " Element:"+elementNumber + " key:"+ key + " Value:" + keyValue+ " triggerValueIndex = "+triggerValueIndex);
        
        // === STATUS ON/OFF UPDATE =====
        if (itemType == "elem"){
            var elementID = "element" + elementNumber;
            var elementStatusID = "elementStatus" + elementNumber;
            if (keyValue == "on"){
                document.getElementById(elementID).checked = true;
                document.getElementById(elementStatusID).innerHTML = "ON";
                if (elementNumber>4) document.getElementById("slider"+elementNumber).removeAttribute('disabled');

            } else {
                document.getElementById(elementID).checked = false;
                document.getElementById(elementStatusID).innerHTML = "OFF";
                if (elementNumber>4) document.getElementById("slider"+elementNumber).setAttribute("disabled","true");

            } 
        }
        
        // ==== SLIDER VALUE UDPATE
        if (itemType == "slid"){
            document.getElementById(key).innerHTML = keyValue;
            document.getElementById("slider"+ elementNumber.toString()).value = myObj[key];
        }

        // === UPDATE SENSOR VALUES
        if (key == "airTempC") document.getElementById(key).innerHTML = keyValue;
        if (key == "airTempF")document.getElementById(key).innerHTML = keyValue;
        if (key == "humidity")document.getElementById(key).innerHTML = keyValue;
        if (key == "fullDate")document.getElementById(key).innerHTML = keyValue;

        // == UPDATE TRIGGER VALUES
        if (itemType == "trig"){
            document.getElementById(key).selectedIndex = triggerValueIndex;
            // == SHOW OR HIDE TRIGGER VALUE INFORMATION
            switch(triggerValueIndex) {
                case '0': //manual0
                    document.getElementById("clockTime"+elementNumber).style.display="none";
                    document.getElementById("cycleTime"+elementNumber).style.display="none";
                    break;
                case '1': //alwasyON1
                    document.getElementById("clockTime"+elementNumber).style.display="none";
                    document.getElementById("cycleTime"+elementNumber).style.display="none";
                    break;
                case '2': //clockTime
                    document.getElementById("clockTime"+elementNumber).style.display="block";
                    document.getElementById("cycleTime"+elementNumber).style.display="none";
                    break;
                case '3': //cycletime
                    document.getElementById("clockTime"+elementNumber).style.display="none";
                    document.getElementById("cycleTime"+elementNumber).style.display="block";
                    break;
                case '4': //sensor4
                    document.getElementById("clockTime"+elementNumber).style.display="none";
                    document.getElementById("cycleTime"+elementNumber).style.display="none";
                    break;
                case '5': //linked5
                    ent.getElementById("clockTime"+elementNumber).style.display="none";
                    document.getElementById("cycleTime"+elementNumber).style.display="none";
                    break;
            }
        }
        if (itemType =="cycl"){
            document.getElementById(key).innerHTML = keyValue;
        }

        if (itemType == "coun"){
            document.getElementById(key).innerHTML = keyValue;
        }

    }
}
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
// ON/OFF STATUS CHANGE
function updateStatus(element) {  
    var elementNumber = element.id.charAt(element.id.length-1);
    if (element.checked){document.getElementById("elementStatus"+elementNumber).innerHTML = "ON!"; elementStatus = "on";}
    else {document.getElementById("elementStatus"+elementNumber).innerHTML = "OFF"; elementStatus = "off";    }

    // Send S1on = "Status", Element 1, on/off
    var statusUpdate = "S" + elementNumber + elementStatus;
    websocket.send(statusUpdate);
}
// SLIDER VALUE CHANGE
function updateSliderPWM(element) {  
    var elementNumber = element.id.charAt(element.id.length-1);
    var sliderValue = document.getElementById(element.id).value;
    document.getElementById("sliderValue"+sliderNumber).innerHTML = sliderValue;
    websocket.send("M"+elementNumber+sliderValue.toString());
}

function triggerChange(element){
    var elementNumber = element.id.charAt(element.id.length-1);
    var triggerSelection = element.value;
    var triggerSelectionIndex = element.value.charAt(element.value.length-1);
    console.log("recieved trigger from plugNumber: "+ plugNumber +" triggerSelection : " + triggerSelection+" index number: "+triggerSelectionIndex);
    websocket.send("T"+elementNumber+triggerSelectionIndex);
}
// =========== END SEND STATUS CHANGES =================


// SETUP TIME CYCLE
function setCycleTime(element){
    var elementNumber = element.id;
    console.log("elementNumber :"+elementNumber);

}

function onMessage(event) {
    console.log("Recieved message : ");
    console.log(event.data);
    var myObj = JSON.parse(event.data);
    var keys = Object.keys(myObj)

    for (var i = 0; i < keys.length; i++){
        var key = keys[i];
        var itemType = key.charAt(0); //  e = element on/off s= slider t = trigger
        var elementNumber = key.charAt(key.length-1);
        var keyValue = myObj[key];
        var triggerValueIndex = keyValue.charAt(keyValue.length-1); // if its a trigger get the idex from the last characture
        console.log("Counter:" + i + " Item:" + itemType + " Element:"+elementNumber + " key:"+ key + " Value:" + keyValue+ " triggerValueIndex = "+triggerValueIndex);
        
        // === STATUS ON/OFF UPDATE =====
        if (itemType == "e"){
            var elementID = "element" + elementNumber;
            var elementStatusID = "elementStatus" + elementNumber;
            if (keyValue == "on"){
                document.getElementById(elementID).checked = true;
                document.getElementById(elementStatusID).innerHTML = "ON";
            } else {
                document.getElementById(elementID).checked = false;
                document.getElementById(elementStatusID).innerHTML = "OFF";
            } 
        }
        
        // ==== SLIDER VALUE UDPATE
        if (itemType == "s"){
            document.getElementById(key).innerHTML = keyValue;
            document.getElementById("slider"+ elementNumber.toString()).value = myObj[key];
        }

        // === UPDATE SENSOR VALUES
        if (key == "airTempC") document.getElementById(key).innerHTML = keyValue;
        if (key == "airTempF")document.getElementById(key).innerHTML = keyValue;
        if (key == "humidity")document.getElementById(key).innerHTML = keyValue;

        // == UPDATE TRIGGER VALUES
        if (itemType == "t"){
            document.getElementById(key).selectedIndex = triggerValueIndex;
            console.log("just changed selected to idex : "+triggerValueIndex+" for key :"+key+" with value:"+keyValue);
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
    }
}
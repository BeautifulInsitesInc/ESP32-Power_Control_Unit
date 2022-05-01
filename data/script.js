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

function onOpen(event) {
    console.log('Connection opened');
    getValues();
}
  
function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
} 
// Save Button
function saveSettings(){
    console.log("Save Button was pressed");
    websocket.send("saveSettings");
}

// Rest Button
function loadSettings(){
    console.log("Load Settings Button was pressed");
    websocket.send("loadSettings");
}

// ON/OFF STATUS CHANGE
function updateStatus(element) {  
    var elementNumber = element.id.charAt(element.id.length-1);
    if (element.checked){
        document.getElementById("elementStatus"+elementNumber).innerHTML = "ON!";
        elementStatus = "on";
    }
    else {
        document.getElementById("elementStatus"+elementNumber).innerHTML = "OFF"; 
        elementStatus = "off";
    }

    // Send S1on = "Status", Element 1, on/off
    var plugDeviceStatus = "S" + elementNumber + elementStatus;

    websocket.send(plugDeviceStatus);
}




function triggerChange(element){
    var plugNumber = element.id.charAt(element.id.length-1);
    var triggerSelection = element.value;
    var triggerSelectionIndex = element.value.charAt(element.value.length-1);
    console.log("recieved trigger from plugNumber: "+ plugNumber +" triggerSelection : " + triggerSelection+" index number: "+triggerSelectionIndex);
    var triggerCode = "T"+plugNumber+triggerSelectionIndex;
    console.log("Sending message : "+triggerCode);
    websocket.send(triggerCode);
    
}

// DC SLIDERS
function updateSliderPWM(element) {  
    var sliderNumber = element.id.charAt(element.id.length-1);
    var sliderValue = document.getElementById(element.id).value;
    document.getElementById("sliderValue"+sliderNumber).innerHTML = sliderValue;
    websocket.send(sliderNumber+"s"+sliderValue.toString());
}

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
        var itemType = key.charAt(0);
        var elementNumber = key.charAt(key.length-1);
        var keyValue = myObj[key];
        var triggerValueIndex = keyValue.charAt(keyValue.length-1);
        console.log("Counter:" + i + " Item:" + itemType + " Element:"+elementNumber + " key:"+ key + " Value:" + keyValue+ " triggerValueIndex = "+triggerValueIndex);
        if (itemType == "p"){
            var switchID = "plug" + elementNumber;
            var switchStateID = "elementStatus" + elementNumber;
            if (keyValue == "on"){
                document.getElementById(switchID).checked = true;
                document.getElementById(switchStateID).innerHTML = "ON";
            } else {
                document.getElementById(switchID).checked = false;
                document.getElementById(switchStateID).innerHTML = "OFF";
            } 
        }
       
        if (itemType == "s"){
            document.getElementById(key).innerHTML = keyValue;
            document.getElementById("slider"+ elementNumber.toString()).value = myObj[key];
        }

        if (key == "airTempC") document.getElementById(key).innerHTML = keyValue;
        if (key == "airTempF")document.getElementById(key).innerHTML = keyValue;
        if (key == "humidity")document.getElementById(key).innerHTML = keyValue;

        //if (key == "triggerPlug1")document.getElementById(key).innerHTML = keyValue;
        if (itemType == "t"){
            document.getElementById(key).selectedIndex = triggerValueIndex;
            console.log("just changed selected to idex : "+triggerValueIndex+" for key :"+key+" with value:"+keyValue);
            switch(triggerValueIndex) {
                case '0': //manual0
                    document.getElementById("plugTimeCycle"+elementNumber).style.display="none";
                    break;
                case '1': //alwasyON1
                    document.getElementById("plugTimeCycle"+elementNumber).style.display="block";
                    break;
                case '2': //timeClock2
                    document.getElementById("plugTimeCycle"+elementNumber).style.display="none";
                    break;
                case '3': //timeCycle3
                    document.getElementById("plugTimeCycle"+elementNumber).style.display="block";
                    break;
                case '4': //sensor4
                    document.getElementById("plugTimeCycle"+elementNumber).style.display="none";
                    break;
                case '5': //linked5
                    document.getElementById("plugTimeCycle"+elementNumber).style.display="none";
                    break;
            }

        }
    }
}
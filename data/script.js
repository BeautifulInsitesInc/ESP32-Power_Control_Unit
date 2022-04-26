var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

// INITIALIZTION
window.addEventListener('load', onLoad);

function onLoad(event) {
    initWebSocket();
}

function getValues(){
    websocket.send("getValues");
}

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
// PLUG TOGGLES
function updatePlugs(element) {  
    var plugNumber = element.id.charAt(element.id.length-1);
    /*console.log("plugNumber :"+plugNumber+ "     plugStatus :" + plugStatus);*/
    /*console.log("Updating PLuging, sending this : " + plugDeviceStatus+ " plugstatus: "+plugStatus); */
    if (element.checked){
        document.getElementById("plugStatus"+plugNumber).innerHTML = "ON!";
        plugStatus = "on";
    }
    else {
        document.getElementById("plugStatus"+plugNumber).innerHTML = "OFF"; 
        plugStatus = "off";
    }
    //var plugStatus = document.getElementById(element.id).value;
    var plugDeviceStatus = plugNumber + "p" + plugStatus;
    websocket.send(plugDeviceStatus);
}

// DC SLIDERS
function updateSliderPWM(element) {  
    var sliderNumber = element.id.charAt(element.id.length-1);
    var sliderValue = document.getElementById(element.id).value;
    document.getElementById("sliderValue"+sliderNumber).innerHTML = sliderValue;
    websocket.send(sliderNumber+"s"+sliderValue.toString());
}

function onMessage(event) {
    console.log("Recieved message : ");
    console.log(event.data);
    var myObj = JSON.parse(event.data);
    var keys = Object.keys(myObj)

    for (var i = 0; i < keys.length; i++){
        var key = keys[i];
        var jackType = key.charAt(0);
        var elementNumber = key.charAt(key.length-1);
        var keyValue = myObj[key];
        //console.log("Counter:" + i + " Jack:" + jackType + " Element:"+elementNumber + " key:"+ key + " Value:" + keyValue);
        
        if (jackType == "p"){
            var switchID = "plug" + elementNumber;
            var switchStateID = "plugStatus" + elementNumber;
            if (keyValue == "on"){
                document.getElementById(switchID).checked = true;
                document.getElementById(switchStateID).innerHTML = "ON";
            } else {
                document.getElementById(switchID).checked = false;
                document.getElementById(switchStateID).innerHTML = "OFF";
            } 
        }
       
        if (jackType == "s"){
            document.getElementById(key).innerHTML = keyValue;
            document.getElementById("slider"+ elementNumber.toString()).value = myObj[key];
        }

        if (key == "airTempC"){
            document.getElementById(key).innerHTML = keyValue;
        }

        if (key == "airTempF")document.getElementById(key).innerHTML = keyValue;
        if (key == "humidity")document.getElementById(key).innerHTML = keyValue;
    }
}
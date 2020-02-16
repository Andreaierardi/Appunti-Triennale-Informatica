/* Pagina iniziale per effettuare il login */

var usr= "";
var host ="193.206.55.23";
var dati= Array();
console.log(host);
var client = new Paho.MQTT.Client(host, Number(9001),"client");
var options = {  onSuccess:onConnect, }

// connect the client
client.connect(options);
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("onConnect");
  client.subscribe("from/retilab/reti8/client/#");

}
// called when the client loses its connection
function onConnectionLost(responseObject) {
  console.log("Connection lost");
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:"+responseObject.errorMessage);
  }
}

function onMessageArrived(message) {

  console.log("onMessageArrived:"+message.payloadString);
  var msgsplit= message.payloadString.split(",");
  if(message.payloadString=="logout")
  {
    return;
  }

  if(msgsplit[1] && msgsplit[0])
  {
    var tipo = msgsplit[1].trim();
    var ack =   msgsplit[0].trim();
  }

  if(ack=="OK")
  {
    mqtt_message = new Paho.MQTT.Message(dati["username"]);
    mqtt_message.destinationName = "from/retilab/reti8/db/risposta/utente"; //+this.name;

    console.log("Message Sent: "+mqtt_message.payloadString);
    console.log("Topic Sent: "+mqtt_message.destinationName );

    client.send(mqtt_message);
    console.log(mqtt_message);

    if(tipo == "atleta")
    window.location.href = "loginAtleta.html?="+dati["username"];
    if(tipo == "trainer")
    window.location.href = "loginTrainer.html?="+dati["username"];

  }
  else
  showError();

}

function parseDati()
{
  var formElements=document.getElementById("form-login").elements;
  var postData={};
  for (var i=0; i<formElements.length; i++)
  if (formElements[i].type!="submit")//Non si vuole includere il bottone di submit
  postData[formElements[i].name]=formElements[i].value;
  return postData;
}

function inviaDati()
{
  dati= parseDati();
  var messaggio = "check:"+dati["username"]+","+dati["password"];
  usr = dati["username"];
  console.log(messaggio);
  mqtt_message = new Paho.MQTT.Message(messaggio);
  mqtt_message.destinationName = "from/retilab/reti8/db/login"

  console.log("Message Sent: "+mqtt_message.payloadString);
  client.send(mqtt_message);
  console.log(mqtt_message);
}

function showError()
{
  var el = document.getElementById("alert");
  el.style = "display: block";
}


var user = window.location.href.split('/').pop().split("=");
user = user[1];
var rip = 0;
var flag = false;
var flag_stop = true;
var scheda = true;
var peso = 0;

var host ="193.206.55.23";
console.log(host);
var client = new Paho.MQTT.Client(host, Number(9001),"client_atleta");

// set callback handlers
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;


// connect the client
client.connect({onSuccess:onConnect});


// called when the client connects
function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("onConnect");
  client.subscribe("smartbench/controlloresponse/#");
  client.subscribe("from/retilab/reti8/client/#");
  schedaPiano();
}


// called when the client loses its connection
function onConnectionLost(responseObject) {
  console.log("Connection lost");
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:"+responseObject.errorMessage);
  }
}

function settaIMG(x)
{
  x.setAttribute("src","img/static.gif");
  x.style.margin="auto";

}

function iterScheda(item, index, array)
{

  let splitto = array[index].split(";");
  var stringa = ""
  for(var ind in splitto)
  {
    if(ind!='unique')
    {
      var node = document.createElement("LI");
      node.className= 'list-group';
      node.innerHTML+= splitto[ind];
      node.style.border= "border 1px solid lightgray";
      node.style.padding = "5px 5px 5px 5px";
      document.getElementById("scheda").appendChild(node);
    }
  }

}



function onMessageArrived(message)
{
  var ms =message.payloadString;
  var topic = message.destinationName;
  var count = 0 ;

  var arg = topic.split("/");
  for (i in arg)
  count++;
  console.log("Messaggio sul topic: " +arg);
  console.log("TOPIC:   " +arg[count-1]);
  console.log("client ricevo: "+ms);

  if(arg[count-1]=="dati")
  {
    if(ms=="posato")
    {
      posato();
      return;
    }
    if(ms="nonposato" && flag_stop)
    {
      nonposato();
      return;
    }
  }

  else {
    if(ms=="logout")
      window.location.href="index.html";

      
    console.log("FLAG_STOP : "+flag_stop);
    if(flag_stop)
    {
      let prec = document.getElementById("sub");
      var value = ms.split(":");
      console.log(value[0]+" "+value[1]);

      if(scheda)
      {
        console.log("Costruisco la scheda del piano");
        if(ms=="ERRORE")
        ms = "Nessuno presente";
        var m = ms.split('-');

        m.forEach(iterScheda);
        scheda = false;
        return;
      }
      show("result");

      if(ms == "allarme")
      {

        solido("buttonpiano");
        solido("buttonstorico");
        solido("buttonallenamento");
        solido("buttonlogout");

        show("start");
        hide("stop");

        let child = prec.lastElementChild;

        while (child) {
          prec.removeChild(child);
          child = prec.lastElementChild;
        }

        var x = document.createElement("IMG");
        x.setAttribute("src", "img/emergency.gif");                           // Append the text to <li>
        document.getElementById("sub").appendChild(x);
        x.setAttribute("width", "200");
        x.setAttribute("height", "200");
        x.setAttribute("text-align", "center");
        x.style.margin="auto";

        var node = document.createElement("LI");

        node.className= 'list-group'// Create a text node
        document.getElementById("sub").appendChild(node);

        writeLI("Allenamento terminato, chiamare subito i soccorsi");
        mqtt_message = new Paho.MQTT.Message("stop()");
        mqtt_message.destinationName = "from/retilab/reti8/cmd" //+this.name;
        console.log("Message Sent: "+mqtt_message.payloadString);
        console.log(mqtt_message);
        client.send(mqtt_message);
        return;
      }

      if(ms =="pull" || value[0] == "riducipeso" || value[0] =="setpeso")
      {

        let child = prec.lastElementChild;

        while (child) {
          prec.removeChild(child);
          child = prec.lastElementChild;
        }

        var node = document.createElement("LI");

        var x = document.createElement("IMG");
        document.getElementById("sub").appendChild(x);
        x.setAttribute("width", "200");
        x.setAttribute("height", "200");
        x.setAttribute("text-align", "center");
        x.style.margin="auto";

        if(ms =="pull")
        {
          x.setAttribute("src", "img/animated.gif");
          rip += 1;
        }
        if(ms != "pull")
        x.setAttribute("src", "img/static.gif");

        node.className= 'list-group';

        var rp = "<img src='img/push.png' style='width:30px';height:30px; display:inline-block>";
        node.innerHTML+= "<p>"+rp + " Ripetizioni eseguite: <re id='valuehigh'>"+rip+"</re> </p>";

        setTimeout(function(){ settaIMG(x);}, 900);

        if(value[1]!=undefined)
        peso = value[1];

        var p = "<img src='img/peso.png' style='width:30px';height:30px; display:inline-block>";

        node.innerHTML+= "<p>"+p + " Peso corrente: <re id='valuehigh'>"+peso+"</re></p>";
        node.className= 'list-group'// Create a text node

        document.getElementById("sub").appendChild(node);

        return;
      }


      else if(ms =="ERRORE")
      {
        let child = prec.lastElementChild;
        while (child) {
          prec.removeChild(child);
          child = prec.lastElementChild;
        }

        var node = document.createElement("LI");
        var textnode = document.createTextNode("Nessuno presente");
        node.className= 'list-group-item'
        node.appendChild(textnode);
        document.getElementById("sub").appendChild(node);
        return;

      }

      if(flag)
      {

        flag = false;
        show("start");
        hide("stop");

        var m = ms.split('-');
        console.log(m);
        m.forEach(iter);
        writeLI("FINE allenamento");

        solido("buttonpiano");
        solido("buttonstorico");
        solido("buttonallenamento");
        solido("buttonlogout");
        mqtt_message = new Paho.MQTT.Message("stop()");
        mqtt_message.destinationName = "from/retilab/reti8/cmd"
        console.log("Message Sent: "+mqtt_message.payloadString);
        console.log(mqtt_message);
        client.send(mqtt_message);


      }

      else {
        child = prec.lastElementChild;
        while (child) {
          prec.removeChild(child);
          child = prec.lastElementChild;
        }
        var m = ms.split('-');
        m.forEach(iter);


        mqtt_message = new Paho.MQTT.Message("stop()");
        mqtt_message.destinationName = "from/retilab/reti8/cmd" //+this.name;
        console.log("Message Sent: "+mqtt_message.payloadString);
        console.log(mqtt_message);
        client.send(mqtt_message);

      }

    }
  }

}


function iter(item, index, array)
{
  var node = document.createElement("LI");


  let splitto = array[index].split(";");
  var stringa = "";
  for(var ind in splitto)
  {
    console.log("IND: "+ind);
    if(ind!='unique')
    stringa += splitto[ind] +"<br>";

    //string += splitto[ind] +"<br>";
  }
  node.className= 'list-group'
  node.innerHTML+=stringa;
  document.getElementById("sub").appendChild(node);
  console.log("APPENDO"+stringa);
}


function writeLI(text)
{
  var node = document.createElement("LI");
  var textnode = document.createTextNode(text);
  node.className= 'list-group';
  node.appendChild(textnode);
  document.getElementById("sub").appendChild(node);
}

function startAllenamento()
{

  trasparente("buttonpiano");
  trasparente("buttonstorico");
  trasparente("buttonallenamento");
  trasparente("buttonlogout");


  flag_stop = true;

  peso = 0 ;
  rip = 0;

  var prec = document.getElementById("sub");

  while(prec)
  {

    let child = prec.lastElementChild;
    if(child)
    prec.removeChild(child);
    else
      break;

  }
  flag = true;
  var w2 = document.getElementById("sub");
  let child3 = w2.lastElementChild;
  if (child3)
    w2.removeChild(child3);


  var h1= document.createElement('H1');
  h1.innerHTML = "Stato allenamento";
  h1.style.color= "white";

  var w = document.getElementById("write");
  let child = w.lastElementChild;
  if (child)
    w.removeChild(child);
  w.appendChild(h1);

  show("result");

  writeLI("In allenamento...");

  var x = document.createElement("IMG");
  x.setAttribute("id" , "immagine");
  x.setAttribute("src", "img/static.gif");
  document.getElementById("sub").appendChild(x);
  x.setAttribute("width", "200");
  x.setAttribute("height", "200");
  x.setAttribute("text-align","center");
  x.style.margin="auto";
  x.setAttribute("src", "img/static.gif");
  hide("start");

  timeFunction("stop") ;


  mqtt_message = new Paho.MQTT.Message("start()");
  mqtt_message.destinationName = "from/retilab/reti8/cmd" //+this.name;
  console.log("Message Sent: "+mqtt_message.payloadString);
  console.log(mqtt_message);
  client.send(mqtt_message);




}

function stopAllenamento()
{
  hide("stop");
  posato();
  solido("buttonpiano");
  solido("buttonstorico");
  solido("buttonallenamento");
  solido("buttonlogout");
  flag_stop = false;
  rip = 0;
  peso = 0 ;


  var h1= document.createElement('H1');
  h1.innerHTML = "Stato allenamento";
  h1.style.color= "white";

  var w = document.getElementById("write");
  let child2 = w.lastElementChild;
  if(child2)
    w.removeChild(child2);
  w.appendChild(h1);

  var prec = document.getElementById("sub");

  while(prec)
  {

    let child = prec.lastElementChild;
    if(child)
      prec.removeChild(child);
    else
    break;

  }

  var node = document.createElement("LI");
  var textnode = document.createTextNode("Allenamento interrotto");
  node.className= 'list-group'
  node.appendChild(textnode);
  document.getElementById("sub").appendChild(node);

  mqtt_message = new Paho.MQTT.Message("stop()");
  mqtt_message.destinationName = "from/retilab/reti8/cmd";
  console.log("Message Sent: "+mqtt_message.payloadString);
  console.log(mqtt_message);
  client.send(mqtt_message);
  timeFunction("start") ;
  delayFlag();


}

function delayFlag()
{
  setTimeout(function(){ flag_stop = true; }, 1500);
}


function exitControllo()
{
  mqtt_message = new Paho.MQTT.Message("exit()");
  mqtt_message.destinationName = "from/retilab/reti8/cmd";
  console.log("Message Sent: "+mqtt_message.payloadString);
  console.log(mqtt_message);
  client.send(mqtt_message);

}
function hide(id)
{
  var b= document.getElementById(id);
  b.style.display=" none";
}
function show(id)
{
  var bs = document.getElementById(id);
  bs.style.display = "block";
}

function timeFunction(id) {
  setTimeout(function(){  show(id); }, 300);
}


function visualizzaAllenamenti()
{

  var h1= document.createElement('H1');
  h1.innerHTML = "Storico allenamenti";
  h1.style.color= "white";

  var w = document.getElementById("write");
  let child = w.lastElementChild;
  if (child)
  w.removeChild(child);
  w.appendChild(h1);

  mqtt_message = new Paho.MQTT.Message("ultimo_allenamento");
  mqtt_message.destinationName = "from/retilab/reti8/db/ricerca_all/"+user;//+this.name;
  console.log("Message Sent: "+mqtt_message.payloadString);
  console.log("ON TOPIC: "+mqtt_message.destinationName);
  client.send(mqtt_message);
}
function visualizzaUltimoAllenamento()
{
  var w = document.getElementById("write");



  let child = w.lastElementChild;
  if (child)
    w.removeChild(child);
  var h1= document.createElement('H1');
  h1.innerHTML = "Performance ultimo allenamento";
  h1.style.color= "white"

  w.appendChild(h1);


  mqtt_message = new Paho.MQTT.Message("ricerca_ultimo_all");
  mqtt_message.destinationName = "from/retilab/reti8/db/ricerca_ultimo_all/"+user //+this.name;
  console.log("Message Sent: "+mqtt_message.payloadString);
  console.log("ON TOPIC: "+mqtt_message.destinationName);
  client.send(mqtt_message);
}

function visualizzaUltimoPiano()
{

  var h1= document.createElement('H1');
  h1.innerHTML = "Piano di allenamento attuale";
  h1.style.color= "white"

  var w = document.getElementById("write");
  let child = w.lastElementChild;
  if (child)
  w.removeChild(child);
  w.appendChild(h1);
  mqtt_message = new Paho.MQTT.Message("ricerca_ultimo_piano");
  mqtt_message.destinationName = "from/retilab/reti8/db/ricerca_ultimo_piano/"+user //+this.name;
  console.log("Message Sent: "+mqtt_message.payloadString);
  console.log("ON TOPIC: "+mqtt_message.destinationName);
  client.send(mqtt_message);

}


function redirect(){


  mqtt_message = new Paho.MQTT.Message("logout");
  mqtt_message.destinationName = "from/retilab/reti8/cmd/logout";
  console.log("Message Sent: "+mqtt_message.payloadString);
  console.log("ON TOPIC: "+mqtt_message.destinationName);
  client.send(mqtt_message);
  window.location.href="index.html";
}
function schedaPiano()
{
  mqtt_message = new Paho.MQTT.Message("ricerca_ultimo_piano");
  mqtt_message.destinationName = "from/retilab/reti8/db/ricerca_ultimo_piano/"+user //+this.name;
  console.log("Message Sent: "+mqtt_message.payloadString);
  console.log("ON TOPIC: "+mqtt_message.destinationName);
  client.send(mqtt_message);
}


function trasparente(id)
{
  var tr= document.getElementById(id);
  tr.style.visibility="hidden";
}

function solido(id)
{
  var sl= document.getElementById(id);
  sl.style.visibility="visible";
}

function posato()
{
  var pos = document.getElementById("posato");
  pos.setAttribute("src","img/sensorON.png");
  var crd = document.getElementById("descr");
  crd.innerHTML= "Bilanciere in sede..";


}

function nonposato()
{
  var pos = document.getElementById("posato");
  pos.setAttribute("src","img/sensorOFF.png");
  var crd = document.getElementById("descr");
  crd.innerHTML= "Bilanciere in uso..";

}


var user = window.location.href.split('/').pop().split("=");
user = user[1];
var rip = 0;
var flag = false;
var flag_stop = true;
var scheda = true;
var peso = 0;

var last="";
var last2="";
var host ="193.206.55.23";
console.log(host);
var client = new Paho.MQTT.Client(host, Number(9001),"client");

// set callback handlers
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

// connect the client
client.connect({onSuccess:onConnect});

// called when the client connects
function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("onConnect");
  client.subscribe("smartbench/controlloresponse");
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
  var stringa = "";
  for(var ind in splitto)
  {
    console.log("IND: "+ind);
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
    {
      window.location.href="index.html";
    }
    if(flag_stop)
    {
      console.log("onMessageArrived:"+message.payloadString);
      let prec = document.getElementById("sub");


      var value = ms.split(":");
      console.log(value[0]+" "+value[1]);
      if(scheda)
      {
        console.log("SCHEDAAAA");
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
        x.setAttribute("src", "img/emergency.gif");
        document.getElementById("sub").appendChild(x);
        x.setAttribute("width", "200");
        x.setAttribute("height", "200");
        x.setAttribute("text-align", "center");
        x.style.margin="auto";

        var node = document.createElement("LI");

        node.className= 'list-group';
        document.getElementById("sub").appendChild(node);

        writeLI("Allenamento terminato, chiamare subito i soccorsi");
        mqtt_message = new Paho.MQTT.Message("stop()");
        mqtt_message.destinationName = "from/retilab/reti8/cmd";
        console.log("Message Sent: "+mqtt_message.payloadString);
        console.log(mqtt_message);
        client.send(mqtt_message);
        return;
      }

      if (value[0]=="wrcheck") {

        let child = prec.lastElementChild;

        while (child) {
          prec.removeChild(child);
          child = prec.lastElementChildpeso;
        }
        var node = document.createElement("LI");
        var textnode = document.createTextNode("Piano scritto correttamente");
        node.className= 'list-group-item';
        node.appendChild(textnode);
        document.getElementById("sub").appendChild(node);
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

        console.log("OKKKK");

        if(value[1]!=undefined)
        peso = value[1];

        var p = "<img src='img/peso.png' style='width:30px';height:30px; display:inline-block>";
        node.innerHTML+= "<p>"+p + " Peso corrente: <re id='valuehigh'>"+peso+"</re></p>";
        node.className= 'list-group';

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
        node.className= 'list-group-item';
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
        mqtt_message.destinationName = "from/retilab/reti8/cmd";
        console.log("Message Sent: "+mqtt_message.payloadString);
        console.log(mqtt_message);
        client.send(mqtt_message);

      }

      else {
        let child = prec.lastElementChild;
        while (child) {
          prec.removeChild(child);
          child = prec.lastElementChild;
        }
        var m = ms.split('-');
        console.log("m: " +m);
        m.forEach(iter);

        mqtt_message = new Paho.MQTT.Message("stop()");
        mqtt_message.destinationName = "from/retilab/reti8/cmd";
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

  }
  node.className= 'list-group';
  node.innerHTML+=stringa;
  document.getElementById("sub").appendChild(node);
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

  if(last!="")
    hide(last);
  if(last2!="")
    hide(last2);
  last="result";
  removeError();
  removeError2();
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
  mqtt_message.destinationName = "from/retilab/reti8/cmd";
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
  peso = 0;


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
  node.className= 'list-group';
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


function visualizzaUltimoPiano()
{
  var h1= document.createElement('H1');
  h1.innerHTML = "Visualizza ultimo piano";
  h1.style.color= "white";

  var w = document.getElementById("write");
  let child = w.lastElementChild;
  if (child)
    w.removeChild(child);
  w.appendChild(h1);
  var dati=parseDati3();
  mqtt_message = new Paho.MQTT.Message("ricerca_ultimo_piano");
  if(dati["ultimoutente"]=="")
  dati["ultimoutente"]=undefined;
  mqtt_message.destinationName = "from/retilab/reti8/db/ricerca_ultimo_piano/"+dati["ultimoutente"];
  console.log("Message Sent: "+mqtt_message.payloadString);
  console.log("ON TOPIC: "+mqtt_message.destinationName);
  client.send(mqtt_message);

}

function parseDati()
{
  var formElements=document.getElementById("newpiano").elements;
  var postData={};
  for (var i=0; i<formElements.length; i++)
  if (formElements[i].type!="submit")
    postData[formElements[i].name]=formElements[i].value;
  last="result";
  return postData;
}

function checkNumber(x)
{
  if (isNaN(x) || x < 1 || x > 500)
  return true;
  return false;
}
function inviaDati()
{
  var dati= parseDati();
  if( dati["username"]!="" &&  dati["totRip"]!="" && dati["peso"]!="" && dati["serie"]!="")
  {
    if (dati["username"].length<3||checkNumber(dati["totRip"]) || checkNumber(dati["peso"]) || checkNumber(dati["serie"]))
    {
      removeError();
      showError2();
    }
    else {
      hide("form3");
      last="result";
      removeError();
      removeError2();
      var messaggio = "nuovopiano: "+dati["username"]+",valid,"+dati["totRip"]+","+dati["peso"]+","+dati["serie"];
      mqtt_message = new Paho.MQTT.Message(messaggio);
      mqtt_message.destinationName = "from/retilab/reti8/db/nuovopiano" //+this.name;

      console.log("Message Sent: "+mqtt_message.payloadString);
      client.send(mqtt_message);
      console.log(mqtt_message);
    }
  }
  else
  {
    removeError2();
    showError();
  }
}
function parseDati3()
{
  var formElements=document.getElementById("cercaUltimoUtente").elements;
  var postData={};
  for (var i=0; i<formElements.length; i++)
  if (formElements[i].type!="submit")//we dont want to include the submit-buttom
    postData[formElements[i].name]=formElements[i].value;
  last="result";

  return postData;
}

function parseDati2()
{
  var formElements=document.getElementById("cercaUtente").elements;
  var postData={};
  for (var i=0; i<formElements.length; i++)
  if (formElements[i].type!="submit")//we dont want to include the submit-buttom
  postData[formElements[i].name]=formElements[i].value;
  last="result";

  return postData;
}

function inviaDati2()
{
  var h1= document.createElement('H1');
  h1.innerHTML = "Storico piani";
  h1.style.color= "white";

  var w = document.getElementById("write");
  let child = w.lastElementChild;
  if (child)
    w.removeChild(child);
  w.appendChild(h1);
  var data= parseDati2();
  var messaggio= "visualizza_piani: "+data["utente"];
  console.log(messaggio);
  mqtt_message = new Paho.MQTT.Message(messaggio);
  mqtt_message.destinationName = "from/retilab/reti8/db/visualizza_piani";

  console.log("Message Sent: "+mqtt_message.payloadString);
  client.send(mqtt_message);
  console.log(mqtt_message);
}

function mostraUt()
{
  if(last!="")
    hide(last);
  if(last2!="")
    hide(last2);
  last = "form1";
  last2="form1";
  var zeta= document.getElementById("form1");
  zeta.style.display="block";
}

function mostraUltimoUt()
{
  if(last!="")
    hide(last);
  if(last2!="")
    hide(last2);
  last = "form2";
  last2="form2";

  var zeta= document.getElementById("form2");
  zeta.style.display="block";
}

function mostraNewPiano()
{
  if(last!="")
    hide(last);
  if(last2!="")
    hide(last2);
  last = "form3";
  last2 = "form3";

  var zeta= document.getElementById("form3");
  zeta.style.display="block";
}

function redirect(){
  mqtt_message = new Paho.MQTT.Message("logout");
  mqtt_message.destinationName = "from/retilab/reti8/cmd/logout";
  console.log("Message Sent: "+mqtt_message.payloadString);
  console.log("ON TOPIC: "+mqtt_message.destinationName);
  client.send(mqtt_message);
  window.location.href="index.html";
}

function showError()
{
  var el = document.getElementById("alert");
  el.style = "display: block";
}

function showError2()
{
  var el = document.getElementById("alert2");
  el.style = "display: block";
}
function removeError()
{
  var el = document.getElementById("alert");
  el.style = "display: none";
}
function removeError2()
{
  var el = document.getElementById("alert2");
  el.style = "display: none";
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

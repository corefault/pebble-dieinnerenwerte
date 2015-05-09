// Listen for when the watchface is opened
function getData() {
   var response;
   var nocache = new Date().getTime();
   var req = new XMLHttpRequest();
   // build the GET request
   req.open('GET', "http://sarah/backend/getdata.php?_=" + nocache, true);
   req.onload = function(e) {
    if (req.readyState == 4) {
      // 200 - HTTP OK
      if(req.status == 200) {
         console.log(req.responseText);
         response = JSON.parse(req.responseText);
         var dict = {"KEY_OXYGEN": response.oxygen, "KEY_BEAT": response.pulse};         
         Pebble.sendAppMessage(dict);
      } else {
        console.log("Request returned error code " + req.status.toString());
      }
    }
  };
  req.send(null);
}

Pebble.addEventListener('ready', 
  function(e) {
    getData();
  }
);

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
  function(e) {
    getData();
  }                     
);
var MessageQueue=function(){var RETRY_MAX=5;var queue=[];var sending=false;var timer=null;return{reset:reset,sendAppMessage:sendAppMessage,size:size};function reset(){queue=[];sending=false}function sendAppMessage(message,ack,nack){if(!isValidMessage(message)){return false}queue.push({message:message,ack:ack||null,nack:nack||null,attempts:0});setTimeout(function(){sendNextMessage()},1);return true}function size(){return queue.length}function isValidMessage(message){if(message!==Object(message)){return false}var keys=Object.keys(message);if(!keys.length){return false}for(var k=0;k<keys.length;k+=1){var validKey=/^[0-9a-zA-Z-_]*$/.test(keys[k]);if(!validKey){return false}var value=message[keys[k]];if(!validValue(value)){return false}}return true;function validValue(value){switch(typeof value){case"string":return true;case"number":return true;case"object":if(toString.call(value)=="[object Array]"){return true}}return false}}function sendNextMessage(){if(sending){return}var message=queue.shift();if(!message){return}message.attempts+=1;sending=true;Pebble.sendAppMessage(message.message,ack,nack);timer=setTimeout(function(){timeout()},1e3);function ack(){clearTimeout(timer);setTimeout(function(){sending=false;sendNextMessage()},200);if(message.ack){message.ack.apply(null,arguments)}}function nack(){clearTimeout(timer);if(message.attempts<RETRY_MAX){queue.unshift(message);setTimeout(function(){sending=false;sendNextMessage()},200*message.attempts)}else{if(message.nack){message.nack.apply(null,arguments)}}}function timeout(){setTimeout(function(){sending=false;sendNextMessage()},1e3);if(message.ack){message.ack.apply(null,arguments)}}}}();

var request_type = 0;

function get_simple_table(craftable){
    var table = craftable.simple_table;
    var new_table = [];
    for(var i = 0; i < 9; i++){
        if(table[i] != "."){
            new_table[i] = table[i];
        }
        else{
            new_table[i] = "";
        }
    }
    return new_table;
}

function get_advanced_table(craftable){
    var simple_table = craftable.simple_table;
    var advanced_table = craftable.advanced_table;

    var new_advanced_table = [];
    for(var i = 0; i < 9; i++){
        if(advanced_table[i].length > 3){
            new_advanced_table[i] = advanced_table[i];
        }
        else{
            var to_search = advanced_table[i];
            for(var search_i = 0; search_i < 9; search_i++){
                if(simple_table[search_i] == to_search){
                    new_advanced_table[i] = advanced_table[search_i];
                    break;
                }
            }
        }
    }
    return new_advanced_table;
}

function get_section_id(section){
    switch(section){
        case "Redstone":
            return 0;
        case "Food":
            return 1;
        case "Special":
            return 2;
        case "Building Blocks":
        case "Building":
            return 3;
        case "Decoration":
            return 4;
        case "Transportation":
            return 5;
        case "Tools/Weapons/Armour":
            return 6;
	    case "Snapshot":
		  return 7;
    }
}

function sendGetRequest(){
    console.log("Sending request for data.");
    var req = new XMLHttpRequest();
    var address = "https://raw.githubusercontent.com/KennethSchlatter/MC-API/master/minecraft_api.json";
    req.open('GET', address, true);

    req.onload = function(e) {
        console.log("changed " + req.readyState + " and " + req.status)
        if (req.readyState == 4 && req.status == 200) {
            var object = JSON.parse(req.responseText);
            var i = request_type;
            for(var i1 = 0; i1 < object.sections[i].items.length; i1++){
                var craftable = object.sections[i].items[i1];
                var simple_table = get_simple_table(craftable);
                var advanced_table = get_advanced_table(craftable);
                var item = {
                    section_id: get_section_id(object.sections[i].title),
                    section_title: object.sections[i].title,
                    item_name: craftable.item_name,
                    s_t_1: simple_table[0],
                    s_t_2: simple_table[1],
                    s_t_3: simple_table[2],
                    s_t_4: simple_table[3],
                    s_t_5: simple_table[4],
                    s_t_6: simple_table[5],
                    s_t_7: simple_table[6],
                    s_t_8: simple_table[7],
                    s_t_9: simple_table[8],
                    a_t_1: advanced_table[0],
                    a_t_2: advanced_table[1],
                    a_t_3: advanced_table[2],
                    a_t_4: advanced_table[3],
                    a_t_5: advanced_table[4],
                    a_t_6: advanced_table[5],
                    a_t_7: advanced_table[6],
                    a_t_8: advanced_table[7],
                    a_t_9: advanced_table[8]
                };
                console.log("Sending " + JSON.stringify(item));
                MessageQueue.sendAppMessage(item, function(data){

                }, function(data, error){
                    console.log("Sent error: " + error + " with data " + JSON.stringify(data));
                });
            }
        }
        else{
            console.error("Error connecting: " + req.responseText);
        }
    };
    req.send();
}

Pebble.addEventListener("appmessage", function(e){
    request_type = e.payload.MESSAGE_TYPE;
    sendGetRequest();
    console.log("Requesting data.");
});

Pebble.addEventListener("ready", function(e){
    console.log("Hello");
});

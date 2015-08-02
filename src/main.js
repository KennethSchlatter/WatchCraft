var MessageQueue=function(){var RETRY_MAX=5;var queue=[];var sending=false;var timer=null;return{reset:reset,sendAppMessage:sendAppMessage,size:size};function reset(){queue=[];sending=false}function sendAppMessage(message,ack,nack){if(!isValidMessage(message)){return false}queue.push({message:message,ack:ack||null,nack:nack||null,attempts:0});setTimeout(function(){sendNextMessage()},1);return true}function size(){return queue.length}function isValidMessage(message){if(message!==Object(message)){return false}var keys=Object.keys(message);if(!keys.length){return false}for(var k=0;k<keys.length;k+=1){var validKey=/^[0-9a-zA-Z-_]*$/.test(keys[k]);if(!validKey){return false}var value=message[keys[k]];if(!validValue(value)){return false}}return true;function validValue(value){switch(typeof value){case"string":return true;case"number":return true;case"object":if(toString.call(value)=="[object Array]"){return true}}return false}}function sendNextMessage(){if(sending){return}var message=queue.shift();if(!message){return}message.attempts+=1;sending=true;Pebble.sendAppMessage(message.message,ack,nack);timer=setTimeout(function(){timeout()},1e3);function ack(){clearTimeout(timer);setTimeout(function(){sending=false;sendNextMessage()},200);if(message.ack){message.ack.apply(null,arguments)}}function nack(){clearTimeout(timer);if(message.attempts<RETRY_MAX){queue.unshift(message);setTimeout(function(){sending=false;sendNextMessage()},200*message.attempts)}else{if(message.nack){message.nack.apply(null,arguments)}}}function timeout(){setTimeout(function(){sending=false;sendNextMessage()},1e3);if(message.ack){message.ack.apply(null,arguments)}}}}();

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

function sendGetRequest(){
    var req = new XMLHttpRequest();
    var address = "https://raw.githubusercontent.com/KennethSchlatter/MC-API/master/minecraft_api.json";
    req.open('GET', address, true);

    req.onload = function(e) {
        if (req.readyState == 4 && req.status == 200) {
            var object = JSON.parse(req.responseText);

            for(var i = 0; i < 1; i++){
                for(var i1 = 0; i1 < object.sections[i].items.length; i1++){
                    var craftable = object.sections[i].items[i1];
                    var item = {
                        name: craftable.item_name,
                        simple_table: get_simple_table(craftable),
                        advanced_table: get_advanced_table(craftable)
                    };
                    console.log("Sending " + JSON.stringify(item));
                    MessageQueue.sendAppMessage(item);
                }
            }
        }
        else{
            console.error("Error connecting: " + req.responseText);
        }
    };
    req.send();
}

Pebble.addEventListener("appmessage", function(e){
    switch(e.payload.MESSAGE_TYPE){
        case 0:
            sendGetRequest();
            break;
    }
});
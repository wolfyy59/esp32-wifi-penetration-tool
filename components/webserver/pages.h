#ifndef PAGES_H
#define PAGES_H

const char page_root[] = 
"<!DOCTYPE html>"
"<html>"
"<head>"
    "<title>ESP32 Management AP</title>"
    "<style>"
        "table, tr, th {"
            "border: 1px solid;"
            "border-collapse: collapse;"
            "text-align: center;"
        "}"
        "th, td {"
            "padding:10px;"
        "}"
        "tr:hover {"
            "background-color: lightblue;"
            "cursor:pointer;"
        "}"
    "</style>"
"</head>"
"<body onLoad=\"refreshAps()\">"
    "<h3>Available APs:</h3>"
    "<table id=\"ap-list\"></table>"
    "<button type=\"button\" onClick=\"refreshAps()\">Refresh</button>"
    "<script>"
    "function refreshAps() {"
        "document.getElementById(\"ap-list\").innerHTML = \"Loading (this may take a while)...\";"
        "var oReq = new XMLHttpRequest();"
        "oReq.onload = function() {"
            "document.getElementById(\"ap-list\").innerHTML = \"<th>SSID</th><th>BSSID</th><th>RSSI</th>\";"
            "var arrayBuffer = oReq.response;"
            "if(arrayBuffer) {"
                "var byteArray = new Uint8Array(arrayBuffer);"
                "for  (let i = 0; i < byteArray.byteLength; i = i + 40) {"
                    "var tr = document.createElement('tr');"
                    "tr.setAttribute(\"id\", i / 40);"
                    "tr.setAttribute(\"onClick\", \"apSelect(this)\");"
                    "var td_ssid = document.createElement('td');"
                    "var td_rssi = document.createElement('td');"
                    "var td_bssid = document.createElement('td');"
                    "td_ssid.innerHTML = new TextDecoder(\"utf-8\").decode(byteArray.subarray(i + 0, i + 32));"
                    "tr.appendChild(td_ssid);"
                    "for(let j = 0; j < 6; j++){"
                        "td_bssid.innerHTML += byteArray[i + 33 + j].toString(16) + \":\";"
                    "}"
                    "tr.appendChild(td_bssid);"
                    "td_rssi.innerHTML = byteArray[i + 39] - 255;"
                    "tr.appendChild(td_rssi);"
                    "document.getElementById(\"ap-list\").appendChild(tr);"
                "}"
            "}"
        "};"
        "oReq.onerror = function() {"
            "document.getElementById(\"ap-list\").innerHTML = \"ERROR\";"
        "};"
        "oReq.open(\"GET\", \"ap-list\", true);"
        "oReq.responseType = \"arraybuffer\";"
        "oReq.send();"
    "}"
    "function apSelect(el) {"
        "console.log(el.id);"
        "var arrayBuffer = new ArrayBuffer(1);"
        "var uint8Array = new Uint8Array(arrayBuffer);"
        "uint8Array[0] = parseInt(el.id);"
        "var oReq = new XMLHttpRequest();"
        "oReq.open(\"POST\", \"ap-select\", true);"
        "oReq.send(arrayBuffer);"
    "}"
    "</script>"
"</body>"
"</html>"
;

const char page_result[] = "Result page";

#endif
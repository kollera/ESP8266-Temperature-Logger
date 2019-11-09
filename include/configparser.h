#pragma once

#include "JsonListener.h"

struct ConfigData {
    String ssid;
    String pass;
    String host;
    int port = 80;
    String url;
    String update;
    int wc_p;  // max. time in seconds to connect to wifi, before giving up
    int gr_p;  // max. times of attemps to perform GET request, before giving up
    bool s_vcc;  // wether to send VCC voltage as a parameter in the url
                 // request.
    bool is_ip;        // wether host adress is IP
    String vcc_parm;   // parameter to pass VCC voltage by.
    String temp_parm;  // parameter to pass temperature by.
    long sleepTime;
};

class ConfigListener : public JsonListener {
   public:
    ConfigData config;
    void whitespace(char c) {}
    void startDocument() {}
    void key(String key) {
        currentKey = key;
    }

    void value(String value) {

        if (currentKey == "ssid") {
            config.ssid = String(value);
        } else if (currentKey == "pass") {
            config.pass = String(value);
        } else if (currentKey == "host") {
            config.host = String(value);
        } else if (currentKey == "uri") {
            config.url = String(value);
        } else if (currentKey == "update") {
            config.update = String(value);
        } else if (currentKey == "is_ip") {
            if (value == "true") {
                config.is_ip = true;
            } else {
                config.is_ip = false;
            }
        } else if (currentKey == "s_vcc") {
            if (value == "true") {
                config.s_vcc = true;
            } else {
                config.s_vcc = false;
            }
        }  else if (currentKey == "port") {
            config.port = value.toInt();
        } else if (currentKey == "wc_p") {
            config.wc_p = value.toInt();
        } else if (currentKey == "gr_p") {
            config.gr_p = value.toInt();
        } else if (currentKey == "vcc_p") {
            config.vcc_parm = String(value);
        } else if (currentKey == "temp_p") {
            config.temp_parm = String(value);
        } else if (currentKey == "sleep") {
            config.sleepTime = value.toInt();
        } else {
            Serial.print("unknown key: ");
            Serial.println(currentKey);
            // blow it up! :)
            while(true){}
        }
    }

    void endArray() {}

    void endObject() {}

    void endDocument() {}

    void startArray() {}

    void startObject() {}

   private:
    String currentKey;
};
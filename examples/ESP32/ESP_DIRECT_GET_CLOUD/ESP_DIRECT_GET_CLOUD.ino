#include <WiFiClientSecure.h>
#include <HTTPClient.h> //LIBRARY FOR HTTP
#include <WiFi.h> //LIBRARY FOR ESP WIFI FUNCTIONALITY

const char* ssid     = "XXXX";     // YOUR NETWORK SSID (name of YOUR wifi network)
const char* password = "YYYY"; // YOUR NETWORK PASSWORD

const char* host = "api.waziup.io"; //WAZIUP SERVER
const char* devID = "XXXX"; //DEVICE ID - example 605db108af408600066050ae
const char* sensorID = "YYYY"; //SENSOR ID - example temperatureSensor_1
const int http_port = 443; //HTTP PORT

const char* root_cert = \
                        "-----BEGIN CERTIFICATE-----\n" \
                        "MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw\n" \
                        "TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n" \
                        "cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4\n" \
                        "WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu\n" \
                        "ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY\n" \
                        "MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc\n" \
                        "h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+\n" \
                        "0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U\n" \
                        "A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW\n" \
                        "T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH\n" \
                        "B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC\n" \
                        "B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv\n" \
                        "KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn\n" \
                        "OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn\n" \
                        "jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw\n" \
                        "qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI\n" \
                        "rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV\n" \
                        "HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq\n" \
                        "hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL\n" \
                        "ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ\n" \
                        "3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK\n" \
                        "NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5\n" \
                        "ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur\n" \
                        "TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC\n" \
                        "jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc\n" \
                        "oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq\n" \
                        "4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA\n" \
                        "mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d\n" \
                        "emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=\n" \
                        "-----END CERTIFICATE-----\n";

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  delay(100);

  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  //IF WIFI DOESNT CONNECT CODE WONT GO PAST THIS BLOCK
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
  }

  Serial.print("Connected to ");
  Serial.println(ssid);

  //PRINT IP ADDRESS ASSIGNED TO ESP
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {

  //CREATING URL PATH - DONT TOUCH THIS
  String url = "/api/v2/devices/";
  url += devID;
  url += "/sensors/";
  url += sensorID;


  if (WiFi.status() == WL_CONNECTED) { //CHECK WIFI CONNECTION STATUS

    WiFiClientSecure client; //CONNECTION FOR HTTPS
    client.setCACert(root_cert); //WAZIUP.IO CERTIFICATE FOR HTTPS
    HTTPClient http;    //DECLARE OBJECT OF CLASS HTTPClient

    http.begin(client , host , http_port , url);   //SPECIFY REQUEST DESTINATION
    int httpCode = http.GET(); //REQUESTING FOR RESOURCE FROM SERVER

    // HTTP CODE WILL BE NEGATIVE IF THERE'S AN ERROR
    if (httpCode > 0) {
      // HTTP HEADER SENT AND SERVER RESPONSE HEADER HANDLED
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // FILE FOUND ON SERVER
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");


        //----UNCOMMENT EITHER 1. OR 2. DEPENDING ON YOUR USE CASE----
        /*
          //1. SUBSTRINGING TO GET THE NEEDED VALUE IN THE "SENSOR" PAYLOAD
          int strt_p = payload.lastIndexOf("value") + 7;
          int end_p = payload.indexOf("name") - 3;
          String control = payload.substring(strt_p, end_p);
          Serial.println(control);
        */

        /*
          //2. SUBSTRINGING TO GET THE NEEDED VALUE IN THE "ACTUATOR OR RELAY" PAYLOAD
          int strt_p = payload.lastIndexOf("value") + 7;
          int end_p = payload.indexOf("name") - 2;
          String control = payload.substring(strt_p, end_p);
          Serial.println(control);

          //UNCOMMENT THIS PART TO USE A RELAY TO PERFORM AN ACTION BASED ON THE VALUE
          //MAKE SURE TO DECLARE relay_pin and set it as an OUTPUT
          if(control.equals("1")){ //RELAY ON IF VALUE IS 1
           digitalWrite(relay_pin, HIGH);
          }else if(control.equals("0")){ //RELAY OFF IF VALUE IS 0
           digitalWrite(relay_pin, LOW);
          }
        */

      }
    } else {
      //IF THE HTTP CODE WAS A NEGATIVE
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();  //CLOSING HTTP CONNECTION

  } else {
    Serial.println("WiFi Connection Fail"); //IF ESP CAN'T CONNECTED TO WIFI
  }

  delay(30000);  //REQUESTING SENSOR DATA EVERY 30 SECONDS
}

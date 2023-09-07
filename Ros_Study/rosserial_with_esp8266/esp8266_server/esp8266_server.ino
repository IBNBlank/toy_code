#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "Rain&Young";
const char* password = "pipijiadewang233";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output_State = "off";


void setup()
{
    Serial.begin(115200);

    // Initialize the output variables as outputs
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    // Connect to Wi-Fi network with SSID and password
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected.");

    // Print local IP address and start web server
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
}


void loop()
{
    WiFiClient client = server.available();     // Listen for incoming clients

    if (client)                                 // If a new client connects,
    {
        Serial.println("New Client.");          // print a message out in the serial port
        String currentLine = "";                // make a String to hold incoming data from the client

        while (client.connected())              // loop while the client's connected
        {
            if (client.available())             // if there's bytes to read from the client,
            {
                char c = client.read();         // read a byte, then
                Serial.write(c);                // print it out the serial monitor
                header += c;
                if (c == '\n')                  // if the byte is a newline character
                {
                    // if the current line is blank, you got two newline characters in a row.
                    // that's the end of the client HTTP request, so send a response:
                    if (currentLine.length() == 0)
                    {
                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                        // and a content-type so the client knows what's coming, then a blank line:
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        // turns the GPIOs on and off
                        if (header.indexOf("GET /LED/on") >= 0)
                        {
                            Serial.println("LED on");
                            output_State = "on";
                            digitalWrite(LED_BUILTIN, LOW);
                        }
                        else if (header.indexOf("GET /LED/off") >= 0)
                        {
                            Serial.println("LED off");
                            output_State = "off";
                            digitalWrite(LED_BUILTIN, HIGH);
                        }


                        // Display the HTML web page
                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                        client.println("<link rel=\"icon\" href=\"data:,\">");
                        // CSS to style the on/off buttons
                        // Feel free to change the background-color and font-size attributes to fit your preferences
                        client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
                        client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
                        client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                        client.println(".button2 {background-color: #77878A;}</style></head>");

                        // Web Page Heading
                        client.println("<body><h1>ESP8266 Web Server</h1>");

                        // Display current state, and ON/OFF buttons for :ED
                        client.println("<p>LED - State " + output_State + "</p>");
                        // If the output_State is off, it displays the ON button
                        if (output_State == "off")
                        {
                            client.println("<p><a href=\"/LED/on\"><button class=\"button\">ON</button></a></p>");
                        }
                        else
                        {
                            client.println("<p><a href=\"/LED/off\"><button class=\"button button2\">OFF</button></a></p>");
                        }

                        client.println("</body></html>");

                        // The HTTP response ends with another blank line
                        client.println();
                        // Break out of the while loop
                        break;
                    }
                    else
                    {
                        // if you got a newline, then clear currentLine
                        currentLine = "";
                    }
                }
                else if (c != '\r')
                {
                    // if you got anything else but a carriage return character,
                    currentLine += c;      // add it to the end of the currentLine
                }
            }
        }

        // Clear the header variable
        header = "";
        // Close the connection
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
    }
}

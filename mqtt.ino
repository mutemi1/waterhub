//*****************MQTT VARIABLES*****************************************************//
// Select your modem:
#define TINY_GSM_MODEM_SIM800

// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial

// Set serial for AT commands (to the module)
#define SerialAT Serial2

// Define the serial console for debug prints, if needed
#define TINY_GSM_DEBUG SerialMon

// Define how you're planning to connect to the internet.
#define TINY_GSM_USE_GPRS true

// set GSM PIN, if any
#define GSM_PIN ""

// Your GPRS credentials, if any
const char apn[] = "telkom";
const char gprsUser[] = "";
const char gprsPass[] = "";

// MQTT details
const char *broker = "176.58.120.70";

const char *topicGPS = "test/gps";
const char *topicInit = "test/init";
const char *topicSpeed = "test/speed";
const char *topicWaterData = "test/waterdata";

#include <TinyGsmClient.h>
#include <PubSubClient.h>

TinyGsm modem(SerialAT);
TinyGsmClient client(modem);
PubSubClient mqtt(client);

uint8_t net_status = 0;
uint32_t lastReconnectAttempt = 0;
void (*resetFunc)(void) = 0;
char mqtt_buffer[256];
int mqtt_buffer_pos;
char imei[20];
char mqttString[256];

char delim[2] = "%";
char validmsg[2] = "#";
char *token;
#define TOKEN_ARR_SIZE 10
char *token_arr[TOKEN_ARR_SIZE]; // array to store tokens.
int tokencount = 0;              // gets the number of token values received

////////////////////TRANSACTION TYPES///////////////////////////////
char trxcheckbal[20] = "checkbalance";
char trxcardtopup[20] = "cardtopup";
char trxmpesapaymode[20] = "mpesapay";
char get_trxcheckbal() { return trxcheckbal; }
char get_trxcardtopup() { return trxcardtopup; }
char get_trxmpesapaymode() { return trxmpesapaymode; }
////////////////////TRANSACTION TYPES///////////////////////////////

// Pull the reset pin of the GSM module down for 200ms then high to rest the GSM module
void reset_gsm()
{
  Serial.println("RESETTING GSM...");
  digitalWrite(gsm_reset, LOW);
  delay(200);
  digitalWrite(gsm_reset, HIGH);
}

// Get the IMEI number of the GSM module
void get_gsm_imei()
{
  Serial2.println("AT+GSN\r\n");
  delay(200);
  char ch;
  int i;
  i = 0;
  while (Serial2.available())
  {
    ch = Serial2.read();
    if (ch == '\r' || ch == '\n' || ch == 'O' || ch == 'K')
      ;
    else
    {
      imei[i] = ch;
      i++;
    }
  }
  Serial.write("IMEI: ");
  Serial.println(imei);
}

void clear_mqtt_buffer()
{
  for (mqtt_buffer_pos = 0; mqtt_buffer_pos < 256; mqtt_buffer_pos++)
  {
    mqtt_buffer[mqtt_buffer_pos] = 0x00;
  }
  mqtt_buffer_pos = 0;
}

void mqttCallback(char *topic, byte *payload, unsigned int len)
{
  mqtt_buffer_pos = 0;
  while (len)
  {
    len--;
    mqtt_buffer[mqtt_buffer_pos] = (char)*payload;
    payload++;
    mqtt_buffer_pos++;
  }

  SerialMon.print("Message arrived [");
  SerialMon.print(topic);
  SerialMon.print("]: ");
  SerialMon.write(mqtt_buffer);
  SerialMon.println();

  if (String(topic) == topicSpeed)
  {
    if (strstr(mqtt_buffer, validmsg))
    {
      char *msg = strtok(mqtt_buffer, validmsg);
      if (tokencount == 0)
      {
        token = strtok(msg, delim);
        while (token != NULL)
        {
          token_arr[tokencount] = token;
          tokencount++;
          token = strtok(NULL, delim);
        }
        for (int i = 0; i < tokencount; i++)
        {
          Serial.println("Token " + String(i) + " is " + token_arr[i]);
        }
      }
      // tokencount = 0;
      String trx_type = String(token_arr[0]);
      if (trx_type == String(trxcheckbal))
      {
        // checkbalancecallback();
      }
      if (trx_type == String(trxcardtopup))
      {
        // cardtopupcallback();
      }
      if (trx_type == String(trxmpesapaymode))
      {
        String trxstatus = String(token_arr[3]);
        // if waiting for stk push status first
        if (get_stkwaiting() && !get_mpesatrx_waiting())
        {
          if (trxstatus == '1')
          {
            set_stksuccess(true);
          }
          else
          {
            set_stksuccess(false);
          }
          set_stkwaiting(false);
          set_mpesatrx_waiting(true);
        }
        // if waiting for mpesa transaction status
        if (get_mpesatrx_waiting())
        {
          if (trxstatus == '1')
          {
            set_mpesatrx_success(true);
          }
          else
          {
            set_mpesatrx_success(false);
          }
          set_mpesatrx_waiting(false);
        }
      }
    }
  }
}

void mqtt_init()
{
  pinMode(gsm_reset, OUTPUT);
  // Set Debug console baud rate
  SerialMon.begin(115200);
  // Set GSM module baud rate
  SerialAT.begin(115200);
  // Reset GSM
  SerialMon.println("Initializing modem...");
  // Reset the GSM first
  reset_gsm();

#if TINY_GSM_USE_GPRS && defined TINY_GSM_MODEM_XBEE
  // The XBee must run the gprsConnect function BEFORE waiting for network!
  modem.gprsConnect(apn, gprsUser, gprsPass);
#endif

  SerialMon.print("Waiting for network...");
  if (!modem.waitForNetwork())
  {
    SerialMon.println(" fail");
    reset_gsm();
    return;
  }
  SerialMon.println(" success");
  if (modem.isNetworkConnected())
  {
    SerialMon.println("Network connected");
    GSM_Net_Connect_Buzz();
  }

#if TINY_GSM_USE_GPRS
  // GPRS connection parameters are usually set after network registration
  SerialMon.print(F("Connecting to "));
  SerialMon.print(apn);
  if (!modem.gprsConnect(apn, gprsUser, gprsPass))
  {
    SerialMon.println(" fail");
    return;
  }
  SerialMon.println(" success");

  if (modem.isGprsConnected())
  {
    SerialMon.println("GPRS connected");
  }
#endif
  get_gsm_imei();
  // MQTT Broker and Callback Setup
  mqtt.setServer(broker, 1883);
  mqtt.setCallback(mqttCallback);
}

boolean mqttConnect()
{
  SerialMon.print("Connecting to ");
  SerialMon.print(broker);

  // Connect to MQTT Broker
  boolean status = mqtt.connect(topicInit);

  // Or, if you want to authenticate MQTT:
  // boolean status = mqtt.connect("GsmClientName", "mqtt_user", "mqtt_pass");

  if (status == false)
  {
    SerialMon.println(" fail");
    reset_gsm();
    resetFunc();
    return false;
  }
  Mqtt_Broker_Connect_Buzz();
  SerialMon.println(" success");
  mqtt.publish(topicInit, "GsmClientTest started");
  mqtt.subscribe(topicSpeed);
  return mqtt.connected();
}

void mqtt_check()
{

  // Make sure we're still registered on the network
  if (!modem.isNetworkConnected())
  {
    SerialMon.println("Network disconnected");
    if (!modem.waitForNetwork(3000L, true))
    { // Try reconnecting to the network after 3 seconds
      SerialMon.println(" fail");
      net_status++;

      if (net_status == 5)
      { // if the network fails after 5 reconnect attempts reset the gsm
        net_status = 0;
        reset_gsm();
      }

      return;
    }

    if (modem.isNetworkConnected())
    {
      SerialMon.println("Network re-connected");
      GSM_Net_Connect_Buzz();
      net_status = 0;
    }

#if TINY_GSM_USE_GPRS
    // and make sure GPRS/EPS is still connected
    if (!modem.isGprsConnected())
    {
      SerialMon.println("GPRS disconnected!");
      SerialMon.print(F("Connecting to "));
      SerialMon.print(apn);
      if (!modem.gprsConnect(apn, gprsUser, gprsPass))
      {
        SerialMon.println(" fail");
        reset_gsm();
        return;
      }
      if (modem.isGprsConnected())
      {
        SerialMon.println("GPRS reconnected");
      }
    }
#endif
  }

  if (!mqtt.connected())
  {
    SerialMon.println("=== MQTT NOT CONNECTED ===");
    // Reconnect every 10 seconds
    uint32_t t = millis();
    if (t - lastReconnectAttempt > 10000L)
    {
      lastReconnectAttempt = t;
      if (mqttConnect())
      {
        lastReconnectAttempt = 0;
      }
    }
    return;
  }

  mqtt.loop();
}

void tagbalancequery()
{
  strcpy(mqttString, trxcheckbal);
  strcat(mqttString, delim);
  strcat(mqttString, imei);
  strcat(mqttString, delim);
  strcat(mqttString, get_cardid().c_str());
  Serial.println("Sending to APi: " + String(mqttString));
  mqtt.publish(topicWaterData, mqttString);
}

// void mpesatopuprequest() {
//   strcpy(mqttString,trxcardtopup);
//   strcat(mqttString,delim);
//   strcat(mqttString,imei);
//   strcat(mqttString,delim);
//   strcat(mqttString,cardidval.c_str());
//   strcat(mqttString,delim);
//   strcat(mqttString,mpesanumber.c_str());
//   strcat(mqttString,delim);
//   strcat(mqttString,Mpesaamt);
//   Serial.println("Sending to APi: "+String(mqttString));
//   mqtt.publish(topicWaterData , mqttString);
// }

void mpesapayrequest()
{
  strcpy(mqttString, trxmpesapaymode);
  strcat(mqttString, delim);
  strcat(mqttString, imei);
  strcat(mqttString, delim);
  strcat(mqttString, "N/A"); // no card needed
  strcat(mqttString, delim);
  strcat(mqttString, get_mpesa_no());
  strcat(mqttString, delim);
  strcat(mqttString, get_mpesa_amt());
  Serial.println("Sending to APi: " + String(mqttString));
  // mqtt.publish(topicWaterData , mqttString);
}
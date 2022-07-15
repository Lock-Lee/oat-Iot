void onMsghandler(char *topic, uint8_t *msg, unsigned int msglen)
{
    String top = (String)topic;
    msg[msglen] = '\0';
    String message = (String)(char *)msg;
    Serial.print(top);
    Serial.print(" ");
    Serial.println(message);
}

void onConnected(char *attribute, uint8_t *msg, unsigned int msglen)
{
    Serial.println("Connected to NETPIE...");

    microgear.setAlias(ALIAS);
    microgear.subscribe("/Oatiot/+");
}
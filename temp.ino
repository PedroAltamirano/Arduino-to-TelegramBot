String getTemp(void){
  int ground_humidity_value = map(analogRead(2), 0, 1023, 100, 0);
  Serial.print("Temp: ");
  Serial.println(ground_humidity_value);
  
  // check if any reads failed
//  if (isnan(humi) || isnan(tempC) || isnan(tempF)) {
//    Serial.println("Failed to read from DHT sensor!");
//    return "Failed to read from DHT sensor!";
//  } else {
//    Serial.print("Humidity: ");
//    Serial.print(humi);
//    Serial.print("%");
//    
//    Serial.print("  |  "); 
//    
//    Serial.print("Temperature: ");
//    Serial.print(tempC);
//    Serial.print("°C");
//    Serial.print(" ~ ");
//    Serial.print(tempF);
//    Serial.println("°F");
//
//    String msg = "Data obtained: \n";
//    msg += "Humidity" + String(humi) + "% \n";
//    msg += "Temperature" + String(tempC) + "°C ~ " + String(tempF) + "°F \n";
//    msg += "Data obtained from Pedro.";
//    return msg;
//  }

  return "Temp reading";
}

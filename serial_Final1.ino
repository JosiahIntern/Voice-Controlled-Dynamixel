#include <DynamixelWorkbench.h>

#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif   

#define BAUDRATE  1000000 //AX-12A baudrate is 1000000 
#define DXL_ID    1       // ID for the AX-12A is 1 can be found through the dynamixel wizard

DynamixelWorkbench dxl_wb; //We're using the Dynamixel Workbench library 

int datafromUser = 0;     //This is the variable that we will store the data from python in 
uint8_t dxl_id = DXL_ID;  // This defines the the Dynamixel ID as a unsigned integer with a width of 8 bits 
uint16_t model_number = 12; //This can be found through the dynamixel wizard 

void setup()

{
  Serial.begin(1000000); //This is the way to intialize our serial communication port 

  const char *log;
  bool result = false;

  result = dxl_wb.init(DEVICE_NAME, BAUDRATE, &log); //This initalizes the Dynamixel connection
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to init");
  }
  else
  {
    Serial.print("Succeeded to init : ");
    Serial.println(BAUDRATE);  
  }

  result = dxl_wb.ping(dxl_id, &model_number, &log); //This function allows the user to check the connection for the Dynamixels 
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  else                                              //If sucessful the id and model number will be showed in the serial monitor 
  {
    Serial.println("Succeeded to ping");
    Serial.print("id : ");
    Serial.print(dxl_id);
    Serial.print(" model_number : ");
    Serial.println(model_number);
  }

  while (!Serial);                               

  Serial.println("Input 1 to Turn LED on and 2 to off");

}

void loop() {

  
  if (Serial.available())   //This checks to see if theres any information(characters/data) coming through the serial port 

  {

    datafromUser=Serial.read();  //This reads the data that is coming from the serial port and saves it in the variable

    if (datafromUser == '1')     //If the code reads a 1 from the serial port it turns on the Dynamixel

    {

 
      dxl_wb.goalPosition(dxl_id, (int32_t)0);    //This sets the position of the Dynamixel to 0
      delay(3000);
      Serial.println("Set to position 0");

      dxl_wb.goalPosition(dxl_id, (int32_t)550);  //This sets the position of the Dynamixel to 550
      delay(3000);
      Serial.println("Set to position 550");

      Serial.println("Command completed LED turned ON");

    }


  }

}

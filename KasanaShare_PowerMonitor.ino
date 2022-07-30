// Author: Aaron Masuba
// Rights reserved to @KasanaShare and Team


// Definition of Voltage Sensor parameters and variables.
#define ANALOG_IN_PIN A3 // Analog input pin for voltage
float adc_voltage = 0.0; // Analog to Digital Converter [ADC] float
float in_voltage = 0.0;  // Input Voltage float
float R1 = 30000.0; // Resistor, R1 divider float in ohms
float R2 = 7500.0;  // Resistor, R2 divider float in ohms
float ref_voltage = 5.0; // Reference voltage float
int adc_value = 0; // Analog to Digital Converter [ADC] Integer value


// Definition of current Sensor ACS712 30A Scale based parameters and variables.
double Vout = 0; // Measured voltage variable
double Current = 0; // Measured Current Variable
const double scale_factor = 0.066; // Scale Factor for 30A. Note, for 5A = 0.185 and for 20A = 0.1
const double vRef = 5.00; // Reference voltage since no AREF is connected
const double resConvert = 1024; // Possible values based on Arduino 10-bit Analog to Digital Converter [ADC]
double resADC = vRef/resConvert; // Analog to Digital Converter [ADC] Resolution constant
double zeroPoint = vRef/2; // Zero point constant which is half of Reference voltage

// Definition of Power parameters and Variables
double Power = 0; // Computed Power variable

void setup() // We Setup Serial Monitor
  { 
    Serial.begin(9600);
    Serial.println("\n ***KasanaShare Power Monitoring Platform*** \n");
  }

void loop()
  {
   // Determination of Voltage Sensor Analog inputs.
    adc_value = analogRead(ANALOG_IN_PIN); // Read volatge analog input
    adc_voltage  = (adc_value * ref_voltage) / 1024.0; // Determine voltage at ADC input
    in_voltage = adc_voltage / (R2/(R1+R2)); // Calculate voltage at divider input
   // Printing the Input Voltage out
    Serial.print("Input Voltage = "); // Print line for Input Voltage results on Serial monitor
    Serial.print(in_voltage, 2); // Correct to 2 decimal places.
    delay(500); // Short delay
  

   // Determination of Current Sensor Analog inputs.
   for(int i = 0; i < 1000; i++) // Read Vout 1000 Times for precision
    {
      Vout = (Vout + (resADC * analogRead(A2))); 
      delay(1);
    }    
   Vout = Vout /1000; // Get Vout in mv
   Current = (Vout - zeroPoint)/ scale_factor; // Convert Vout into Current using Scale Factor
   // Print Vout and Current to two Current = ");
   /*Serial.print("\t\t Vout = ");           
    Serial.print(Vout,2); 
    Serial.print(" Volts"); */                            
    Serial.print("\t Current = ");                  
    Serial.print(Current,2);
    Serial.print(" Amps");                             
    delay(500); 

    // Determination of Power Computations [eliminating time aspect] [P = I * V]
    Power = (in_voltage * Current); //Power computation
    Serial.print("\t\t Power = ");
	  Serial.print(Power, 2);
	  Serial.println(" VA");
    delay(500);
  }
 
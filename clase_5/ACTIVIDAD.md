# Actividad en Clases: Captura de Información mediante Arduino y la Librería SD

En esta actividad trabajamos con un sensor analógico (como un potenciómetro o un sensor TMP36) conectado a un microcontrolador Arduino. El objetivo es capturar datos analógicos, convertirlos en valores legibles y almacenarlos en una tarjeta microSD utilizando la librería `SD.h`.

## Contenidos y pasos:

1. **Protocolos de comunicación**  
   Primero distinguimos entre los protocolos de comunicación **I2C (o IIC)** y **SPI**. En este caso utilizamos **SPI**, que es el requerido para la comunicación con tarjetas microSD.

2. **Formato de la tarjeta microSD**  
   La tarjeta debe estar formateada en **FAT32**. Creamos un archivo de texto plano llamado `datalog.txt` que será utilizado para almacenar las lecturas de los sensores.

3. **Lectura de datos analógicos**  
   Conectamos un potenciómetro (o en este caso, un sensor TMP36) al pin **A0 (Analog 0)** de Arduino. La lectura se realiza con `analogRead()`, y posteriormente se mapea con la función `map()` desde un rango de **0–1023** a un rango más acotado, como **0–100**.

4. **Esquema de conexión del módulo microSD**  
   Según el esquema de conexión estándar SPI, los pines del módulo microSD deben conectarse de la siguiente manera:

   | Módulo microSD | Arduino UNO (SPI) |
   |----------------|-------------------|
   | **VCC**        | 5V                |
   | **GND**        | GND               |
   | **MOSI**       | Pin 11            |
   | **MISO**       | Pin 12            |
   | **SCK**        | Pin 13            |
   | **CS**         | Pin 10 (configurable) |

   > En una comunicación SPI:  
   > - **VCC**: Alimentación 5V (generalmente)  
   > - **GND**: Tierra  
   > - **MOSI**: Master Output Slave Input  
   > - **MISO**: Master Input Slave Output  
   > - **SCK**: System Clock  
   > - **CS**: Chip Select  

   ### 🖼 Esquemático de conexión  
   ![Esquemático de conexión con TMP36 y módulo microSD](./tmp35_SD.png)

5. **Guardado de datos**  
   En el archivo `datalog.txt`, se registran los valores leídos y convertidos por el Arduino. Se abre el archivo en modo `FILE_WRITE`, se escriben los datos y luego se cierra el archivo para asegurar que la información se guarde correctamente.

## Recursos
- Librería: [`SD.h`](https://www.arduino.cc/en/Reference/SD)
- Placa recomendada: Arduino UNO
- Editor sugerido: Arduino IDE

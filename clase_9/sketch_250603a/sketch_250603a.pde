import processing.serial.*;

Serial myPort;
String dato;
int opacidad;        // Valor entre 0–100 recibido desde Arduino
PImage img;          // Imagen a mostrar

void setup() {
  size(1024, 768);
  // fullScreen(); //en caso de usar pantalla completa
  println(Serial.list()); // Muestra los puertos disponibles
  myPort = new Serial(this, Serial.list()[0], 9600); // Ajustar índice según tu equipo
  myPort.bufferUntil('\n');
  img = loadImage("foto.jpg"); // Imagen colocada en la carpeta del sketch
}

void draw() {
  background(255);
  
  // Aplicar opacidad (0-255)
  tint(255, opacidad * 2.55);
  image(img, 0, 0, width, height);
  
  // Mostrar datos en pantalla
  fill(0);
  text("Opacidad: " + opacidad + " / 100", 20, height - 20);
}

void serialEvent(Serial puerto) {
  dato = puerto.readStringUntil('\n');
  if (dato != null) {
    dato = trim(dato);
    if (dato.length() > 0) {
      opacidad = int(dato);
      println("Dato recibido: " + opacidad);
    }
  }
}

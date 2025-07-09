import java.util.HashMap;

HashMap<Character, String> instrucciones;

void setup() {
  size(800, 400);
  background(0);
  fill(255);
  textSize(20);
  
  instrucciones = new HashMap<Character, String>();
  
  Table tabla = loadTable("comandos.csv", "csv");
  
  for (TableRow row : tabla.rows()) {
    String teclaStr = row.getString(0);
    String instruccion = row.getString(1);
    
    if (teclaStr != null && teclaStr.length() == 1) {
      char tecla = teclaStr.charAt(0);
      instrucciones.put(tecla, instruccion);
    }
  }
  
  text("Presiona una tecla para ejecutar una instrucción...", 20, 50);
}

void draw() {
  // Nada
}

void keyPressed() {
  background(0);
  if (instrucciones.containsKey(key)) {
    String instruccion = instrucciones.get(key);
    fill(0, 255, 0);
    text("Instrucción para '" + key + "': " + instruccion, 20, 100);
  } else {
    fill(255, 0, 0);
    text("No hay instrucción para '" + key + "'", 20, 100);
  }
}

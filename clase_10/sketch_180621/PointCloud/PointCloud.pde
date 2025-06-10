// Modificado por Bruno Perelli S.
// Daniel Shiffman
// Kinect Point Cloud example

// https://github.com/shiffman/OpenKinect-for-Processing
// http://shiffman.net/p5/kinect/

import org.openkinect.freenect.*;
import org.openkinect.processing.*;
import codeanticode.syphon.*;

// Kinect Library object
Kinect kinect;
KinectTracker tracker;
// Objeto de Servidor Syphon
SyphonServer server;

// Angle for rotation
float a = 0;
float deg;

// We'll use a lookup table so that we don't have to repeat the math over and over
float[] depthLookUp = new float[2048];

void setup() {
  // Rendering in P3D
  size(800, 600, P3D); //size (ancho o X, alto o Y, Motor P3D);
  server = new SyphonServer(this, "Processing Syphon");
  //fullScreen(P3D);
  kinect = new Kinect(this);
  kinect.initDepth();// inicia la cámara de profundidad
  
  deg = kinect.getTilt();
  // kinect.tilt(deg);

  // Lookup table for all possible depth values (0 - 2047)
  for (int i = 0; i < depthLookUp.length; i++) {
    depthLookUp[i] = rawDepthToMeters(i);
  }
}

void draw() {
  //modificar el color de fondo
  background(0); //RGB red, green, blue
  // Get the raw depth as array of integers
  int[] depth = kinect.getRawDepth();

  // We're just going to calculate and draw every 4th pixel (equivalent of 160x120)
  int skip = 2;// establece la concentración de puntos expresados en cuartos 4, 16, etc.

  // Translate and rotate
  translate(width/2, height/2, 100); //esta ultima modifiza tamaño o zoom.
  //rotateY(a);//acciona la rotacion

  for (int x = 0; x < kinect.width; x += skip) {
    for (int y = 0; y < kinect.height; y += skip) {
      int offset = x + y*kinect.width;

      // Convert kinect data to world xyz coordinate
      int rawDepth = depth[offset];
      PVector v = depthToWorld(x, y, rawDepth);

      stroke(255);
      pushMatrix();
      // Scale up by 200
      float factor = 200;
      translate(v.x*factor, v.y*factor, v.z*factor/4);
      // Draw a point
      point(0, 0);
      popMatrix();
   
    }
  }

  // Rotate
  a += 0.015f;//como no se usa queda en 0
  
  server.sendScreen(); //esta linea publica o envia la pantalla a otros clientes syphon
}

// These functions come from: http://graphics.stanford.edu/~mdfisher/Kinect.html
float rawDepthToMeters(int depthValue) {
  if (depthValue < 2047) {
    return (float)(1.0 / ((double)(depthValue) * -0.0030711016 + 3.3309495161));
  }
  return 0.0f;
}

PVector depthToWorld(int x, int y, int depthValue) {

  final double fx_d = 1.0 / 5.9421434211923247e+02;
  final double fy_d = 1.0 / 5.9104053696870778e+02;
  final double cx_d = 3.3930780975300314e+02;
  final double cy_d = 2.4273913761751615e+02;

  PVector result = new PVector();
  double depth =  depthLookUp[depthValue];//rawDepthToMeters(depthValue);
  result.x = (float)((x - cx_d) * depth * fx_d);
  result.y = (float)((y - cy_d) * depth * fy_d);
  result.z = (float)(depth);
  return result;
}
//la función de teclas para ángulo de cámara
void keyPressed() {
  if (keyCode == UP) {
      deg++;
    } else if (keyCode == DOWN) {
      deg--;
    }
    deg = constrain(deg, 0, 30);
    kinect.setTilt(deg);
}

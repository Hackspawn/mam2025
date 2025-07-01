# Clase 13 – Cuatro Métodos con Sonic Pi

Este repositorio contiene ejemplos prácticos para trabajar con **Sonic Pi** utilizando cuatro métodos fundamentales:

1. **Uso de samples locales**
2. **Conversión de frecuencias (Hertz) a notas MIDI**
3. **Comunicación en tiempo real mediante OSC (Open Sound Control)**
4. **Lectura y uso de archivos CSV para disparar samples**

Estos métodos permiten combinar programación musical, interacción en tiempo real y estructuras de datos para crear obras interactivas y generativas.

---

## 📁 Estructura del Repositorio

├── samples/ # Carpeta con archivos de audio .wav
│ └── sonido1.wav
├── data/ # Carpeta con archivo CSV de control
│ └── sonidos.csv
├── 1_sample.rb # Reproducción de samples
├── 2_hz_to_midi.rb # Conversión de Hz a nota MIDI
├── 3_osc_touchosc.rb # Control mediante mensajes OSC
└── 4_csv_player.rb # Lectura de samples desde archivo CSV


---

## 🧱 Requisitos

Para poder utilizar los ejemplos incluidos, asegúrate de contar con:

- [Sonic Pi](https://sonic-pi.net/) (versión 3.2 o superior)
- Ruby instalado en tu sistema (para la lectura avanzada de rutas y CSV, si usas fuera de Sonic Pi)
- [TouchOSC](https://hexler.net/touchosc) o app OSC similar (opcional)
- Archivos `.wav` ubicados correctamente en la carpeta `/samples`
- Archivo CSV llamado `sonidos.csv` ubicado en `/data`

---

## 🧪 Ejercicios Incluidos

### `1_sample.rb` – Uso de Samples de Audio

- Reproduce un archivo de audio `.wav` desde una carpeta local.
- Ajusta el tempo usando `use_bpm`.

```ruby
use_bpm 90
sample "/home/usuario/Clase13-SonicPi/samples/sonido1.wav"
sleep 1

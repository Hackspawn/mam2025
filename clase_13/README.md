# Clase 13 – Cuatro Métodos con Sonic Pi

Este repositorio contiene ejemplos prácticos para trabajar con **Sonic Pi** utilizando cuatro métodos fundamentales:

1. **Uso de samples locales**
2. **Conversión de frecuencias (Hertz) a notas MIDI**
3. **Comunicación en tiempo real mediante OSC (Open Sound Control)**
4. **Lectura y uso de archivos CSV para disparar samples**

Estos métodos permiten combinar programación musical, interacción en tiempo real y estructuras de datos para crear obras interactivas y generativas.

---

## 📁 Estructura del Repositorio

| Carpeta / Archivo         | Descripción                                               |
|---------------------------|-----------------------------------------------------------|
| `samples/`                | Carpeta con archivos de audio `.wav`                      |
| `samples/sonido1.wav`     | Sample de ejemplo para reproducción                       |
| `data/`                   | Carpeta con archivo CSV de control                        |
| `data/sonidos.csv`        | CSV con rutas de samples y valores de BPM                 |
| `1_sample.rb`             | Script básico para reproducir un sample con `use_bpm`     |
| `2_hz_to_midi.rb`         | Script para convertir Hz a notas MIDI con envolvente ADSR |
| `3_osc_touchosc.rb`       | Control remoto con mensajes OSC desde TouchOSC            |
| `4_csv_player.rb`         | Reproduce samples a partir de datos contenidos en un CSV  |

---

## 🧱 Requisitos

- [Sonic Pi](https://sonic-pi.net/) (v3.2 o superior)
- Ruby instalado en el sistema (si se usa fuera de Sonic Pi)
- [TouchOSC](https://hexler.net/touchosc) (opcional)
- Archivos `.wav` correctamente ubicados en la carpeta `/samples`
- Archivo `sonidos.csv` en la carpeta `/data`

---

## 🧪 Ejercicios Incluidos

### `1_sample.rb` – Uso de Samples de Audio

```ruby
use_bpm 90
sample "/home/usuario/Clase13-SonicPi/samples/sonido1.wav"
sleep 1

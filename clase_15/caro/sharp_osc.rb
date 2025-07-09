use_debug false
use_osc "localhost", 4560

live_loop :sensor do
  use_real_time
  distancia = sync "/osc*/distancia"[0]  # Recibe mensaje OSC

  # Convertimos directamente a nota MIDI
  nota = distancia.clamp(36, 84)  # Aseguramos un rango musical razonable

  puts "→ Reproduciendo nota MIDI: #{nota}"
  use_synth :pluck
  play nota, release: 0.3
end

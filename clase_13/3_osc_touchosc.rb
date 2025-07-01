use_osc "192.168.1.100", 9000  # Reemplazar con la IP del dispositivo

live_loop :controlador do
  use_real_time
  a, b = sync "/osc/slider1"
  play scale(:c4, :minor_pentatonic)[(a * 5).to_i], release: 0.2
end

fcpu = 84e6              # частота процессора
#ftimer = 400e3            # частота отсчета таймера
#ftick = ftimer / 4       # частота тиков для мультипликатора

rpm = 50                # максимальные обороты
npulses = 600*3*4         # количество отсчетов энкодера на оборот

screw_pitch = 2.00       # шаг резьбы ходового винта
stepper_pulses = 200*2*3 # количество шагов на оборот винта

frot = rpm / 60
fpulse = frot * npulses

#multiplicator = 32
#nticks = ftick / fpulse / multiplicator  # количество тиков между выходными импульсами мультипликатора

#print("Ftick = %i" % ftick)
#print("Nticks = %0.2f" % nticks)

max_thread_pitch = npulses * screw_pitch / stepper_pulses

print("Max pitch = %0.2f" % max_thread_pitch)

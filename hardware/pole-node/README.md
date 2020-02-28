## Datasheets

- APA3211: [datasheet](https://www.diodes.com/assets/Datasheets/AP3211.pdf), [application notes](https://www.diodes.com/assets/Part-Support-Files/AP3211/6434133.pdf)

## Calculations

### Voltage regulator

- Feedback voltage is 0.81V. Use [this voltage divider calculator](http://www.ti.com/download/kbase/volt/volt_div3.htm). For E96, this yields 11500 and 2210 Ohms, which produces 5.02v.
- Inductor value: `L1 = 5V * (12V - 5V) / (1.4MHz * 12V * 1.5A * .26) = 5.3uH -> 5.6 uH`
- Peak inductor current: `1.5A + ((12V - 5V) * 5V) / (2 * 1.4MHz * 12V * 5.6uH) = 1.69A`
- Inductor current rating is `1.5 * 1.69A = 2.5A`
- Input ripple with 10uF cap: `1.5A / (1.4Mhz * 10uF) * (5V / 12V) * (1 - (5V / 12V)) = .026V`

### RS485 termination

- [Application note](http://www.ti.com/lit/an/snla034b/snla034b.pdf)
- AC termination should yield clean signal without significantly increasing power consumption
- Assuming 40' max cable length:
- `C<sub>T <= (40ft * 2 * 1.7ns/ft) / 100 Ohm = 1.36 nF`
- This yields an RC time constant of `136 ns`. At `800 kHz`, the signal period is `1.25 us`.

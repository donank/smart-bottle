<p align="center">
  <img src="https://github.com/donank/smart-bottle/blob/main/logo.svg" width="150" height="200"/>
</p>

# Ọ̀ṣun: A Smart Water Bottle

A smart device (bottle) that helps the user decide whether the water in the bottle is fit for drinking in real time. The system consists of several electrochemical sensors interfaced to a Raspberry Pi through an Analog to Digitial converter. The designed algorithm collates the sensor data and produces an optimal result based on specified hard-coded strategy. The result is displayed on a 16 X 2 LCD device in a user friendly manner.

## Schematic Diagram
<p align="center">
  <img src="https://raw.githubusercontent.com/donank/smart-bottle/51891a3bb961518fbd0d75c031baf2d21b2ab916/schematic.svg" />
</p>


## Threshold Values 

| Parameter  | Units | Expected Range |
| ------------- | ------------- | ------------- |
| Conductivity  | µs/cm  | 500-1000  |
| Turbidity  | NTU | 0-5  |
| pH  | PH  | 6.5-8.5 |

## References
[1] World Health Organization Guidelines for drinking-water quality, fourth edition, 2011

[2] Y.J. Yang, R.C Haught and J.A Goodrich, Real-time contaminant detection and classification in a drinking water pipe using conventional water quality sensors: Techniques and experimental results, in Journal of Environmental Management, 2009

## Sensors to explore

[1] https://phys.org/news/2016-12-world-solid-state-multi-ion-sensor-internet.html

[2] https://pubs.acs.org/doi/full/10.1021/acs.analchem.7b00843

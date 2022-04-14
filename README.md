<<<<<<< HEAD
=======
<p align="center">
  <img src="https://github.com/donank/smart-bottle/blob/main/logo.png" width="150" height="220"/>
</p>


[![Build Status](https://github.com/donank/smart-bottle/actions/workflows/build.yml/badge.svg)](https://github.com/donank/smart-bottle/actions/)


Winner of RS Grassroots Student Project Fund! https://www.rs-online.com/designspark/the-student-project-fund-2022-winners-announced
# Ọ̀ṣun: A Smart Water Bottle

It is a known fact that availability of drinkable water is critical to human survival and longevity of life. Earth is abundant in water resources but the availability of drinking water resources is marginal in comparison. The situation seems more grim in the poorer regions of the world, where due to lack of proper infrastructure, standard testing code and compliance, the quality of drinking water that is available to the average citizen is poor. People living in such regions also do not have any proper tools or capability to verify the quality of the drinking water. They have to rely on the local municipal body for such information which can be dated or unreliable.  According to WHO, today, more than 144 million people depend on surface drinking water and around 485,000 people die every year due to illnesses related to contaminated water such as Diarrhoea. In addition, waterborne infections affect around 20-50% of the travellers around the world. Thus aligning with the UN sustainable development goals, there is an urgent need for an affordable smart portable device that caters to the real time testing needs for environments with inadequate drinking water and sanitation facilities. 

Ọ̀ṣun is smart device (bottle) that helps the user decide, in real time, whether the water in the bottle is fit for drinking. The system consists of several electrochemical and optoelectronic sensors interfaced with a Raspberry Pi through an Analog to Digital converter. The designed algorithm collates the sensor data and produces an optimal result based on specified hard-coded strategy. The result is displayed on a 16 X 2 LCD device in a user friendly manner. The module can be interfaced with a smart watch or an android application through bluetooth to track daily water consumption and also display other parameters specifying the drinkability of the water in real time. The data collected by the end-user can be used to form a public spatio-temporal database of the drinking water quality of various regions.

This device can be customised and targeted according to the needs of the end customers. People belonging to the poorer parts like Sub-saharan Africa can be provided with LCD embedded bottles which will give them real time results, ideally in the language of their choice. Customers such as travellers and tourists, who carry smarter devices like a smart watch or a mobile device, can be provided with a bluetooth enabled Ọ̀ṣun system that interfaces with their smart devices. The addition of rich user interface such as that of a smartphone or watch helps in delivering more user friendly reports. Such a device can also be used to monitor daily water consumption and help the end users make more conscious decisions about their daily water intake.

## Schematic Diagram
<p align="center">
  <img src="https://raw.githubusercontent.com/donank/smart-bottle/51891a3bb961518fbd0d75c031baf2d21b2ab916/schematic.svg" />
</p>

Note: Sensor units are composed of pre-filters and amplifiers to attenuate noise and deliver adequate results.


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
>>>>>>> efbf0eb637cbf27f73d188c2cbda5974adcc6620

function [sin_gen , t] = SinewaveGen(freq,sampling_frequency)

    period = 1/sampling_frequency;
    Length = 24000;
    t = (0:Length - 1)*period;
    sin_gen = sin(2*pi*freq*t) ;

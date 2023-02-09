function Hd = DSPLab3IIRFilter
%DSPLAB3IIRFILTER Returns a discrete-time filter object.

% MATLAB Code
% Generated by MATLAB(R) 9.9 and Signal Processing Toolbox 8.5.
% Generated on: 18-Nov-2022 19:56:29

% Elliptic Bandstop filter designed using FDESIGN.BANDSTOP.

% All frequency values are in Hz.
Fs = 10000;  % Sampling Frequency

N      = 6;     % Order
Fpass1 = 2000;  % First Passband Frequency
Fpass2 = 4000;  % Second Passband Frequency
Apass  = 1;     % Passband Ripple (dB)
Astop  = 50;    % Stopband Attenuation (dB)

% Construct an FDESIGN object and call its ELLIP method.
h  = fdesign.bandstop('N,Fp1,Fp2,Ap,Ast', N, Fpass1, Fpass2, Apass, ...
                      Astop, Fs);
Hd = design(h, 'ellip', 'FilterStructure', 'df2sos');

% [EOF]
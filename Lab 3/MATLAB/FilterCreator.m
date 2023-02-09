function [num, denum] = FilterCreator(gain,N)
num = zeros (1, N);
denum = zeros (1, N);
denum (1, 1) = 1; 
denum (1, N) = -gain;
num (1, 1) = 1 ;
num (1, N) = 1 - gain;
end

function outp = ReadTXT(filename)
fileID = fopen(filename, 'r');
outp = fscanf(fileID, '%f');
fclose(fileID);
end

